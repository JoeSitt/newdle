#ifndef TIME_SLOT_H
#define TIME_SLOT_H

#include <iostream>
#include <vector>

using namespace std;

class TimeSlot
{
  public:
    TimeSlot(string creator);
    ~TimeSlot();
    int getNumberOfAttendees();
    void addPerson(string name);
    bool doesAttend(string name);


  private:
    vector<string> *t_attendees;
    int t_number_of_attendees;

};

#endif
