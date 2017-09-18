//Valid.cpp

#include "Valid.h"
// #include <string>
// #include <fstream>
// #include <iostream>
// #include <stdlib.h>
// #include <cctype>

// using namespace std;

Valid::Valid(){}

bool Valid::isValidDate(string date) {
	if(date.size() != 11) {
		return false;
	}
	else {
		string m_month = date.substr(0,3);
		string m_day = date.substr(4,2);
		string m_year = date.substr(7);
		int mi_day;
		int mi_year;
		int mi_month;
		char dayC1 = m_day.at(0);
		char dayC2 = m_day.at(1);
		char yearC1 = m_year.at(0);
		char yearC2 = m_year.at(1);
		char yearC3 = m_year.at(2);
		char yearC4 = m_year.at(3);
		if(isdigit(dayC1) && isdigit(dayC2) && isdigit(yearC1) && isdigit(yearC2) && isdigit(yearC3) && isdigit(yearC4)) {
			mi_day = stoi (m_day);
			mi_year = stoi (m_year);
			if(m_month == "JAN") {
				mi_month = 1;
			}
			else if(m_month == "FEB") {
				mi_month = 2;
			}
			else if(m_month == "MAR") {
				mi_month = 3;
			}
			else if(m_month == "APR") {
				mi_month = 4;
			}
			else if(m_month == "MAY") {
				mi_month = 5;
			}
			else if(m_month == "JUN") {
				mi_month = 6;
			}
			else if(m_month == "JUL") {
				mi_month = 7;
			}
			else if(m_month == "AUG") {
				mi_month = 8;
			}
			else if(m_month == "SEP") {
				mi_month = 9;
			}
			else if(m_month == "OCT") {
				mi_month = 10;
			}
			else if(m_month == "NOV") {
				mi_month = 11;
			}
			else if(m_month == "DEC") {
				mi_month = 12;
			}
			else {
				return false;
			}
			return isValidDay(mi_month, mi_day, mi_year);
		}
	}
	return false;
}

bool Valid::isValidTime(string start) {
	if(start.size() == 4) {
		if(start.at(0) == '0') {
			return (isdigit(start.at(1)) && check0030(start));
		}
		else if(start.at(0) == '1') {
			return (isdigit(start.at(1)) && check0030(start));
		}
		else if(start.at(0) == '2') {
			if(start.at(1) == '0' || start.at(1) == '1' || start.at(1) == '2' || start.at(1) == '3') {
				return check0030(start);
			}
		}
	}
	return false;
}

bool Valid::isValidTime12Hour(string start) {
	if(start.size() < 6 || start.size() > 7) {
		return false;
	}
	else if(start.substr(start.size()-2) == "AM") {
		if(start.size()==6) {
			//SIZE = 6
			if(isdigit(start.at(0)) && (start.at(0) != '0') && (start.at(1) == ':') && ((start.substr(2,2) == "00") || (start.substr(2,2) == "30"))) {
				//checks that the first digit is a nonzero number followed by a ':' followed by "00" or "30"
				return true;
			}
			return false;
		}
		else {
			//SIZE = 7
			if((start.at(0) == '1') && (start.at(1) == '0' || start.at(1) == '1' || start.at(1) == '2') && start.at(2) == ':' && ((start.substr(3,2) == "00") || (start.substr(3,2) == "30"))) {
				return true;
			}
			return false;
		}
	}
	else if(start.substr(start.size()-2) == "PM") {
		if(start.size()==6) {
			//SIZE = 6
			if(isdigit(start.at(0)) && (start.at(0) != '0') && (start.at(1) == ':') && ((start.substr(2,2) == "00") || (start.substr(2,2) == "30"))) {
				//checks that the first digit is a nonzero number followed by a ':' followed by "00" or "30"
				return true;
			}
			return false;
		}
		else {
			//SIZE = 7
			if((start.at(0) == '1') && (start.at(1) == '0' || start.at(1) == '1' || start.at(1) == '2') && start.at(2) == ':' && ((start.substr(3,2) == "00") || (start.substr(3,2) == "30"))) {
				return true;
			}
			return false;
		}
	}
	return false;
}

