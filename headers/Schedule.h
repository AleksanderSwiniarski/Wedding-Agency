#ifndef SCHEDULE
#define SCHEDULE

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

struct period{
    int hour;
    int minute;
};

class Schedule
{
private:

    period beginning;
    period ending;
    string description;
    // Basic data of the schedule

    Schedule* next;
    // Pointer to the next time span

public:

    Schedule(period beginning, period ending, string description);
    ~Schedule();
    Schedule(const Schedule& s);
    Schedule& operator=(const Schedule& s);
    // Basic methods of a class like Constructor, Destructor, Copy Constructor and Assignment operator

    period& refBeginning();
    period& refEnding();
    string& refDescription();
    Schedule*& refNext();
    // Basic referential methods for access to the data and lists of the object

    friend ostream& operator<< (ostream& os, const Schedule& s);
    // Method to display data of the time span
};

    bool operator< (const period& first, const period& second);
    bool operator> (const period& first, const period& second);
    bool operator== (const period& first, const period& second);
    //Logical methods for simplification of sorting the Schedule list


#endif // SCHEDULE
