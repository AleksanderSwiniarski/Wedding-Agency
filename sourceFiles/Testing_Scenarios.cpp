#include <iostream>
#include <string>
#include "Testing_Scenarios.h"
#include "Wedding_Agency.h"

#define DAY 86400
#define MONTH 2678400
#define YEAR 32140800

bool Testing_Scenarios::addingClients()
{
    bool flag = true;

    //Checking if object is empty

    Wedding_Agency* agencyPtr = new Wedding_Agency();

    flag = flag && agencyPtr->countWeddings() == 0 && agencyPtr->countClients() == 0;

    //Checking if objects are connected

    time_t testingDate = time(0);

    testingDate += 4*MONTH;

    agencyPtr->insertClient("Tester_1", testingDate);

    flag = flag && agencyPtr->countWeddings() == 1 && agencyPtr->countClients() == 1 &&
            agencyPtr->refWeddings()->refGroomAndBride() == agencyPtr->refClients() &&
            agencyPtr->refClients()->refOwnWedding() == agencyPtr->refWeddings();

    //Checking if sorted & and if Clients with the same Surnames are added to the list

    testingDate += 8*MONTH;
    agencyPtr->insertClient("Tester_1", testingDate);
    testingDate += 4*MONTH;
    agencyPtr->insertClient("Tester_1", testingDate, 3000);
    testingDate -= 7*MONTH;
    agencyPtr->insertClient("Tester_1", testingDate);
    testingDate += YEAR;
    agencyPtr->insertClient("Tester_1", testingDate);

    flag = flag && agencyPtr->countWeddings() == 5 && agencyPtr->countClients() == 5 && agencyPtr->ifSorted();

    //Adding Wedding with already reserved date

    agencyPtr->insertClient("Tester_1", testingDate);

    flag = flag && agencyPtr->countWeddings() == 5 && agencyPtr->countClients() == 5 && agencyPtr->ifSorted();

    //Adding client with date before the current one

    testingDate -= 20*YEAR;

    agencyPtr->insertClient("Tester_1", testingDate);

    flag = flag && agencyPtr->countWeddings() == 5 && agencyPtr->countClients() == 5 && agencyPtr->ifSorted();

    return flag;
}

bool Testing_Scenarios::agencyIndependence()
{
    bool flag = true;

    // Creating two distinct objects

    time_t testingDate = time(0);

    Wedding_Agency* firstAgency = new Wedding_Agency();
    Wedding_Agency* secondAgency = new Wedding_Agency();

    // Checking if empty after creating

    flag = flag && firstAgency->refClients() == nullptr && firstAgency->refWeddings() == nullptr
                && secondAgency->refClients() == nullptr && secondAgency->refWeddings() == nullptr;

    // Adding client to only one object

    testingDate += 2*YEAR;
    time_t firstDate = testingDate;

    firstAgency->insertClient("First Agency", firstDate, 5000);

    flag = flag && firstAgency->refClients() != nullptr && firstAgency->refWeddings() != nullptr
                && firstAgency->refClients()->refSurname() == "First Agency" && firstAgency->refWeddings()->refDateOfWedding() == firstDate
                && firstAgency->refClients()->refBudget() == 5000
                && secondAgency->refClients() == nullptr && secondAgency->refWeddings() == nullptr;

    // Adding elements to wedding in the first agency

    testingDate += 3*YEAR;
    time_t secondDate = testingDate;
    period beginning, ending;
    beginning.hour = 12;
    beginning.minute = 30;
    ending.hour = 18;
    ending.minute = 0;

    secondAgency->insertClient("Second Agency", secondDate, 3500);
    secondAgency->addClientInfo("Second Agency", "Tester Name", "Tester Name", "Test contact", "Test email");
    secondAgency->addGuest("Second Agency", "Test Surname1", "Test Name1", vegetarian);
    secondAgency->addGuest("Second Agency", "Test Surname2", "Test Name2", diverse);
    secondAgency->addLocation("Second Agency", "Location1", "Address", 200, 30);
    secondAgency->addLocation("Second Agency", "Location2", "Address", 150, 50);
    secondAgency->addWeddingSetting("Second Agency", "Setting1", 200, "Description1");
    secondAgency->addSchedulePeriod("Second Agency", beginning, ending, "Description");
    secondAgency->addNote("Second Agency", "Note1", "Scribble1");

    period testingPeriod1, testingPeriod2;
    testingPeriod1.hour = 0;
    testingPeriod1.minute = 0;
    testingPeriod2.hour = 5;
    testingPeriod2.minute = 30;

                //First agency
    flag = flag && firstAgency->refClients() != nullptr && firstAgency->refWeddings() != nullptr
                && firstAgency->refClients()->refSurname() == "First Agency" && firstAgency->refWeddings()->refDateOfWedding() == firstDate
                && firstAgency->refClients()->refBudget() == 5000
                && firstAgency->refWeddings()->countGuest() == 0
                && firstAgency->refWeddings()->countLocations() == 0
                && firstAgency->refWeddings()->countWeddingSettings() == 0
                && firstAgency->refWeddings()->checkScheduleLength() == testingPeriod1
                && firstAgency->refWeddings()->countNotes() == 0
                //Second agency
                && secondAgency->refClients() != nullptr && secondAgency->refWeddings() != nullptr
                && secondAgency->refClients()->refSurname() == "Second Agency" && secondAgency->refWeddings()->refDateOfWedding() == secondDate
                && secondAgency->refClients()->refBudget() == 3500
                // Client info
                && secondAgency->refClients()->refName() == "Tester Name" && secondAgency->refClients()->refBridesName() == "Tester Name"
                && secondAgency->refClients()->refContactNumber() == "Test contact" && secondAgency->refClients()->refEmail() == "Test email"
                //Guest
                && secondAgency->refWeddings()->countGuest() == 2 && secondAgency->refWeddings()->refGuestList()->refFoodPreference() == vegetarian
                && secondAgency->refWeddings()->refGuestList()->refName() == "Test Name1" && secondAgency->refWeddings()->refGuestList()->refSurname() == "Test Surname1"
                && secondAgency->refWeddings()->refGuestList()->refNext()->refName() == "Test Name2" && secondAgency->refWeddings()->refGuestList()->refNext()->refSurname() == "Test Surname2"
                && secondAgency->refWeddings()->refGuestList()->refNext()->refFoodPreference() == diverse
                //Location
                && secondAgency->refWeddings()->countLocations() == 2 && secondAgency->refWeddings()->refLocationsList()->refTitle() == "Location1"
                && secondAgency->refWeddings()->refLocationsList()->refAdress() == "Address" && secondAgency->refWeddings()->refLocationsList()->refCostPerGuest() == 30
                && secondAgency->refWeddings()->refLocationsList()->refguestCapacity() == 200
                && secondAgency->refWeddings()->refLocationsList()->refNext()->refTitle() == "Location2"
                && secondAgency->refWeddings()->refLocationsList()->refNext()->refAdress() == "Address"
                && secondAgency->refWeddings()->refLocationsList()->refNext()->refCostPerGuest() == 50
                && secondAgency->refWeddings()->refLocationsList()->refNext()->refguestCapacity() == 150
                //Setting
                && secondAgency->refWeddings()->countWeddingSettings() == 1
                && secondAgency->refWeddings()->refWeddingSettingList()->refTitle() == "Setting1"
                && secondAgency->refWeddings()->refWeddingSettingList()->refDescription() == "Description1"
                && secondAgency->refWeddings()->refWeddingSettingList()->refPrice() == 200
                //Period
                && secondAgency->refWeddings()->checkScheduleLength() == testingPeriod2
                && secondAgency->refWeddings()->refSchedule()->refBeginning() == beginning
                && secondAgency->refWeddings()->refSchedule()->refEnding() == ending
                && secondAgency->refWeddings()->refSchedule()->refDescription() == "Description"
                //Note
                && secondAgency->refWeddings()->countNotes() == 1
                && secondAgency->refWeddings()->refNotes()->refTitle() == "Note1"
                && secondAgency->refWeddings()->refNotes()->refScribble() == "Scribble1"
                ;
    return flag;
}

