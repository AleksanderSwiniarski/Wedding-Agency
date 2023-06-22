#include <iostream>
#include <ctime>
#include "Wedding.h"


using namespace std;

Wedding::Wedding(time_t dateOfWedding, Engaged* groomAndBride)
{
    this -> dateOfWedding = dateOfWedding;
    this -> groomAndBride = groomAndBride;
    groomAndBride->refOwnWedding() = this;
    this -> guestList = nullptr;
    this -> weddingSetting = nullptr;
    this -> locations = nullptr;
    this -> timePeriods = nullptr;
    this -> notes = nullptr;
    this -> next = nullptr;
}

Wedding::Wedding(const Wedding& w)
{

    this -> dateOfWedding = w.dateOfWedding;
    this -> groomAndBride = new Engaged(*w.groomAndBride);
    this -> guestList = nullptr;
    this -> weddingSetting = nullptr;
    this -> locations = nullptr;
    this -> timePeriods = nullptr;
    this -> notes = nullptr;

    // Copying guests

    Guest* guestPtr;
    Guest* copyGuestPtr = w.guestList;

    while (copyGuestPtr)
    {
        Guest* newGuest = new Guest(*copyGuestPtr);
        if(!guestList)
            guestList = newGuest;
        else
            guestPtr->refNext() = newGuest;
        guestPtr = newGuest;
        copyGuestPtr = copyGuestPtr -> refNext();
    }

    // Copying settings

    Wedding_Setting* settingPtr;
    Wedding_Setting* copySettingPtr = w.weddingSetting;

    while (copySettingPtr)
    {
        Wedding_Setting* newSetting = new Wedding_Setting(*copySettingPtr);
        if(!weddingSetting)
            weddingSetting = newSetting;
        else
            settingPtr = newSetting;
        settingPtr = newSetting;
        copySettingPtr = copySettingPtr -> refNext();
    }

    // Copying locations

    Location* locationsPtr;
    Location* copyLocationPtr = w.locations;

    while (copyLocationPtr)
    {
        Location* newLocation = new Location(*copyLocationPtr);
        if(!locations)
            locations = newLocation;
        else
            locationsPtr = newLocation;
        locationsPtr = newLocation;
        copyLocationPtr = copyLocationPtr -> refNext();
    }


    // Copying schedule

    Schedule* schedulePtr;
    Schedule* copySchedulePtr = w.timePeriods;

    while (copySchedulePtr)
    {
        Schedule* newPeriod = new Schedule(*copySchedulePtr);
        if(!timePeriods)
            timePeriods = newPeriod;
        else
            schedulePtr = newPeriod;
        schedulePtr = newPeriod;
        copySchedulePtr = copySchedulePtr -> refNext();
    }

    // Copying notes

    Note* notePtr;
    Note* copyNotePtr = w.notes;

    while (copyNotePtr)
    {
        Note* newNote = new Note(*copyNotePtr);
        if(!notes)
            notes = newNote;
        else
            notePtr = newNote;
        notePtr = newNote;
        copyNotePtr = copyNotePtr -> refNext();
    }

    this -> next = nullptr;
}

