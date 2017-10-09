#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

#include "Time.h"

Time::Time(int day, int month, int year, int hour, int minute): day(day), month(month), year(year), hour(hour), minute(minute) {}

std::string Time::toString(bool useMil) const {
    std::string outStr = "";
    outStr += std::to_string(month);
    outStr += "/";
    outStr += std::to_string(day);
    outStr += "/";
    outStr += std::to_string(year);

    outStr += " ";

    outStr += getTime(useMil);

    return outStr;
}

std::string Time::getTime(bool useMil) const {
    Valid v;

    std::string outStr = "";
    if (hour < 10) {
        outStr += "0";
    }
    outStr += std::to_string(hour);

    if (minute < 10) {
        outStr += "0";
    }
    outStr += std::to_string(minute);

    if (useMil) {
        return outStr;
    } else {
        return v.changeTo12Hour(outStr);
    }
}

bool Time::operator< (const Time &otherTime) const {
    if (year == otherTime.year) {
        if (month == otherTime.month) {
            if (day == otherTime.day) {
                if (hour == otherTime.hour) {
                    return minute < otherTime.minute;
                } else {
                    return hour < otherTime.hour;
                }
            } else {
                return day < otherTime.day;
            }
        } else {
            return month < otherTime.month;
        }
    } else {
        return year < otherTime.year;
    }
}
