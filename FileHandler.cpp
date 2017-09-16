/**
*	@file FileHandler.cpp
*	@author Jonathon Greene
*	@date
*	@brief
*/
// #include "Event.h"
#include "FileHandler.h"

FileHandler::FileHandler(){

}

FileHandler::~FileHandler(){

}

bool FileHandler::openFile(vector<*Event> &calendar_param){
  // calendar = new std::vector<Event>();
  if(checkFile()){
    parseXML(calendar_param);
    return true;
  }
  return false;
}

// to do: finish attendee iteration printing
bool FileHandler::saveFile(Event calendar){
  ofstream myfile;
  myfile.open ("schedule.xml");
  myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n<Calendar>\n";
  // for each event
  // {
    // string event_name = calendar.getEventName();
    // string event_startTime = calendar.getEventStartTime();
    // string event_stopTime = calendar.getEventStopTime();
    string event_name = "Party";
    string event_startTime = "OCT 9 600 2017";
    string event_stopTime = "OCT 9 1200 2017";

    myfile << "\t<Event name=\""
      + event_name + "\" starTime=\""
      + event_startTime + "\" stopTime=\""
      + event_stopTime + "\">\n";

  // Interate over the attendees
    // for each Attendee
    // {
    //   string attendee_name = attendee_node->first_attribute("name")->value();
    string attendee_name = "Jeff";
    myfile << "\t\t<Attendee name=\"" + attendee_name + "\">\n";
    //   cout << "\nAttendee Name: " + attendee_name + "\n";
    //
    //   for each attendee_time_slot
    //   {
    //     string attendee_startTime = attendeeTime_node->first_attribute("startTime")->value();
    //     string attendee_stopTime = attendeeTime_node->first_attribute("stopTime")->value();
        string attendee_startTime = "OCT 9 800 2017";
        string attendee_stopTime = "OCT 9 900 2017";
        myfile << "\t\t\t<Time startTime=\"" + attendee_startTime + "\" stopTime=\"" + attendee_stopTime + "\"></Time>\n";
    //   }
    myfile << "\t\t</Attendee>";
    // }
    myfile << "\n\t</Event>\n";
  // }
    myfile << "</Calendar>";
  myfile.close();
}

void FileHandler::addAttendee(vector<string>){

}

bool FileHandler::checkFile(){
  // Check if file exists. Create it and load with default text if it does not.
  if (!ifstream("schedule.xml"))
  {
    ofstream file("schedule.xml");
    if (!file)
    {
      //  File could not be created
      return false;
    }
    ofstream myfile;
    myfile.open ("schedule.xml");
    myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n<Calendar>\n</Calendar>";
    myfile.close();
  }
  return true;
}

void FileHandler::parseXML(vector<*Event> &calendar_param){
  xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile ("schedule.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("Calendar");
	// Iterate over the events
  int size = 0;
	for (xml_node<> * event_node = root_node->first_node("Event");
		event_node;
		event_node = event_node->next_sibling())
	{
		string eventName = event_node->first_attribute("eventName")->value();
		string eventCreator = event_node->first_attribute("eventCreator")->value();
		string startTime = event_node->first_attribute("startTime")->value();
		string endTime = event_node->first_attribute("endTime")->value();
		string date = event_node->first_attribute("date")->value();

		calendar_param.emplace_back(eventName, eventCreator, startTime, endTime, date);

		// Interate over the attendees
		for(xml_node<> * attendee_node = event_node->first_node("Attendee");
			attendee_node;
			attendee_node = attendee_node->next_sibling())
		{
			string attendeeName = attendee_node->first_attribute("attendeeName")->value();

			for(xml_node<> * attendeeTime_node = attendee_node->first_node("Time");
				attendeeTime_node;
				attendeeTime_node = attendeeTime_node->next_sibling())
			{
				string attendee_arriveTime = attendeeTime_node->first_attribute("arriveTime")->value();
				string attendee_leaveTime = attendeeTime_node->first_attribute("leaveTime")->value();

        // TODO add addAttendee call
				calendar_param[size].addAttendee(attendeeName,attendee_arriveTime,attendee_leaveTime);
			}
		}
    size++;
	}
}
