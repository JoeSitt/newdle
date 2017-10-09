#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

#include "Session.h"

std::string Session::getSummary(bool useMil) const {
    std::string outStr = "";
    outStr += "start: ";
    outStr += start.toString(useMil);
    outStr += "\n";
    outStr += "end: ";
    outStr += end.toString(useMil);
    outStr += "\n";
    return outStr;
}

std::string Session::getAttendeeSummary(bool useMil) const {
    std::string outStr = "";

    for (const std::pair<Time, std::set<std::string>>& pair : tSlots) {
        Time t = pair.first;
        std::set<std::string> attendees = pair.second;

        outStr += t.toString(useMil);
        outStr += ": ";

        for (std::string attendee : attendees) {
            outStr += attendee;
            outStr += ", ";
        }
        outStr[outStr.size()-2]=' ';
        outStr += "\n";
    }

    return outStr;
}

Session::Session(const Time& start, const Time &end) {
    this->start = start;
    this->end = end;
}

// Add User to requested time slot. Returns true if addition was successful.
bool Session::RSVP(const Time& desired_time, const std::string &name) {
    if (!contains(desired_time)) {
        return false;
    }

    // If the time is not in the map, create entry. Else add to entry.
    if (tSlots.find(desired_time) == tSlots.end()) {
        std::set<std::string> new_set;
        new_set.insert(name);
        tSlots.insert(std::pair<Time, std::set<std::string>>(desired_time, new_set));
    } else {
        std::set<std::string> time_set = tSlots.find(desired_time)->second;
        time_set.insert(name);
        tSlots.erase(desired_time);
        tSlots.insert(std::pair<Time, std::set<std::string>>(desired_time, time_set));
    }

    return true;  // TEMP
}

// Returns whether or not the time passed occurs during the session.
bool Session::contains(const Time& t) const {
    if (end < t || t < start) {
        return false;
    }
    return true;
}

// Returns true of passed session overlaps
bool Session::overlaps(const Session &s) const {
    if (contains(s.start) || contains(s.end)) {
        return true;
    }
    return false;
}

bool Session::operator< (const Session &otherSession) const {
    return start < otherSession.start;
}
