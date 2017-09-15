//Valid.cpp

#include "Valid.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

Valid::Valid() {
	/*
	TODO:
	create starting stuff
	*/
}

bool Valid::isValidDate(std::string date) {
	/*
	TODO:
	write method
	*/
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
		if(isdigit(m_day) && isdigit(m_year)) {  
			mi_day = atoi (m_day);
			mi_year = atoi (m_year);
			switch(m_month) {
				case "JAN":
					mi_month = 1;
					break;
				case "FEB":
					mi_month = 2;
					break;
				case "MAR":
					mi_month = 3;
					break;
				case "APR":
					mi_month = 4;
					break;
				case "MAY":
					mi_month = 5;
					break;
				case "JUN":
					mi_month = 6;
					break;
				case "JUL":
					mi_month = 7;
					break;
				case "AUG":
					mi_month = 8;
					break;
				case "SEP":
					mi_month = 9;
					break;
				case "OCT":
					mi_month = 10;
					break;
				case "NOV":
					mi_month = 11;
					break;
				case "DEC":
					mi_month = 12;
					break;
				default:
					return false;
					break;
			}
			return isValidDay(mi_month, mi_day, mi_year);
		}
		else {
			return false;
		}
	}
	//
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


bool Valid::isLeapYear(int year) {
	/*
	TODO:
	write method
	*/
	return false;
}

bool Valid::isValidDay(int month, int day, int year) {
	/*
	TODO:
	write method
	*/
	return false;
}