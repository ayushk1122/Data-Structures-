// File course_scheduling.cpp
// Purpose: main program to execute output of statistics 
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Course.h"
#include <array>
#include <algorithm>
#include <iomanip>

using namespace std;

//converts day abbreviations to full day format given an input char
string convertToFullDay(char day) {
	if (day == 'M') return "Monday";
	else if (day == 'T') return "Tuesday";
	else if (day == 'W') return "Wednesday";
	else if (day == 'R') return "Thursday";
	else return "Friday";
}

//finds longest class title, day, and department for formattig purposes 
void getMaxTitleDayLengthDept(vector<Course> courses, int& maxClassTitleLen, int& maxDayLen, int& maxDeptLen) {
	maxClassTitleLen = 0;
	maxDayLen = 0;
	maxDeptLen = 0;
	string classTitle = "Class Title"; //possibility of class title being too short
	for (Course c : courses) {
		if (c.getCourseTitle().length() > maxClassTitleLen) {
			if (c.getCourseTitle().length() < classTitle.length()) {
				maxClassTitleLen = classTitle.length();
			}
			else {
				maxClassTitleLen = c.getCourseTitle().length();
			}
		}

		if (c.getCourseDays().length() > maxDayLen) {
			maxDayLen = c.getCourseDays().length();
		}

		if (c.getDepCode().length() > maxDeptLen) {
			maxDeptLen = c.getDepCode().length();
		}
	}
}

/*helper function for my custom open hours statistic
* calculates the approximate number of hours between the given opening start time and closing time
* returns a string of the level of busyness and the total number of hours
* */
string calcOpenHoursApprox(string openHour, string closeHour, int& totHours) {
	int openHourCol = openHour.find(":");
	int closeHourCol = closeHour.find(":");
	int approxTime = 0;

	if ((openHour.length() > 0) && (closeHour.length() > 0)) { //checks to make sure open and close times are valid
		//conditional block to correctly account for difference in AM and PM times to calc correct total hours
		//uses string indexing to check if time is AM or PM
		if ((openHour[openHour.length() - 2] == 'A') && (closeHour[closeHour.length() - 2] == 'A')) {
			approxTime = stoi(closeHour.substr(0, closeHourCol - 0)) - stoi(openHour.substr(0, openHourCol - 0));
		}
		else if ((openHour[openHour.length() - 2] == 'P') && (closeHour[closeHour.length() - 2] == 'P')) {
			if ((stoi(openHour.substr(0, openHourCol - 0)) == 12) && (stoi(closeHour.substr(0, closeHourCol - 0)) != 12)) {
				approxTime = stoi(closeHour.substr(0, closeHourCol - 0));
			}
			else {
				approxTime = stoi(closeHour.substr(0, closeHourCol - 0)) - stoi(openHour.substr(0, openHourCol - 0));
			}
		}
		else if ((openHour[openHour.length() - 2] == 'A') && (closeHour[closeHour.length() - 2] == 'P')) {
			if (stoi(closeHour.substr(0, closeHourCol - 0)) == 12) {
				approxTime = 12 - stoi(openHour.substr(0, openHourCol - 0));
			}
			else {
				approxTime = (12 - stoi(openHour.substr(0, openHourCol - 0)) + (stoi(closeHour.substr(0, closeHourCol - 0))));
			}
		}
		totHours = approxTime;
	}

	//based on total number of hours returns how busy it is
	if (approxTime == 0) return "Open";
	else if ((approxTime > 0) && (approxTime <= 4)) return "Moderate";
	else return "Busy";


}

/*
*used for room and dept statistics to print correct header based which statistic is being performed
*takes a typeHeader = room or dept, an out stream to print, and max lengths for class title, day, and dept
*returns out stream reference to print to file
*/
ofstream& printHeader(string typeHeader, ofstream& out_str, int maxClassTitleLen, int maxDayLen, int maxDeptLen) {
	if (typeHeader.compare("room") == 0) {
		out_str << left << setw(maxDeptLen) << "Dept" << "  " << "Coursenum" << "  " << setw(maxClassTitleLen) << "Class Title"
		    << "  " << setw(maxDayLen) << "Day" << "  " << "Start Time" << "  " << "End Time" << endl;

		out_str << string(maxDeptLen, '-') << "  " << string(9, '-') << "  " << string(maxClassTitleLen, '-')
			<< "  " << string(maxDayLen, '-') << "  " << string(10, '-') << "  " << string(8, '-') << endl;
	}
	else if (typeHeader.compare("dept") == 0) {
		out_str << left << "Coursenum" << "  " << setw(maxClassTitleLen) << "Class Title" << "  "
			<< setw(maxDayLen) << "Day" << "  " << "Start Time"
			<< "  " << "End Time" << endl;

		out_str << string(9, '-') << "  " << string(maxClassTitleLen, '-') << "  "
			<< string(maxDayLen, '-') << "  " << string(10, '-') << "  " << string(8, '-') << endl;
	}
	return out_str;
}

