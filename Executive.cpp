/**
*	@file Executive.cpp
*	@author Ferocious Hammerheads
*	@date
*	@brief Executive functions
*/

#include "Executive.h"

Executive::Executive()
{
  Valid* talid = new Valid;
  FileHandler* fileHandle = new FileHandler;
  //creates vector of events
  calendar = new std::vector<Event>();
  //calls filehandler to remake calendar from file
  fileHandle->openFile(calendar);
}


Executive::~Executive()
{
  //calls filehandler to write to file
  fileHandle->saveFile(calendar);
  for( int i = 0 ; i < calendar.size(); i++)
   delete calendar[i];
}


void Executive::run()
{
  int mode = 0;
  bool looper = true;
  std::string temp;
  do {
    looper = false;
    std::cout << "Enter 0 for 24 hour clock mode or 1 for 12 hour clock mode:\n";
    std::cin >> temp;
    if(temp == "0")
    {
      twelveHourMode = false;
    }
    else if(temp == "1")
    {
      twelveHourMode = true;
    }
    else
    {
      std::cout << "Invalid input, please put '0' or '1'";
      looper = true;
    }
  } while(looper == true);
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
      looper = false;
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
    if(eventChoice == 0)
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
        if(twelveHourMode == true)
        {
          std::cout << calendar[eventChoice - 1].getEventName() << " takes place between " << talid->changeTo12Hour(calendar[eventChoice - 1].getEventStartTime()) << " and " << talid->changeTo12Hour(calendar[eventChoice - 1].getEndTime());
          std::cout << ". What time will you arrive?(Intervals are 30 mins, please use this format: 8:30PM )\n";
          std::cin >> arriveTime;
          if(talid->isValidTime12Hour(arriveTime))
          {
            arriveTime = talid->changeTo24Hour(arriveTime);
            if(arriveTime < calendar[eventChoice - 1].getEventStartTime() || arriveTime >  calendar[eventChoice - 1].getEndTime() || !talid->isValidTime(arriveTime))
            {
              std::cout << "Invalid arrival time, please try a different time:\n";
              looper2 = true;
            }
          }
          else
          {
            std::cout << "Invalid arrival time, please try a different time:\n";
            looper2 = true;
          }
        }
        else
        {
          std::cout << calendar[eventChoice - 1].getEventName() << " takes place between " << calendar[eventChoice - 1].getEventStartTime() << " and " << calendar[eventChoice - 1].getEndTime();
          std::cout << ". What time will you arrive?(Intervals are 30 mins, please use military time )\n";
          std::cin >> arriveTime;
          if(arriveTime < calendar[eventChoice - 1].getEventStartTime() || arriveTime >  calendar[eventChoice - 1].getEndTime() || !talid->isValidTime(arriveTime))
          {
            std::cout << "Invalid arrival time, please try a different time:\n";
            looper2 = true;
          }
        }
      } while(looper2 == true);
      do {
        looper2 = false;
        if(twelveHourMode == true)
        {
          std::cout << "What time would you like to leave?(Intervals are 30 mins, please use this format: 8:30PM )\n";
          std::cin >> leaveTime;
          if(talid->isValidTimeSlots12Hour(talid->changeTo24Hour(arriveTime), leaveTime))
          {
            leaveTime = talid->changeTo24Hour(leaveTime);
            if(leaveTime < calendar[eventChoice - 1].getEventStartTime() || leaveTime >  calendar[eventChoice - 1].getEndTime() || !talid->isValidTimeSlots(arriveTime,leaveTime))
            {
              std::cout << "Invalid leaving time, please try a different time:\n";
              looper2 = true;
            }
          }
          else
          {
            std::cout << "Invalid leaving time, please try a different time:\n";
            looper2 = true;
          }
        }
        else
        {
          std::cout << "What time would you like to leave?(Intervals are 30 mins, please use military time)\n";
          std::cin >> leaveTime;
          if(leaveTime < calendar[eventChoice - 1].getEventStartTime() || leaveTime >  calendar[eventChoice - 1].getEndTime() || !talid->isValidTimeSlots(arriveTime,leaveTime))
          {
            std::cout << "Invalid leaving time, please try a different time:\n";
            looper2 = true;
          }
        }
      } while(looper2 == true);
      std::cout << "What is the name you would like to RSVP with?\n";
      std::cin >> attendeeName;
      calendar[eventChoice - 1].addAttendee(attendeeName, arriveTime, leaveTime);
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
    std::transform(date.begin(), date.end(), date.begin(), ::toupper);
    std::cout << "What day of the month would you like the event?(format as two digits)\n";
    std::cin >> temp;
    date = date + " " + temp + " ";
    std::cout << "What year would you like the event?(format as four digits)\n";
     std::cin >> temp;
    date = date + temp;
    if(!talid->isValidDate(date))
    {
      looper = true;
      std::cout << "Invalid date, please try another date(check format):\n";
    }
  } while(looper == true);
  do {//takes in and checks start time
    looper = false;
    if(twelveHourMode == true)
    {
      std::cout << "What time would you like the event to start?(format as 12 hour time. Exeample, 2:00PM)\n";
      std::cin >> startTime;
      if(talid->isValidTime12Hour(startTime))
      {
        startTime = talid->changeTo24Hour(startTime);
        if(!talid->isValidTime(startTime))
        {
          looper = true;
          std::cout << "Invalid start time, please try another time:\n";
        }
      }
      else
      {
        std::cout << "Invalid start time, please try another time:\n";
        looper = true;
      }
    }
    else
    {
      std::cout << "What time would you like the event to start?(format as military time. Exeample, 2:00PM would be 1400)\n";
      std::cin >> startTime;
      if(!talid->isValidTime(startTime))
      {
        looper = true;
        std::cout << "Invalid start time, please try another time:\n";
      }
    }
  } while(looper == true);
  do{//takes in and checks end time
    looper = false;
    if(twelveHourMode == true)
    {
      std::cout << "What time would you like the event to end?(format as 12 hour time. Exeample, 2:00PM)\n";
      std::cin >> endTime;
      if(talid->isValidTimeSlots12Hour(talid->changeTo12Hour(startTime),endTime))
      {
        endTime = talid->changeTo24Hour(endTime);
      }
      else
      {
        std::cout << "Invalid end time, please try another time:\n";
        looper = true;
      }
    }
    else
    {
      std::cout << "What time would you like the event to end?(format as military time. Exeample, 2:00PM would be 1400)\n";
      std::cin >> endTime;
      if(!talid->isValidTimeSlots(startTime,endTime))
      {
        looper = true;
        std::cout << "Invalid end time, please try another time:\n";
      }
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
     if(eventChoice == 0)
    {
      std::cout << "Exiting Attendance Check.\n";
      looper = false;
    }
    else
    {
      bool looper2 = false;
      do {//take in and check time
        if(twelveHourMode == true)
        {
          std::cout << calendar[eventChoice - 1].getEventName() << " takes place between " << talid->changeTo12Hour(calendar[eventChoice - 1].getEventStartTime()) << " and " << talid->changeTo12Hour(calendar[eventChoice - 1].getEndTime());
          std::cout << ". What time would you like to check the attendance for?(Intervals are 30 mins, please format as 12 hour time. Exeample, 2:00PM)\n";
          std::cin >> checkTime;
          if(talid->isValidTime12Hour(checkTime))
          {
            checkTime = talid->changeTo12Hour(checkTime);
            if(checkTime < calendar[eventChoice - 1].getEventStartTime() || checkTime >  calendar[eventChoice - 1].getEndTime() || !talid->isValidTime(checkTime))
            {
              std::cout << "Invalid time, please try a different time:\n";
              looper2 = true;
            }
          }
          else
          {
            std::cout << "Invalid time, please try a different time:\n";
            looper2 = true;
          }
        }
        else
        {
          std::cout << calendar[eventChoice - 1].getEventName() << " takes place between " << calendar[eventChoice - 1].getEventStartTime() << " and " << calendar[eventChoice - 1].getEndTime();
          std::cout << ". What time would you like to check the attendance for?(Intervals are 30 mins, please use military time)\n";
          std::cin >> checkTime;
          if(checkTime < calendar[eventChoice - 1].getEventStartTime() || checkTime >  calendar[eventChoice - 1].getEndTime() || !talid->isValidTime(checkTime))
          {
            std::cout << "Invalid time, please try a different time:\n";
            looper2 = true;
          }
        }
      } while(looper2 == true);
      std::cout << calendar[eventChoice - 1].getAttendance(checkTime) << " people are attending at the given time.\n";
    }
  } while(looper == true);
}


void Executive::getEventList()
{
  displays event list
  for(int i = 0; i < calendar.size(); i++)
  {
    std::cout << i+1 << ") " << calendar[i].getEventName() << "  on " << calendar[i].getEventDate() << "\n";
  }
}
