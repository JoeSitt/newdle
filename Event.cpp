/**
*	@file Event.h
*	@author Bisher Anadani
*	@date 9/17/2017
*	@brief Event implementation
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

#include "Event.h"

std::string Event::getTaskSummary() const {
    std::string outStr = "";

    // Handle no task case
    if (tasks.size() == 0) {
        return "This event has no tasks\n";
    }

    int i = 1;
    for (const Task& t : tasks) {
        outStr += std::to_string(i) + ": ";
        outStr += t.description;
        outStr += ": ";
        outStr += t.guestName;
        outStr += "\n";
        i++;
    }

    return outStr;
}

Event::Event(std::string name): name(name) {}

// Add attendee at the requested date and time. Returns true if addition was successful.
bool Event::addAttendee(const Time& this_time, const std::string& attendee) {
    std::set<Session> new_sessions;
    bool was_added = false;

    for (const Session& s : sessions) {
        Session new_sess(s);
        if (s.contains(this_time)) {

            // TODO: delete after testing
            if (was_added) {
                std::cout << "ERROR: double addition of session in Event::addAttendee()" << std::endl;
            }

            new_sess.RSVP(this_time, attendee);
            was_added = true;
        }
        new_sessions.insert(new_sess);
    }

    sessions = new_sessions;
    return was_added;
}

// Add attendee at the requested date and time. Returns true if addition was successful.
bool Event::addAttendee(int day, int month, int year, int hour, int minute, const std::string& attendee) {
    Time this_time(day, month, year, hour, minute);
    return addAttendee(this_time, attendee);
}

// Returns a summary of the sessions
std::string Event::getSessions(bool useMil) const {
    std::string outStr = name;
    outStr += "\n";
    int sessCount = 1;
    for (const Session& session : sessions) {
        outStr += "Session ";
        outStr += std::to_string(sessCount);
        outStr += "\n";
        outStr += session.getSummary(useMil);
        sessCount++;
    }
    return outStr;
}

// Returns a summary of the sessions, times, and attendees
std::string Event::getAttendees(bool useMil) const {
    std::string outStr = name;

    // TODO update with task information
    // outStr += getTaskSummary();

    outStr += "\n";
    int sessCount = 1;
    for (const Session& session : sessions) {
        outStr += "Session ";
        outStr += std::to_string(sessCount);
        outStr += "\n";
        outStr += session.getAttendeeSummary(useMil);
        sessCount++;
    }
    return outStr;
}

// Add new Session to Event. Returns true if addition was successful.
bool Event::addSession(const Time& start, const Time& end) {
    Session newSession(start, end);
    // New session must have valid (non overlapping) times
    if (!(start < end)) {
                // std::cout << "died here" << '\n';
        return false;
    }

    // New session cannot impede on old
    for (const Session& s : sessions) {
        if (s.overlaps(newSession)) {
        //   std::cout << "died here1" << '\n';
            return false;
        }
    }
    sessions.insert(newSession);
    return true;
}

// Add new Session to Event. Returns true if addition was successful.
bool Event::addSession(int startDay, int startMonth, int startYear, int startHour, int startMinute, int endDay, int endMonth, int endYear, int endHour, int endMinute) {
    //std::cout << "made it to 1" << '\n';
    Time start(startDay, startMonth, startYear, startHour, startMinute);
    Time end(endDay, endMonth, endYear, endHour, endMinute);
    return addSession(start, end);
}

// void Event::addTasks() { //modified
//     bool looper = false;
//     do { //modified
//         looper = false;
//         cout << "What task(s) do you want attendee(s) to complete? (To add a task, write a task and press Enter). (Enter 0 to stop adding task.)" << endl;
//         int start = 1;
//         string task;
//         while (start) {
//             do {
//                 getline(cin, task, '\n');
//             } while (task == "");
//
//             if (task == "0") {
//                 start = 0; break;
//             }
//             eventTask.push_back(task);
// 	    taskTaken.push_back(task);
//         }
//     } while (looper == true);
// }
//
// void Event::acceptTask(string attendee) { //modified
//     Task acceptTask;
//     bool looper2 = false;
//     acceptTask.guestName = attendee;
//     do {
//         looper2 = false;
//         cout << "Here are the list of tasks for this event." << endl;
//         int numberofTasks = taskTaken.size();
//         if (numberofTasks == 0){
//         	cout << "All the tasks are already taken." << endl;
//        	}
//        else {
//            	for (int i = 0; i < taskTaken.size(); i++) {
//              		cout << (i+1) << ". " << taskTaken[i] << "  ";
//       	}
//        	cout << endl;
//        	cout << "What task(s) do you want to complete? (To add a task, write the task number and press Enter). (Enter 0 to stop adding task.)" << endl;
//         int start = 1;
//         int task;
//         int countTask = 0;
//        	int trackIndex = 0;
//        	int index;
//        	while (start) {
//        		while (!(cin >> task)) {
//         		cout << "Enter a number." << endl;
//         		cin.clear();
//         		cin.ignore(numeric_limits<streamsize>::max(), '\n');
//         	}
//             	if (task == 0) {
//               		start = 0;
//             	}
//            	else if (task > numberofTasks || task < 0) {
//              		cout << "Enter the correct task number." << endl;
//            	}
//            	else {
//           		index = task - trackIndex - 1;
//               		acceptTask.taskAccepted.push_back(task);
//           		taskTaken.erase(taskTaken.begin() + (index));
//               		countTask++;
//           		trackIndex++;
//            	}
//            	if (countTask == numberofTasks) {
//              		start = 0;
//            	}
//          	}
//      	}
//  } while(looper2 == true);
//  acceptedTask.push_back(acceptTask);
// }
