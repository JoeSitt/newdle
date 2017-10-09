
#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;

class Task
{
  public:
      friend class boost::serialization::access;
      // When the class Archive corresponds to an output archive, the
      // & operator is defined similar to <<.  Likewise, when the class Archive
      // is a type of input archive the & operator is defined similar to >>.
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
          ar & taskAccepted;
      }
      string guestName; //name of the guest
	  vector<int> taskAccepted; //when listing attendes and the task they accepted, iterate through the taskList first to show the list of tasks.
};

#endif
