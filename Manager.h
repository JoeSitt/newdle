/**
*	@file Event.h
*	@author Bisher Anadani
*	@date 9/17/2017
*	@brief Event class
*/

#ifndef MANAGER_H
#define MANAGER_H

#include <fstream>

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#include "Event.h"

using namespace std;

class Manager
{
public:
    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & events;
    }

    std::vector<Event*> events;

    bool saveManager(std::string fileName);

    static Manager* getManager(std::string fileName);
};

#endif
