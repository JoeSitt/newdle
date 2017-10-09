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
    // Initialize valid
    talid = new Valid();

    // Load save file if it exists
    if (ifstream("save.txt")) {
        Manager* m2 = Manager::getManager("save.txt");
        calendar = m2->events;
    }
}


Executive::~Executive()
{
    // Saves events to file
    Manager m;
    m.events = calendar;
    m.saveManager("save.txt");
    for( int i = 0 ; i < calendar.size(); i++) {
        delete calendar[i];
    }
}

void Executive::run()
{
  bool addSession(int startDay, int startMonth, int startYear, int startHour, int startMinute, int endDay, int endMonth, int endYear, int endHour, int endMinute);
  bool addAttendee(int day, int month, int year, int hour, int minute, const std::string& attendee);
    Event a("Party");
    a.addSession(1, 1, 1990, 9, 30, 1, 1, 1990, 11, 30);
    a.addAttendee(1, 1, 1990, 9, 30, "John");
    a.addAttendee(1, 1, 1990, 9, 30, "a");
    a.addAttendee(1, 1, 1990, 9, 30, "J");
    a.addAttendee(1, 1, 1990, 9, 30, "abigail");
    a.addAttendee(1, 1, 1990, 10, 30, "new");
    a.addAttendee(1, 1, 1990, 10, 0, "newer");

    a.addSession(1, 1, 20, 9, 30, 1, 1, 200, 11, 30);
    a.addAttendee(1, 1, 20, 9, 30, "John");
    a.addAttendee(1, 1, 20, 9, 30, "a");
    a.addAttendee(1, 1, 20, 9, 30, "J");
    a.addAttendee(1, 1, 20, 9, 30, "abigail");
    a.addAttendee(1, 1, 20, 10, 30, "new");
    a.addAttendee(1, 1, 20, 10, 0, "newer");
    std::cout << a.getAttendees(false) << std::endl;

  string mode;
  bool looper = true;
  string temp;
  clean();
  do {//prompts dor 12 or 24 hour mode
    looper = false;
    cout << "Enter 0 for 24 hour clock mode or 1 for 12 hour clock mode:\n";
    cin >> temp;
    if(temp == "0"||temp=="24")
    {
      twelveHourMode = false;
    }
    else if(temp == "1"||temp=="12")
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

void Executive::attendeeMode()
{
  Time d1,d2;
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
    { //calendar[eventChoice - 1]->getSessions(!twelveHourMode);
    //   std::cout << "which session would you like to attend?" << '\n';
    //   //getEventList();//shows list of events
    //   looper = true;
    //   int sessionChoice=-1;
    //   string input;
    //   //Prompts which event to select
    //   cout << "Enter the number for the event you would like to attend(0 to exit):\n";
    //   cin >> input;
    //   //cout<<input<<" \n";
    //   try{
    //   eventChoice=std::stoi( input );
    //   }
    //   catch (std::invalid_argument& e){
    //
    //   }
    //
    //   if(sessionChoice > calendar[eventChoice-1]->sessions.size() || sessionChoice < 0)//checks if input is valid
    //   {
    //       clean();
    //     cout << "There is no session with that number, please try again:\n";
    //   }
    //   clean();
      bool keeplooping=true;
      while(keeplooping){
      string arriveTime;
      string arriveTime12;
      string leaveTime;
      string leaveTime12;
      string attendeeName;
      Task acceptTask; //modified
      bool looper2 = false;
      do {//loops for start time till it is valid
        looper2 = false;
        if(twelveHourMode == true)
        {//switches inputs and outputs to 12 hour mode
          //cout << calendar[eventChoice - 1]->getEventName() << " takes place between " << talid->changeTo12Hour(calendar[eventChoice - 1]->getEventStartTime()) << " and " << talid->changeTo12Hour(calendar[eventChoice - 1]->getEventEndTime());
          std::cout << calendar[eventChoice - 1]->getAttendees(!twelveHourMode) << '\n';
          cout << ". What time will you arrive?(Intervals are 30 mins, please use this format: 8:30PM )\n";
          cin >> arriveTime12;
          if(talid->isValidTime12Hour(arriveTime12))//error checks
          {
            arriveTime12=talid->fix12Hr(arriveTime12);
            arriveTime = talid->changeTo24Hour(arriveTime12);
          //   if(arriveTime < calendar[eventChoice - 1]->getEventStartTime() || arriveTime >  calendar[eventChoice - 1]->getEventEndTime() || !talid->isValidTime(arriveTime))
          //   {
          //     cout << "Invalid arrival time, please try a different time:\n";
          //     looper2 = true;
          //   }
           }
          else
          {
            cout << "Invalid arrival time, please try a different time:\n";
            looper2 = true;
          }
        }
        else
        {
          std::cout << calendar[eventChoice - 1]->getAttendees(!twelveHourMode) << '\n';
          //cout << calendar[eventChoice - 1]->getEventName() << " takes place between " << calendar[eventChoice - 1]->getEventStartTime() << " and " << calendar[eventChoice - 1]->getEventEndTime();
          cout << ". What time will you arrive?(Intervals are 30 mins, please use military time )\n";
          cin >> arriveTime;
          if (arriveTime.size()==3) {
            arriveTime='0'+arriveTime;
          }
          if(/*arriveTime < calendar[eventChoice - 1]->getEventStartTime() || arriveTime >  calendar[eventChoice - 1]->getEventEndTime() ||*/ !talid->isValidTime(arriveTime))
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
          if(talid->isValidTime12Hour(leaveTime12))
          {
            leaveTime12=talid->fix12Hr(leaveTime12);
            leaveTime = talid->changeTo24Hour(leaveTime12);
            if(/*leaveTime < calendar[eventChoice - 1]->getEventStartTime() || leaveTime >  calendar[eventChoice - 1]->getEventEndTime() ||*/ !talid->isValidTime(leaveTime))
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
          if (leaveTime.size()==3) {
            leaveTime='0'+leaveTime;
          }
          if(/*leaveTime < calendar[eventChoice - 1]->getEventStartTime() || leaveTime >  calendar[eventChoice - 1]->getEventEndTime() || */!talid->isValidTime(leaveTime))
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

      string date = "";
      string date2 = "";
      string startTime = "";
      string endTime = "";
      bool looper = false;
      string m_month2;
      string m_day2;
      string m_year2;
      string m_month;
      string m_day;
      string m_year;
      bool datecompair=true;
      while (datecompair) {//runs until user makes end date and start take valid dates and start date is not greater than end date

        do {//takes in and checks date
            string temp = "";
            looper = false;
            bool dejavu=false;
            while (talid->monthtoint(date)==0) {
              if (dejavu) {
                std::cout << "That month was not in the correct format or not actually a month. please try again" << '\n';
              }
              cout << "What month would you like to show up to the event?(format as the three letter abreviation in all caps)\n"<<"Example January = \"JAN\"\n";
              cin >> date;
              dejavu=1;
              transform(date.begin(), date.end(), date.begin(), ::toupper);
            }

            //transform(date.begin(), date.end(), date.begin(), ::toupper); //makes all letters upper case
            cout << "What day of the month would you like to show up to the event?(format as two digits)\n";
            cin >> temp;
            m_day=temp;
            date = date + " " + temp + " ";//puts in pre determined format for date
            cout << "What year would you like to show up to the event?(format as four digits)\n";
             cin >> temp;
             m_year=temp;
            date = date + temp;
            if(!talid->isValidDate(date))//checks if date is valid
            {
              looper = true;
              cout << "Invalid date, please try another date(check format):\n";
            }
          }while (looper);
          do {//takes in and checks date
            string temp = "";
            looper = false;
            bool dejavu=false;
            while (talid->monthtoint(date2)==0) {
              if (dejavu) {
                std::cout << "That month was not in the correct format or not actually a month. please try again" << '\n';
              }
              cout << "What month would you like to leave the event?(format as the three letter abreviation in all caps)\n"<<"Example January = \"JAN\"";
              cin >> date2;
              dejavu=1;
              transform(date2.begin(), date2.end(), date2.begin(), ::toupper); //makes all letters upper case
            }



            cout << "What day of the month would you like to leave the event?(format as two digits)\n";
            cin >> temp;
            m_day2=temp;
            date2 = date2 + " " + temp + " ";//puts in pre determined format for date
             cout << "What year would you like to leave the event?(format as four digits)\n";
             cin >> temp;
             m_year2=temp;
            date2 = date2 + temp;
            if(!talid->isValidDate(date2))//checks if date is valid
            {
              looper = true;
              cout << "Invalid date, please try another date(check format):\n";
            }
        } while(looper == true);


    }
    string endHour1, endHour2, endHour3, endHour4;
    endHour1 = leaveTime[0]; endHour2 = leaveTime[1]; endHour3 = leaveTime[2]; endHour4 = leaveTime[3];
    string endHour=endHour1+endHour2;
    if (endHour1=="0") {
      endHour=endHour2;
    } //Why is string used like an array? What does the index represent? Go through it manually first.
    string startHour1, startHour2, startHour3, startHour4;
    startHour1 = arriveTime[0]; startHour2 = arriveTime[1]; startHour3 = arriveTime[2]; startHour4 = arriveTime[3];
    string startHour=startHour1+startHour2;
    if (startHour1=="0") {
      startHour=startHour2;
    }
    string endmin=endHour3+endHour4;
    if (endmin=="00"){
      endmin="0";
    }
    string startmin=startHour3+startHour4;
    if (startmin=="00"){
      startmin="0";
    }

    int smin,shour,ehour,emin,syear,eyear,sday,eday,smonth,emonth;
    smin=stoi(startmin);
    shour=stoi(startHour);

    emin=stoi(endmin);
    ehour=stoi(endHour);

    eday=stoi(m_day2);
    sday=stoi(m_day);

    syear=stoi(m_year);
    eyear=stoi(m_year2);

    smonth=talid->monthtoint(m_month);
    emonth=talid->monthtoint(m_month2);

        d1=Time(stoi(m_day), talid->monthtoint(m_month), stoi(m_year), shour, smin);
        d2=Time(stoi(m_day2), talid->monthtoint(m_month2), stoi(m_year2), ehour, emin);
        // Time d3;
        // if (emin==30) {
        //   d3=Time(stoi(m_day2), talid->monthtoint(m_month2), stoi(m_year2), ehour, 0);
        // }else if (ehour!=0) {
        //   d3=Time(stoi(m_day2), talid->monthtoint(m_month2), stoi(m_year2), ehour-1, 30);
        // }else if(eday!=1){
        //   d3=Time(stoi(m_day2)-1, talid->monthtoint(m_month2), stoi(m_year2), 23, 30);
        // }else{
        //   if(emonth==1){
        //     d3=Time(31, 12, stoi(m_year2)-1, 23, 30);
        //   }
        //   if(emonth==2||emonth==4||emonth==6||emonth==8||emonth==9||emonth==11){
        //     d3=Time(31, emonth-1, stoi(m_year2), 23, 30);
        //   }
        //   if(emonth==3){
        //     if(!talid->isLeapYear(eyear)){
        //     d3=Time(28, emonth-1, stoi(m_year2), 23, 30);
        //     }else{
        //     d3=Time(29, emonth-1, stoi(m_year2), 23, 30);
        //     }
        //   }
        //   if (emonth==5||emonth==7||emonth==10||emonth==12) {
        //     d3=Time(30, emonth-1, stoi(m_year2), 23, 30);
        //   }
        // }
        bool goodtimes=true;
        if(!(d1<d2)){
          std::cout << "that end time wont work" << '\n';
          goodtimes=false;
        }
        // if (!(d3<calendar[eventChoice-1]->sessions[sessionChoice-1]->end)) {
        //   std::cout << "that end time wont work as it is no longer in the session" << '\n';
        //   goodtimes=false;
        // }
        // if(uptime(d1)<calendar[eventChoice-1]->sessions[sessionChoice-1]->start){
        //   std::cout << "That start time wont work as it is oput side of the session" << '\n';
        //   goodtimes=false;
        // }
        if(goodtimes){
          keeplooping=false;
        }
      }
      string attendeeName;
      cout << "What is the name you would like to RSVP with?\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      getline (cin,attendeeName);
      calendar[eventChoice - 1]->acceptTask(attendeeName);

      while(d1<d2){
        calendar[eventChoice-1]->addAttendee(d1.day, d1.month, d1.year, d1.hour, d1.minute, attendeeName);
/*sessions[sessionChoice-1]->RSVP(d1, attendeeName);*/
        d1=uptime(d1);
      }
      //calendar[eventChoice - 1]->addAttendee(attendeeName, arriveTime, leaveTime, acceptTask); //adds attendee to event //modified
      clean();
      cout << "You have been added as an attendee to the event.\n\n\n";
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
        // std::cout << "not currently implemented press any button to continue" << '\n';
        // string d;
        // std::cin >> d;
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

void Executive::addEvent()
{
  string eventName = "";

  string eventCreator = "";
  vector<string> eTask; //modified

  bool looper = false;
  cout << "What would you like to name the event?\n";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  getline (cin,eventName); //takes in event name
  Event temp(eventName);
  bool keeplooping=true;
  do {
    temp=addSession(temp);
    std::cout << "would you like to keep adding sessions?(yes or no)" << '\n';
    string input;
    std::cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    if (input!="YES") {
      keeplooping=false;
    }
  } while(keeplooping);

  temp.addTasks();
  //cout << "What is your name so we can add you as an attendee?\n";
  //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  //getline (cin,eventCreator);
  //temp.addAttendee(int day, int month, int year, int hour, int minute, const std::string& attendee)
  cout << "Event creation";
  Event* toAdd =  &temp; //modified
  cout << "Event: "<<eventName<<" created\n";
  calendar.push_back(toAdd); //adds event to back of calendar vector
  cout << "Event has been added sucessfully.\n";
}


// TODO: show all of the attendiess and times, then give the option to search?-Js
void Executive::checkAttendance()
{
  bool looper = true;
  int eventChoice;
  string checkTime;
  std::cout << "made it in check" << '\n';
  do {//takes in and checks event name
    std::cout << "made it in the loop" << '\n';
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
    { cout<<calendar[eventChoice-1]->getAttendees(!twelveHourMode)<<"\n";

      }
  } while(looper == true);
}


void Executive::getEventList()
{
  // displays event list
  std::cout << "made it into getEventList" << '\n';
  for(int i = 0; i < calendar.size(); i++)
  {        // std::cout << "not currently implemented press any button to continue" << '\n';
        // string d;
        // std::cin >> d/cycles through the calendar vector
    cout << i+1 << ") " << calendar[i]->name;
    cout << "  on " << calendar[i]->getSessions(!twelveHourMode) << "\n";
  }
}

Event Executive::addSession(Event a){
  string eventCreator;
  cout << "What is your name so we can add you as an attendee?\n";
  //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  getline (cin,eventCreator);
  //a.addSession(12, 12,9999, 23, 00, 12, 12, 9999, 23, 30);
  //temp.addAttendee(int day, int month, int year, int hour, int minute, const std::string& attendee)
  bool datecompair=true;
  string date = "";
  string date2 = "";
  string startTime = "";
  string endTime = "";
  bool looper = false;
  string m_month2;
  string m_day2;
  string m_year2;
  string m_month;
  string m_day;
  string m_year;
  while (datecompair) {//runs until user makes end date and start take valid dates and start date is not greater than end date

    do {//takes in and checks date
        string temp = "";
        looper = false;
        bool dejavu=false;
        while (talid->monthtoint(date)==0) {
          if (dejavu) {
            std::cout << "That month was not in the correct format or not actually a month. please try again" << '\n';
          }
          cout << "What month would you like the event to start on?(format as the three letter abreviation in all caps)\n"<<"Example January = \"JAN\"\n";
          cin >> date;
          dejavu=1;
          transform(date.begin(), date.end(), date.begin(), ::toupper);
        }

        //transform(date.begin(), date.end(), date.begin(), ::toupper); //makes all letters upper case
        cout << "What day of the month would you like the event to start on?(format as two digits)\n";
        cin >> temp;
        m_day=temp;
        date = date + " " + temp + " ";//puts in pre determined format for date
        cout << "What year would you like the event to start on?(format as four digits)\n";
         cin >> temp;
         m_year=temp;
        date = date + temp;
        if(!talid->isValidDate(date))//checks if date is valid
        {
          looper = true;
          cout << "Invalid date, please try another date(check format):\n";
        }
      }while (looper);
      do {//takes in and checks date
        string temp = "";
        looper = false;
        bool dejavu=false;
        while (talid->monthtoint(date2)==0) {
          if (dejavu) {
            std::cout << "That month was not in the correct format or not actually a month. please try again" << '\n';
          }
          cout << "What month would you like to end the event?(format as the three letter abreviation in all caps)\n"<<"Example January = \"JAN\"";
          cin >> date2;
          dejavu=1;
          transform(date2.begin(), date2.end(), date2.begin(), ::toupper); //makes all letters upper case
        }



        cout << "What day of the month would you like the event to end?(format as two digits)\n";
        cin >> temp;
        m_day2=temp;
        date2 = date2 + " " + temp + " ";//puts in pre determined format for date
        cout << "What year would you like the event to end?(format as four digits)\n";
         cin >> temp;
         m_year2=temp;
        date2 = date2 + temp;
        if(!talid->isValidDate(date2))//checks if date is valid
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
          startTime="0"+startTime; //changed to double quote instead of single quote
        }
        if(!talid->isValidTime(startTime))
        {
          looper = true;
          cout << "Invalid start time, please try another time:\n";
        }
      }
    }while(looper == true);

    do{//takes in and checks end time
      looper = false;
      if(twelveHourMode == true)
      {
        cout << "What time would you like the event to end?(format as 12 hour time. Example, 2:00PM)\n";
        cin >> endTime;
        if(talid->isValidTime12Hour(endTime))
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
        looper=false;
        cout << "What time would you like the event to end?(format as military time. Example, 2:00PM would be 1400)\n";
        cin >> endTime;
        if (endTime.size()==3) {
          endTime="0"+endTime; //changed to double quote instead of single quote
        }
        if(!talid->isValidTime(endTime))
        {
          looper = true;
          cout << "Invalid end time, please try another time:\n";
        }
      }
    } while(looper == true);
    int z=0;
    int thirty=30;
    string m_month = date.substr(0,3);
		string m_dy = date.substr(4,2);
		string m_yea = date.substr(7);
    string m_month2 = date2.substr(0,3);
		string m_da2 = date2.substr(4,2);
		string m_yea2 = date2.substr(7);
    //std::cout << "made it here" << '\n';
    Time d1=Time(stoi(m_day), talid->monthtoint(m_month), stoi(m_year), z, z);
    Time d2=Time(stoi(m_day2), talid->monthtoint(m_month2), stoi(m_year2), z, thirty);
    if (!(d1<d2)) {
      std::cout << "Your end date is before your start date. please try again." << '\n';
    }else{
      datecompair=false;
    }
  }
  //std::cout << "made it out of the loop" << '\n';
  /*string endHour=endTime[0]+endTime[1]; //Why is string used like an array? What does the index represent? Go through it manually first.
  string startHour=startTime[0]+startTime[1];
  string endmin=endTime[2]+endTime[3];
  string startmin=startTime[2]+startTime[3];*/
  string endHour1, endHour2, endHour3, endHour4;
  endHour1 = endTime[0]; endHour2 = endTime[1]; endHour3 = endTime[2]; endHour4 = endTime[3];
  string endHour=endHour1+endHour2;
  // if (endHour1=="0") {
  //   endHour=endHour2;
  // } //Why is string used like an array? What does the index represent? Go through it manually first.
  string startHour1, startHour2, startHour3, startHour4;
  startHour1 = startTime[0]; startHour2 = startTime[1]; startHour3 = startTime[2]; startHour4 = startTime[3];
  string startHour=startHour1+startHour2;
  if (startHour1=="0") {
    startHour=startHour2;
  }
  string endmin=endHour3+endHour4;
  if (endmin=="00"){
    endmin="0";
  }
  string startmin=startHour3+startHour4;
  if (startmin=="00"){
    startmin="0";
  }

  int smin,shour,ehour,emin,syear,eyear,sday,eday,smonth,emonth;
  smin=stoi(startmin);
  shour=stoi(startHour);

  emin=stoi(endmin);
  ehour=stoi(endHour);

  eday=stoi(m_day2);
  sday=stoi(m_day);

  syear=stoi(m_year);
  eyear=stoi(m_year2);

  smonth=talid->monthtoint(m_month);
  emonth=talid->monthtoint(m_month2);
  //Event::addSession(int startDay, int startMonth, int startYear, int startHour, int startMinute, int endDay, int endMonth, int endYear, int endHour, int endMinute
  std::cout << "was added sucessfully =" <<a.addSession(sday, smonth, syear, shour, smin, eday, emonth, eyear, ehour, emin);
  Time t1(sday, smonth, syear, shour, smin);
  Time t2(eday, emonth, eyear, ehour, emin);
  while (t1<t2) {
    a.addAttendee(t1.day, t1.month, t1.year, t1.hour, t1.minute, eventCreator);
    t1=uptime(t1);
  }

  //std::cout << "out" << '\n';
  return a;
}

Time Executive::uptime(Time t1){
  if(t1.minute!=30){
    t1=Time(t1.day, t1.month, t1.year, t1.hour, 30);
  }else if(t1.hour!=23){
    t1=Time(t1.day, t1.month, t1.year, t1.hour+1, 0);
  }else if(!(t1.month==12&&t1.day==31)||!((t1.month==1||t1.month==3||t1.month==5||t1.month==7||t1.month==8||t1.month==10)&&t1.day==31)||!((t1.month==4||t1.month==6||t1.month==9||t1.month==11)&&t1.day==30)||!((t1.day==29)&& t1.month==2 &&talid->isLeapYear(t1.year))||!((t1.day==2)&& t1.month==2 &&!talid->isLeapYear(t1.year))){
    t1=Time(t1.day+1, t1.month, t1.year, t1.hour+1, 0);
  }else{
    if(t1.month==12){
      t1=Time(1, 1, t1.year+1, 0, 0);
    }else{
      t1=Time(1, t1.month+1, t1.year, 0, 0);
    }
  }
  return t1;
}
