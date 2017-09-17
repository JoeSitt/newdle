/**
*	@file FileHandler.h
*	@author Jonathon Greene
*	@date 10/03/16
*	@brief
*/

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "FileHandler.cpp"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include <sys/stat.h>
#include <unistd.h>
#include <string>

using namespace rapidxml;
using namespace std;

class FileHandler
{
	public:
		// equals - are the 2 lists equal?
		// @param rhs = List to compare to this list (right hand side of equality)
		// @Pre TRUE
		// @Post return TRUE if lists match in size and values of all
		//   component elements; otherwise return FALSE
		FileHandler();

		// @param
		// @Pre
		// @Post
		~FileHandler();


		// @param
		// @Pre
		// @Post
    bool openFile();

		// @param
		// @Pre
		// @Post
    bool saveFile(vector<string>);

	private:
		std::string fileName;

		void addEvent(vector<string>);

		void addAttendee(vector<string>);

		bool checkFile();

		void parseXML();

};

#include "FileHandler.hpp"

#endif