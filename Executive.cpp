/**
*	@file Executive.cpp
*	@author Ferocious Hammerheads
*	@date
*	@brief Executive functions
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Executive.h"
#include "Event.h"
#include "Valid.h"
#include "FileHandler.h"

Executive::Executive()
{
  //creates vector of events
  calendar = new std::vector<Event>();
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
      addEvent();
    }
    else if(adminChoice == 2)
    {
      //check attendees of event
      checkAttendance();
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
  bool looper = true;
  do {
    getEventList();//shows list of events
    looper = true;
    int eventChoice = 0;
    //Prompts which event to select
    std::cout << "Enter the number for the event you would like to attend(0 to exit):\n";
    std::cin >> eventChoice;
    if(eventChoice > calendar.size() || eventChoice < 0)
    {
      std::cout << "There is no event with that number, please try again:\n";
    }
    else if(eventChoice == 0)
    {
      std::cout << "Exiting Attendee Mode:\n";
      looper = false;
    }
    else
    {
      std::string arriveTime;
      std::string leaveTime;
      std::string attendeeName;
      bool looper2 = false;
      do {
        looper2 = false;
        std::cout << calendar[eventChoice].getEventName() << " takes place between " << calendar[eventChoice].getStartTime() << " and " << calendar[eventChoice].getEndTime();
        std::cout << ". What time will you arrive?(Intervals are 30 mins, please use military time)\n";
        std::cin >> arriveTime;
        if(arriveTime < calendar[eventChoice].getStartTime() || arriveTime >  calendar[eventChoice].getEndTime() || !Valid.isValidTime(arriveTime))
        {
          std::cout << "Invalid arrival time, please try a different time:\n";
          looper2 = true;
        }
      } while(looper2 == true);
      do {
        looper2 = false;
        std::cout << "What time would you like to leave?(Intervals are 30 mins, please use military time)\n";
        std::cin >> leaveTime;
        if(leaveTime < calendar[eventChoice].getStartTime() || leaveTime >  calendar[eventChoice].getEndTime() || !Valid.isValidTimeSlots(arriveTime,leaveTime))
        {
          std::cout << "Invalid leaving time, please try a different time:\n";
          looper2 = true;
        }
      } while(looper2 == true);
      std::cout << "What is the name you would like to RSVP with?\n";
      std::cin >> attendeeName;
      calendar[eventChoice].addAttendee(attendeeName, arriveTime, leaveTime);
      std::cout << "You have been added as an attendee to the event.\n";
    }
  } while(looper == true);
}
void Executive::addEvent()
{
  std::string eventName = "";
  std::string date = "";
  std::string startTime = "";
  std::string endTime = "";
  std::string eventCreator = "";
  bool looper = false;
  std::cout << "What would you like to name the event?\n";
  std::cin >> eventName;
  do {//takes in and checks date
    std::string temp = "";
    looper = false;
    std::cout << "What month would you like the event?(format as the three letter abreviation in all caps)\n";
    std::cin >> date;
    transform(date.begin(), date.end(), date.begin(), toupper);
    std::cout << "What day of the month would you like the event?(format as two digits)\n";
    date = " " + date + std::cin >> temp + " ";
    std::cout << "What year would you like the event?(format as four digits)\n";
    date = " " + date + std::cin >> temp + " ";
    if(!Valid.isValidDate(date))
    {
      looper = true;
      std::cout << "Invalid date, please try another one:\n";
    }
  } while(looper == true);
  do {//takes in and checks start time
    looper = false;
    std::cout << "What time would you like the event to start?(format as military time. Exeample, 2:00PM would be 1400)\n";
    std::cin >> startTime;
    if(!Valid.isValidTime(startTime))
    {
      looper = true;
      std::cout << "Invalid start time, please try another time:\n";
    }
  } while(looper == true);
  do{//takes in and checks end time
    looper = false;
    std::cout << "What time would you like the event to end?\n";
    std::cin >> endTime;
    if(!Valid.isValidTimeSlot(startTime,endTime))
    {
      looper = true;
      std::cout << "Invalid end time, please try another time:\n";
    }
  } while(looper == true);
  std::cout << "What is your name so we can add you as an attendee?\n";
  std::cin >> eventCreator;
  calendar.emplace_back(eventName, eventCreator, startTime, endTime, date);
  std::cout << "Event has been created.\n";
}
void Executive::checkAttendance()
{
  bool looper = true;
  int eventChoice;
  std::string checkTime;
  do {//takes in and checks event name
    getEventList();
    std::cout << "Enter the number for the event you would like to check attendance for:(0 to exit)\n";
    std::cin >> eventChoice;
    if(eventChoice > calendar.size() || eventChoice < 0)
    {
      looper = true;
      std::cout << "That event is not currently in our calendar, please try another event:\n";
    }
    else if(eventChoice == 0)
    {
      std::cout << "Exiting Attendance Check.\n";
      looper = false;
    }
    else
    {
      bool looper2 = false;
      do {//take in and check time
        std::cout << calendar[eventChoice].getEventName() << " takes place between " << calendar[eventChoice].getStartTime() << " and " << calendar[eventChoice].getEndTime();
        std::cout << ". What time would you like to check the attendance for?(Intervals are 30 mins, please use military time)\n";
        std::cin >> checkTime;
        if(checkTime < calendar[eventChoice].getStartTime() || checkTime >  calendar[eventChoice].getEndTime() || !Valid.isValidTime(checkTime))
        {
          std::cout << "Invalid time, please try a different time:\n";
          looper2 = true;
        }
      } while(looper2 == true);
      std::cout << calendar[eventChoice].getAttendance(checkTime) << " people are attending at the given time.\n";
    }
  } while(looper == true);
}
void Executive::getEventList();
{
  //displays event list
  for(int i = 1; i <= calendar.size(); i++)
  {
    std::cout << i << ") " << calendar[i].getEventName() << "\n";
  }
}