/*
assumes variable start is valid
*/
bool Valid::isValidTimeSlots(string start, string end) {
	if(isValidTime(end)) {
		int i_start = stoi(start);
		int i_end = stoi(end);
		if(i_start < i_end) {
			return true;
		}
	}
	return false;
}
/*
assumes variable start is valid
*/
bool Valid::isValidTimeSlots12Hour(string start, string end) {
	if(isValidTime12Hour(end)) {
		string time24start = changeTo24Hour(start);
		string time24end = changeTo24Hour(end);
		return isValidTimeSlots(time24start, time24end);
	}
	return false;
}

/*
assumes variable time is valid
*/
string Valid::changeTo12Hour(string time) {
	string returner = "";
	int i_time = stoi(time);
	if((i_time >= 0) && (i_time <= 2330)) {
		if(i_time == 0) {
			return "12:00AM";
		}
		else if(i_time == 30) {
			return "12:30AM";
		}
		else if(i_time < 1000) {
			returner += time.at(1);
			returner += ':';
			returner += time.substr(2);
			returner += "AM";
			return returner;
		}
		else if(i_time < 1200) {
			returner += time.substr(0,2);
			returner += ':';
			returner += time.substr(2);
			returner += "AM";
			return returner;
		}
		else if(i_time == 1200) {
			return "12:00PM";
		}
		else if(i_time == 1230) {
			return "12:30PM";
		}
		else if(i_time > 1230) {
			int i_hourTime = (i_time / 100) - 12;
			returner += to_string(i_hourTime);
			returner += ':';
			if(i_time % 100 == 0) {
				returner += "00PM";
				return returner;
			}
			else {
				returner += "30PM";
				return returner;
			}
		}
	}
	return "0";
}

//assumes variable time is a valid 12hour time
string Valid::changeTo24Hour(string time) {
	string returner = "";
	if(time.substr(time.size()-2) == "AM") {
		if(time.size()==6) {
			returner += "0";
			returner += time.at(0);
			returner += time.substr(2,2);
			return returner;
		}
		else if (time == "12:00AM") {
			return "0000";
		}
		else if (time == "12:30AM") {
			return "0030";
		}
		else {
			returner += time.substr(0,2);
			returner += time.substr(3,2);
			return returner;
		}
	}
	else {
		if(time.size()==6) {
			int temp = stoi(time.substr(0,1));
			temp += 12;
			returner += to_string(temp);
			returner += time.substr(2,2);
			return returner;
		}
		else if(time == "12:00PM") {
			return "1200";
		}
		else if(time == "12:30PM") {
			return "1230";
		}
		else {
			int temp = stoi(time.substr(0,2));
			temp += 12;
			returner += to_string(temp);
			returner += time.substr(3,2);
			return returner;
		}
	}
	return "0";
}

/*
Code used from one of my former APCS assignments ~Kate
Web page to double check algorithm: https://www.accuracyproject.org/leapyears.html
*/
bool Valid::isLeapYear(int year) {
	if(year >= 1582 && year <=9999) {
		if(year % 4 == 0) {
			if((year % 100 == 0) && (year % 400 != 0)) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			return false;
		}
	}
	return false;
}

bool Valid::isValidDay(int month, int day, int year) {
	int min_day = 1;
	int max_day;
	/*
	calculates the max number of days in a month
	*/
	if(month == 2) {
		if(isLeapYear(year)) {
			max_day = 29;
		}
		else {
			max_day = 28;
		}
	}
	else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		max_day = 31;
	}
	else {
		max_day = 30;
	}
	/*
	is the day valid given the month and the year
	*/
	if(min_day <= day && day <= max_day) {
		return true;
	}
	return false;
}

bool Valid::check0030(string time) {
	if(time.substr(2) == "00" || time.substr(2) == "30") {
		return true;
	}
	return false;
}
