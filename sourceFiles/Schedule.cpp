#include <iostream>
#include <ctime>
#include <string>
#include "Schedule.h"

using namespace std;

Schedule::Schedule(period beginning, period ending, string description)
{
    this -> beginning = beginning;
    this -> ending = ending;
    this -> description = description;
    next = nullptr;
}

Schedule::~Schedule()
{

}

Schedule::Schedule(const Schedule& s)
{
    this -> beginning.hour = s.beginning.hour;
    this -> beginning.minute = s.beginning.minute;
    this -> ending.hour = s.ending.hour;
    this -> ending.minute = s.ending.minute;
    this -> description = s.description;
    next = nullptr;
}
Schedule& Schedule::operator=(const Schedule& s)
{
    //Check for self assignment
    if(this == &s)
        return *this;

    this -> beginning.hour = s.beginning.hour;
    this -> beginning.minute = s.beginning.minute;
    this -> ending.hour = s.ending.hour;
    this -> ending.minute = s.ending.minute;
    this -> description = s.description;

    return *this;
}

period& Schedule::refBeginning()
{
    return beginning;
}

period& Schedule::refEnding()
{
    return ending;
}

string& Schedule::refDescription()
{
    return description;
}

Schedule*& Schedule::refNext()
{
    return next;
}

ostream& operator<< (ostream& os, const Schedule& s)
{
    os << s.description << " is from " << s.beginning.hour <<":";
    if(s.beginning.minute == 0)
        os << "00";
    else
        os << s.beginning.minute;
    os << " to " << s.ending.hour <<":";
    if(s.ending.minute == 0)
        os << "00";
    else
        os << s.ending.minute;
    return os;
}

bool operator< (const period& first, const period& second)
{
    if(first.hour < second.hour ||
            (first.hour == second.hour && first.minute < second.minute))
    {
        return true;
    }

    return false;
}

bool operator> (const period& first, const period& second)
{
    return (second < first);
}

bool operator== (const period& first, const period& second)
{
    if ((first.hour == second.hour) && (first.minute == second.minute))
    {
        return true;
    }
    return false;
}