bool Testing_Scenarios::findingWedding()
{
    bool flag = true;

    // Checking if find wedding method will return proper pointer

    Wedding_Agency* agencyPtr = new Wedding_Agency();

    time_t testingDate = time(0);

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate);

    testingDate -= 5*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    testingDate += 22*DAY;
    agencyPtr->insertClient("Tester_3", testingDate);

    testingDate += 22*DAY;
    agencyPtr->insertClient("Tester_3", testingDate);

    flag = flag && agencyPtr->countWeddings() == 4 && agencyPtr->countClients() == 4 && agencyPtr->ifSorted();

    // To check finding method we will check Costs of 3 of wedding

    // Finding by date

    cout << "Wedding of Tester_3 by date: " << endl;
    flag = flag && agencyPtr->checkCost(testingDate);
    cout << endl;

    // Finding by Surname

    cout << "Wedding of Tester_1 by Surname: " << endl;
    flag = flag && agencyPtr->checkCost("Tester_1");
    cout << endl;

    // Finding by surname Client with repeating surname - Should print every client with this Surname

    cout << "Wedding of Tester_3 (Repeating) by Surname: " << endl;
    flag = flag && !agencyPtr->checkCost("Tester_3");

    return flag;
}

bool Testing_Scenarios::removingOfWedding()
{
    bool flag = true;
    time_t testingDate = time(0);

    Wedding_Agency* agencyPtr = new Wedding_Agency();

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate);

    testingDate -= 5*DAY;
    time_t check = testingDate;
    agencyPtr->insertClient("Tester_2", testingDate);

    testingDate += 22*DAY;
    agencyPtr->insertClient("Tester_3", testingDate);

    flag = flag && agencyPtr->countWeddings() == 3 && agencyPtr->countClients() == 3 && agencyPtr->ifSorted();

    //Deleting existing wedding

    agencyPtr->removeWedding(check);

    flag = flag && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2 && agencyPtr->ifSorted();

    //Deleting non existent wedding

    testingDate += 22*DAY;
    agencyPtr->removeWedding(testingDate);

    flag = flag && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2 && agencyPtr->ifSorted();

    return flag;

}

bool Testing_Scenarios::addingClientInfo()
{
    bool flag = true;
    time_t testingDate = time(0);

    Wedding_Agency* agencyPtr = new Wedding_Agency();

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate);

    testingDate -= 5*DAY;
    time_t check = testingDate;
    agencyPtr->insertClient("Tester_2", testingDate);

    testingDate += 22*DAY;
    agencyPtr->insertClient("Tester_3", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    flag = flag && agencyPtr->countWeddings() == 3 && agencyPtr->countClients() == 3 && agencyPtr->ifSorted();

    // Changing data of existing client

    agencyPtr->addClientInfo("Tester_2", "Tester Groom", "Tester Bride", "Tester Contact", "Tester Email");
    agencyPtr->changeClientsFoodPreferences("Tester_2", vegan, vegetarian);
    agencyPtr->changeClientsBudget("Tester_2", 3000);

    flag = flag && agencyPtr->countWeddings() == 3 && agencyPtr->countClients() == 3 && agencyPtr->ifSorted() &&
            weddingPtr->refGroomAndBride()->refFoodPreference() == vegan &&
            weddingPtr->refGroomAndBride()->refBridesFoodPreference() == vegetarian &&
            weddingPtr->refGroomAndBride()->refBudget() == 3000 &&
            weddingPtr->refGroomAndBride()->refName() == "Tester Groom" &&
            weddingPtr->refGroomAndBride()->refBridesName() == "Tester Bride" &&
            weddingPtr->refGroomAndBride()->refContactNumber() == "Tester Contact" &&
            weddingPtr->refGroomAndBride()->refEmail() == "Tester Email";

    // Changing budget for Negative value

    agencyPtr->changeClientsBudget("Tester_2", -5000);

    flag = flag && agencyPtr->countWeddings() == 3 && agencyPtr->countClients() == 3 && agencyPtr->ifSorted() && weddingPtr->refGroomAndBride()->refBudget() > 0;

    // Changing info of non existing client
    agencyPtr->addClientInfo("Tester_4", "Tester Groom", "Tester Bride", "Tester Contact", "Tester Email");
    agencyPtr->changeClientsBudget("Tester_4", 3000);

    flag = flag && agencyPtr->countWeddings() == 3 && agencyPtr->countClients() == 3 && agencyPtr->ifSorted();

    return flag;
}

