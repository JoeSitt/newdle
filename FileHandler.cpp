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
  }
}

bool FileHandler::saveFile(vector<string>){

}


void FileHandler::addEvents(vector<string>){

}

void FileHandler::addAttendees(vector<string>){

}

bool FileHandler::checkFile(){
  if (ifstream("schedule.xml"))
  {
       cout << "File already exists" << endl;
      //  To do: if file is newly created add default text
       return true;
  }
  ofstream file("schedule.xml");
  if (!file)
  {
       cout << "File could not be created" << endl;
       return false;
  }
  return false;
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
	    printf("Event name: %s\nEvent start time: %s\nEvent end time: %s\n",
	    	event_node->first_attribute("name")->value(),
				event_node->first_attribute("starTime")->value(),
	    	event_node->first_attribute("stopTime")->value());
            // Interate over the attendees
	    for(xml_node<> * attendee_node = event_node->first_node("Attendee");
				attendee_node;
				attendee_node = attendee_node->next_sibling()
			)
	    {
				printf("\nAttendee Name: %s\n",
		    	attendee_node->first_attribute("name")->value());

					for(xml_node<> * attendeeTime_node = attendee_node->first_node("Time");
						attendeeTime_node;
						attendeeTime_node = attendeeTime_node->next_sibling()
					)
			    {
						printf("Attendee start time: %s\nAttendee end time: %s\n",
							attendeeTime_node->first_attribute("startTime")->value(),
							attendeeTime_node->first_attribute("stopTime")->value());
			    }
	    }
	    cout << endl;
	}
}
