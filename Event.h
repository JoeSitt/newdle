#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

#include "TimeSlot.h"

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
    vector<vector<string>> getAttendees();

    vector<TimeSlot*> *e_timeslots;
    vector<string> *e_attendees;


  private:
    string e_name;
    string e_creator;
    string e_start_time;
    string e_end_time;
    string e_date;
    int e_number_of_attendees;
    double convert_time(string atime);
    string convert_to_string(double atime);
    double e_digi_start;
    double e_digi_end;
    int e_number_of_timeslots;
};

#endif
