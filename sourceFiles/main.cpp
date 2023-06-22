#include <iostream>
#include <ctime>
#include "Wedding_Agency.h"
#include "Testing_Scenarios.h"

using namespace std;

int main()
{

    int inputNumber = 1;
    Testing_Scenarios test;

    cout << "Which test would you like to perform?" << endl;

    while (inputNumber)
    {
        cout << "0. Leave program" << endl;
        cout << "1. addingClients() " << endl;
        cout << "2. agencyIndependence()" << endl;
        cout << "3. findingWedding() " << endl;
        cout << "4. removingOfWedding()" << endl;
        cout << "5. addingClientInfo()" << endl;
        cout << "6. addingGuest()" << endl;
        cout << "7. removingGuests()" << endl;
        cout << "8. addingLocations()" << endl;
        cout << "9. removingLocations()" << endl;
        cout << "10. addingWeddingSettings()" << endl;
        cout << "11. removingWeddingSettings()" << endl;
        cout << "12. addingSchedulePeriods()" << endl;
        cout << "13. removingSchedulesPeriods()" << endl;
        cout << "14. addingNotes()" << endl;
        cout << "15. removingNotes()" << endl;
        cout << "16. changingClientsData()" << endl;
        cout << "17. changingGuestsData()" << endl;
        cout << "18. changingOrganisationElements()" << endl;
        cout << "19. changingSchedulesData()" << endl;
        cout << "20. changingNotesData()" << endl;
        cout << "21. displayTest()" << endl;
        cout << "22. costCheckTest()" << endl;
        cout << "23. organisationCheckTest()" << endl;
        cout << "24. guestCapacityCheckTest()" << endl;
        cout << "25. guestConfirmationCheckTest()" << endl;
        cout << "26. expensiveElementsCheckTest()" << endl;
        cout << "27. dishesCountCheckTest()" << endl;
        cout << "28. dateOfNearestWeddingCheckTest()" << endl;
        cout << "29. weddingFromTimePeriodDisplayTest()" << endl;
        cout << "30. negativeValuesTesting()" << endl;


        cout << "Test: ";
        cin >> inputNumber;
        cout << endl;

        switch(inputNumber)
        {
        case 0:
            break;
        case 1:
            if(test.addingClients())
                cout << "addingClients() test - SUCCESS" << endl << endl;
            else
                cout << "addingClients() test - FAIL" << endl << endl;
            break;
        case 2:
            if(test.agencyIndependence())
                cout << "agencyIndependence() test - SUCCESS" << endl << endl;
            else
                cout << "agencyIndependence() test - FAIL" << endl << endl;
            break;
        case 3:
            if(test.findingWedding())
                cout << "findingWedding() test - SUCCESS" << endl << endl;
            else
                cout << "findingWedding() test - FAIL" << endl << endl;
            break;
        case 4:
            if(test.removingOfWedding())
                cout << "removingOfWedding() test - SUCCESS" << endl << endl;
            else
                cout << "removingOfWedding() test - FAIL" << endl << endl;
            break;
        case 5:
            if(test.addingClientInfo())
                cout << "addingClientInfo() test - SUCCESS" << endl << endl;
            else
                cout << "addingClientInfo() test - FAIL" << endl << endl;
            break;
        case 6:
            if(test.addingGuest())
                cout << "addingGuest() test - SUCCESS" << endl << endl;
            else
                cout << "addingGuest() test - FAIL" << endl << endl;
            break;
        case 7:
            if(test.removingGuests())
                cout << "removingGuests() test - SUCCESS" << endl << endl;
            else
                cout << "removingGuests() test - FAIL" << endl << endl;
            break;
        case 8:
            if(test.addingLocations())
                cout << "addingLocations() test - SUCCESS" << endl << endl;
            else
                cout << "addingLocations() test - FAIL" << endl << endl;
            break;
        case 9:
            if(test.removingLocations())
                cout << "removingLocations() test - SUCCESS" << endl << endl;
            else
                cout << "removingLocations() test - FAIL" << endl << endl;
            break;
        case 10:
            if(test.addingWeddingSettings())
                cout << "addingWeddingSettings() test - SUCCESS" << endl << endl;
            else
                cout << "addingWeddingSettings() test - FAIL" << endl << endl;
            break;
        case 11:
            if(test.removingWeddingSettings())
                cout << "removingWeddingSettings() test - SUCCESS" << endl << endl;
            else
                cout << "removingWeddingSettings() test - FAIL" << endl << endl;
            break;
        case 12:
            if(test.addingSchedulePeriods())
                cout << "addingSchedulePeriods() test - SUCCESS" << endl << endl;
            else
                cout << "addingSchedulePeriods() test - FAIL" << endl << endl;
            break;
        case 13:
            if(test.removingSchedulesPeriods())
                cout << "removingSchedulesPeriods() test - SUCCESS" << endl << endl;
            else
                cout << "removingSchedulesPeriods() test - FAIL" << endl << endl;
            break;
        case 14:
            if(test.addingNotes())
                cout << "addingNotes() test - SUCCESS" << endl << endl;
            else
                cout << "addingNotes() test - FAIL" << endl << endl;
            break;
        case 15:
            if(test.removingNotes())
                cout << "removingNotes() test - SUCCESS" << endl << endl;
            else
                cout << "removingNotes() test - FAIL" << endl << endl;
            break;
        case 16:
            if(test.changingClientsData())
                cout << "changingClientsData() test - SUCCESS" << endl << endl;
            else
                cout << "changingClientsData() test - FAIL" << endl << endl;
            break;
        case 17:
            if(test.changingGuestsData())
                cout << "changingGuestsData() test - SUCCESS" << endl << endl;
            else
                cout << "changingGuestsData() test - FAIL" << endl << endl;
            break;
        case 18:
            if(test.changingOrganisationElements())
                cout << "changingOrganisationElements() test - SUCCESS" << endl << endl;
            else
                cout << "changingOrganisationElements() test - FAIL" << endl << endl;
            break;
        case 19:
            if(test.changingSchedulesData())
                cout << "changingSchedulesData() test - SUCCESS" << endl << endl;
            else
                cout << "changingSchedulesData() test - FAIL" << endl << endl;
            break;
        case 20:
            if(test.changingNotesData())
                cout << "changingNotesData() test - SUCCESS" << endl << endl;
            else
                cout << "changingNotesData() test - FAIL" << endl << endl;
            break;
        case 21:
            if(test.displayTest())
                cout << "displayTest() test - SUCCESS" << endl << endl;
            else
                cout << "displayTest() test - FAIL" << endl << endl;
            break;
        case 22:
            if(test.costCheckTest())
                cout << "costCheckTest() test - SUCCESS" << endl << endl;
            else
                cout << "costCheckTest() test - FAIL" << endl << endl;
            break;
        case 23:
            if(test.organisationCheckTest())
                cout << "organisationCheckTest() test - SUCCESS" << endl << endl;
            else
                cout << "organisationCheckTest() test - FAIL" << endl << endl;
            break;
        case 24:
            if(test.guestCapacityCheckTest())
                cout << "guestCapacityCheckTest() test - SUCCESS" << endl << endl;
            else
                cout << "guestCapacityCheckTest() test - FAIL" << endl << endl;
            break;
        case 25:
            if(test.guestConfirmationCheckTest())
                cout << "guestConfirmationCheckTest() test - SUCCESS" << endl << endl;
            else
                cout << "guestConfirmationCheckTest() test - FAIL" << endl << endl;
            break;
        case 26:
            if(test.expensiveElementsCheckTest())
                cout << "expensiveElementsCheckTest() test - SUCCESS" << endl << endl;
            else
                cout << "expensiveElementsCheckTest() test - FAIL" << endl << endl;
            break;
        case 27:
            if(test.dishesCountCheckTest())
                cout << "dishesCountCheckTest() test - SUCCESS" << endl << endl;
            else
                cout << "dishesCountCheckTest() test - FAIL" << endl << endl;
            break;
        case 28:
            if(test.dateOfNearestWeddingCheckTest())
                cout << "dateOfNearestWeddingCheckTest() test - SUCCESS" << endl << endl;
            else
                cout << "dateOfNearestWeddingCheckTest() test - FAIL" << endl << endl;
            break;
        case 29:
            if(test.weddingFromTimePeriodDisplayTest())
                cout << "weddingFromTimePeriodDisplayTest() test - SUCCESS" << endl << endl;
            else
                cout << "weddingFromTimePeriodDisplayTest() test - FAIL" << endl << endl;
            break;
        case 30:
            if(test.negativeValuesTesting())
                cout << "negativeValuesTesting() test - SUCCESS" << endl << endl;
            else
                cout << "negativeValuesTesting() test - FAIL" << endl << endl;
            break;
        default:
            cout << "Input only one Integer from 0 to 30!" << endl << endl;
            break;
        }
    }
    return 0;
}
