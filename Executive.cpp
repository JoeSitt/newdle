#include <iostream>
#include <vector>
#include <string>
#include "Executive.h"
#include "Event.h"
#include "Valid.h"
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
  int mode = 0;
  bool looper = true;
  do {
    //propts user for desired mode
    std::cout << "Enter the number for the desired mode:\n1) Admin Mode\n2) Attendee Mode\n3) Exit Newdle\n";
    looper = true;
    std::cin >> mode;
    if(mode == 1)//sends user to correct mode
    {
      adminMode();
    }
    else if(mode == 2)
    {
      attendeeMode();
    }
    else if(mode == 3)
    {
      std::cout << "Thank you for using Newdle!\n";
      looper = false
    }
    else //checks if input is valid, if not asks for new input
    {
      std::cout << "Invalid input:\n";
    }
  } while(looper == true);
}
void Executive::adminMode()
{
  int adminChoice = 0;
  bool looper = true;
  do {
    //propts user to add event or check status or exit
    std::cout << "Enter the number for action you would like to do:\n1) Create event\n2) Check attendance list of an event\n3) Exit Admin Mode\n";
    looper = true;
    std::cin >> adminChoice;
    if(adminChoice == 1)//sends user to correct action
    {
      //create event
      std::string eventName = "";
      std::string eventName = "";
      std::string eventName = "";
      std::string eventName = "";
      std::string eventName = "";
      std::cout << "";
    }
    else if(adminChoice == 2)
    {
      //check attendees of event
    }
    else if(adminChoice == 3)
    {
      std::cout << "Exiting Admin Mode\n";
      looper = false; //only way to exit Admin Mode
    }
    else //checks if input is valid, if not asks for new input
    {
      std::cout << "Invalid input:\n";
    }
  } while(looper == true);
}
void Executive::attendeeMode()
{
  getEventList();
  //shows list of events
  //Prompts which event to select
  //ask what time they are available
  //adds user to event
  //loops till they want to exit
}
bool Executive::addEvent(std::string eventName, std::string date, std::string startTime,std::string endTime,std::string eventCreator)
{
  Valid.isValidDate(date);
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
void Executive::getEventList();
{
  //displays event list
}
