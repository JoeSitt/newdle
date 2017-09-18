/**
*	@file Executive.cpp
*	@author Ferocious Hammerheads
*	@date
*	@brief Executive functions
*/

#include "Executive.h"

Executive::Executive()
{
  //initialize valid anf filehandler
   talid = new Valid();
   fileHandle = new FileHandler();
  //calls filehandler to remake calendar from file
  fileHandle->openFile(calendar);
}


Executive::~Executive()
{
  //calls filehandler to write to file
  fileHandle->saveFile(calendar);
  //cleans up calendar
  for( int i = 0 ; i < calendar.size(); i++)
   delete calendar[i];
}


void Executive::run()
{
  int mode = 0;
  bool looper = true;
  string temp;
  do {//prompts dor 12 or 24 hour mode
    looper = false;
    cout << "Enter 0 for 24 hour clock mode or 1 for 12 hour clock mode:\n";
    cin >> temp;
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
      cout << "Invalid input, please put '0' or '1'";
      looper = true;
    }
  } while(looper == true);
  do {//propts user for admin or attendee mode
    cout << "Enter the number for the desired mode:\n1) Admin Mode\n2) Attendee Mode\n3) Exit Newdle\n";
    looper = true;
    cin >> mode;
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
      cout << "Thank you for using Newdle!\n";
      looper = false;
    }
    else //checks if input is valid, if not asks for new input
    {
      cout << "Invalid input:\n";
    }
  } while(looper == true);
}


void Executive::adminMode()
{
  int adminChoice = 0;
  bool looper = true;
  do {//propts user to add event or check status or exit
    cout << "Enter the number for action you would like to do:\n1) Create event\n2) Check attendance list of an event\n3) Exit Admin Mode\n";
    looper = true;
    cin >> adminChoice;
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
      cout << "Exiting Admin Mode\n";
      looper = false; //only way to exit Admin Mode
    }
    else //checks if input is valid, if not asks for new input
    {
      cout << "Invalid input:\n";
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
    cout << "Enter the number for the event you would like to attend(0 to exit):\n";
    cin >> eventChoice;
    if(eventChoice > calendar.size() || eventChoice < 0)//checks if input is valid
    {
      cout << "There is no event with that number, please try again:\n";
    }
    else if(eventChoice == 0)
    {
      cout << "Exiting Attendee Mode:\n";
      looper = false;
    }
    else
    {
      string arriveTime;
      string leaveTime;
      string attendeeName;
      bool looper2 = false;
      do {//loops for start time till it is valid
        looper2 = false;
        if(twelveHourMode == true)
        {//switches inputs and outputs to 12 hour mode
          cout << calendar[eventChoice - 1]->getEventName() << " takes place between " << talid->changeTo12Hour(calendar[eventChoice - 1]->getEventStartTime()) << " and " << talid->changeTo12Hour(calendar[eventChoice - 1]->getEventEndTime());
          cout << ". What time will you arrive?(Intervals are 30 mins, please use this format: 8:30PM )\n";
          cin >> arriveTime;
          if(talid->isValidTime12Hour(arriveTime))//error checks
          {
            arriveTime = talid->changeTo24Hour(arriveTime);
            if(arriveTime < calendar[eventChoice - 1]->getEventStartTime() || arriveTime >  calendar[eventChoice - 1]->getEventEndTime() || !talid->isValidTime(arriveTime))
            {
              cout << "Invalid arrival time, please try a different time:\n";
              looper2 = true;
            }
          }
          else
          {
            cout << "Invalid arrival time, please try a different time:\n";
            looper2 = true;
          }
        }
        else
        {
          cout << calendar[eventChoice - 1]->getEventName() << " takes place between " << calendar[eventChoice - 1]->getEventStartTime() << " and " << calendar[eventChoice - 1]->getEventEndTime();
          cout << ". What time will you arrive?(Intervals are 30 mins, please use military time )\n";
          cin >> arriveTime;
          if(arriveTime < calendar[eventChoice - 1]->getEventStartTime() || arriveTime >  calendar[eventChoice - 1]->getEventEndTime() || !talid->isValidTime(arriveTime))
          {
            cout << "Invalid arrival time, please try a different time:\n";
            looper2 = true;
          }
        }
      } while(looper2 == true);
      do {//loops for leaving time until it is valid
        looper2 = false;
        if(twelveHourMode == true)
        {
          cout << "What time would you like to leave?(Intervals are 30 mins, please use this format: 8:30PM )\n";
          cin >> leaveTime;
          if(talid->isValidTimeSlots12Hour(talid->changeTo24Hour(arriveTime), leaveTime))
          {
            leaveTime = talid->changeTo24Hour(leaveTime);
            if(leaveTime < calendar[eventChoice - 1]->getEventStartTime() || leaveTime >  calendar[eventChoice - 1]->getEventEndTime() || !talid->isValidTimeSlots(arriveTime,leaveTime))
            {
              cout << "Invalid leaving time, please try a different time:\n";
              looper2 = true;
            }
          }
          else
          {
            cout << "Invalid leaving time, please try a different time:\n";
            looper2 = true;
          }
        }
        else
        {
          cout << "What time would you like to leave?(Intervals are 30 mins, please use military time)\n";
          cin >> leaveTime;
          if(leaveTime < calendar[eventChoice - 1]->getEventStartTime() || leaveTime >  calendar[eventChoice - 1]->getEventEndTime() || !talid->isValidTimeSlots(arriveTime,leaveTime))
          {
            cout << "Invalid leaving time, please try a different time:\n";
            looper2 = true;
          }
        }
      } while(looper2 == true);
      cout << "What is the name you would like to RSVP with?\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      getline (cin,attendeeName);
      calendar[eventChoice - 1]->addAttendee(attendeeName, arriveTime, leaveTime); //adds attendee to event
      cout << "You have been added as an attendee to the event.\n";
    }
  } while(looper == true);
}


