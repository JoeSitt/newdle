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

Event::Event(std::string name): name(name) {}

std::string Event::getTaskSummary() const {
    return "";  // TEMP
}

// Add attendee at the requested date and time. Returns true if addition was successful.
bool Event::addAttendee(int day, int month, int year, int hour, int minute, const std::string& attendee) {
    Time this_time(day, month, year, hour, minute);
    std::set<Session> new_sessions;

    for (const Session& s : sessions) {
        Session new_sess(s);
        if (s.contains(this_time)) {
            new_sess.RSVP(this_time, attendee);
        }
        new_sessions.insert(new_sess);
    }

    sessions = new_sessions;
    return false;
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
    outStr += getTaskSummary();

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
bool Event::addSession(int startDay, int startMonth, int startYear, int startHour, int startMinute, int endDay, int endMonth, int endYear, int endHour, int endMinute) {
    //std::cout << "made it to 1" << '\n';
    Time start(startDay, startMonth, startYear, startHour, startMinute);
    Time end(endDay, endMonth, endYear, endHour, endMinute);
    Session newSession(start, end);
    //std::cout << "made it to 2" << '\n';
    // New session must have valid (non overlapping) times
    if (!(start < end)) {
                std::cout << "died here" << '\n';
        return false;
    }

    // New session cannot impede on old
    for (const Session& s : sessions) {
        if (s.overlaps(newSession)) {
          std::cout << "died here1" << '\n';
            return false;
        }
    }
//std::cout << "made it to 3" << '\n';
    sessions.insert(newSession);
    //std::cout << "made it out" << '\n';
    return true;
}

void Event::addTasks() { //modified
    bool looper = false;
    do { //modified
        looper = false;
        cout << "What task(s) do you want attendee(s) to complete? (To add a task, write a task and press Enter). (Enter 0 to stop adding task.)" << endl;
        int start = 1;
        string task;
        while (start) {
            do {
                getline(cin, task, '\n');
            } while (task == "");

            if (task == "0") {
                start = 0; break;
            }
            eventTask.push_back(task);
	    taskTaken.push_back(task);
        }
    } while (looper == true);
}

void Event::acceptTask(string attendee) { //modified
    Task acceptTask;
    bool looper2 = false;
    acceptTask.guestName = attendee;
    do {
        looper2 = false;
        cout << "Here are the list of tasks for this event." << endl;
        int numberofTasks = taskTaken.size();
        if (numberofTasks == 0){
        	cout << "All the tasks are already taken." << endl;
       	}
       else {
           	for (int i = 0; i < taskTaken.size(); i++) {
             		cout << (i+1) << ". " << taskTaken[i] << "  ";
      	}
       	cout << endl;
       	cout << "What task(s) do you want to complete? (To add a task, write the task number and press Enter). (Enter 0 to stop adding task.)" << endl;
        int start = 1;
        int task;
        int countTask = 0;
       	int trackIndex = 0;
       	int index;
       	while (start) {
       		while (!(cin >> task)) {
        		cout << "Enter a number." << endl;
        		cin.clear();
        		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	}
            	if (task == 0) {
              		start = 0;
            	}
           	else if (task > numberofTasks || task < 0) {
             		cout << "Enter the correct task number." << endl;
           	}
           	else {
          		index = task - trackIndex - 1;
              		acceptTask.taskAccepted.push_back(task);
          		taskTaken.erase(taskTaken.begin() + (index));
              		countTask++;
          		trackIndex++;
           	}
           	if (countTask == numberofTasks) {
             		start = 0;
           	}
         	}
     	}
 } while(looper2 == true);
 acceptedTask.push_back(acceptTask);
}


// Event::Event() {}
//
// Event::Event(string name, string creator, string start_time, string end_time, string date, vector<string> tasks) : e_name(name), e_creator(creator), e_start_time(start_time), e_end_time(end_time), e_date(date), eventTask(tasks) //modified
// {
//   //initialize the vector pointers
//   e_timeslots = new vector<TimeSlot*>();
//   e_attendees = new vector<string>();
//   taskTaken = eventTask; //modified
//
//   //convert times to digital double from string format
//   e_digi_start = convert_time(e_start_time);
//   e_digi_end = convert_time(e_end_time);
//
//   //calculate no. of timeslots
//   e_number_of_timeslots = (e_digi_end - e_digi_start)/0.5;
//   e_attendees->push_back(e_creator);
//   for(int i=0; i<e_number_of_timeslots; i++){
//     //for each timeslot, create the timeslot object pointer
//     e_timeslots->push_back(new TimeSlot(creator));
//   }
// }
//
// Event::Event(string name, string creator, string start_time, string end_time, string date) : e_name(name), e_creator(creator), e_start_time(start_time), e_end_time(end_time), e_date(date)
// {
//   //initialize the vector pointers
//   e_timeslots = new vector<TimeSlot*>();
//   e_attendees = new vector<string>();
//
//   //convert times to digital double from string format
//   e_digi_start = convert_time(e_start_time);
//   e_digi_end = convert_time(e_end_time);
//
//   //calculate no. of timeslots
//   e_number_of_timeslots = (e_digi_end - e_digi_start)/0.5;
//   e_attendees->push_back(e_creator);
//   for(int i=0; i<e_number_of_timeslots; i++){
//     //for each timeslot, create the timeslot object pointer
//     e_timeslots->push_back(new TimeSlot(creator));
//   }
// }
//
// Event::~Event()
// {
//   for(int i=0; i < e_timeslots->size(); i++){
//     delete e_timeslots->at(i);
//   }
//
//   delete e_timeslots;
//   delete e_attendees;
// }
//
//
// void Event::addAttendee(string name, string arrival_time, string leave_time, Task accepted_Task) //modified
// {
//   e_attendees->push_back(name);
//   acceptedTask.push_back(accepted_Task); //modified
//
//   double digi_arrival = convert_time(arrival_time);
//   double digi_leave = convert_time(leave_time);
//   int num_slots = (digi_leave - digi_arrival)/0.5;
//
//   int start_index = (digi_arrival - e_digi_start)/0.5;
//
//   for(int i=0; i < num_slots; i++){
//     e_timeslots->at(start_index)->addPerson(name);
//     start_index++;
//   }
// }
//
// void Event::addAttendee(string name, string arrival_time, string leave_time)
// {
//   e_attendees->push_back(name);
//   double digi_arrival = convert_time(arrival_time);
//   double digi_leave = convert_time(leave_time);
//   int num_slots = (digi_leave - digi_arrival)/0.5;
//
//   int start_index = (digi_arrival - e_digi_start)/0.5;
//
//   // TEMP
//   cout << "e_digi_start: " << e_digi_start << endl;
//   cout << "digi_arrival: " << digi_arrival << endl;
//   cout << "digi_leave: " << digi_leave << endl;
//   cout << "num_slots: " << num_slots << endl;
//   cout << "start_index: " << start_index << endl;
//
//   for(int i=0; i < num_slots; i++){
//     e_timeslots->at(start_index)->addPerson(name);
//     start_index++;
//   }
// }
//
// double Event::convert_time(string atime)
// {
//   int tmp = stoi(atime);
//   double tmp2 = tmp;
//   tmp2 = tmp2/100;
//   double tmp3 = round(tmp2);
//   if(tmp2>tmp3){
//     tmp2 = tmp3 + 0.5;
//   }
//
//   return(tmp2);
// }
//
// string Event::convert_to_string(double atime){
//   string f;
//   if(atime < 10){
//     //if less than 10, then first two characters are 0 and first digit of double
//     int temp = floor(atime);
//     string tmp2 = to_string(temp);
//     f = "0"+tmp2;
//   }
//   else{
//     int tmp = floor(atime);
//     f = to_string(tmp);
//   }
//
//
//   int j = floor(atime);
//   //if the double ends in 0.5, then there's a :30
//   if( (atime - j) > 0){
//     f = f+"30";
//   }
//   else{
//     f = f+"00";
//   }
//
//   return(f);
// }
//
// string Event::getEventName()
// {
//   return(e_name);
// }
//
// string Event::getEventCreator()
// {
//   return(e_creator);
// }
//
// string Event::getEventStartTime()
// {
//   return(e_start_time);
// }
//
// string Event::getEventEndTime()
// {
//   return(e_end_time);
// }
//
// string Event::getEventDate()
// {
//   return(e_date);
// }
//
// int Event::getAttendance(string start_time)
// {
//   //find the start time of the timeslot in question
//   double digi_arrival = convert_time(start_time);
//   int start_index = (digi_arrival- e_digi_start)/0.5;
//
//   //get the number of attendees for that timeslot
//   int num = e_timeslots->at(start_index)->getNumberOfAttendees();
//
//   return(num);
// }
//
// vector<vector<string>> Event::getAttendees()
// {
//   //output vector
//   vector<vector<string>> output;
//
//   for(int i=0; i < e_attendees->size(); i++){
//     //for each attendee
//     string name = e_attendees->at(i);
//     vector<string> list;
//     //attendee name is index 0 for each vector
//     list.push_back(name);
//
//     for(int j=0; j < e_timeslots->size(); j++){
//       //for each timeslot check if the person's name is included
//       if(e_timeslots->at(j)->doesAttend(name)){
//         //calculate the starting time for the timeslot and convert to string
//         double tmp = e_digi_start + (j * 0.5);
//         string time_to_store = convert_to_string(tmp);
//
//         //add timeslot to the vector
//         list.push_back(time_to_store);
//       }
//     }
//
//     //pushing vector for an attendee containing all their available times
//     output.push_back(list);
//   }
//
//   return(output);
// }
//
// void Event::addTasks(string taskName) { //modified
// 	eventTask.push_back(taskName);
// }
