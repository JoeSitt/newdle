#include <iostream>
#include <string>
#include <vector>
using namespace std;


Event::Event(string name, string creator, string start_time, string end_time, string date) : e_name(name), e_creator(creator), e_start_time(start_time), e_end_time(end_time), e_date(date)
{
  e_timeslots = new vector<TimeSlot*>();
  digi_start = convert_time(start_time);
  digi_end = convert_time(end_time);
  number_of_timeslots = (digi_end - digi_start)/0.5;

  for(i=0; i<number_of_timeslots; i++){
    e_timeslots->push_back(new TimeSlot(creator));
  }
}

Event::addAttendee(string name, string arrival_time, string leave_time)
{
  int digi_arrival = convert_time(arrival_time);
  int digi_leave = convert_time(leave_time);
  int num_slots = (digi_leave - digi_arrival)/0.5;

  int start_index = digi_arrival - digi_start;

  for(i=start_index; i < num_slots; i++){
    e_timeslots->at(i)->addPerson(name);
  }
}

Event::convert_time(string atime)
{
  double tmp2 = stoi(atime);
  tmp2 = tmp2/100;
  if(tmp2 > round(tmp2)){
    tmp2 = round(tmp2) + 0.5;
  }

  return(tmp2);
}
