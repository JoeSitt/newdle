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
    if (ifstream("saveFile")) {
        Manager* m2 = Manager::getManager("saveFile");
        calendar = m2->events;
    }
}


Executive::~Executive()
{
    // Saves events to file
    Manager m;
    m.events = calendar;
    m.saveManager("saveFile");
    // for( int i = 0 ; i < calendar.size(); i++) {
    //     delete calendar[i];
    // }
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
        if(temp == "0"||temp=="24")
        {
            useMilTime = true;
        }
        else if(temp == "1"||temp=="12")
        {
            useMilTime = false;
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

void Executive::attendeeMode() {
    string userChoice;
    bool looper = true;
    clean();
    do {//propts user to add event or check status or exit
        cout << "Enter the number for action you would like to do:\n1) Attend an eventt\n2) Complete a task\n3) Exit Attendee Mode\n";
        looper = true;
        cin >> userChoice;
        if(userChoice == "1")//sends user to correct action
        {
            clean();
            addAttendeeMode();
        }
        else if(userChoice == "2")
        {
            clean();
            completeTask();
        }
        else if(userChoice == "3")
        {
            clean();
            cout << "Exiting Attendee Mode\n";
            looper = false; //only way to exit Admin Mode
        }
        else //checks if input is valid, if not asks for new input
        {
            clean();
            cout << "Invalid input: "<<userChoice<<"\n";
        }
    } while(looper == true);
}

void Executive::completeTask() {
    if (calendar.size() == 0) {
        std::cout << "No Events!" << std::endl;
        return;
    }
    std::string name = readString("What is your name?(Please no spaces): ");
    cout << "Select the event whose task you'd like to complete" << endl;
    Event* event = readEventSelection(calendar);
    readCompleteTask(event, name);
}

void Executive::adminMode()
{
    string adminChoice;
    bool looper = true;
    clean();
    do {//propts user to add event or check status or exit
        cout << "Enter the number for action you would like to do:\n1) Create event\n2) Check attendance list of an event\n3) Check the tasks for an event\n4) Exit Admin Mode\n";
        looper = true;
        cin >> adminChoice;
        if(adminChoice == "1")//sends user to correct action
        {
            clean();
            addEventMode();
        }
        else if(adminChoice == "2")
        {
            clean();
            checkAttendanceMode();
        }
        else if(adminChoice == "3")
        {
            clean();
            checkTasksMode();
        }
        else if(adminChoice == "4")
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

void Executive::checkTasksMode() {
    if (calendar.size() == 0) {
        std::cout << "No Events!" << std::endl;
        return;
    }
    Event* event = readEventSelection(calendar);
    std::cout << event->getTaskSummary() << std::endl;
}

void Executive::addAttendeeMode() {
    if (calendar.size() == 0) {
        std::cout << "No Events!" << std::endl;
        return;
    }
    Event* event = readEventSelection(calendar);
    if (readNewAttendee(event, useMilTime)) {
        std::cout << "Attendee successfully added!" << std::endl;
    } else {
        std::cout << "Attendee could not be added" << std::endl;
    }
}

void Executive::addEventMode() {
    Event* newEvent = readEvent(useMilTime);
    readAddTasks(newEvent);
    calendar.push_back(newEvent);
}

void Executive::checkAttendanceMode() {
    if (calendar.size() == 0) {
        std::cout << "No Events!" << std::endl;
        return;
    }
    Event* event = readEventSelection(calendar);
    std::cout << event->getAttendees(useMilTime) << std::endl;
}

void Executive::readAddTasks(Event* e) {
    bool done = false;
    do {
        std::string input = readString("Enter a task that a guest should complete (Please no spaces in task). Enter 0 when done: ");
        if (input == "0") {
            done = true;
        } else {
            Task t;
            t.description = input;
            e->tasks.push_back(t);
        }
    } while (!done);
}

void Executive::readCompleteTask(Event* e, std::string name) {
    std::cout << e->getTaskSummary() << std::endl;

    if (e->tasks.size() == 0) {
        return;
    }

    bool done = false;
    do {
        int choice = readInt("Enter the index of the task you would like to complete: ", "ERROR non index entered");

        if (choice > 0 && choice <= e->tasks.size()) {
            e->tasks[choice - 1].guestName = name;
            done = true;
        } else {
            std::cout << "Invalid index" << std::endl;
        }
    } while (!done);
}

int Executive::readInt(string requestMessage, string failMessage)
{
    int n = 0;
    std::cout << requestMessage;
    std::cin >> n;

    while ( std::cin.fail() ) {
        std::cin.clear(); // unset failbit
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip bad input
        std::cout << failMessage << endl;
        std::cout << requestMessage;
        std::cin >> n;
    }

    return n;
}

std::string Executive::readString(std::string requestMessage) {
    std::string input;
    std::cout << requestMessage;
    std::cin >> input;
    return input;
}

// Read time from user
Time Executive::readTime(bool useMil) {
    bool inputGood = false;
    std::string input;
    std::string input_message;
    Valid v;

    // Get time from user
    if (useMil) {
        input_message = "Please enter a time, in a 30-minute interval, using military time: ";
    } else {
        input_message = "Please enter a time, intervals are 30 mins, please use this format 8:30PM: ";
    }
    do {
        input = readString(input_message);

        if (useMil) {
            if (v.isValidTime(input)) {
                inputGood = true;
            } else {
                std::cout << "Unreadable time. Please try again." << std::endl;
            }
        } else {
            if (v.isValidTime12Hour(input)) {
                inputGood = true;
            } else {
                std::cout << "Unreadable time. Please try again." << std::endl;
            }
        }
    } while (!inputGood);

    // Parse Time info
    if (!useMil) {
        input = v.changeTo24Hour(input);
    }
    int minute = std::stoi(input.substr(2, 4));
    int hour = std::stoi(input.substr(0, 2));

    // Get date from user
    inputGood = false;

    std::string month_string;
    std::string day_string;
    std::string year_string;

    do {
        month_string = readString("Enter a month, with format as the three letter abreviation in all caps: ");
        day_string = readString("Enter a day, formatted as two digits: ");
        year_string = readString("Enter a year, formatted as four digits: ");
        input = month_string + " " + day_string + " " + year_string;

        if (v.isValidDate(input)) {
            inputGood = true;
        } else {
            std::cout << "Unreadable date. Please try again." << std::endl;
        }
    } while (!inputGood);

    int month = v.monthtoint(month_string);
    int day = std::stoi(day_string);
    int year = std::stoi(year_string);

    return Time(day, month, year, hour, minute);
}

// NOTE day extension could possibly be done here
bool Executive::readNewSession(Event* event, bool useMil) {
    std::cout << "Enter the start time and date... " << std::endl;
    Time start = readTime(useMil);
    std::cout << "Enter the end time and date... " << std::endl;
    Time end = readTime(useMil);
    return event->addSession(start, end);
}

// Read new Event from user
Event* Executive::readEvent(bool useMil) {
    // Get event name
    std::string name = readString("What would you like to name the event? (Please no spaces): ");
    Event* event = new Event(name);

    // Get as many sessions as are desired
    bool keepAdding = true;
    std::cout << "Please add some sessions for the event." << std::endl;
    do {
        std::string input = readString("Enter 1 to add a session. Enter 0 if done: ");

        if (input == "1") {
            bool result = readNewSession(event, useMil);
            if (result) {
                std::cout << "Session successfully added!" << std::endl;
            } else {
                std::cout << "Session could not be added. It must conflict with another session." << std::endl;
            }
        } else {
            keepAdding = false;
        }
    } while (keepAdding);

    return event;
}

Event* Executive::readEventSelection(std::vector<Event*> event_list) {
    std::cout << "Enter the index of the event to select it" << std::endl;
    int index = 0;
    for (Event* e : event_list) {
        std::cout << index << ": " << e->name << std::endl;
        index++;
    }

    bool goodInput = false;
    int response = -1;
    do {
        response = readInt("Enter the index of the desired event: ", "ERROR: non integer entred. Try again");
        if (response >= 0 && response < event_list.size()) {
            goodInput = true;
        } else {
            std::cout << "Invalid index entered. Try again" << std::endl;
        }
    } while (!goodInput);

    std::cout << event_list.size() << std::endl;
    std::cout << response << std::endl;
    return event_list[response];
}

bool Executive::readNewAttendee(Event* event, bool useMil) {
    std::string name = readString("Enter your name(Please no spaces): ");
    std::cout << "Enter the time you would like to RSVP for" << std::endl;
    Time t = readTime(useMil);
    return event->addAttendee(t, name);
}
