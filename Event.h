#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

#include "TimeSlot.h"
#include "Task.h" //modified

class Event
{
  public:
    /** @pre Receives event name, creator, start_time, end_time, date all as strings.
    *   @post creates the event object timelots, assigns the parameters to member variables.
    *   @return none.
    */
    Event(string name, string creator, string start_time, string end_time, string date, vector<string> tasks);
  
    Event(string name, string creator, string start_time, string end_time, string date);
    /** @pre none.
    *   @post deletes pointers of timeslots, and the member variable pointers.
    *   @return none.
    */
    ~Event();
    /** @pre takes the name of the attendee, arrival time and leave time.
    *   @post adds the name of the attendee to all the timeslots they chose.
    *   @return none.
    */
    void addAttendee(string name, string arrival_time, string leave_time, Task accepted_Task); //modified
  
    void addAttendee(string name, string arrival_time, string leave_time);
    /** @pre none.
    *   @post none.
    *   @return member variable event name.
    */
    string getEventName();
    /** @pre none.
    *   @post none.
    *   @return member varibale event creator.
    */
    string getEventCreator();
    /** @pre none.
    *   @post none.
    *   @return member variable start time.
    */
    string getEventStartTime();
    /** @pre none.
    *   @post none.
    *   @return member variable end time.
    */
    string getEventEndTime();
    /** @pre none.
    *   @post none.
    *   @return member variable event date.
    */
    string getEventDate();
    /** @pre the start time of the timeslot being queried.
    *   @post counts the attendees for chosen time slot.
    *   @return number of attendees for the timeslot.
    */
    int getAttendance(string start_time);
    /** @pre none.
    *   @post finds all the timeslots each person is attending.
    *   @return a vector of all the timeslots a person is attending, index 0 being the person's name.
    */
    vector<vector<string>> getAttendees();

    vector<TimeSlot*>* e_timeslots;
    vector<string>* e_attendees;
    
    vector<string> eventTask; //Stores list of event Tasks 	
  
    vector<Task> acceptedTask; //Stores	list of accepted Tasks by attendes
	
    vector<string> taskTaken; //Stores list of tasks already taken
  
    void addTasks(string taskName); //allows admin to add list of Tasks to eventTask		
  
  private:
    string e_name;
    string e_creator;
    string e_start_time;
    string e_end_time;
    string e_date;
    int e_number_of_attendees;
    /** @pre Receives a string of time in 24 hr format (ex: 0230)
    *   @post computes a double of size 0-23.5, smallest increment being 0.5.
    *   @return the calculated double.
    */
    double convert_time(string atime);
    /** @pre Receives a double of time between 0-23.5.
    *   @post converts the double to a string in 24 hr format.
    *   @return the time in string format.
    */
    string convert_to_string(double atime);
    double e_digi_start;
    double e_digi_end;
    int e_number_of_timeslots;
};

#endif
