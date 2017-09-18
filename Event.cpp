#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

#include "Event.h"

Event::Event(string name, string creator, string start_time, string end_time, string date) : e_name(name), e_creator(creator), e_start_time(start_time), e_end_time(end_time), e_date(date)
{cout << "Event.cpp line 11\n" << endl;
  e_timeslots = new vector<TimeSlot*>();
  cout << "Convert start\n";
  e_digi_start = convert_time(start_time);
  cout << "Convert end\n";
  e_digi_end = convert_time(end_time);
  e_number_of_timeslots = (e_digi_end - e_digi_start)/0.5;
  e_attendees->push_back(creator);


  for(int i=0; i<e_number_of_timeslots; i++){
    cout << "=== The timeslot creator loop ===";
    e_timeslots->push_back(new TimeSlot(creator));
  }
}

Event::~Event()
{cout << "even.cpp line 24" << endl;
  for(int i=0; i < e_timeslots->size(); i++){
    delete e_timeslots->at(i);
  }

  delete e_timeslots;
  delete e_attendees;
}

void Event::addAttendee(string name, string arrival_time, string leave_time)
{cout << "event.cpp line 34" << endl;
  e_attendees->push_back(name);
  double digi_arrival = convert_time(arrival_time);
  double digi_leave = convert_time(leave_time);
  int num_slots = (digi_leave - digi_arrival)/0.5;

  int start_index = (digi_arrival - e_digi_start)/0.5;

  for(int i=0; i < num_slots; i++){
    e_timeslots->at(start_index)->addPerson(name);
    start_index++;
  }
}

double Event::convert_time(string atime)
{cout << "event.cpp line 49" << endl;
  double tmp2 = stoi(atime);cout << "event.cpp line 50" << endl;
  tmp2 = tmp2/100;cout << "event.cpp line 51" << endl;
  double tmp3 = round(tmp2);cout << "event.cpp line 51.5" << endl;
  if(tmp2>tmp3){cout << "event.cpp line 52" << endl;
    tmp2 = tmp3 + 0.5;cout << "event.cpp line 53" << endl;
  }

  cout << "return";
  return(tmp2);
}

string Event::convert_to_string(double atime){
  string f;cout << "event.cpp line 60" << endl;
  if(atime < 10){
    int temp = floor(atime);
    string tmp2 = to_string(temp);
    f = "0"+tmp2;
  }
  else{
    int tmp = floor(atime);
    f = to_string(tmp);
  }

  int j = floor(atime);
  if( (atime - j) > 0){
    f = f+"30";
  }
  else{
    f = f+"00";
  }

  return(f);
}

string Event::getEventName()
{cout << "event.cpp line 83" << endl;
  return(e_name);
}

string Event::getEventCreator()
{cout << "event.cpp line 88" << endl;
  return(e_creator);
}

string Event::getEventStartTime()
{cout << "event.cpp line 93" << endl;
  return(e_start_time);
}

string Event::getEventEndTime()
{cout << "event.cpp line 98" << endl;
  return(e_end_time);
}

string Event::getEventDate()
{cout << "event.cpp line 103" << endl;
  return(e_date);
}

int Event::getAttendance(string start_time)
{cout << "event.cpp line 108" << endl;
  double digi_arrival = convert_time(start_time);
  int start_index = (digi_arrival- e_digi_start)/0.5;

  int num = e_timeslots->at(start_index)->getNumberOfAttendees();

  return(num);
}

vector<vector<string>> Event::getAttendees()
{cout << "event.cpp line 118" << endl;
  vector<vector<string>> output;

  for(int i=0; i < e_attendees->size(); i++){
    string name = e_attendees->at(i);
    vector<string> list;
    list.push_back(name);

    for(double j=0; j < e_timeslots->size(); j++){
      if(e_timeslots->at(j)->doesAttend(name)){
        double tmp = e_digi_start + (j * 0.5);
        string time_to_store = convert_to_string(tmp);
        list.push_back(time_to_store);
      }
    }

    output.push_back(list);
  }

  return(output);
}
