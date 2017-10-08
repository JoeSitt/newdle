#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#include "Valid.h"

/**
    Encapsulates a time.

    Can have contents serialized.

    NOTE:
    None of the attributes are checked to represent realistic states. The class
    is essentially just providing a way to order and represent already
    checked times.
*/
class Time {
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
        ar & day;
        ar & month;
        ar & year;
        ar & hour;
        ar & minute;
    }

    int day;
    int month;
    int year;
    int hour;
    int minute;

    Time() {}

    /** Initialize a time object */
    Time(int day, int month, int year, int hour, int minute);

    /** Provide string representation of the represented time */
    std::string toString(bool useMil) const;

    /**
        Formats hour/minute component of time.

        NOTE:
        Hours and minutes are not checked to correspond to realistic times.
        Use with caution.
     */
    std::string getTime(bool useMil) const;

    /** Comparision with preference to year, then month, etc. */
    bool operator< (const Time &otherTime) const ;
};

#endif
