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

bool FileHandler::openFile(){
  if(checkFile()){
    parseXML();
    return true;
  }
  return false;
}

bool FileHandler::saveFile(Event calendar){

}


void FileHandler::addEvent(vector<string>){

}

void FileHandler::addAttendee(vector<string>){

}

bool FileHandler::checkFile(){
  //
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

void FileHandler::parseXML(){
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
	for (xml_node<> * event_node = root_node->first_node("Event");
		event_node;
		event_node = event_node->next_sibling())
	{
		string event_name = event_node->first_attribute("name")->value();
		string event_startTime = event_node->first_attribute("starTime")->value();
		string event_stopTime = event_node->first_attribute("stopTime")->value();

    // To do: call addEvent
    // addEvent(event_name,event_startTime,event_stopTime);

		cout << "Event name: " + event_name + "\nEvent start time: " + event_startTime + "\nEvent end time: " + event_stopTime +"\n";
		// Interate over the attendees
		for(xml_node<> * attendee_node = event_node->first_node("Attendee");
			attendee_node;
			attendee_node = attendee_node->next_sibling())
		{
			string attendee_name = attendee_node->first_attribute("name")->value();
			cout << "\nAttendee Name: " + attendee_name + "\n";

			for(xml_node<> * attendeeTime_node = attendee_node->first_node("Time");
				attendeeTime_node;
				attendeeTime_node = attendeeTime_node->next_sibling())
			{

        // To do: call addAttendee
        // addAttendee(event_name,attendee_name,attendee_startTime,attendee_stopTime);

				string attendee_startTime = attendeeTime_node->first_attribute("startTime")->value();
				string attendee_stopTime = attendeeTime_node->first_attribute("stopTime")->value();
				cout << "Attendee start time: " + attendee_startTime + "\nAttendee end time: " + attendee_stopTime + "\n";
			}
		}
		cout << endl;
	}
}
