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
		string m_day = date.substr(4,2);
		std::string m_year = date.substr(7);
		int mi_day;
		int mi_year;
		int mi_month;
		/* TODO:
			need to put a check around stoi function calls to make sure each character is a digit
		*/  
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
	return false;
}

bool Valid::isValidTime(std::string start) {
	/*
	TODO:
	write method
	*/
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