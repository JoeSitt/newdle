#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

#include <map>

#include "Time.h"

class Session {
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
        ar & start;
        ar & end;
        ar & tSlots;
    }

    Time start;
    Time end;
    std::map<Time, std::set<std::string>> tSlots;

    Session() {}

    /** Returns string summary of the start and end time */
    std::string getSummary(bool useMil) const;

    /** Returns string summary of who is going and when */
    std::string getAttendeeSummary(bool useMil) const;

    /** Initialize Session with start and end times */
    Session(const Time& start, const Time &end);

    /** Add User to requested time slot. Returns true if addition was successful. */
    bool RSVP(const Time& desired_time, const std::string &name);

    /** Returns whether or not the time passed occurs during the session. */
    bool contains(const Time& t) const;

    /** Returns true of passed session overlaps */
    bool overlaps(const Session &s) const;

    /**
        Allows for sessions to be compared.
        Comparison is done with respect to time in which session starts
    */
    bool operator< (const Session &otherSession) const;
};

#endif