void Executive::addEvent()
{
  string eventName = "";
  string date = "";
  string startTime = "";
  string endTime = "";
  string eventCreator = "";
  bool looper = false;
  cout << "What would you like to name the event?\n";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  getline (cin,eventName); //takes in event name
  do {//takes in and checks date
    string temp = "";
    looper = false;
    cout << "What month would you like the event?(format as the three letter abreviation in all caps)\n";
    cin >> date;
    transform(date.begin(), date.end(), date.begin(), ::toupper); //makes all letters upper case
    cout << "What day of the month would you like the event?(format as two digits)\n";
    cin >> temp;
    date = date + " " + temp + " ";//puts in pre determined format for date
    cout << "What year would you like the event?(format as four digits)\n";
     cin >> temp;
    date = date + temp;
    if(!talid->isValidDate(date))//checks if date is valid
    {
      looper = true;
      cout << "Invalid date, please try another date(check format):\n";
    }
  } while(looper == true);
  do {//takes in and checks start time
    looper = false;
    if(twelveHourMode == true)
    {
      cout << "What time would you like the event to start?(format as 12 hour time. Exeample, 2:00PM)\n";
      cin >> startTime;
      if(talid->isValidTime12Hour(startTime))
      {
        startTime = talid->changeTo24Hour(startTime);
        if(!talid->isValidTime(startTime))
        {
          looper = true;
          cout << "Invalid start time, please try another time:\n";
        }
      }
      else
      {
        cout << "Invalid start time, please try another time:\n";
        looper = true;
      }
    }
    else
    {//only enters if in 24 hour clock mode
      cout << "What time would you like the event to start?(format as military time. Exeample, 2:00PM would be 1400)\n";
      cin >> startTime;
      if(!talid->isValidTime(startTime))
      {
        looper = true;
        cout << "Invalid start time, please try another time:\n";
      }
    }
  } while(looper == true);
  do{//takes in and checks end time
    looper = false;
    if(twelveHourMode == true)
    {
      cout << "What time would you like the event to end?(format as 12 hour time. Exeample, 2:00PM)\n";
      cin >> endTime;
      if(talid->isValidTimeSlots12Hour(talid->changeTo12Hour(startTime),endTime))
      {
        endTime = talid->changeTo24Hour(endTime);
      }
      else
      {
        cout << "Invalid end time, please try another time:\n";
        looper = true;
      }
    }
    else
    {//takes in end time for event
      cout << "What time would you like the event to end?(format as military time. Exeample, 2:00PM would be 1400)\n";
      cin >> endTime;
      if(!talid->isValidTimeSlots(startTime,endTime))
      {
        looper = true;
        cout << "Invalid end time, please try another time:\n";
      }
    }
  } while(looper == true);
  cout << "What is your name so we can add you as an attendee?\n";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  getline (cin,eventCreator);
  cout << "Event creation";
  Event* toAdd =  new Event(eventName, eventCreator, startTime, endTime, date);
  cout << "Event created";
  calendar.push_back(toAdd); //adds event to back of calendar vector
  cout << "Event has been created.\n";
}


