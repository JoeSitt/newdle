#include "Executive.h"
#include "Valid.h"
#include "Event.h"

// TODO
// - Inform user on case of no tasks

int main() {
    Executive exec;
    exec.run();

    // vector<Event*> e_list;
    //
    // Event *a = new Event("Party");
    // a->addSession(1, 1, 1990, 9, 30, 1, 1, 1990, 11, 30);
    // std::cout << a->addAttendee(1, 1, 1990, 9, 30, "John") << std::endl;
    // a->addAttendee(1, 1, 1990, 9, 30, "a");
    // a->addAttendee(1, 1, 1990, 9, 30, "J");
    // a->addAttendee(1, 1, 1990, 9, 30, "abigail");
    // a->addAttendee(1, 1, 1990, 10, 30, "new");
    // a->addAttendee(1, 1, 1990, 10, 0, "newer");
    //
    // a->addSession(1, 1, 20, 9, 30, 1, 1, 200, 11, 30);
    // a->addAttendee(1, 1, 20, 9, 30, "John");
    // a->addAttendee(1, 1, 20, 9, 30, "a");
    // a->addAttendee(1, 1, 20, 9, 30, "J");
    // a->addAttendee(1, 1, 20, 9, 30, "abigail");
    // a->addAttendee(1, 1, 20, 10, 30, "new");
    // a->addAttendee(1, 1, 20, 10, 0, "newer");
    // std::cout << a->getAttendees(false) << std::endl;
    //
    // readAddTasks(a);
    // readCompleteTask(a, "BOB");
    //
    // std::cout << a->getTaskSummary() << std::endl;
    //
    // std::cout << readNewAttendee(a, false) << std::endl;

    // Event *b = new Event("Lame");
    //
    // e_list.push_back(a);
    // Event *e1 = nullptr;
    //
    // Manager m;
    // m.events = e_list;
    // m.saveManager("test");
    //
    // Manager *m2 = Manager::getManager("test");
    //
    // for (Event* e : m2->events) {
    //     std::cout << e->getSessions(false) << std::endl;
    // }

    // bool useMil = true;
    // Event* e = readEvent(useMil);
    //
    // std::cout << e->getSessions(useMil) << std::endl;
}
