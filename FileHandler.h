/**
*	@file FileHandler.h
*	@author Jonathon Greene
*	@date 10/03/16
*	@brief
*/

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

#include "Event.h"
#include "rapidxml-1.13/rapidxml.hpp"


using namespace rapidxml;
using namespace std;

class FileHandler
{
	public:
		/** @pre none.
		*   @post none.
		*   @return none.
		*/
		FileHandler();

		/** @pre none.
		*   @post none.
		*   @return none.
		*/
		~FileHandler();


		/** @pre file can be made or opened by checkfile
		*   @post all attendees for that time slot displayed.
		*   @return true if event/time valid, false if invalid.
		*/
    bool openFile(vector<Event*> &calendar_param);

		/** @pre calendar_param is passed by reference
		*   @post file saved as well formatted
		*   @return none. bool for successfully opening file
		*/
    bool saveFile(vector<Event*> &calendar_param);

	private:
		/** @pre none.
		*   @post file opened or created
		*   @return bool for file created or successfully opened
		*/
		bool checkFile();

		/** @pre none.
		*   @post xml is loaded and events created
		*   @return none.
		*/
		void parseXML(vector<Event*> &calendar_param);

};

#endif
