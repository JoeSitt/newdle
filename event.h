#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "timeslot.h"

class Event
{
  public:
    Event(string name, string creator, string start_time, string end_time, string date);
    ~Event();
    void addAttendee(string name, string arrival_time, string leave_time);
    string getEventName();
    string getEventCreator();
    string getEventStartTime();
    string getEventEndTime();
    string getEventDate();
    int getAttendance(string start_time);

    vector<*TimeSlot> *e_timeslots;


  private:
    string e_name;
    string e_creator;
    string e_date;
    int e_start_time;
    int e_end_time;
    int e_number_of_attendees;
    int convert_time(string atime);
    int e_digi_start;
    int e_digi_end;
    int e_number_of_timeslots;
};

#include "event.hpp"

#endif
