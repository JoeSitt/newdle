#include <iostream>
#include <vector>
#include "Executive.h"
#include "Event.h"
#include "FileHandler.h"

Executive::Executive()
{
  //creates vector of events
  //calls filehandler to remake calendar from file
}
Executive::~Executive()
{
  //calls filehandler to write to file
}
void Executive::run()
{
  //prompts user for admin or attendee mode
}
void Executive::adminMode()
{
  //propts user to add event or check status
  //if add, create event object in event vector after geting event info from user
  //if check, asks what event name and time for attendee list
  //loop till they want to exit
}
void Executive::attendeeMode()
{
  //shows list of events
  //Prompts which event to select
  //ask what time they are available
  //adds user to event
  //loops till they want to exit
}
bool Executive::addEvent(eventName,startTime,endTime,eventCreator)
{
  //sends info to error checker class
  //if came back true, add event to calendar vector return true
  //if false, return false
}
bool Executive::checkAttendance(eventName,time)
{
  //send info to error checker class
  //if true, display attendees. return true
  //if false, return false
}
bool Executive::addAttendee(eventName,time,attendee)
{
  //send info to error checker class
  //if true, add attendee to event time return true
  //if false, return false
}
