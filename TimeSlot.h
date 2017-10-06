#ifndef TIME_SLOT_H
#define TIME_SLOT_H

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

class TimeSlot
{
public:
    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & t_attendees;
        ar & t_number_of_attendees;
    }

    TimeSlot();
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

    TimeSlot(const TimeSlot& ts);


private:
    vector<string> *t_attendees;
    int t_number_of_attendees;

};

#endif
