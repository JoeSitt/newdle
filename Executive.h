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
#include <algorithm>
#include "Event.h"
#include "Valid.h"
// #include "FileHandler.h"
#include "Manager.h"
using namespace std;

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

	/** @pre none.
	*   @post will clear the terminal window.
	*   @return none.
	*/
	void clean();

	Time uptime(Time t1);


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
	void addEvent();
	/** @pre event name, time.
	*   @post all attendees for that time slot displayed.
	*   @return true if event/time valid, false if invalid.
	*/
	void checkAttendance();
	/** @pre none.
	*   @post displays events.
	*   @return none.
	*/
	void getEventList();
	bool useMilTime;
	vector<Event*> calendar;
	Manager m;
	Valid* talid;

	void completeTask();

	void addEventMode();

	void checkAttendanceMode();

	void addAttendeeMode();

	void checkTasksMode();

	// Read from user which tasks an event should have
	void readAddTasks(Event* e);

	// Read from user which task they would like to complete
    void readCompleteTask(Event* e, std::string name);

	// Read Int from user
	int readInt(string requestMessage, string failMessage);

	// Read raw string from user (cannot contain spaces)
	std::string readString(std::string requestMessage);

	// Read time from user
	Time readTime(bool useMil);

	// Read and add a new session from the user
	bool readNewSession(Event* event, bool useMil);

	// Read new Event from user
	Event* readEvent(bool useMil);

	// Allow user to select an event
	Event* readEventSelection(std::vector<Event*> event_list);

	// Read a new RSVP-er from the user
	bool readNewAttendee(Event* event, bool useMil);
};

#endif