bool Testing_Scenarios::addingGuest()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    //Empty Wedding:

    flag = flag && weddingPtr->countGuest() == 0 && weddingPtr->countMeatEaters() == 0;

    //Adding one guest

    agencyPtr->addGuest("Tester_1", "Test_Surname", "Test_Name", vegan);

    flag = flag && weddingPtr->countGuest() == 1 && weddingPtr->countVegans() == 1 && weddingPtr->countMeatEaters() == 0;

    //Adding multiple guest and repeating ones

    agencyPtr->addGuest("Tester_1", "Test_Surname1", "Test_Name1", vegan);
    agencyPtr->addGuest("Tester_1", "Test_Surname", "Test_Name", meatEater);
    agencyPtr->addGuest("Tester_1", "Test_Surname2", "Test_Name2", meatEater);
    agencyPtr->addGuest("Tester_1", "Test_Surname3", "Test_Name3", meatEater);
    agencyPtr->addGuest("Tester_1", "Test_Surname", "Test_Name", vegan);

    flag = flag && weddingPtr->countGuest() == 4 && weddingPtr->countMeatEaters() == 2 && weddingPtr->countVegans() == 2;

    //Adding guests to non existing wedding

    agencyPtr->addGuest("Tester_3", "Test_Surname1", "Test_Name1", vegan);
    agencyPtr->addGuest("Tester_3", "Test_Surname", "Test_Name", meatEater);
    agencyPtr->addGuest("Tester_3", "Test_Surname2", "Test_Name2", meatEater);

    flag = flag && agencyPtr->ifSorted();

    return flag;
}

bool Testing_Scenarios::removingGuests()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->addGuest("Tester_1", "Test_Surname1", "Test_Name1", vegan);
    agencyPtr->addGuest("Tester_1", "Test_Surname2", "Test_Name2", vegan);
    agencyPtr->addGuest("Tester_1", "Same", "Test_Name3", vegan);
    agencyPtr->addGuest("Tester_1", "Same", "Test_Name4", vegan);
    agencyPtr->addGuest("Tester_1", "Same", "Test_Name5", vegan);


    flag = flag && agencyPtr->ifSorted() && weddingPtr->countGuest() == 5 && weddingPtr->countVegans() == 5 && agencyPtr->countWeddings() == 2;

    // Removing one and guests with the same Surname "Same" and non existing one

    agencyPtr->removeGuest("Tester_1", "Test_Surname2", "Test_Name2");
    agencyPtr->removeGuest("Tester_1", "Same");
    agencyPtr->removeGuest("Tester_1", "Test_Surname6", "Test_Name6");
    agencyPtr->removeGuest("Tester_1", "Same_not");

    flag = flag && agencyPtr->ifSorted() && weddingPtr->countGuest() == 1 && weddingPtr->countVegans() == 1 && agencyPtr->countWeddings() == 2;

    // Removing guest from non existing wedding

    agencyPtr->removeGuest("Tester_3", "Test_Surname2", "Test_Name2");
    agencyPtr->removeGuest("Tester_3", "Same");

    flag = flag && agencyPtr->ifSorted() && weddingPtr->countGuest() == 1 && weddingPtr->countVegans() == 1 && agencyPtr->countWeddings() == 2;

    return flag;
}

bool Testing_Scenarios::addingLocations()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->addLocation("Non_Existing_Surname", "Title1", "Address1", 300, 300);

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    // Adding locations and also repeating ones

    agencyPtr->addGuest("Tester_1", "Test_Surname1", "Test_Name1", vegan);

    agencyPtr->addLocation("Tester_1", "Title1", "Address1", 300, 300);
    agencyPtr->addLocation("Tester_1", "Title2", "Address2", 250, 250);
    agencyPtr->addLocation("Tester_1", "Title3", "Address3", 300, 123);
    agencyPtr->addLocation("Tester_1", "Title1", "Address4", 32, 300);
    agencyPtr->addLocation("Tester_1", "Title4", "Address5", 300, 459);
    agencyPtr->addLocation("Tester_1", "Title1", "Address6", 78, 123);

    flag = flag && weddingPtr->countLocations() == 4 && weddingPtr->countLocationCost() == 1132
                && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2;

    return flag;
}

bool Testing_Scenarios::removingLocations()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->removeLocation("Non_Existing_Surname", "Title1");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    // Removing non existing and existing locations

    agencyPtr->addGuest("Tester_1", "Test_Surname1", "Test_Name1", vegan);

    agencyPtr->addLocation("Tester_1", "Title1", "Address1", 300, 300);
    agencyPtr->addLocation("Tester_1", "Title2", "Address2", 250, 250);
    agencyPtr->addLocation("Tester_1", "Title3", "Address3", 300, 123);
    agencyPtr->addLocation("Tester_1", "Title4", "Address4", 32, 300);
    agencyPtr->addLocation("Tester_1", "Title5", "Address5", 300, 459);
    agencyPtr->addLocation("Tester_1", "Title6", "Address6", 78, 123);

    agencyPtr->removeLocation("Tester_1", "Title1");
    agencyPtr->removeLocation("Tester_1", "Title4");
    agencyPtr->removeLocation("Tester_1", "Title6");
    agencyPtr->removeLocation("Tester_1", "Title10");

    flag = flag && weddingPtr->countLocations() == 3 && weddingPtr->countLocationCost() == 832
                && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2;

    return flag;
}

bool Testing_Scenarios::addingWeddingSettings()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->addWeddingSetting("Non_Existing_Surname", "Title1", 300, "Desc.");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    // Adding settings and also repeating ones

    agencyPtr->addWeddingSetting("Tester_1", "Title1", 300, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title2", 800, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title3", 750, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title1", 250, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title4", 100, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title1", 300, "Desc.");

    flag = flag && weddingPtr->countWeddingSettings() == 4 && weddingPtr->countWeddingSettingCost() == 1950
                && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2;

    return flag;
}