Wedding& Wedding::operator=(const Wedding& w)
{
    // Check for self assignment

    if (this == &w)
        return *this;

    // Deleting all objects

    // engaged

    delete groomAndBride;

    // guests

    Guest* delGuestPtr = guestList;
    while(delGuestPtr)
    {
        delGuestPtr = delGuestPtr->refNext();
        delete guestList;
        guestList = delGuestPtr;
    }

    // settings

    Wedding_Setting* delSettingPtr = weddingSetting;
    while(delSettingPtr)
    {
        delSettingPtr = delSettingPtr->refNext();
        delete weddingSetting;
        weddingSetting = delSettingPtr;
    }

    // locations

    Location* delLocationPtr = locations;
    while(delLocationPtr)
    {
        delLocationPtr = delLocationPtr->refNext();
        delete locations;
        locations = delLocationPtr;
    }

    // schedule

    Schedule* delPeriodPtr = timePeriods;
    while(delPeriodPtr)
    {
        delPeriodPtr = delPeriodPtr->refNext();
        delete timePeriods;
        timePeriods = delPeriodPtr;
    }

    // notes

    Note* delNotePtr = notes;
    while(delNotePtr)
    {
        delNotePtr = delNotePtr->refNext();
        delete notes;
        notes = delNotePtr;
    }


    // Inserting new objects

    // date

    this -> dateOfWedding = w.dateOfWedding;

    // engaged

    this -> groomAndBride = w.groomAndBride;

    // guests

    Guest* guestPtr;
    Guest* copyGuestPtr = w.guestList;

    while (copyGuestPtr)
    {
        Guest* newGuest = new Guest(*copyGuestPtr);
        if(!guestList)
            guestList = newGuest;
        else
            guestPtr->refNext() = newGuest;
        guestPtr = newGuest;
        copyGuestPtr = copyGuestPtr -> refNext();
    }

    // settings

    Wedding_Setting* settingPtr;
    Wedding_Setting* copySettingPtr = w.weddingSetting;

    while (copySettingPtr)
    {
        Wedding_Setting* newSetting = new Wedding_Setting(*copySettingPtr);
        if(!weddingSetting)
            weddingSetting = newSetting;
        else
            settingPtr = newSetting;
        settingPtr = newSetting;
        copySettingPtr = copySettingPtr -> refNext();
    }

    // locations

    Location* locationsPtr;
    Location* copyLocationPtr = w.locations;

    while (copyLocationPtr)
    {
        Location* newLocation = new Location(*copyLocationPtr);
        if(!locations)
            locations = newLocation;
        else
            locationsPtr = newLocation;
        locationsPtr = newLocation;
        copyLocationPtr = copyLocationPtr -> refNext();
    }


    // schedule

    Schedule* schedulePtr;
    Schedule* copySchedulePtr = w.timePeriods;

    while (copySchedulePtr)
    {
        Schedule* newPeriod = new Schedule(*copySchedulePtr);
        if(!timePeriods)
            timePeriods = newPeriod;
        else
            schedulePtr = newPeriod;
        schedulePtr = newPeriod;
        copySchedulePtr = copySchedulePtr -> refNext();
    }

    // notes

    Note* notePtr;
    Note* copyNotePtr = w.notes;

    while (copyNotePtr)
    {
        Note* newNote = new Note(*copyNotePtr);
        if(!notes)
            notes = newNote;
        else
            notePtr = newNote;
        notePtr = newNote;
        copyNotePtr = copyNotePtr -> refNext();
    }


    return *this;

}

Wedding::~Wedding()
{

}

time_t& Wedding::refDateOfWedding()
{
    return dateOfWedding;
}

Engaged*& Wedding::refGroomAndBride()
{
    return groomAndBride;
}

Guest*& Wedding::refGuestList()
{
    return guestList;
}

Wedding_Setting*& Wedding::refWeddingSettingList()
{
    return weddingSetting;
}

Location*& Wedding::refLocationsList()
{
    return locations;
}

Schedule*& Wedding::refSchedule()
{
    return timePeriods;
}

Note*& Wedding::refNotes()
{
    return notes;
}

Wedding*& Wedding::refNext()
{
    return next;
}

int Wedding::countGuest() const
{
    if(guestList == nullptr)
        return 0;
    Guest* guestPtr = guestList;
    int amount = 0;
    while(guestPtr)
    {
        amount ++;
        guestPtr = guestPtr -> refNext();
    }
    return amount;
}

int Wedding::countMeatEaters() const
{
    if(guestList == nullptr)
        return 0;
    Guest* guestPtr = guestList;
    int meatEaters = 0;
    while (guestPtr)
    {
        if(meatEater == guestPtr -> refFoodPreference())
            meatEaters++;
        guestPtr = guestPtr -> refNext();
    }
    return meatEaters;
}

int Wedding::countVegetarians() const
{
    if(guestList == nullptr)
        return 0;
    Guest* guestPtr = guestList;
    int vegetarians = 0;
    while (guestPtr)
    {
        if(vegetarian == guestPtr -> refFoodPreference())
            vegetarians++;
        guestPtr = guestPtr -> refNext();
    }
    return vegetarians;
}

int Wedding::countVegans() const
{
    if(guestList == nullptr)
        return 0;
    Guest* guestPtr = guestList;
    int vegans = 0;
    while (guestPtr)
    {
        if(vegan == guestPtr -> refFoodPreference())
            vegans++;
        guestPtr = guestPtr -> refNext();
    }
    return vegans;
}

int Wedding::countDiverse() const
{
    if(guestList == nullptr)
        return 0;
    Guest* guestPtr = guestList;
    int diverseEaters = 0;
    while (guestPtr)
    {
        if(diverse == guestPtr -> refFoodPreference())
            diverseEaters++;
        guestPtr = guestPtr -> refNext();
    }
    return diverseEaters;
}

int Wedding::countConfirmedGuests() const
{
    if(guestList == nullptr)
        return 0;
    Guest* guestPtr = guestList;
    int confirmedGuests = 0;
    while (guestPtr)
    {
        if (guestPtr -> refConfirmation())
            confirmedGuests++;
        guestPtr = guestPtr -> refNext();
    }
    return confirmedGuests;
}

