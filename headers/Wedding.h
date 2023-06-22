#ifndef WEDDING
#define WEDDING

#include <iostream>
#include <ctime>
#include "Note.h"
#include "Organisation_Element.h"
#include "Schedule.h"
#include "Person.h"

class Wedding
{
private:

    time_t dateOfWedding;
    // Date of the wedding
    Engaged* groomAndBride;
    // Pointer to the Engaged couple of which is this wedding
    Guest* guestList;
    // Pointer to the guests list
    Wedding_Setting* weddingSetting;
    // Pointer to the list of wedding settings
    Location* locations;
    // Pointer to the list of the locations
    Schedule* timePeriods;
    // Pointer to the schedule of the wedding
    Note* notes;
    // Pointer to the notes
    Wedding* next;
    // Pointer to the next wedding

public:

    Wedding(time_t dateOfWedding, Engaged* groomAndBride);
    ~Wedding();
    Wedding(const Wedding& w);
    Wedding& operator= (const Wedding& w);
    // Basic methods of a class like Constructor, Destructor, Copy Constructor and Assignment operator

    time_t& refDateOfWedding();
    Engaged*& refGroomAndBride();
    Guest*& refGuestList();
    Wedding_Setting*& refWeddingSettingList();
    Location*& refLocationsList();
    Schedule*& refSchedule();
    Note*& refNotes();
    Wedding*& refNext();
    // Basic referential methods for access to the data and lists of the object

    // Special Methods
    int countGuest() const;
    // Methods counts how many guests are on the guest list
    // If its empty, methods returns 0
    int countMeatEaters() const;
    // Methods to count how many persons are meat eaters (clients and guests)
    // If guests list is empty it will count 0 for them
    int countVegetarians() const;
    // Methods to count how many persons are vegetarians (clients and guests)
    // If guests list is empty it will count 0 for them
    int countVegans() const;
    // Methods to count how many persons are vegans (clients and guests)
    // If guests list is empty it will count 0 for them
    int countDiverse() const;
    // Methods to count how many persons have diverse food preferences (clients and guests)
    // If guests list is empty it will count 0 for them
    int countConfirmedGuests() const;
    // Method to count how many guests confirmed their presence
    // If guest list is empty it will count 0
    int countLocations() const;
    // Method to count how many locations are on the locations list
    // If list is empty it will count 0
    float countLocationCost() const;
    // Method to count cost of every location from the list, cost of each location is multiplied by the number of guests
    // If list is empty it will count 0
    int countCompletionOfLocations() const;
    // Method to count how many locations from the list still are needed to be reserved
    // If list is empty it will count 0
    int countWeddingSettings() const;
    // Method to count how many wedding settings are on the wedding settings list
    // If list is empty it will count 0
    float countWeddingSettingCost() const;
    // Method to count summarised cost of every wedding setting from the list
    // If list is empty it will count 0
    int countCompletionOfWeddingSetting() const;
    // Method to count how many wedding settings from the list still are needed to be prepared
    // If list is empty it will count 0
    period checkScheduleLength() const;
    // Method to check how long is the schedule
    // If list is empty it will count 0
    int countNotes() const;
    // Method to count how many notes are on the list
    // If list is empty it will count 0

    Wedding operator+(Guest& g);
    Wedding operator+(Location& l);
    Wedding operator+(Wedding_Setting& we);
    Wedding operator+(Schedule& s);
    Wedding operator+(Note& n);
    // Operators for simpler manipulation of the object when adding new elements

    friend ostream& operator<< (ostream& os, const period& p);
    friend ostream& operator<< (ostream& os, const Wedding& w);
    // Methods to display data of the wedding
};

#endif // WEDDING