//used for my custome statistic, prints custom header 
ofstream& printCustomHeader(ofstream& out_str) {
	out_str << left << "|" << setw(9) << "Day" << "  " << setw(8) << "Status" << "  " << 
		setw(11) << "Total Hours" << "  " << setw(14) << "Class Hours" << endl;
	return out_str;
}

/*
* Custom to string function for my custom statistic 
* takes all start and end times for each day of the week and prints to the output file the correct formatting
* and information for each day.
* Uses multiple helper functions to attain necessarry statistics
*/
ofstream& customToString(ofstream& out_str, string mOpenHour, string mCloseHour, string tOpenHour, string tCloseHour,
	string wOpenHour, string wCloseHour, string rOpenHour, string rCloseHour, string fOpenHour, string fCloseHour) {

	int monHours = 0, tueHours = 0, wedHours = 0, thurHours = 0, friHours = 0; //hours are passed by reference to calcOpenHoursApprox method
	
	string daysOfWeek[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
	//array of strings to store how busy the room is on each day, uses calcOpenHoursApprox helper method
	string dayStatus[] = { calcOpenHoursApprox(mOpenHour, mCloseHour, monHours) , calcOpenHoursApprox(tOpenHour, tCloseHour, tueHours),
	calcOpenHoursApprox(wOpenHour, wCloseHour, wedHours), calcOpenHoursApprox(rOpenHour, rCloseHour, thurHours),
	calcOpenHoursApprox(fOpenHour, fCloseHour, friHours) };
	int hoursOfWeek[] = { monHours, tueHours, wedHours, thurHours, friHours };
	//string 2d array to store start and end times as a pair for each day
	string classHours[5][2] = { {mOpenHour, mCloseHour}, {tOpenHour, tCloseHour}, {wOpenHour, wCloseHour},
		{rOpenHour, rCloseHour}, {fOpenHour, fCloseHour} };

	for (int i = 0; i < 5; i++) { //prints statistics for each day of the week 
		out_str << "|" << left << setw(9) << daysOfWeek[i] << "  " << setw(8) << dayStatus[i] << "  " << setw(11) << hoursOfWeek[i] << "  "
			<< classHours[i][0] << " - " << classHours[i][1] << endl;
	}
	out_str << endl;
	return out_str;
}

/*
* Function used for room and custom operations
* Creates a 2d vector to store courses in different rooms seperatly 
* Takes all courses and a empty 2d vector passed by reference 
*/
void createMultiRoomCourseList(vector<Course> courses, vector<vector<Course> >& multiRoomCourses) {
	string startRoom = courses[0].getCourseRoom();
	vector<Course> newCourseRoom;
	for (Course c : courses) { 
		// if room is different, adds vector to multiroom 2d vector, and clears current vector
		if (c.getCourseRoom().compare(startRoom) != 0) { 
			startRoom = c.getCourseRoom();
			multiRoomCourses.push_back(newCourseRoom);
			newCourseRoom.clear();
			newCourseRoom.push_back(c);
		}
		else { //adds course to current vector if of the same room
			newCourseRoom.push_back(c);
			if (c == courses[courses.size() - 1]) { //checks last course to make sure it isn't skipped
				multiRoomCourses.push_back(newCourseRoom);
			}
		}
	}
}

/*
* Essential processing function to perform roomand dept statistics
* takes an empty filtered Courses vector as reference, arg paramaters, list of courses, and type of operation 
*/
void processCourses(vector<Course>& filteredCourses, int argc, char* argv[], vector<Course>& courses, string filterType) {
	ofstream out_str(argv[2]);
	if (!out_str.good()) {
		std::cerr << "Can't open " << argv[4] << " to write.\n";
		exit(1);
	}

	if (argc == 5) {
		//creates filtered course vector dependent on if a room or dept operation is being performed 
		//adds courses that match the inputted command arguments 
		for (Course c : courses) {
			if (filterType.compare("room") == 0) {
				if (c.getCourseRoom().compare(string(argv[4])) == 0) {
					filteredCourses.push_back(c);
				}
			}
			else if (filterType.compare("dept") == 0) {
				if (c.getDepCode().compare(string(argv[4])) == 0) {
					filteredCourses.push_back(c);
				}
			}
		}

		if (filteredCourses.size() == 0) { //empty case
			out_str << "No data available." << endl;
			out_str.close();
			exit(1);
		}

		//stores biggest length class title, day, and dept
		int maxClassTitleLen = 0;
		int maxDayLen = 0;
		int maxDeptLen = 0;
		getMaxTitleDayLengthDept(filteredCourses, maxClassTitleLen, maxDayLen, maxDeptLen);

		//prints respective header types based on operation
		if (filterType.compare("room") == 0) {
			out_str << "Room" << " " << filteredCourses[0].getCourseRoom() << endl;
			printHeader(filterType, out_str, maxClassTitleLen, maxDayLen, maxDeptLen);
			//sorts the filtered course vector using room sorting criteria 
			sort(filteredCourses.begin(), filteredCourses.end(), roomBasedSorting);
		}
		else if (filterType.compare("dept") == 0) {
			out_str << "Dept" << " " << filteredCourses[0].getDepCode() << endl;
			printHeader(filterType, out_str, maxClassTitleLen, maxDayLen, maxDeptLen);
			//sorts the filtered course vector using dept sorting criteria
			sort(filteredCourses.begin(), filteredCourses.end(), depBasedSorting);
		}

		//loops through all courses in the filtered vector and prints and formats to the output file
		for (Course c : filteredCourses) {
			if (filterType.compare("room") == 0)
				toStringRoom(c, out_str, maxClassTitleLen, maxDayLen, maxDeptLen);
			else if (filterType.compare("dept") == 0)
				toStringDept(c, out_str, maxClassTitleLen, maxDayLen, maxDeptLen);
		}
		out_str << filteredCourses.size() << " " << "entries" << endl; //last line of each room or dept
		if (filterType.compare("dept") == 0) { //extra blank line for end of dept operation
			out_str << endl;
		}
		out_str.close();
	}
	else { //multiple room output
		if (courses.size() == 0) { //empty case
			out_str << "No data available." << endl;
			out_str.close();
			exit(1);
		}

		sort(courses.begin(), courses.end(), roomBasedSorting); //sorts using room based criteria 
		vector<vector<Course> > multiRoomCourses; //passed by reference 
		createMultiRoomCourseList(courses, multiRoomCourses); //creates multi room 2d vector divided by diff rooms

		int maxClassTitleLen = 0;
		int maxDayLen = 0;
		int maxDeptLen = 0;
		

		for (vector<Course> clist : multiRoomCourses) { //loops through each room of courses
			out_str << "Room" << " " << clist[0].getCourseRoom() << endl;
			getMaxTitleDayLengthDept(clist, maxClassTitleLen, maxDayLen, maxDeptLen); //gets max lengths for each room
			printHeader("room", out_str, maxClassTitleLen, maxDayLen, maxDeptLen);
			for (Course c : clist) { //loops through each course in room
				toStringRoom(c, out_str, maxClassTitleLen, maxDayLen, maxDeptLen); //prints and formats to output file
			}
			out_str << clist.size() << " " << "entries" << endl;
			out_str << endl;
		}
	}
	out_str.close();
}

/*
* Essential processing function for my custom statistic 
* Takes list of courses and arg paramaters and prints to output file statistics 
*/
void roomOpenHours(vector<Course> courses, int argc, char* argv[]) { //custom operation
	ofstream out_str(argv[2]);
	if (!out_str.good()) {
		std::cerr << "Can't open " << argv[4] << " to write.\n";
		exit(1);
	}

	if (courses.size() == 0) { //empty case 
		out_str << "No data available." << endl;
		out_str.close();
		exit(1);
	}

	sort(courses.begin(), courses.end(), roomBasedSorting);
	vector<vector<Course> > multiRoomCourses;
	createMultiRoomCourseList(courses, multiRoomCourses);
	
	for (vector<Course> clist : multiRoomCourses) { //loops through each room 
		out_str << "Room" << " " << clist[0].getCourseRoom() << endl;
		printCustomHeader(out_str);
		int monCount = 0, tueCount = 0, wedCount = 0, thurCount = 0, friCount = 0;

		//holds open and closing times for each day
		string mondayOpenHour = "", mondayCloseHour = "";
		string tuesdayOpenHour = "", tuesdayCloseHour = "";
		string wednesdayOpenHour = "", wednesdayCloseHour = "";
		string thursdayOpenHour = "", thursdayCloseHour = "";
		string fridayOpenHour = "", fridayCloseHour = "";

		for (Course c : clist) { //loops through each course and counts number of same days 
			if (c.getCourseDays().compare("Monday") == 0) monCount++;
			else if (c.getCourseDays().compare("Tuesday") == 0) tueCount++;
			else if (c.getCourseDays().compare("Wednesday") == 0) wedCount++;
			else if (c.getCourseDays().compare("Thursday") == 0) thurCount++;
			else if (c.getCourseDays().compare("Friday") == 0) friCount++;
		}
		
		//conditional block to find and store all opening and closing times for all days of the week
		if (monCount > 0) {
			mondayOpenHour = clist[0].getCourseStartTime();
			mondayCloseHour = clist[monCount - 1].getCourseEndTime();
		}
		if (tueCount > 0) {
			tuesdayOpenHour = clist[monCount].getCourseStartTime();
			tuesdayCloseHour = clist[(monCount + tueCount) - 1].getCourseEndTime();
		}
		if (wedCount > 0) {
			wednesdayOpenHour = clist[monCount + tueCount].getCourseStartTime();
			wednesdayCloseHour = clist[(monCount + tueCount + wedCount) - 1].getCourseEndTime();
		}
		if (thurCount > 0) {
			thursdayOpenHour = clist[monCount + tueCount + wedCount].getCourseStartTime();
			thursdayCloseHour = clist[(monCount + tueCount + wedCount + thurCount) - 1].getCourseEndTime();
		}
		if (friCount > 0) {
			fridayOpenHour = clist[monCount + tueCount + wedCount + thurCount].getCourseStartTime();
			fridayCloseHour = clist[(monCount + tueCount + wedCount + thurCount + friCount) - 1].getCourseEndTime();
		}

		//prints custom statistics to output file for each room of courses 
		customToString(out_str, mondayOpenHour, mondayCloseHour, tuesdayOpenHour, tuesdayCloseHour,
			wednesdayOpenHour, wednesdayCloseHour, thursdayOpenHour, thursdayCloseHour,
			fridayOpenHour, fridayCloseHour);
	}
	out_str.close();
}

/*
* Function to change abbreviates days to full length days using helper convertToFullDay function
* Takes in a list of courses passed by reference 
*/
void updateCourseDays(vector<Course>& courses) {
	vector<Course> coursesToAdd; //in order to avoid changing list while looping through it 
	for (int j = 0; j < courses.size(); j++) {
		if (courses[j].getCourseDays().length() == 1) {
			courses[j].setCourseDay(convertToFullDay(courses[j].getCourseDays()[0])); //case for only one abbreviation
		}
		else {
			for (int i = 1; i < courses[j].getCourseDays().length(); i++) {
				//creates new course for each new day 
				Course temp_Course = Course(courses[j].getCrn(), courses[j].getDepCode(), courses[j].getCourseCode(),
					courses[j].getCourseTitle(), courses[j].getCourseDays(), courses[j].getCourseStartTime(),
					courses[j].getCourseEndTime(), courses[j].getCourseRoom());
				temp_Course.setCourseDay(convertToFullDay(courses[j].getCourseDays()[i]));
				//adds new course to list of courses
				coursesToAdd.push_back(temp_Course);
			}
			courses[j].setCourseDay(convertToFullDay(courses[j].getCourseDays()[0])); 
		}
	}

	for (Course c : coursesToAdd) { //adds all new courses to the original course list
		courses.push_back(c);
	}
}

/*
* Main function of program
* Uses all above helper methods to execute the correct operations based on command line arguments
*/
int main(int argc, char* argv[]) {
	ifstream in_str(argv[1]);

	if (!in_str.good()) {
		std::cerr << "Can't open " << argv[3] << " to read.\n";
		exit(1);
	}

	string crn, dep_code, course_code, course_title, course_days,
		course_stime, course_etime, course_room;

	vector<Course> courses;

	while (in_str >> crn >> dep_code >> course_code >> course_title
		>> course_days >> course_stime >> course_etime >> course_room) { 

		courses.push_back(Course(crn, dep_code, course_code, course_title,
			course_days, course_stime, course_etime, course_room));
	}
	updateCourseDays(courses);

	if (string(argv[3]).compare("room") == 0) {
		vector<Course> filteredCourses;
		processCourses(filteredCourses, argc, argv, courses, "room");
	}
	else if (string(argv[3]).compare("dept") == 0) {
		vector<Course> filteredCourses;
		processCourses(filteredCourses, argc, argv, courses, "dept");
	}
	else if (string(argv[3]).compare("custom") == 0) {
		roomOpenHours(courses, argc, argv);
	}
}