bool Testing_Scenarios::removingWeddingSettings()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->removeWeddingSetting("Non_Existing_Surname", "Title1");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    // Removing settings and also non existing ones

    agencyPtr->addWeddingSetting("Tester_1", "Title1", 300, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title2", 800, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title3", 750, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title4", 250, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title5", 100, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title6", 300, "Desc.");

    agencyPtr->removeWeddingSetting("Tester_1", "Title1");
    agencyPtr->removeWeddingSetting("Tester_1", "Title2");
    agencyPtr->removeWeddingSetting("Tester_1", "Title4");
    agencyPtr->removeWeddingSetting("Tester_1", "Title6");
    agencyPtr->removeWeddingSetting("Tester_1", "Title60");

    flag = flag && weddingPtr->countWeddingSettings() == 2 && weddingPtr->countWeddingSettingCost() == 850
                && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2;

    return flag;
}

bool Testing_Scenarios::addingSchedulePeriods()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    period beginning, beginning1, beginning2, beginning3, beginning4, beginning5;
    period ending, ending1, ending2, ending3, ending4, ending5;

    beginning.hour = 8;
    beginning.minute = 30;
    beginning1.hour = 10;
    beginning1.minute = 0;
    beginning2.hour = 14;
    beginning2.minute = 25;
    beginning3.hour = 7;
    beginning3.minute = 0;
    beginning4.hour = 15;
    beginning4.minute = 30;
    beginning5.hour = 20;
    beginning5.minute = 0;
    ending.hour = 11;
    ending.minute = 30;
    ending1.hour = 13;
    ending1.minute = 30;
    ending2.hour = 17;
    ending2.minute = 30;
    ending3.hour = 6;
    ending3.minute = 0;
    ending4.hour = 19;
    ending4.minute = 30;
    ending5.hour = 21;
    ending5.minute = 30;


    agencyPtr->addSchedulePeriod("Non_Existing_Surname", beginning, ending, "Non_Existing_Surname");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    // Adding periods and also repeating ones and wrong ones

    agencyPtr->addSchedulePeriod("Tester_1", beginning, ending, "Period_0");
    agencyPtr->addSchedulePeriod("Tester_1", beginning1, ending1, "Period_1");
    agencyPtr->addSchedulePeriod("Tester_1", beginning2, ending2, "Period_2");
    agencyPtr->addSchedulePeriod("Tester_1", beginning3, ending3, "Period_3");
    agencyPtr->addSchedulePeriod("Tester_1", beginning, ending, "Period_0");
    agencyPtr->addSchedulePeriod("Tester_1", beginning4, ending4, "Period_4");
    agencyPtr->addSchedulePeriod("Tester_1", beginning5, ending5, "Period_5");
    agencyPtr->addSchedulePeriod("Tester_1", beginning, ending, "Period_0");

    period check;

    check.hour = 13;
    check.minute = 0;

    flag = flag && weddingPtr->checkScheduleLength() == check && agencyPtr->ifSorted()
                && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    return flag;
}

bool Testing_Scenarios::removingSchedulesPeriods()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    period beginning, beginning1, beginning2, beginning3, beginning4, beginning5 , beginning8;
    period ending, ending1, ending2, ending3, ending4, ending5, ending8;

    beginning.hour = 8;
    beginning.minute = 30;
    beginning1.hour = 10;
    beginning1.minute = 0;
    beginning2.hour = 14;
    beginning2.minute = 25;
    beginning3.hour = 7;
    beginning3.minute = 0;
    beginning4.hour = 15;
    beginning4.minute = 30;
    beginning5.hour = 20;
    beginning5.minute = 0;
    ending.hour = 11;
    ending.minute = 30;
    ending1.hour = 13;
    ending1.minute = 30;
    ending2.hour = 17;
    ending2.minute = 30;
    ending3.hour = 12;
    ending3.minute = 0;
    ending4.hour = 19;
    ending4.minute = 30;
    ending5.hour = 21;
    ending5.minute = 30;

    agencyPtr->addSchedulePeriod("Non_Existing_Surname", beginning, ending, "Non_Existing_Surname");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    // Adding then removing periods

    agencyPtr->addSchedulePeriod("Tester_1", beginning, ending, "Period_0");
    agencyPtr->addSchedulePeriod("Tester_1", beginning1, ending1, "Period_1");
    agencyPtr->addSchedulePeriod("Tester_1", beginning2, ending2, "Period_2");
    agencyPtr->addSchedulePeriod("Tester_1", beginning3, ending3, "Period_3");
    agencyPtr->addSchedulePeriod("Tester_1", beginning4, ending4, "Period_4");
    agencyPtr->addSchedulePeriod("Tester_1", beginning5, ending5, "Period_5");

    beginning8.hour = 14;
    beginning8.minute = 30;

    ending8.hour = 23;
    ending8.minute = 45;

    agencyPtr->removeSchedulePeriod("Tester_1", beginning, ending);
    agencyPtr->removeSchedulePeriod("Tester_1", beginning2, ending2);
    agencyPtr->removeSchedulePeriod("Tester_1", beginning3, ending3);
    agencyPtr->removeSchedulePeriod("Tester_1", beginning5, ending5);
    agencyPtr->removeSchedulePeriod("Tester_1", beginning5, ending5);
    agencyPtr->removeSchedulePeriod("Tester_1", beginning8, ending8);

    period check;

    check.hour = 9;
    check.minute = 30;

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2
                && weddingPtr->checkScheduleLength() == check;


    return flag;
}

bool Testing_Scenarios::addingNotes()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->addNote("Non_Existing_Surname", "Title", "Scribble");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    //Adding notes and repeating ones

    agencyPtr->addNote("Tester_1", "Title", "Scribble");
    agencyPtr->addNote("Tester_1", "Title1", "Scribble1");
    agencyPtr->addNote("Tester_1", "Title2", "Scribble2");
    agencyPtr->addNote("Tester_1", "Title3", "Scribble3");
    agencyPtr->addNote("Tester_1", "Title", "Scribble");
    agencyPtr->addNote("Tester_1", "Title4", "Scribble4");
    agencyPtr->addNote("Tester_1", "Title5", "Scribble5");
    agencyPtr->addNote("Tester_1", "Title6", "Scribble6");
    agencyPtr->addNote("Tester_1", "Title7", "Scribble7");
    agencyPtr->addNote("Tester_1", "Title", "Scribble");

    flag = flag && weddingPtr->countNotes() == 8 && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2
                && agencyPtr->countClients() == 2;

    return flag;
}

