#include <iostream>
#include <string>
#include <vector>
using namespace std;

TimeSlot::TimeSlot(string creator) : t_number_of_attendees(1)
{
  t_attendees = new vector<string>();
  t_attendees->push_back(creator);
}

TimeSlot::GET_number_of_attendees()
{
  return (t_number_of_attendees);
}

TimeSlot::addPerson(string name)
{
  t_attendees->push_back(name);
  t_number_of_attendees++;
}
TimeSlot::~TimeSlot()
{
  delete t_attendees;
}
