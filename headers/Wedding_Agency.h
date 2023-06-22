#ifndef WEDDING_AGENCY
#define WEDDING_AGENCY

#include <string.h>
#include "Person.h"
#include "Wedding.h"

using namespace std;

// Methods will have versions to find a wedding to modify by couples surname or date of wedding, if on the client list exists more than one couple with such surname, program will display their info and dates of their weddings so user can still find the wedding by the date

class Wedding_Agency
{

    Engaged* clients;
    Wedding* weddings;
    // These are pointers to main lists of the program

    time_t currentDate;
    // Date variable so program can check if the wedding has proper date

private:

    void removeAllElements();
    void copyAllElements(const Wedding_Agency& wa);
    // Methods to simplify the memory management of the object

    Wedding* findWedding(string surname) const;
    Wedding* findWedding(time_t date) const;
    // Methods for finding pointers to specific wedding based on date of wedding / surname of
    // the couple, return nullptr if such wedding is not found

    template <typename searchMethod>
    bool isGuest(searchMethod method, string guestSurname, string guestName) const;
    template <typename searchMethod>
    bool isLocation(searchMethod method, string title) const;
    template <typename searchMethod>
    bool isSetting(searchMethod method, string title) const;
    template <typename searchMethod>
    bool isPeriod(searchMethod method, period begining, period ending) const;
    template <typename searchMethod>
    bool isNote(searchMethod method, string title) const;
    // Methods to detect if the specific elements exist in searched wedding

public:

    Wedding_Agency();
    ~Wedding_Agency();
    Wedding_Agency(const Wedding_Agency& wa);
    Wedding_Agency& operator=(const Wedding_Agency& wa);
    // Basic methods of a class like Constructor, Destructor, Copy Constructor and Assignment operator


    Engaged*& refClients();
    Wedding*& refWeddings();
    // Basic reference methods

    // Management of Elements

    void insertClient(string surname, time_t date, float budget);
    void insertClient(string surname, time_t date);
    // Methods for inserting a clients with given data to the list, creation of the client also creates wedding in the weddings list

    template <typename searchMethod>
    void addClientInfo(searchMethod method, string groomName, string bridesName, string contact, string email);
    // Method to add additional, optional info about a client, will not add if such couple does not exists

    void removeWedding(time_t date);
    // Method to remove wedding and connected client to it from the lists
    // Method delete the data and will not remove if such elements don't exist

    template <typename searchMethod>
    void addGuest(searchMethod method, string guestSurname, string guestName, food_preference fp);
    // Methods to add guest to specific weddings
    // Methods will not create data if such a wedding does not exist

    template <typename searchMethod>
    void removeGuest(searchMethod method, string guestSurname, string guestName);
    template <typename searchMethod>
    void removeGuest(searchMethod method, string guestSurname);
    // Methods remove guests from the specific lists, first version lets remove specific guest and second let’s remove everyone with the same surname
    // Methods delete the data and will not remove if such elements don't exist

    template <typename searchMethod>
    void addLocation(searchMethod method, string title, string address, int guestCapacity,  float price);
    // Methods to add Locations to specific weddings
    // Methods will not create data if such a wedding does not exist

    template <typename searchMethod>
    void removeLocation(searchMethod method, string title);
    // Methods to remove Location by their Names from specific weddings
    // Methods delete the data and will not remove if such elements don't exist

    template <typename searchMethod>
    void addWeddingSetting(searchMethod method, string title, float price, string description);
    // Methods to add WeddingSetting to specific weddings
    // Methods will not create data if such a wedding does not exist

    template <typename searchMethod>
    void removeWeddingSetting(searchMethod method, string title);
    // Methods to remove WeddingSetting by their titles from specific weddings
    // Methods delete the data and will not remove if such elements don't exist

    template <typename searchMethod>
    void addSchedulePeriod(searchMethod method, period beginning, period ending, string description);
    // Methods to add Schedule Period to specific weddings
    // Methods will not create data if such a wedding does not exist

    template <typename searchMethod>
    void removeSchedulePeriod(searchMethod method, period beginning, period ending);
    // Methods to remove Schedule Periods by their time spans
    // Methods delete the data and will not remove if such elements don't exist

    template <typename searchMethod>
    void addNote(searchMethod method, string title, string scribble);
    // Methods to add Note to specific weddings
    // Methods will not create data if such a wedding does not exist

