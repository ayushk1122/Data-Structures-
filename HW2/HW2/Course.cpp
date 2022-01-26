// File:   Course.cpp
// Purpose: Class file for the Course class
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Course.h"
#include <algorithm>
#include <iomanip>

using namespace std;

Course::Course(string acrn, string adep_code, string acourse_code, 
	string acourse_title, string acourse_days,
	string acourse_stime, string acourse_etime, string acourse_room) { // overloaded constructor 

	crn = acrn;
	dep_code = adep_code;
	course_code = acourse_code;
	course_title = acourse_title;
	course_days = acourse_days;
	course_stime = acourse_stime;
	course_etime = acourse_etime;
	course_room = acourse_room;
}

// Accessor methods 
string Course::getCrn() const {
	return crn;
}

string Course::getDepCode() const {
	return dep_code;
}

string Course::getCourseCode() const {
	return course_code;
}

string Course::getCourseTitle() const {
	return course_title;
}

string Course::getCourseDays() const {
	return course_days;
}

string Course::getCourseStartTime() const {
	return course_stime;
}

string Course::getCourseEndTime() const {
	return course_etime;
}

string Course::getCourseRoom() const {
	return course_room;
}

// Modifier - purpose to convert days from MR -> Monday Thursday
void Course::setCourseDay(string day) {
	course_days = day;
}

//out streams correct formatting for each course given a room operation
ostream& toStringRoom(const Course& c1, ofstream& out_str, const int& maxClassTitleLen, const int& maxDayLen, const int& maxDeptLen) {
	//cout << c1.getCrn() << " " << c1.getDepCode() << " " << c1.getCourseCode() << " " <<
	//	c1.getCourseTitle() << " " << c1.getCourseDays() << " " << c1.getCourseStartTime() << " "
	//	<< c1.getCourseEndTime() << " " << c1.getCourseRoom() << endl;

	out_str << left << setw(maxDeptLen) << c1.getDepCode() << "  " << c1.getCourseCode() << "    " << setw(maxClassTitleLen) << c1.getCourseTitle()
		<< "  " << setw(maxDayLen) << c1.getCourseDays() << "  " << c1.getCourseStartTime()
		<< "     " << c1.getCourseEndTime() << " " << endl;
	return out_str;
}

//out streams correct formatting for each course given a dept operation
ostream& toStringDept(const Course& c1, ofstream& out_str, const int& maxClassTitleLen, const int& maxDayLen, const int& maxDeptLen) {
	out_str << left << c1.getCourseCode() << "    " << setw(maxClassTitleLen) << c1.getCourseTitle() << "  "
		<< setw(maxDayLen) << c1.getCourseDays() << "  " << c1.getCourseStartTime() << "     " << c1.getCourseEndTime() << " " << endl;
	return out_str;
}

//function to return true if course 1 is earlier than course 2
bool checkHours(const Course& c1, const Course& c2) {
	string c1Start = c1.getCourseStartTime();
	string c2Start = c2.getCourseStartTime();
	int c1ColIndex = c1Start.find(":");
	int c2ColIndex = c2Start.find(":");

	//use of stoi to convert strings to int for comparision
	int c1Hour = stoi(c1Start.substr(0, c1ColIndex - 0));
	int c2Hour = stoi(c2Start.substr(0, c2ColIndex - 0));

	//12AM and 12PM will always be earlier in their respective time frames
	if (c1Hour == 12) { 
		c1Hour = -1;
	}

	if (c2Hour == 12) {
		c2Hour = -1;
	}
	
	if ((c1Start.find("PM") < c1Start.length()) && (c2Start.find("PM") < c2Start.length())) {
		return (c1Hour < c2Hour);

	}
	else if ((c1Start.find("AM") < c1Start.length()) && (c2Start.find("AM") < c2Start.length())) {
		return (c1Hour < c2Hour);
		 
	}
	else if ((c1Start.find("AM") < c1Start.length()) && (c2Start.find("PM") < c2Start.length())) {
		return true;
	}
	else {
		return false;
	}
}

//room specified sorting
bool roomBasedSorting(const Course& c1, const Course& c2) {
	string days = "Monday Tuesday Wednesday Thursday Friday"; //used to determine order of days,
	//since days are not able to be alphabetically sorted

	//uses index to determine order
	size_t c1DayIndex = days.find(c1.getCourseDays());
	size_t c2DayIndex = days.find(c2.getCourseDays());

	//conditional block to sort with correct mechanics
	if (c1.getCourseRoom().compare(c2.getCourseRoom()) == 0) {
		if (c1DayIndex == c2DayIndex) {
			if (c1.getCourseStartTime().compare(c2.getCourseStartTime()) == 0) {
				if (c1.getCourseCode().compare(c2.getCourseCode()) == 0) {
					return (c1.getDepCode() < c2.getDepCode());
				}
				else {
					return (stoi(c1.getCourseCode()) < stoi(c2.getCourseCode()));
				}
			}
			else {
				return (checkHours(c1, c2));
			}
		}
		else {
			return (c1DayIndex < c2DayIndex);
		}
	}
	else {
		return (c1.getCourseRoom() < c2.getCourseRoom());
	}
}

//sorting specific to department criteria 
bool depBasedSorting(const Course& c1, const Course& c2) {
	string days = "Monday Tuesday Wednesday Thursday Friday";
	size_t c1DayIndex = days.find(c1.getCourseDays());
	size_t c2DayIndex = days.find(c2.getCourseDays());

	if (c1.getCourseCode().compare(c2.getCourseCode()) == 0) {
		if (c1DayIndex == c2DayIndex) {
			return (!checkHours(c1, c2));
		}
		else {
			return (c1DayIndex < c2DayIndex);
		}
	}
	else {
		return (c1.getCourseCode() < c2.getCourseCode());
	}
}

//special operator function to compare equivelancy of courses
bool operator==(const Course& c1, const Course& c2) {
	return ((c1.getCrn().compare(c2.getCrn()) == 0) && (c1.getDepCode().compare(c2.getDepCode()) == 0)
		&& (c1.getCourseCode().compare(c2.getCourseCode()) == 0) && (c1.getCourseTitle().compare(c2.getCourseTitle()) == 0)
		&& (c1.getCourseDays().compare(c2.getCourseDays()) == 0) && (c1.getCourseStartTime().compare(c2.getCourseStartTime()) == 0)
		&& (c1.getCourseEndTime().compare(c2.getCourseEndTime()) == 0) && (c1.getCourseRoom().compare(c2.getCourseRoom()) == 0));
}

 