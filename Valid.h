//katherine ramge
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
		@post creates a Valid class
		*/
		Valid(int x);
		Valid();
		
		/*
		@pre 
		@param date as MMM DD YYYY, MMM should be all capitilized
		@post returns true if the combo of date is correct
		*/
		bool isValidDate(std::string date);
		
		/*
		@pre 
		@param start as TTTT in 24 hour
		@post returns true if the time given is valid in 24
		*/
		bool isValidTime(std::string start);
		
		/*
		@pre 
		@param start as TTTT, end as TTTT both in 24 hour
		@post returns true if the two time slots are valid together
		*/
		bool isValidTimeSlots(std::string start, std::string end);
		
		/*
		@pre 
		@param eventName as a string
		@post returns true if the event is a valid existing event
		*/
		bool isEvent(std::string eventName);
		
		/*
		@pre 
		@param time as #### in 24 hour
		@post returns #### in 12 hour
		*/
		int changeTo12Hour(int time);
		
	private:

		//string validDays[];
		int my_x;
		/*
		@pre 
		@param
		@post 
		*/
		bool isLeapYear(int year);
		
		/*
		@pre 
		@param
		@post 
		*/
		bool isValidDay(int month, int day, int year);
		
		/*
		@pre 
		@param
		@post 
		*/
		bool check0030(std::string time);
};
#endif