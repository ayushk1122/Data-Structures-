#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
//File:     Course.h
//Purpose:  Header file with decleration of the Course class, including
// member functions and private member variables

class Course {
public:
	Course(string acrn, string adep_code, string acourse_code, string acourse_title, string acourse_days,
		string acourse_stime, string acourse_etime, string acourse_room);

	//Accessors
    string getCrn() const;
	string getDepCode() const;
	string getCourseCode() const;
	string getCourseTitle() const;
	string getCourseDays() const;
	string getCourseStartTime() const;
	string getCourseEndTime() const;
	string getCourseRoom() const;

	//Modifiers
	void setCourseDay(string day);
	 
//private member variables 
private:
	string crn, dep_code, course_code, course_title, 
		course_days, course_stime, course_etime, course_room;


};

ostream& toStringRoom(const Course& c1, ofstream& out_str, const int& maxClassTitleLen, const int& maxDayLen, const int& maxDeptLen);
ostream& toStringDept(const Course& c1, ofstream& out_str, const int& maxClassTitleLen, const int& maxDayLen, const int& maxDeptLen);
bool roomBasedSorting(const Course& c1, const Course& c2); //
bool depBasedSorting(const Course& c1, const Course& c2);
bool checkHour(const Course& c1, const Course& c2);
bool operator==(const Course& c1, const Course& c2);