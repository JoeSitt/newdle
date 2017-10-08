#ifndef VALID_H
#define VALID_H
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cctype>

using namespace std;

class Valid {
	public:
		/*
		@pre
		@param
		@post creates a Valid class object
		*/
		Valid();

		/*
		@pre
		@param date as MMM DD YYYY, MMM should be all capitilized
		@post returns true if the combo of date is correct
		*/
		bool isValidDate(string date);

		/*
		@pre
		@param takes any string in 24 hour time
		@post returns true if the time given is valid in 24 hour and is on a half hour
		*/
		bool isValidTime(string start);

		/*
		@pre
		@param takes any string in 12 hour time
		@post returns true if the time given is valid in 12 hour and is on a half hour
		*/
		bool isValidTime12Hour(string start);

		/*
		@pre assumes start has already been checked by isValidTime
		@param start as TTTT, end as TTTT both in 24 hour
		@post returns true if the two time slots are valid together
		*/
		bool isValidTimeSlots(string start, string end);

		/*
		@pre assumes start has already been checked by isValidTime
		@param start as a valid 12hour time, end as any string in 12 hour form
		@post returns true if the two time slots are valid together
		*/
		bool isValidTimeSlots12Hour(string start, string end);

		/*
		@pre assumes start has already been checked by isValidTime12Hour
		@param start as a valid 12hour time, end as any string in 12 hour form
		@post returns string of the 12hr time with AM or PM
		*/
		string fix12Hr(string start);

		/*
		@pre passing in a valid 24 hour time
		@param time as string in valid 24 hour
		@post returns string in 12 hour
		*/
		string changeTo12Hour(string time);

		/*
		@pre passing in a calid 12 hour time
		@param time as string in valid 12 hour
		@post returns string in 24 hour
		*/
		string changeTo24Hour(string time);

	private:

		/*
		@pre
		@param year as an int (from 1582 to 9999)
		@post returns true if the year passed is a leap year
		*/
		bool isLeapYear(int year);

		/*
		@pre
		@param month as 1, 2, ..., 9, 10, 11, 12, day as a one or two digit int, year as a 4 digit int.
		@post returns true if the combo of day month year exists
		*/
		bool isValidDay(int month, int day, int year);

		/*
		@pre
		@param time passes as a 4 digit 24 hour time string
		@post returns true if the time is on a half hour
		*/
		bool check0030(string time);
};
#endif
