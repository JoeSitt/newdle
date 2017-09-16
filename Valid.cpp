//Valid.cpp

#include "Valid.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cctype>

using namespace std;

Valid::Valid(){}

Valid::Valid(int x) {
	/*
	TODO:
	create starting stuff
	*/
	my_x = x;
}

bool Valid::isValidDate(std::string date) {
	if(date.size() != 11) {
		return false;
	}
	else {
		std::string m_month = date.substr(0,3);
		std::string m_day = date.substr(4,2);
		std::string m_year = date.substr(7);
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

bool Valid::isValidTime(std::string start) {
	/*
	TODO:
	write method
	*/
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


bool Valid::isValidTimeSlots(std::string start, std::string end) {
	/*
	TODO:
	write method
	call isValidTime for end
	*/
	return false;
}

bool Valid::isEvent(std::string eventName) {
	/*
	TODO:
	write method
	*/
	return false;
}

int Valid::changeTo12Hour(int time) {
	/*
	TODO:
	write method
	*/
	return 0;
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

bool Valid::check0030(std::string time) {
	if(time.substr(2) == "00" || time.substr(2) == "30") {
		return true;
	}
	return false;
}