bool Testing_Scenarios::removingNotes()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->removeNote("Non_Existing_Surname", "Title");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    // Removing notes and non existing ones

    agencyPtr->addNote("Tester_1", "Title", "Scribble");
    agencyPtr->addNote("Tester_1", "Title1", "Scribble1");
    agencyPtr->addNote("Tester_1", "Title2", "Scribble2");
    agencyPtr->addNote("Tester_1", "Title3", "Scribble3");
    agencyPtr->addNote("Tester_1", "Title4", "Scribble4");
    agencyPtr->addNote("Tester_1", "Title5", "Scribble5");
    agencyPtr->addNote("Tester_1", "Title6", "Scribble6");
    agencyPtr->addNote("Tester_1", "Title7", "Scribble7");

    agencyPtr->removeNote("Tester_1", "Title");
    agencyPtr->removeNote("Tester_1", "Title2");
    agencyPtr->removeNote("Tester_1", "Title4");
    agencyPtr->removeNote("Tester_1", "Title5");
    agencyPtr->removeNote("Tester_1", "Title7");
    agencyPtr->removeNote("Tester_1", "Title10");

    flag = flag && weddingPtr->countNotes() == 3 && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2
                && agencyPtr->countClients() == 2;

    return flag;
}

bool Testing_Scenarios::changingClientsData()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for not existing lists

    agencyPtr->addClientInfo("Non_Existing_Surname", "Test_Groom_Name", "Test_Brides_Name", "Test_Contact", "Test_Email");
    agencyPtr->changeClientsBudget("Non_Existing_Surname", 6500);

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 0 && agencyPtr->countClients() == 0;

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);
    testingDate += 25*DAY;
    agencyPtr->insertClient("Tester_3", testingDate);
    testingDate -= 17*DAY;
    agencyPtr->insertClient("Tester_4", testingDate);
    testingDate += 80*DAY;
    agencyPtr->insertClient("Tester_5", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->addClientInfo("Non_Existing_Surname", "Test_Groom_Name", "Test_Brides_Name", "Test_Contact", "Test_Email");
    agencyPtr->changeClientsBudget("Non_Existing_Surname", 6500);

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 5 && agencyPtr->countClients() == 5;

    // Checking for existing client and different values

    agencyPtr->addClientInfo("Tester_1", "Groom1", "Bride1", "Contact1", "Email1");
    agencyPtr->addClientInfo("Tester_2", "Groom2", "Bride5", "Contact7", "Email4");
    agencyPtr->addClientInfo("Tester_3", "Groom4", "Bride2", "Contact6", "Email6");
    agencyPtr->addClientInfo("Tester_4", "Groom3", "Bride1", "Contact1", "Email7");
    agencyPtr->addClientInfo("Tester_5", "Groom5", "Bride5", "Contact12", "Email9");

    agencyPtr->changeClientsBudget("Tester_1", -500);
    agencyPtr->changeClientsBudget("Tester_2", 2000);
    agencyPtr->changeClientsBudget("Tester_3", 1000);
    agencyPtr->changeClientsBudget("Tester_4", 300);
    agencyPtr->changeClientsBudget("Tester_5", 1200);

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 5 && agencyPtr->countClients() == 5
                && weddingPtr->refGroomAndBride()->refBudget() == 300 && weddingPtr->refGroomAndBride()->refBridesName() == "Bride1"
                && weddingPtr->refGroomAndBride()->refEmail() == "Email1" && weddingPtr->refGroomAndBride()->refName() == "Groom1";

    return flag;
}

bool Testing_Scenarios::changingGuestsData()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for not existing lists

    agencyPtr->changeFoodPreferenceGuest("Non_Existing_Surname", "Non_Existing_Surname", "Non_Existing_Name", meatEater);
    agencyPtr->confirmPresence("Non_Existing_Surname", "Non_Existing_Surname", "Non_Existing_Name");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 0 && agencyPtr->countClients() == 0;

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->changeFoodPreferenceGuest("Non_Existing_Surname", "Non_Existing_Surname", "Non_Existing_Name", meatEater);
    agencyPtr->confirmPresence("Non_Existing_Surname", "Non_Existing_Surname", "Non_Existing_Name");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    // Checking for existing client and different values

    agencyPtr->addGuest("Tester_1", "Surname1", "Name1", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname2", "Name2", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname3", "Name3", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname4", "Name4", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname5", "Name5", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname6", "Name6", meatEater);

    agencyPtr->changeFoodPreferenceGuest("Tester_1", "Surname1", "Name1", vegan);
    agencyPtr->changeFoodPreferenceGuest("Tester_1", "Surname2", "Name2", vegetarian);
    agencyPtr->changeFoodPreferenceGuest("Tester_1", "Surname3", "Name3", vegan);
    agencyPtr->changeFoodPreferenceGuest("Tester_1", "Surname6", "Name6", vegan);

    agencyPtr->confirmPresence("Tester_1", "Surname1", "Name1");
    agencyPtr->confirmPresence("Tester_1", "Surname2", "Name2");
    agencyPtr->confirmPresence("Tester_1", "Surname4", "Name4");
    agencyPtr->confirmPresence("Tester_1", "Surname6", "Name6");

    flag = flag && weddingPtr->countGuest() == 6 && weddingPtr->countVegans() == 3 && weddingPtr->countVegetarians() == 1
                && weddingPtr->countMeatEaters() == 2 && weddingPtr->countConfirmedGuests() == 4 && agencyPtr->ifSorted()
                && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    return flag;
}

