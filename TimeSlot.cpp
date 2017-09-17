#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "TimeSlot.h"

TimeSlot::TimeSlot(string creator) : t_number_of_attendees(1)
{
  t_attendees = new vector<string>();
  t_attendees->push_back(creator);
}

int TimeSlot::getNumberOfAttendees()
{
  return (t_number_of_attendees);
}

void TimeSlot::addPerson(string name)
{
  t_attendees->push_back(name);
  t_number_of_attendees++;
}

bool TimeSlot::doesAttend(string name)
{
  if(find(t_attendees->begin(), t_attendees->end(), name) != t_attendees.end() ){
    return(true);
  }
  else{
    return(false);
  }
}

TimeSlot::~TimeSlot()
{
  delete t_attendees;
}