int Wedding::countLocations() const
{
    if(locations == nullptr)
        return 0;
    Location* locationsPtr = locations;
    int amount = 0;
    while (locationsPtr)
    {
        amount++;
        locationsPtr = locationsPtr -> refNext();
    }
    return amount;
}

float Wedding::countLocationCost() const
{
    if(locations == nullptr)
        return 0;
    Location* locationsPtr = locations;
    float cost = 0;
    while (locationsPtr)
    {
        cost += countGuest() * locationsPtr -> refCostPerGuest();
        locationsPtr = locationsPtr -> refNext();
    }
    return cost;
}

int Wedding::countCompletionOfLocations() const
{
    if(locations == nullptr)
        return 0;
    Location* locationPtr = locations;
    int notReserved = 0;
    while (locationPtr)
    {
        if(!locationPtr ->refToDo())
            notReserved++;
        locationPtr = locationPtr -> refNext();
    }
    return notReserved;
}

int Wedding::countWeddingSettings() const
{
    if (weddingSetting == nullptr)
        return 0;
    Wedding_Setting* settingPtr = weddingSetting;
    int amount = 0;
    while (settingPtr)
    {
        amount++;
        settingPtr = settingPtr -> refNext();
    }
    return amount;
}

float Wedding::countWeddingSettingCost() const
{
    if (weddingSetting == nullptr)
        return 0;
    Wedding_Setting* settingPtr = weddingSetting;
    int cost = 0;
    while (settingPtr)
    {
        cost += settingPtr -> refPrice();
        settingPtr = settingPtr -> refNext();
    }
    return cost;
}

int Wedding::countCompletionOfWeddingSetting() const
{
    if (weddingSetting == nullptr)
        return 0;
    Wedding_Setting* settingPtr = weddingSetting;
    int notReserved = 0;
    while (settingPtr)
    {
        if(!settingPtr->refToDo())
            notReserved++;
        settingPtr = settingPtr -> refNext();
    }
    return notReserved;
}

period Wedding::checkScheduleLength() const
{
    period returnTime;
    returnTime.hour = 0;
    returnTime.minute = 0;
    if(!timePeriods)
    {
        return returnTime;
    }
    period beginning = timePeriods -> refBeginning();
    period ending = timePeriods -> refEnding();
    Schedule* periodPtr = timePeriods;
    while (periodPtr)
    {
        if(ending < periodPtr->refEnding())
            ending = periodPtr->refEnding();
        periodPtr = periodPtr->refNext();
    }
    int intBeginning = beginning.hour*60 + beginning.minute;
    int intEnding = ending.hour*60 + ending.minute;
    int timeDifference = intEnding - intBeginning;
    returnTime.hour = timeDifference / 60;
    returnTime.minute = timeDifference%60;

    return returnTime;
}

int Wedding::countNotes() const
{
    if(!notes)
        return 0;
    Note* notePtr = notes;
    int amount = 0;
    while (notePtr)
    {
        amount++;
        notePtr = notePtr -> refNext();
    }
    return amount;
}

Wedding Wedding::operator+(Guest& g)
{
    //Adding element when the list is empty
    if (!guestList)
    {
        guestList = &g;
        g.refNext() = nullptr;
    }
    //Adding element at the end of the list
    else
    {
        Guest* guestPtr = guestList;
        while (guestPtr)
        {
            if(!guestPtr -> refNext())
            {
                guestPtr -> refNext() = &g;
                g.refNext() = nullptr;
            }
            guestPtr = guestPtr -> refNext();
        }
    }
}

Wedding Wedding::operator+(Location& l)
{
    //Adding element when the list is empty
    if (!locations)
    {
        locations = &l;
        l.refNext() = nullptr;
    }
    //Adding element at the end of the list
    else
    {
        Location* locationsPtr = locations;
        while (locationsPtr)
        {
            if(!locationsPtr -> refNext())
            {
                locationsPtr -> refNext() = &l;
                l.refNext() = nullptr;
            }
            locationsPtr = locationsPtr -> refNext();
        }
    }
}

Wedding Wedding::operator+(Wedding_Setting& we)
{
    //Adding element when the list is empty
    if (!weddingSetting)
    {
        weddingSetting = &we;
        we.refNext() = nullptr;
    }
    //Adding element at the end of the list
    else
    {
        Wedding_Setting* settingPtr = weddingSetting;
        while (settingPtr)
        {
            if(!settingPtr -> refNext())
            {
                settingPtr -> refNext() = &we;
                we.refNext() = nullptr;
            }
            settingPtr = settingPtr -> refNext();
        }
    }
}