bool Testing_Scenarios::changingOrganisationElements()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for not existing lists

    agencyPtr->changeReservationStateLocation("Non_Existing_Surname", "Non_Existing_Title");
    agencyPtr->changeReservationStateWeddingSetting("Non_Existing_Surname", "Non_Existing_Title");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 0 && agencyPtr->countClients() == 0;

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->changeReservationStateLocation("Non_Existing_Surname", "Non_Existing_Title");
    agencyPtr->changeReservationStateWeddingSetting("Non_Existing_Surname", "Non_Existing_Title");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    // Checking for existing client and different values

    agencyPtr->addLocation("Tester_1", "Title1", "Address1", 300, 300);
    agencyPtr->addLocation("Tester_1", "Title2", "Address2", 250, 250);
    agencyPtr->addLocation("Tester_1", "Title3", "Address3", 300, 123);
    agencyPtr->addLocation("Tester_1", "Title4", "Address4", 32, 300);
    agencyPtr->addLocation("Tester_1", "Title5", "Address5", 300, 459);
    agencyPtr->addLocation("Tester_1", "Title6", "Address6", 78, 123);

    agencyPtr->addWeddingSetting("Tester_1", "Title1", 300, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title2", 800, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title3", 750, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title4", 250, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title5", 100, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title6", 300, "Desc.");

    agencyPtr->changeReservationStateLocation("Tester_1", "Title1");
    agencyPtr->changeReservationStateLocation("Tester_1", "Title4");
    agencyPtr->changeReservationStateLocation("Tester_1", "Title6");

    agencyPtr->changeReservationStateWeddingSetting("Tester_1", "Title1");
    agencyPtr->changeReservationStateWeddingSetting("Tester_1", "Title3");
    agencyPtr->changeReservationStateWeddingSetting("Tester_1", "Title5");
    agencyPtr->changeReservationStateWeddingSetting("Tester_1", "Title6");

    flag = flag && weddingPtr->countLocations() == 6 && weddingPtr->countWeddingSettings() == 6
                && weddingPtr->countCompletionOfLocations() == 3 && weddingPtr->countCompletionOfWeddingSetting() == 2
                && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    return flag;
}

bool Testing_Scenarios::changingSchedulesData()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for not existing lists

    period Non_Existing_Begining, Non_Existing_Ending;

    agencyPtr->changeScheduleDescription("Non_Existing_Surname", Non_Existing_Begining, Non_Existing_Ending, "Desc.");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 0 && agencyPtr->countClients() == 0;

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->changeScheduleDescription("Non_Existing_Surname", Non_Existing_Begining, Non_Existing_Ending, "Desc.");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    // Checking for existing client and different values

    period beginning, beginning1, beginning2, beginning3, beginning4, beginning5;
    period ending, ending1, ending2, ending3, ending4, ending5;

    beginning.hour = 8;
    beginning.minute = 30;
    beginning1.hour = 10;
    beginning1.minute = 0;
    beginning2.hour = 14;
    beginning2.minute = 25;
    beginning3.hour = 7;
    beginning3.minute = 0;
    beginning4.hour = 15;
    beginning4.minute = 30;
    beginning5.hour = 20;
    beginning5.minute = 0;
    ending.hour = 11;
    ending.minute = 30;
    ending1.hour = 13;
    ending1.minute = 30;
    ending2.hour = 17;
    ending2.minute = 30;
    ending3.hour = 6;
    ending3.minute = 0;
    ending4.hour = 19;
    ending4.minute = 30;
    ending5.hour = 21;
    ending5.minute = 30;

    agencyPtr->addSchedulePeriod("Tester_1", beginning, ending, "Period_0");
    agencyPtr->addSchedulePeriod("Tester_1", beginning1, ending1, "Period_1");
    agencyPtr->addSchedulePeriod("Tester_1", beginning2, ending2, "Period_2");
    agencyPtr->addSchedulePeriod("Tester_1", beginning3, ending3, "Period_3");
    agencyPtr->addSchedulePeriod("Tester_1", beginning4, ending4, "Period_4");
    agencyPtr->addSchedulePeriod("Tester_1", beginning5, ending5, "Period_5");

    agencyPtr->changeScheduleDescription("Tester_1", beginning, ending, "Changed");
    agencyPtr->changeScheduleDescription("Tester_1", beginning2, ending2, "Changed");
    agencyPtr->changeScheduleDescription("Tester_1", beginning4, ending4, "Changed");
    agencyPtr->changeScheduleDescription("Tester_1", beginning5, ending5, "Changed");

    period check;

    check.hour = 13;
    check.minute = 0;

    flag = flag && weddingPtr->checkScheduleLength() == check && agencyPtr->ifSorted()
                && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2
                && weddingPtr->refSchedule()->refDescription() == "Changed"
                && weddingPtr->refSchedule()->refNext()->refDescription() == "Period_1"
                && weddingPtr->refSchedule()->refNext()->refNext()->refDescription() == "Changed";

    return flag;
}

bool Testing_Scenarios::changingNotesData()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for not existing lists

    agencyPtr->changeNote("Non_Existing_Surname", "Non_Existing_Title", "Scribble");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 0 && agencyPtr->countClients() == 0;

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->changeNote("Non_Existing_Surname", "Non_Existing_Title", "Scribble");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    // Checking for existing client and different values

    agencyPtr->addNote("Tester_1", "Title", "Scribble");
    agencyPtr->addNote("Tester_1", "Title1", "Scribble1");
    agencyPtr->addNote("Tester_1", "Title2", "Scribble2");
    agencyPtr->addNote("Tester_1", "Title3", "Scribble3");
    agencyPtr->addNote("Tester_1", "Title4", "Scribble4");
    agencyPtr->addNote("Tester_1", "Title5", "Scribble5");
    agencyPtr->addNote("Tester_1", "Title6", "Scribble6");
    agencyPtr->addNote("Tester_1", "Title7", "Scribble7");

    agencyPtr->changeNote("Tester_1", "Title", "Changed");
    agencyPtr->changeNote("Tester_1", "Title2", "Changed");
    agencyPtr->changeNote("Tester_1", "Title3", "Changed");
    agencyPtr->changeNote("Tester_1", "Title4", "Changed");
    agencyPtr->changeNote("Tester_1", "Title5", "Changed");

    flag = flag && weddingPtr->countNotes() == 8 && agencyPtr->ifSorted()
                && weddingPtr->refNotes()->refScribble() == "Changed"
                && weddingPtr->refNotes()->refNext()->refScribble() == "Scribble1"
                && weddingPtr->refNotes()->refNext()->refNext()->refScribble() == "Changed"
                && agencyPtr->countWeddings() == 2 && agencyPtr->countClients() == 2;

    return flag;
}

