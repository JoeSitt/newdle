//katherine ramge
#ifndef VALID_H
#define VALID_H
#include <string>
#include <fstream>

using namespace std;

class Valid {
	public:
		/*
		@pre 
		@param
		@post creates a Valid class
		*/
		Valid();
		
		/*
		@pre 
		@param date as MMDDYYYY, day as first letter capitilized or lowercase
		@post returns true if the combo of date(day month year) and day is correct
		*/
		bool isValidDate(std::string date, std::string day);
		
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
		/*
		@pre 
		@param
		@post 
		*/
		string validDays[];
		
		/*
		@pre 
		@param
		@post 
		*/
		bool isValidYear(int year);
		
		/*
		@pre 
		@param
		@post 
		*/
		bool isValidMonth(int month);
		
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
		bool isValidDay(int month, bool leapYear, int day);
}