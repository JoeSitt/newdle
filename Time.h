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

class Time {
public:

    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
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

    Time(int day, int month, int year, int hour, int minute);

    std::string toString(bool useMil) const;

    std::string getTime(bool useMil) const;

    bool operator< (const Time &otherTime) const ;
};

#endif