bool Testing_Scenarios::displayTest()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 300);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    cout << "Displaying non existing wedding: " << endl << endl;
    agencyPtr->displayWedding("Non_Existing_Surname");

    // Checking for filled wedding

    agencyPtr->addClientInfo("Tester_1", "Tester Groom", "Tester Bride", "Tester Contact", "Tester Email");

    agencyPtr->addGuest("Tester_1", "Surname1", "Name1", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname2", "Name2", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname3", "Name3", meatEater);

    agencyPtr->addLocation("Tester_1", "Title1", "Address", 3, 300);
    agencyPtr->addLocation("Tester_1", "Title2", "Address", 2, 500);

    agencyPtr->addWeddingSetting("Tester_1", "Title1", 300, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title2", 400, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title3", 200, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title4", 1000, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title5", 300, "Desc.");

    period begining, ending, begining1, ending1;

    begining.hour = 12;
    begining.minute = 30;

    ending.hour = 14;
    ending.minute = 45;

    begining1.hour = 13;
    begining1.minute = 30;

    ending1.hour = 18;
    ending1.minute = 45;

    agencyPtr->addSchedulePeriod("Tester_1", begining, ending, "Desc.");
    agencyPtr->addSchedulePeriod("Tester_1", begining1, ending1, "Desc.");

    agencyPtr->addNote("Tester_1", "Note1", "Scribble");

    cout << "Displaying existing wedding (Tester_1)" << endl;

    agencyPtr->displayWedding("Tester_1");

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2 && weddingPtr->countGuest() == 3
                && weddingPtr->countLocations() == 2 && weddingPtr->countWeddingSettings() == 5
                && weddingPtr->countNotes() == 1 && weddingPtr->countWeddingSettingCost() == 2200;

    cout << endl;

    return flag;
}

bool Testing_Scenarios::costCheckTest()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate, 5000);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate, 5000);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    flag = flag && !agencyPtr->checkCost("Non_Existing_Surname");

    // Checking for non existing list

    cout << "Test for non existing list of elements: " << endl << endl;

    flag = flag && agencyPtr->checkCost("Tester_1");

    cout << endl;

    // Checking for filled lists and added guests

    agencyPtr->addGuest("Tester_1", "Surname1", "Name1", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname2", "Name2", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname3", "Name3", meatEater);

    agencyPtr->addLocation("Tester_1", "Title1", "Address", 3, 300);
    agencyPtr->addLocation("Tester_1", "Title2", "Address", 2, 500);

    agencyPtr->addWeddingSetting("Tester_1", "Title1", 300, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title2", 400, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title3", 200, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title4", 1000, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title5", 300, "Desc.");

    cout << "Test for non filled list of elements: " << endl << endl;

    flag = flag && agencyPtr->checkCost("Tester_1") && weddingPtr->countLocations() == 2
                && weddingPtr->countWeddingSettings() == 5 && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2;

    cout << endl;

    return flag;
}

bool Testing_Scenarios::organisationCheckTest()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    flag = flag && !agencyPtr->checkOrganisation("Non_Existing_Surname");

    // Checking for non existing lists

    flag = flag && !agencyPtr->checkOrganisation("Tester_1");

    //Checking for filled lists and mixed reservations

    agencyPtr->addLocation("Tester_1", "Title1", "Address", 3, 300);
    agencyPtr->addLocation("Tester_1", "Title2", "Address", 2, 300);
    agencyPtr->changeReservationStateLocation("Tester_1", "Title1");

    agencyPtr->addWeddingSetting("Tester_1", "Title1", 300, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title2", 300, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title3", 300, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title4", 300, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title5", 300, "Desc.");
    agencyPtr->changeReservationStateWeddingSetting("Tester_1", "Title1");
    agencyPtr->changeReservationStateWeddingSetting("Tester_1", "Title4");

    cout << "Method should display one location (Title2) and three settings(Title2, Title3, Title5): " << endl << endl;

    flag = flag && agencyPtr->checkOrganisation("Tester_1") && weddingPtr->countLocations() == 2
                && weddingPtr->countWeddingSettings() == 5 && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2;

    cout << endl;

    return flag;
}

bool Testing_Scenarios::guestCapacityCheckTest()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    flag = flag && !agencyPtr->checkGuestCapacity("Non_Existing_Surname");

    // Checking for empty Location list

    flag = flag && !agencyPtr->checkGuestCapacity("Tester_1");

    // Checking for filled list with not reserved locations

    agencyPtr->addLocation("Tester_1", "Title1", "Address", 3, 300);
    agencyPtr->addLocation("Tester_1", "Title2", "Address", 2, 300);

    flag = flag && !agencyPtr->checkGuestCapacity("Tester_1");

    // Checking for filled list with reserved locations and guests

    agencyPtr->addGuest("Tester_1", "Surname1", "Name1", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname2", "Name2", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname3", "Name3", meatEater);
    agencyPtr->changeReservationStateLocation("Tester_1", "Title1");
    agencyPtr->changeReservationStateLocation("Tester_1", "Title2");

    cout << "Only first location is sufficient for 3 guest and method will inform about difference for second location: " << endl << endl;

    flag = flag && agencyPtr->checkGuestCapacity("Tester_1") && weddingPtr->countLocations() == 2
                && weddingPtr->countGuest() == 3 && weddingPtr->countMeatEaters() == 3
                && agencyPtr->ifSorted();

    cout << endl;

    return flag;
}

bool Testing_Scenarios::guestConfirmationCheckTest()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for non existing wedding

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    flag = flag && !agencyPtr->checkGuestConfirmation("Non_Existing_Surname");

    // Checking for non existing guest list

    flag = flag && !agencyPtr->checkGuestConfirmation("Tester_1");

    // Checking for filled list with not everyone confirmed

    agencyPtr->addGuest("Tester_1", "Surname1", "Name1", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname2", "Name2", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname3", "Name3", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname4", "Name4", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname5", "Name5", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname6", "Name6", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname7", "Name7", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname8", "Name8", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname9", "Name9", meatEater);
    agencyPtr->addGuest("Tester_1", "Surname10", "Name10", meatEater);

    agencyPtr->confirmPresence("Tester_1", "Surname1", "Name1");
    agencyPtr->confirmPresence("Tester_1", "Surname3", "Name3");
    agencyPtr->confirmPresence("Tester_1", "Surname4", "Name4");
    agencyPtr->confirmPresence("Tester_1", "Surname7", "Name7");
    agencyPtr->confirmPresence("Tester_1", "Surname8", "Name8");
    agencyPtr->confirmPresence("Tester_1", "Surname10", "Name10");
    agencyPtr->confirmPresence("Tester_1", "NonExisting", "NonExisting");

    cout << "Only 6 out of 10 guests should confirm their presence: " << endl << endl;
    flag = flag && agencyPtr->checkGuestConfirmation("Tester_1") && agencyPtr->ifSorted()
                && weddingPtr->countGuest() == 10 && weddingPtr->countMeatEaters() == 10
                && weddingPtr->countConfirmedGuests() == 6;

    cout << endl;

    return flag;
}