    template <typename searchMethod>
    void removeNote(searchMethod method, string title);
    // Methods to remove Note by their titles
    // Methods delete the data and will not remove if such elements don't exist

    // Changing Data of Elements
    // Clients:

    template <typename searchMethod>
    void changeClientsFoodPreferences(searchMethod method, food_preference groomFP, food_preference bridesFP);
    template <typename searchMethod>
    void changeClientsBudget(searchMethod method, float budget);
    // Methods to change specific data of each existing clients
    // If such client does not exist nothing happens
    // Guests:

    template <typename searchMethod>
    void confirmPresence(searchMethod method, string guestSurname, string guestName);
    // Methods to change confirmation of specific guests
    // If such Guest does not exist nothing happens

    template <typename searchMethod>
    void changeFoodPreferenceGuest(searchMethod method, string guestSurname, string guestName, food_preference fp);
    // Methods to change food preference of specific guests
    // If such Guest does not exist nothing happens
    // Location:

    template <typename searchMethod>
    void changeReservationStateLocation(searchMethod method, string title);
    // Methods to change reservation status of specific locations
    // If such Location does not exist nothing happens
    // Wedding Setting:

    template <typename searchMethod>
    void changeReservationStateWeddingSetting(searchMethod method, string title);
    // Methods to change reservation status of specific wedding settings
    // If such wedding setting does not exist nothing happens
    // Schedule:

    template <typename searchMethod>
    void changeScheduleDescription(searchMethod method, period beginning, period ending, string description);
    // Methods to change description of specific schedule
    // If such schedule does not exists nothing happens
    // Note:

    template <typename searchMethod>
    void changeNote(searchMethod method, string title, string scribble);
    // Methods to change scribble of specific note
    // If such note does not exist nothing happens
    // Operators

    // Display
    // _Whole list:

    friend ostream& operator << (ostream& os, const Wedding_Agency& wa);
    // Operator will display contents of each lists segregated
    // If any list is empty program will inform about it
    // _Whole wedding:

    template <typename searchMethod>
    void displayWedding(searchMethod method);
    // Method to display specific info about given wedding
    // If any lists are empty program will inform about it

    // Method to check properties of objects

    bool ifSorted();
    // Method returns true if weddings are sorted, otherwise it returns false

    int countClients();
    // Method returns number of clients in the list, if list is empty it returns 0

    int countWeddings();
    // Method returns number of weddings in the list, if list is empty it returns 0

    // Main Functionality

    template <typename searchMethod>
    bool checkCost(searchMethod method) const;
    // Methods to check if cost of the wedding is not over the budget of the client and display whole cost
    // In situation of not defined budget method will still compare values and display the whole cost
    // If wedding does not exist method will return false

    template <typename searchMethod>
    bool checkOrganisation(searchMethod method) const;
    // Methods to check which organisation elements are not completed
    // If list is empty program does not check them
    // If wedding does not exist method will return false

    template <typename searchMethod>
    bool checkGuestCapacity(searchMethod method) const;
    // Methods to check if reserved location aren't too small for all guests and for the confirmed ones
    // If guests list is empty, method will not check it and return false
    // If Locations list is empty, method will not check it and return false
    // If wedding does not exist method will return false

    template <typename searchMethod>
    bool checkGuestConfirmation(searchMethod method) const;
    // Methods to check how many guests have confirmed their presence
    // If guests list is empty, method will not check it and return false
    // If wedding does not exist method will return false

    template <typename searchMethod>
    bool checkExpensiveElements(searchMethod method) const;
    // Methods to display the most expensive location and three most expensive settings
    // If there exists less than 3 settings, method will still display the possible elements
    // If there does not exists both of the lists, method will return false
    // If wedding does not exist method will return false

    template <typename searchMethod>
    bool checkDishesCount(searchMethod method) const;
    // Methods to display how many dishes are needed to be prepared based on the food preferences of the guests and clients
    // If guests list is empty, method will still check preferences of the clients
    // If wedding does not exist method will return false

    bool checkDateOfNearestWedding() const;
    // Method will display info of the first wedding in the list (because list of weddings is sorted by dates)
    // If weddings list does not exist method will return false

    bool displayWeddingFromTimePeriod(time_t from, time_t to) const;
    // Method will display the weddings given from the specific time period
    // If weddings list does not exist method will return false
    // If there are no weddings in this time period, method will inform about it and return false
};

#endif // WEDDING_AGENCY
