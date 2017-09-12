/**
*	@file FileHandler.h
*	@author Jonathon Greene
*	@date 10/03/16
*	@brief
*/

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "FileHandler.h"

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"

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
    FileHandler(char* fileIn);

		// @param
		// @Pre
		// @Post
		~FileHandler();

		// @param
		// @Pre
		// @Post
		bool checkFile();

		// @param
		// @Pre
		// @Post
    bool readFile();

		// @param
		// @Pre
		// @Post
    bool saveFile();

		// @param
		// @Pre
		// @Post
    void parseXML() const;

	private:
		std::string fileName;

		// get events

		// get attendees

		//
};

#include "FileHandler.hpp"

#endif
