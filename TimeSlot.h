#ifndef TIME_SLOT_H
#define TIME_SLOT_H

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

class TimeSlot
{
  public:
    /** @pre Receives the creator's name as a string.
    *   @post creates a timeslot object and adds the creator as an attendee in this timeslot.
    *   @return none.
    */
    TimeSlot(string creator);
    /** @pre None.
    *   @post Delets the vector pointer.
    *   @return none.
    */
    ~TimeSlot();
    /** @pre None.
    *   @post None.
    *   @return member variable which tracks the number of attendees.
    */
    int getNumberOfAttendees();
    /** @pre Receives a person's name in string form.
    *   @post adds the person to the vector that stores attendees.
    *   @return none.
    */
    void addPerson(string name);
    /** @pre Receives a person's name to check if they attend the timeslot.
    *   @post checks if the person's name exists in the attendees vector list.
    *   @return bool; true if they attend and false if they don't.
    */
    bool doesAttend(string name);


  private:
    vector<string> *t_attendees;
    int t_number_of_attendees;

};

#endif