bool Testing_Scenarios::expensiveElementsCheckTest()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for empty lists

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    flag = flag && !agencyPtr->checkExpensiveElements("Tester_1");

    // Checking for lists with only 2 locations

    agencyPtr->addLocation("Tester_1", "Title1", "Address1", 200, 350);
    agencyPtr->addLocation("Tester_1", "Title2", "Address2", 200, 800);

    flag = flag && !agencyPtr->checkExpensiveElements("Tester_1");

    // Checking for lists with 2 settings and 2 locations

    agencyPtr->addWeddingSetting("Tester_1", "Title1", 500, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title2", 800, "Desc.");

    cout << "Method should display one location with cost per guest = 800" << endl;
    cout << "And only two settings sorted by their prices" << endl << endl;

    flag = flag && agencyPtr->checkExpensiveElements("Tester_1");

    cout << endl;

    // Checking for lists with more than 2 settings and only 2 locations

    agencyPtr->addWeddingSetting("Tester_1", "Title3", 100, "Desc.");
    agencyPtr->addWeddingSetting("Tester_1", "Title4", 5000, "Desc.");

    cout << "Method should display one location with cost per guest = 800" << endl;
    cout << "And three sorted, most expensive settings, 5000, 800, 500: " << endl << endl;

    flag = flag && agencyPtr->checkExpensiveElements("Tester_1");

    cout << endl;

    agencyPtr->addGuest("Tester_1", "Test Surname1", "Test Name1", meatEater);

    flag = flag && agencyPtr->ifSorted() && agencyPtr->countWeddings() == 2
                && weddingPtr->countWeddingSettings() == 4 && weddingPtr->countLocations() == 2
                && weddingPtr->countWeddingSettingCost() == 6400 && weddingPtr->countLocationCost() == 1150;

    return flag;
}

bool Testing_Scenarios::dishesCountCheckTest()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    //Checking for empty list

    flag = flag && !agencyPtr->checkDishesCount("Tester_1");

    //Checking for filled list

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->addGuest("Tester_1", "Test Surname1", "Test Name1", meatEater);
    agencyPtr->addGuest("Tester_1", "Test Surname2", "Test Name2", meatEater);
    agencyPtr->addGuest("Tester_1", "Test Surname3", "Test Name3", vegan);
    agencyPtr->addGuest("Tester_1", "Test Surname4", "Test Name4", vegan);
    agencyPtr->addGuest("Tester_1", "Test Surname5", "Test Name5", vegan);
    agencyPtr->addGuest("Tester_1", "Test Surname6", "Test Name6", vegetarian);
    agencyPtr->addGuest("Tester_1", "Test Surname7", "Test Name7", meatEater);
    agencyPtr->addGuest("Tester_1", "Test Surname8", "Test Name8", diverse);
    agencyPtr->addGuest("Tester_1", "Test Surname9", "Test Name9", diverse);
    agencyPtr->addGuest("Tester_1", "Test Surname10", "Test Name10", diverse);

    cout << "Method Should show: " << endl;
    cout << "Meat eaters: 5, Vegetarians: 1" << endl;
    cout << "Vegans: 3, Diverse: 3" << endl;

    flag = flag && agencyPtr->checkDishesCount("Tester_1");

    // meatEaters = 3 + 2 form clients

    flag = flag && weddingPtr->countMeatEaters() == 3 && weddingPtr->countVegans() == 3 &&
            weddingPtr->countVegetarians() == 1 && weddingPtr->countDiverse() == 3 &&
            weddingPtr->countGuest() == 10 && agencyPtr->ifSorted();

    cout << endl;

    return flag;
}

bool Testing_Scenarios::dateOfNearestWeddingCheckTest()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for empty list
    cout << "Empty list," << endl;
    cout << "Should output information about no weddings on the list: " << endl;
    flag = flag && !agencyPtr->checkDateOfNearestWedding();

    cout << endl;

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    cout << "Filled list, " << endl;
    cout << "Should output information about wedding which is in 17 days: " << endl;
    flag = flag && agencyPtr->checkDateOfNearestWedding();

    cout << endl;

    return flag;
}

bool Testing_Scenarios::weddingFromTimePeriodDisplayTest()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    // Checking for empty list

    cout << "Empty list, " << endl;
    flag = flag && !agencyPtr->displayWeddingFromTimePeriod(testingDate, testingDate);
    cout << endl;

    // Checking for filled list

    testingDate += 17*DAY;
    time_t beginning = testingDate;
    beginning += DAY;
    agencyPtr->insertClient("Tester_1", testingDate);
    testingDate += 30*DAY;
    time_t ending = testingDate;
    ending += 3*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    cout << "Filled list, " << endl;
    cout << "Should display wedding of Tester_2 Client: " << endl;
    flag = flag && agencyPtr->displayWeddingFromTimePeriod(beginning, ending);

    return flag;
}

bool Testing_Scenarios::negativeValuesTesting()
{
    bool flag = true;
    time_t testingDate = time(0);
    Wedding_Agency* agencyPtr = new Wedding_Agency();

    testingDate += 17*DAY;
    agencyPtr->insertClient("Tester_1", testingDate);
    testingDate += 30*DAY;
    agencyPtr->insertClient("Tester_2", testingDate);

    Wedding* weddingPtr = agencyPtr->refWeddings();

    agencyPtr->changeClientsBudget("Tester_1", -5000);
    agencyPtr->addLocation("Tester_1", "Tester Title", "Tester Address", -250, 39.99);
    agencyPtr->addLocation("Tester_1", "Tester Title", "Tester Address", 250, -39.99);
    agencyPtr->addLocation("Tester_1", "Tester Title", "Tester Address", -250, -39.99);
    agencyPtr->addWeddingSetting("Tester_1", "Tester Title" , -300, "Tester Desc.");

    flag = flag && weddingPtr->refGroomAndBride()->refBudget() != -5000
                && weddingPtr->countLocations() == 0
                && weddingPtr->countWeddingSettings() == 0 ;

    return flag;
}
