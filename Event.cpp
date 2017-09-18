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

Event::Event(string name, string creator, string start_time, string end_time, string date) : e_name(name), e_creator(creator), e_start_time(start_time), e_end_time(end_time), e_date(date)
{
  //initialize the vector pointers
  e_timeslots = new vector<TimeSlot*>();
  e_attendees = new vector<string>();

  //convert times to digital double from string format
  e_digi_start = convert_time(e_start_time);
  e_digi_end = convert_time(e_end_time);

  //calculate no. of timeslots
  e_number_of_timeslots = (e_digi_end - e_digi_start)/0.5;
  e_attendees->push_back(e_creator);
  for(int i=0; i<e_number_of_timeslots; i++){
    //for each timeslot, create the timeslot object pointer
    e_timeslots->push_back(new TimeSlot(creator));
  }
}

Event::~Event()
{
  for(int i=0; i < e_timeslots->size(); i++){
    delete e_timeslots->at(i);
  }

  delete e_timeslots;
  delete e_attendees;
}

void Event::addAttendee(string name, string arrival_time, string leave_time)
{
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
{
  int tmp = stoi(atime);
  double tmp2 = tmp;
  tmp2 = tmp2/100;
  double tmp3 = round(tmp2);
  if(tmp2>tmp3){
    tmp2 = tmp3 + 0.5;
  }

  return(tmp2);
}

string Event::convert_to_string(double atime){
  string f;
  if(atime < 10){
    //if less than 10, then first two characters are 0 and first digit of double
    int temp = floor(atime);
    string tmp2 = to_string(temp);
    f = "0"+tmp2;
  }
  else{
    int tmp = floor(atime);
    f = to_string(tmp);
  }


  int j = floor(atime);
  //if the double ends in 0.5, then there's a :30
  if( (atime - j) > 0){
    f = f+"30";
  }
  else{
    f = f+"00";
  }

  return(f);
}

string Event::getEventName()
{
  return(e_name);
}

string Event::getEventCreator()
{
  return(e_creator);
}

string Event::getEventStartTime()
{
  return(e_start_time);
}

string Event::getEventEndTime()
{
  return(e_end_time);
}

string Event::getEventDate()
{
  return(e_date);
}

int Event::getAttendance(string start_time)
{
  //find the start time of the timeslot in question
  double digi_arrival = convert_time(start_time);
  int start_index = (digi_arrival- e_digi_start)/0.5;

  //get the number of attendees for that timeslot
  int num = e_timeslots->at(start_index)->getNumberOfAttendees();

  return(num);
}

vector<vector<string>> Event::getAttendees()
{
  //output vector
  vector<vector<string>> output;

  for(int i=0; i < e_attendees->size(); i++){
    //for each attendee
    string name = e_attendees->at(i);
    vector<string> list;
    //attendee name is index 0 for each vector
    list.push_back(name);

    for(int j=0; j < e_timeslots->size(); j++){
      //for each timeslot check if the person's name is included
      if(e_timeslots->at(j)->doesAttend(name)){
        //calculate the starting time for the timeslot and convert to string
        double tmp = e_digi_start + (j * 0.5);
        string time_to_store = convert_to_string(tmp);

        //add timeslot to the vector
        list.push_back(time_to_store);
      }
    }

    //pushing vector for an attendee containing all their available times
    output.push_back(list);
  }

  return(output);
}