Wedding Wedding::operator+(Schedule& s)
{
    //Adding element when the list is empty
    if(!timePeriods)
    {
        timePeriods = &s;
        s.refNext() = nullptr;
    }
    //Adding element to the sorted list by the start and end of each period
    else
    {

        Schedule* currentPeriodtPtr = timePeriods;
        Schedule* nextPeriodPtr = timePeriods -> refNext();

        //Adding before head

        if (s.refBeginning() < currentPeriodtPtr->refBeginning()||
                (s.refBeginning() == currentPeriodtPtr->refBeginning() && s.refEnding() < currentPeriodtPtr->refEnding()))
        {
            timePeriods = &s;
            s.refNext() = currentPeriodtPtr;
        }

        // Adding after head

        else if(!timePeriods->refNext())
        {
            timePeriods->refNext() = &s;
            s.refNext() = nullptr;
        }

        else
        {
            while (nextPeriodPtr)
            {
                //Adding before bigger element

                if (s.refBeginning() < nextPeriodPtr->refBeginning()||
                        (s.refBeginning() == nextPeriodPtr->refBeginning() && s.refEnding() < nextPeriodPtr->refEnding()))
                {
                    s.refNext() = nextPeriodPtr;
                    currentPeriodtPtr->refNext() = &s;
                    break;
                }

                //Adding at the end

                if (!nextPeriodPtr->refNext())
                {
                    nextPeriodPtr->refNext() = &s;
                    s.refNext() = nullptr;
                    break;
                }

                currentPeriodtPtr = currentPeriodtPtr -> refNext();
                nextPeriodPtr = nextPeriodPtr -> refNext();
            }
        }
    }
}

Wedding Wedding::operator+(Note& n)
{
    //Adding element when the list empty
    if(!notes)
    {
        notes = &n;
        n.refNext() = nullptr;
    }
    //Adding element at the end of the list
    else
    {
        Note* notePtr = notes;
        while (notePtr)
        {
            if(!notePtr -> refNext())
            {
                notePtr -> refNext() = &n;
                n.refNext() = nullptr;
            }
            notePtr = notePtr -> refNext();
        }
    }
}

ostream& operator<< (ostream& os, const period& p)
{
    os << p.hour << ":" << p.minute <<endl;
    return os;
}

ostream& operator<< (ostream& os, const Wedding& w)
{
    os << "Wedding details: " << endl << endl;

    // Engaged

    os << "Clients: " << endl;
    os << *w.groomAndBride << endl << endl;

    // Date

    tm* gmDate = gmtime(&w.dateOfWedding);
    os << "Date of the wedding: ";
    switch (gmDate->tm_wday)
    {
    case 0:
        os << "Sunday";
        break;
    case 1:
        os << "Monday";
        break;
    case 2:
        os << "Tuesday";
        break;
    case 3:
        os << "Wednesday";
        break;
    case 4:
        os << "Thursday";
        break;
    case 5:
        os << "Friday";
        break;
    case 6:
        os << "Saturday";
        break;
    }

    os << " " << gmDate->tm_mday << "." << gmDate->tm_mon+1 << "." << gmDate->tm_year+1900 << endl << endl;


    // Guest list

    os << "Guests: " << endl;
    if(!w.guestList)
    {
        os << "Guest list is empty!" << endl;
    }
    else
    {
        int amount = 0;
        Guest* guestPtr = w.guestList;
        while (guestPtr)
        {
            os << "Guest nr." << ++amount << ":" << endl;
            os << *guestPtr << endl;
            guestPtr = guestPtr->refNext();
        }
    }

    os << endl;

    // Wedding Settings

    os << "Wedding Settings: " << endl;
    if(!w.weddingSetting)
    {
        os << "Wedding settings list is empty!" << endl;
    }
    else
    {
        Wedding_Setting* settingPtr = w.weddingSetting;
        while (settingPtr)
        {
            os << *settingPtr << endl;
            settingPtr = settingPtr->refNext();
        }
    }

    os << endl;

    // Locations

    os << "Locations: " << endl;
    if(!w.locations)
    {
        os << "Locations list is empty!" << endl;
    }
    else
    {
        Location* locationPtr = w.locations;
        while (locationPtr)
        {
            os << *locationPtr << endl;
            locationPtr = locationPtr->refNext();
        }
    }

    os << endl;

    // Schedule

    os << "Schedule: " << endl;
    if(!w.timePeriods)
    {
        cout << "Schedule is empty!" << endl;
    }
    else
    {
        Schedule* periodPtr = w.timePeriods;
        while (periodPtr)
        {
            os << *periodPtr << endl;
            periodPtr = periodPtr->refNext();
        }
    }

    os << endl;

    // Notes

    os << "Notes: " << endl;
    if(!w.notes)
    {
        cout << "There are no notes" << endl;
    }
    else
    {
        Note* notesPtr = w.notes;
        while (notesPtr)
        {
            os << *notesPtr << endl;
            notesPtr = notesPtr -> refNext();
        }
    }

    return os;
}
