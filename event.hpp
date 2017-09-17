#include <iostream>
#include <string>
#include <vector>
using namespace std;


Event::Event(string name, string creator, string start_time, string end_time, string date) : e_name(name), e_creator(creator), e_start_time(start_time), e_end_time(end_time), e_date(date)
{
  e_timeslots = new vector<TimeSlot*>();
  e_digi_start = convert_time(start_time);
  e_digi_end = convert_time(end_time);
  e_number_of_timeslots = (e_digi_end - e_digi_start)/0.5;

  for(i=0; i<e_number_of_timeslots; i++){
    e_timeslots->push_back(new TimeSlot(creator));
  }
}

Event::addAttendee(string name, string arrival_time, string leave_time)
{
  int digi_arrival = convert_time(arrival_time);
  int digi_leave = convert_time(leave_time);
  int num_slots = (digi_leave - digi_arrival)/0.5;

  int start_index = digi_arrival - e_digi_start;

  for(i=start_index; i < num_slots; i++){
    e_timeslots->at(i)->addPerson(name);
  }
}

int Event::convert_time(string atime)
{
  double tmp2 = stoi(atime);
  tmp2 = tmp2/100;
  if(tmp2 > round(tmp2)){
    tmp2 = round(tmp2) + 0.5;
  }

  return(tmp2);
}

string Event::getEventName()
{
  return(e_name);
}

string Event::getEventCreator()
{
  return(e_creator);
}

string Event::getEventStartTime()
{
  return(e_start_time);
}

string Event::getEventEndTime()
{
  return(e_end_time);
}

string Event::getEventDate()
{
  return(e_date);
}

int Event::getAttendance(string start_time)
{
  int digi_arrival = convert_time(start_time);
  int start_index = digi_arrival- e_digi_start;

  int num = e_timeslots->at(start_index)->getNumberOfAttendees();

  return(num);
}
