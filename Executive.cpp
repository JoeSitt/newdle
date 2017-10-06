/**
*	@file Executive.cpp
*	@author Ferocious Hammerheads
*	@date
*	@brief Executive functions
*/

#include "Executive.h"


void Executive::clean(){
  for (int i = 0; i < 101; i++) {
      cout << "\n";
  }
}

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
  string mode;
  bool looper = true;
  string temp;
  clean();
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
      clean();
      cout << "Invalid input, please put '0' or '1'"<<'\n';
      looper = true;
    }
  } while(looper == true);
  clean();
  do {//propts user for admin or attendee mode
    cout << "Enter the number for the desired mode:\n1) Admin Mode\n2) Attendee Mode\n3) Exit Newdle\n";
    looper = true;
    cin >> mode;
    if(mode == "1")//sends user to correct mode
    {
      clean();
      adminMode();
    }
    else if(mode == "2")
    {
      clean();
      attendeeMode();
    }
    else if(mode == "3")
    {
      clean();
      cout << "Thank you for using Newdle!\n";
      looper = false;
    }
    else //checks if input is valid, if not asks for new input
    {
      clean();
      cout << "Invalid input:"<<mode<<"\n";
    }
  } while(looper == true);
}


void Executive::adminMode()
{
  string adminChoice;
  bool looper = true;
  clean();
  do {//propts user to add event or check status or exit
    cout << "Enter the number for action you would like to do:\n1) Create event\n2) Check attendance list of an event\n3) Exit Admin Mode\n";
    looper = true;
    cin >> adminChoice;
    if(adminChoice == "1")//sends user to correct action
    {
      //create event
        clean();
      addEvent();
    }
    else if(adminChoice == "2")
    {
      //check attendees of event
        clean();
      checkAttendance();
    }
    else if(adminChoice == "3")
    {
      clean();
      cout << "Exiting Admin Mode\n";
      looper = false; //only way to exit Admin Mode
    }
    else //checks if input is valid, if not asks for new input
    {
      clean();
      cout << "Invalid input: "<<adminChoice<<"\n";
    }
  } while(looper == true);
}