void Executive::checkAttendance()
{
  bool looper = true;
  int eventChoice;
  string checkTime;
  do {//takes in and checks event name
    getEventList();
    cout << "Enter the number for the event you would like to check attendance for:(0 to exit)\n";
    cin >> eventChoice;
    if(eventChoice > calendar.size() || eventChoice < 0)
    {
      looper = true;
      cout << "That event is not currently in our calendar, please try another event:\n";
    }
    else if(eventChoice == 0)
    {
      cout << "Exiting Attendance Check.\n";
      looper = false;
    }
    else
    {
      bool looper2 = false;
      do {//take in and check time
        if(twelveHourMode == true)
        {
          cout << calendar[eventChoice - 1]->getEventName() << " takes place between " << talid->changeTo12Hour(calendar[eventChoice - 1]->getEventStartTime()) << " and " << talid->changeTo12Hour(calendar[eventChoice - 1]->getEventEndTime());
          cout << ". What time would you like to check the attendance for?(Intervals are 30 mins, please format as 12 hour time. Exeample, 2:00PM)\n";
          cin >> checkTime;
          if(talid->isValidTime12Hour(checkTime))
          {
            checkTime = talid->changeTo12Hour(checkTime);
            if(checkTime < calendar[eventChoice - 1]->getEventStartTime() || checkTime >  calendar[eventChoice - 1]->getEventEndTime() || !talid->isValidTime(checkTime))
            {
              cout << "Invalid time, please try a different time:\n";
              looper2 = true;
            }
          }
          else
          {
            cout << "Invalid time, please try a different time:\n";
            looper2 = true;
          }
        }
        else
        {
          cout << calendar[eventChoice - 1]->getEventName() << " takes place between " << calendar[eventChoice - 1]->getEventStartTime() << " and " << calendar[eventChoice - 1]->getEventEndTime();
          cout << ". What time would you like to check the attendance for?(Intervals are 30 mins, please use military time)\n";
          cin >> checkTime;
          if(checkTime < calendar[eventChoice - 1]->getEventStartTime() || checkTime >  calendar[eventChoice - 1]->getEventEndTime() || !talid->isValidTime(checkTime))
          {
            cout << "Invalid time, please try a different time:\n";
            looper2 = true;
          }
        }
      } while(looper2 == true);
      cout << calendar[eventChoice - 1]->getAttendance(checkTime) << " people are attending at the given time.\n"; //displayes attendance for that time
    }
  } while(looper == true);
}


void Executive::getEventList()
{
  // displays event list
  for(int i = 0; i < calendar.size(); i++)
  {//cycles through the calendar vector
    cout << i+1 << ") " << calendar[i]->getEventName() << "  on " << calendar[i]->getEventDate() << "\n";
  }
}
