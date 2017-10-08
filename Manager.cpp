#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

#include "Manager.h"

Manager* Manager::getManager(std::string fileName) {
    Manager m;
    std::cout << "Loading Manager..." << std::endl;
    try {
       std::ifstream ifs(fileName);
       boost::archive::text_iarchive ia(ifs);
       // read class state from archive
       ia >> m;
    } catch(std::exception e) {
       return nullptr;
    }
    return new Manager(m);
}

bool Manager::saveManager(std::string fileName) {
    try {
        std::ofstream ofs(fileName);
        boost::archive::text_oarchive oa(ofs);
        oa << *this;
    } catch(std::exception e) {
        return false;
    }
    return true;
}
