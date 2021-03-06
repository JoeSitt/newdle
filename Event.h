/**
*	@file Event.h
*	@author Bisher Anadani
*	@date 9/17/2017
*	@brief Event class
*/

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>

#include <map>
#include <set>

#include "Task.h"
#include "Session.h"

class Event {
public:

    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & sessions;
        ar & name;
        ar & tasks;
    }

    Event(std::string name);

    std::string getTaskSummary() const;

    // Add attendee at the requested date and time. Returns true if addition was successful.
    bool addAttendee(const Time& this_time, const std::string& attendee);

    // Add attendee at the requested date and time. Returns true if addition was successful.
    bool addAttendee(int day, int month, int year, int hour, int minute, const std::string& attendee);

    // Returns a summary of the sessions
    std::string getSessions(bool useMil) const;

    // Returns a summary of the sessions, times, and attendees
    std::string getAttendees(bool useMil) const;

    // Add new Session to Event. Returns true if addition was successful.
    bool addSession(const Time& start, const Time& end);

    // Add new Session to Event. Returns true if addition was successful.
    bool addSession(int startDay, int startMonth, int startYear, int startHour, int startMinute, int endDay, int endMonth, int endYear, int endHour, int endMinute);

    std::set<Session> sessions;
    std::string name;

    Event() {}

    vector<Task> tasks;
};

#endif