void Executive::attendeeMode()
{
  bool looper = true;
  do {
    std::cout << "Current events:" << '\n';
    getEventList();//shows list of events
    looper = true;
    int eventChoice=-1;
    string input;
    //Prompts which event to select
    cout << "Enter the number for the event you would like to attend(0 to exit):\n";
    cin >> input;
    //cout<<input<<" \n";
    try{
    eventChoice=std::stoi( input );
    }
    catch (std::invalid_argument& e){

    }

    if(eventChoice > calendar.size() || eventChoice < 0)//checks if input is valid
    {
        clean();
      cout << "There is no event with that number, please try again:\n";
    }
    else if(eventChoice == 0)
    {
        clean();
      cout << "Exiting Attendee Mode:\n";
      looper = false;
    }
    else
    {
      clean();
      string arriveTime;
      string arriveTime12;
      string leaveTime;
      string leaveTime12;
      string attendeeName;
      bool looper2 = false;
      do {//loops for start time till it is valid
        looper2 = false;
        if(twelveHourMode == true)
        {//switches inputs and outputs to 12 hour mode
          cout << calendar[eventChoice - 1]->getEventName() << " takes place between " << talid->changeTo12Hour(calendar[eventChoice - 1]->getEventStartTime()) << " and " << talid->changeTo12Hour(calendar[eventChoice - 1]->getEventEndTime());
          cout << ". What time will you arrive?(Intervals are 30 mins, please use this format: 8:30PM )\n";
          cin >> arriveTime12;
          if(talid->isValidTime12Hour(arriveTime12))//error checks
          {
            arriveTime12=talid->fix12Hr(arriveTime12);
            arriveTime = talid->changeTo24Hour(arriveTime12);
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
          cout<<"If your Arival time is "<<arriveTime12<<",\n";
          cout << "What time would you like to leave?(Intervals are 30 mins, please use this format: 8:30PM )\n";
          cin >> leaveTime12;
          if(talid->isValidTimeSlots12Hour(talid->changeTo24Hour(arriveTime), leaveTime12))
          {
            leaveTime12=talid->fix12Hr(leaveTime12);
            leaveTime = talid->changeTo24Hour(leaveTime12);
            if(leaveTime < calendar[eventChoice - 1]->getEventStartTime() || leaveTime >  calendar[eventChoice - 1]->getEventEndTime() || !talid->isValidTimeSlots(arriveTime,leaveTime))
            {
              cout << "Invalid leaving time, please try a different time:\n";
              cout<<"Arival time: "<<arriveTime;
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
          cout<<"If your Arival time is "<<arriveTime<<",\n";
          cout << "What time would you like to leave?(Intervals are 30 mins, please use military time)\n";
          cin >> leaveTime;
          if(leaveTime < calendar[eventChoice - 1]->getEventStartTime() || leaveTime >  calendar[eventChoice - 1]->getEventEndTime() || !talid->isValidTimeSlots(arriveTime,leaveTime))
          {
            cout << "Invalid leaving time, please try a different time:\n";
            looper2 = true;
          }
          clean();
        }
      } while(looper2 == true);
      if (twelveHourMode) {
        cout<<"If your Arival time is "<<arriveTime12<<" and you're leaving at "<<leaveTime12<<",\n";
      }else{
        cout<<"If your Arival time is "<<arriveTime<<" and you're leaving at "<<leaveTime<<",\n";
      }
      cout << "What is the name you would like to RSVP with?\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      getline (cin,attendeeName);
      calendar[eventChoice - 1]->addAttendee(attendeeName, arriveTime, leaveTime); //adds attendee to event
      clean();
      cout << "You have been added as an attendee to the event.\n\n\n";
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
    cout << "What month would you like the event?(format as the three letter abreviation in all caps)\n"<<"Example January = \"JAN\"";
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
      cout << "What time would you like the event to start?(format as 12 hour time. Example, 2:00PM)\n";
      cin >> startTime;
      if(talid->isValidTime12Hour(startTime))
      {
        startTime=talid->fix12Hr(startTime);
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
      cout << "What time would you like the event to start?(format as military time. Example, 2:00PM would be 1400)\n";
      cin >> startTime;
      if (startTime.size()==3) {
        startTime='0'+startTime;
      }
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
      cout << "What time would you like the event to end?(format as 12 hour time. Example, 2:00PM)\n";
      cin >> endTime;
      if(talid->isValidTimeSlots12Hour(talid->changeTo12Hour(startTime),endTime))
      {
        endTime=talid->fix12Hr(endTime);
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
      cout << "What time would you like the event to end?(format as military time. Example, 2:00PM would be 1400)\n";
      cin >> endTime;
      if (endTime.size()==3) {
        endTime='0'+endTime;
      }
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
  cout << "Event: "<<eventName<<" created";
  calendar.push_back(toAdd); //adds event to back of calendar vector
  cout << "Event has been created.\n";
}


// TODO: show all of the attendiess and times, then give the option to search?-Js
void Executive::checkAttendance()
{
  bool looper = true;
  int eventChoice;
  string checkTime;
  do {//takes in and checks event name
    getEventList();
    cout << "Enter the number for the event you would like to check attendance for:(0 to exit)\n";
    cin >> eventChoice;
    clean();
    if(eventChoice > calendar.size() || eventChoice < 0)
    {
      looper = true;
      cout << "That event is not currently in our calendar, please try another event:\n\n\n";
    }
    else if(eventChoice == 0)
    {
      cout << "Exiting Attendance Check.\n";
      looper = false;
    }
    else
    {
      bool looper2 = false;
      for(int i=0; i < calendar[eventChoice - 1]->e_attendees->size(); i++){
        //for each attendee
        string name = calendar[eventChoice - 1]->e_attendees->at(i);
        std::cout << name<<" is attending" << '\n';
        vector<string> list;
        //attendee name is index 0 for each vector
        list.push_back(name);
      }
      do {//take in and check time
        looper2 = false;
        if(twelveHourMode == true)
        {
        //  calendar[eventChoice - 1]->getAttendees();

          for(int i=0; i < calendar[eventChoice - 1]->e_attendees->size(); i++){
            //for each attendee
            string name = calendar[eventChoice - 1]->e_attendees->at(i);
            std::cout << name<<" is attending" << '\n';
            vector<string> list;
            //attendee name is index 0 for each vector
            list.push_back(name);
          }

          cout << calendar[eventChoice - 1]->getEventName() << " takes place between " << talid->changeTo12Hour(calendar[eventChoice - 1]->getEventStartTime()) << " and " << talid->changeTo12Hour(calendar[eventChoice - 1]->getEventEndTime());
          cout << ". What time would you like to check the attendance for?(Intervals are 30 mins, please format as 12 hour time. Example, 2:00PM)\n";
          cin >> checkTime;
          if(talid->isValidTime12Hour(checkTime))
          {
            checkTime=talid->fix12Hr(checkTime);
            checkTime = talid->changeTo12Hour(checkTime);
            if(checkTime < calendar[eventChoice - 1]->getEventStartTime() || checkTime >=  calendar[eventChoice - 1]->getEventEndTime() || !talid->isValidTime(checkTime))
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




          //calendar[eventChoice - 1]->getAttendees();
          cout << calendar[eventChoice - 1]->getEventName() << " takes place between " << calendar[eventChoice - 1]->getEventStartTime() << " and " << calendar[eventChoice - 1]->getEventEndTime();
          cout << ". What time would you like to check the attendance for?(Intervals are 30 mins, please use military time)\n";
          cin >> checkTime;
          if (checkTime.size()==3) {
            checkTime='0'+checkTime;
          }
          if(checkTime < calendar[eventChoice - 1]->getEventStartTime() || checkTime >=  calendar[eventChoice - 1]->getEventEndTime() || !talid->isValidTime(checkTime))
          {
            cout << "Invalid time, please try a different time:\n";
            looper2 = true;
          }
        }
      } while(looper2 == true);
      if (calendar[eventChoice - 1]->getAttendance(checkTime)==1) {
        cout << calendar[eventChoice - 1]->getAttendance(checkTime) << " person is attending at the given time.\n";
      }else{
      cout << calendar[eventChoice - 1]->getAttendance(checkTime) << " people are attending at the given time.\n"; //displayes attendance for that time
      }
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
