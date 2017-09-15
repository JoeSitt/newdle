/**
*	@file Executive.h
*	@author Ferocious Hammerheads
*	@date
*	@brief A header file for Executive
*/

#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include <iostream>
#include <vector>
#include <string>
#include "Event.h"
#include "Valid.h"
//more includes when files added

class Executive
{
	public:
	/** @pre None.
	*   @post The saved list of events is imported.
	*/
	Executive();
	/** @pre None.
	*   @post The list of events is saved and.
	*/
	~Executive();
	/** @pre none.
	*   @post will ask which mode and send user to that mode.
	*   @return none.
	*/
	void run();


private:
	/** @pre none.
	*   @post User is in admin mode.
	*   @return none.
	*/
	void adminMode();
	/** @pre none.
	*   @post User is in attendee mode.
	*   @return none.
	*/
	void attendeeMode();
	/** @pre none.
	*   @post new event in calendar vector created.
	*   @return true if created, false if error occured.
	*/
	bool addEvent();
	/** @pre event name, time.
	*   @post all attendees for that time slot displayed.
	*   @return true if event/time valid, false if invalid.
	*/
	bool checkAttendance();
	/** @pre none.
	*   @post displays events.
	*   @return none.
	*/
	void getEventList();
	std::vector<Event> calendar;
};

#include "Executive.cpp"
#end if
