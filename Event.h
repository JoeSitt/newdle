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
using namespace std;

/**
    Encapsulates an event. Contains an ordered collection of non-overlapping
    Sessions that can be RSVP'd to at desired times.

    Can have contents serialized.
*/
class Event {
public:

    friend class boost::serialization::access;

    /**
        When the class Archive corresponds to an output archive, the
        & operator is defined similar to <<.  Likewise, when the class Archive
        is a type of input archive the & operator is defined similar to >>.
    */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & sessions;
        ar & name;
        ar & eventTask;
        ar & acceptedTask;
        ar & taskTaken;
    }

    Event(std::string name);

    /**
        TODO:
        Provide summary of the tasks that have/should be completed.
    */
    std::string getTaskSummary() const;

    /** Add attendee at the requested date and time. Returns true if addition was successful. */
    bool addAttendee(int day, int month, int year, int hour, int minute, const std::string& attendee);

    /** Returns a summary of the sessions */
    std::string getSessions(bool useMil) const;

    /** Returns a summary of the sessions, times, and attendees */
    std::string getAttendees(bool useMil) const;

    /** Add new Session to Event. Returns true if addition was successful. */
    bool addSession(int startDay, int startMonth, int startYear, int startHour, int startMinute, int endDay, int endMonth, int endYear, int endHour, int endMinute);

    std::set<Session> sessions;
    std::string name;

    Event() {}

    vector<string> eventTask; //Stores list of event Tasks
    vector<Task> acceptedTask; //Stores	list of accepted Tasks by attendes
    vector<string> taskTaken; //Stores list of tasks already taken

    void addTasks();
    void acceptTask(string attendee); //attendees accept task from this function
};

#endif
