#include <iostream>
#include <ctime>
#include "Wedding_Agency.h"

using namespace std;

void Wedding_Agency::removeAllElements()
{
    // By deleting all elements from the weddings list we will also
    // delete every element from the clients list, because each of the client
    // has to be connected to each wedding

    Wedding* weddingPtr = weddings;
    while (weddingPtr)
    {
        // Deleting Pair

        delete weddingPtr -> refGroomAndBride();

        // Deleting Guests

        Guest* guestPtr = weddingPtr -> refGuestList();
        while (guestPtr)
        {
            guestPtr = guestPtr->refNext();
            delete weddingPtr -> refGuestList();
            weddingPtr->refGuestList() = guestPtr;
        }

        // Deleting Settings

        Wedding_Setting* settingPtr = weddingPtr->refWeddingSettingList();
        while (settingPtr)
        {
            settingPtr = settingPtr->refNext();
            delete weddingPtr->refWeddingSettingList();
            weddingPtr->refWeddingSettingList() = settingPtr;
        }

        // Deleting Locations

        Location* locationPtr = weddingPtr->refLocationsList();
        while (locationPtr)
        {
            locationPtr = locationPtr->refNext();
            delete weddingPtr->refLocationsList();
            weddingPtr->refLocationsList() = locationPtr;
        }

        // Deleting Schedule

        Schedule* periodPtr = weddingPtr->refSchedule();
        while (periodPtr)
        {
            periodPtr = periodPtr->refNext();
            delete weddingPtr->refSchedule();
            weddingPtr->refSchedule() = periodPtr;
        }

        // Deleting Notes

        Note* notePtr = weddingPtr->refNotes();
        while (notePtr)
        {
            notePtr = notePtr->refNext();
            delete weddingPtr->refNotes();
            weddingPtr->refNotes() = notePtr;
        }

        // Deleting Wedding

        weddingPtr = weddingPtr -> refNext();
        delete weddings;
        weddings = weddingPtr;
    }
}

void Wedding_Agency::copyAllElements(const Wedding_Agency& wa)
{
    Engaged* clientPtr;
    Engaged* copyClientPtr = wa.clients;

    while(copyClientPtr)
    {
        Engaged* newClient = new Engaged(*copyClientPtr);
        if(!clients)
            clients = newClient;
        else
            clientPtr->refNext() = newClient;
        clientPtr = newClient;
        copyClientPtr = copyClientPtr->refNext();
    }

    // Copying weddings

    Wedding* weddingPtr;
    Wedding* copyWeddingPtr = wa.weddings;

    while(copyWeddingPtr)
    {
        Wedding* newWedding = new Wedding(*copyWeddingPtr);
        if(!weddings)
            weddings = newWedding;
        else
            weddingPtr->refNext() = newWedding;
        weddingPtr = newWedding;
        copyWeddingPtr = copyWeddingPtr->refNext();
    }
}

Wedding* Wedding_Agency::findWedding(string surname)const
{
    // Checking if there are multiple clients with the same name

    int sameSurname = 0;

    Engaged* clientPtr = clients;
    while (clientPtr)
    {
        if (clientPtr->refSurname() == surname)
            sameSurname++;
        clientPtr = clientPtr->refNext();
    }

    if(sameSurname>1)
    {
        cout << "Unable to find specific Wedding, because there are multiple clients with the same surname:" << endl << endl;
        clientPtr = clients;
        while(clientPtr)
        {
            if (clientPtr->refSurname() == surname)
            {
                cout << *clientPtr << endl;
                tm* gmDate = gmtime(&clientPtr->refOwnWedding()->refDateOfWedding());
                cout << "Date of Wedding: ";
                switch (gmDate->tm_wday)
                {
                case 0:
                    cout << "Sunday";
                    break;
                case 1:
                    cout << "Monday";
                    break;
                case 2:
                    cout << "Tuesday";
                    break;
                case 3:
                    cout << "Wednesday";
                    break;
                case 4:
                    cout << "Thursday";
                    break;
                case 5:
                    cout << "Friday";
                    break;
                case 6:
                    cout << "Saturday";
                    break;
                }

                cout << " " << gmDate->tm_mday << "." << gmDate->tm_mon+1 << "." << gmDate->tm_year+1900 << endl << endl;

            }
            clientPtr = clientPtr -> refNext();
        }
        return nullptr;
    }
    else
    {
        clientPtr = clients;
        while(clientPtr)
        {
            if (clientPtr->refSurname() == surname)
                return clientPtr->refOwnWedding();
            clientPtr = clientPtr -> refNext();
        }
    }
    return nullptr;
}

Wedding* Wedding_Agency::findWedding(time_t date)const
{
    Wedding* weddingPtr = weddings;
    while (weddingPtr)
    {
        if (weddingPtr->refDateOfWedding() == date)
            return weddingPtr;
        weddingPtr = weddingPtr -> refNext();
    }
    return nullptr;
}

template <typename searchMethod>
bool Wedding_Agency::isGuest(searchMethod method, string guestSurname, string guestName)const
{
    Guest* guestPtr = findWedding(method)->refGuestList();
    while (guestPtr)
    {
        if (guestPtr->refSurname() == guestSurname && guestPtr->refName() == guestName)
            return true;
        guestPtr = guestPtr -> refNext();
    }
    return false;
}

template <typename searchMethod>
bool Wedding_Agency::isLocation(searchMethod method, string title)const
{
    Location* locationPtr = findWedding(method)->refLocationsList();
    while (locationPtr)
    {
        if(locationPtr->refTitle() == title)
            return true;
        locationPtr = locationPtr->refNext();
    }
    return false;
}

template <typename searchMethod>
bool Wedding_Agency::isSetting(searchMethod method, string title)const
{
    Wedding_Setting* settingPtr = findWedding(method)->refWeddingSettingList();
    while(settingPtr)
    {
        if(settingPtr->refTitle()==title)
            return true;
        settingPtr = settingPtr->refNext();
    }
    return false;
}

template <typename searchMethod>
bool Wedding_Agency::isPeriod(searchMethod method, period begining, period ending)const
{
    Schedule* periodPtr = findWedding(method)->refSchedule();
    while (periodPtr)
    {
        if(periodPtr->refBeginning() == begining && periodPtr->refEnding() == ending)
            return true;
        periodPtr = periodPtr->refNext();
    }
    return false;
}

template <typename searchMethod>
bool Wedding_Agency::isNote(searchMethod method, string title)const
{
    Note* notePtr = findWedding(method)->refNotes();
    while (notePtr)
    {
        if(notePtr->refTitle() == title)
            return true;
        notePtr = notePtr->refNext();
    }
    return false;
}

Wedding_Agency::Wedding_Agency()
{
    this -> clients = nullptr;
    this -> weddings = nullptr;

    currentDate = time(0);
}

Wedding_Agency::~Wedding_Agency()
{
    removeAllElements();
}

Wedding_Agency::Wedding_Agency(const Wedding_Agency& wa)
{
    this -> clients = nullptr;
    this -> weddings = nullptr;
    currentDate = time(0);

    // Copying clients

    copyAllElements(wa);
}

Wedding_Agency& Wedding_Agency::operator=(const Wedding_Agency& wa)
{
    // Check for self assignment
    if (this == &wa)
        return *this;

    removeAllElements();
    copyAllElements(wa);

    return *this;
}

Engaged*& Wedding_Agency::refClients()
{
    return clients;
}

Wedding*& Wedding_Agency::refWeddings()
{
    return weddings;
}

void Wedding_Agency::insertClient(string surname, time_t date, float budget)
{
    //Checking if variables are appropriate

    if (date < currentDate || budget < 0 || findWedding(date))
    {
        return;
    }
    else
    {
        //Creating new elements

        Engaged* newClient = new Engaged(surname);
        newClient->refBudget() = budget;
        Wedding* newWedding = new Wedding(date, newClient);

        //Adding client to the list

        //Adding when list is empty:
        if(!clients)
        {
            clients = newClient;
            newClient->refNext() = nullptr;
        }
        //Adding client at the end of the list
        else
        {
            Engaged* engagedPtr = clients;
            while (engagedPtr)
            {
                if(!engagedPtr->refNext())
                {
                    engagedPtr->refNext() = newClient;
                    newClient->refNext() = nullptr;
                }
                engagedPtr = engagedPtr -> refNext();
            }
        }

        //Adding wedding to the sorted list

        //Adding when list is empty
        if(!weddings)
        {
            weddings = newWedding;
            newWedding->refNext() = nullptr;
        }
        else
        {
            Wedding* currentWeddingPtr = weddings;
            Wedding* nextWeddingPtr = weddings -> refNext();

            //Adding before head
            if(newWedding->refDateOfWedding() < currentWeddingPtr->refDateOfWedding())
            {
                weddings = newWedding;
                newWedding -> refNext() = currentWeddingPtr;
            }
            //Adding after head
            else if(weddings->refNext() == nullptr)
            {
                weddings->refNext() = newWedding;
                newWedding->refNext() = nullptr;
                return;
            }
            else
            {
                while (nextWeddingPtr)
                {
                    //Adding before bigger element

                    if(newWedding->refDateOfWedding() < nextWeddingPtr->refDateOfWedding())
                    {
                        newWedding->refNext() = nextWeddingPtr;
                        currentWeddingPtr->refNext() = newWedding;
                        return;
                    }

                    //Adding at the end

                    if(!nextWeddingPtr->refNext())
                    {
                        nextWeddingPtr->refNext() = newWedding;
                        newWedding->refNext() = nullptr;
                        return;
                    }
                    currentWeddingPtr = currentWeddingPtr->refNext();
                    nextWeddingPtr = nextWeddingPtr->refNext();
                }
            }
        }
    }
}

void Wedding_Agency::insertClient(string surname, time_t date)
{
    //Checking if variables are appropriate

    if (date < currentDate || findWedding(date))
    {
        return;
    }
    else
    {
        //Creating new elements

        Engaged* newClient = new Engaged(surname);
        Wedding* newWedding = new Wedding(date, newClient);

        //Adding client to the list

        //Adding when list is empty:
        if(!clients)
        {
            clients = newClient;
            newClient->refNext() = nullptr;
        }
        //Adding client at the end of the list
        else
        {
            Engaged* engagedPtr = clients;
            while (engagedPtr)
            {
                if(!engagedPtr->refNext())
                {
                    engagedPtr->refNext() = newClient;
                    newClient->refNext() = nullptr;
                }
                engagedPtr = engagedPtr -> refNext();
            }
        }

        //Adding wedding to the sorted list

        //Adding when list is empty
        if(!weddings)
        {
            weddings = newWedding;
            newWedding->refNext() = nullptr;
        }
        else
        {
            Wedding* currentWeddingPtr = weddings;
            Wedding* nextWeddingPtr = weddings -> refNext();

            //Adding before head
            if(newWedding->refDateOfWedding() < currentWeddingPtr->refDateOfWedding())
            {
                weddings = newWedding;
                newWedding -> refNext() = currentWeddingPtr;
            }
            //Adding after head
            else if(weddings->refNext() == nullptr)
            {
                weddings->refNext() = newWedding;
                newWedding->refNext() == nullptr;
                return;
            }
            else
            {
                while (nextWeddingPtr)
                {
                    //Adding before bigger element

                    if(newWedding->refDateOfWedding() < nextWeddingPtr->refDateOfWedding())
                    {
                        newWedding->refNext() = nextWeddingPtr;
                        currentWeddingPtr->refNext() = newWedding;
                        return;
                    }

                    //Adding at the end

                    if(!nextWeddingPtr->refNext())
                    {
                        nextWeddingPtr->refNext() = newWedding;
                        newWedding->refNext() = nullptr;
                        return;
                    }
                    currentWeddingPtr = currentWeddingPtr->refNext();
                    nextWeddingPtr = nextWeddingPtr->refNext();
                }
            }
        }
    }

}

template <typename searchMethod>
void Wedding_Agency::addClientInfo(searchMethod method, string groomName, string bridesName, string contact, string email)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        weddingPtr->refGroomAndBride()->refName() = groomName;
        weddingPtr->refGroomAndBride()->refBridesName() = bridesName;
        weddingPtr->refGroomAndBride()->refContactNumber() = contact;
        weddingPtr->refGroomAndBride()->refEmail() = email;
    }
}

void Wedding_Agency::removeWedding(time_t date)
{
    Wedding* weddingPtr = findWedding(date);
    if(weddingPtr)
    {
        // At first we delete the Client from the list

        Engaged* clientPtr = clients;
        Engaged* tempClient;

        if(clients == weddingPtr->refGroomAndBride())
        {
            tempClient = clients;
            clients = clients->refNext();
            delete tempClient;
        }
        else
        {
            while(clientPtr)
            {
                if(clientPtr->refNext() == weddingPtr->refGroomAndBride())
                {
                    tempClient = clientPtr->refNext();
                    clientPtr->refNext() = clientPtr->refNext()->refNext();
                    delete tempClient;
                    break;
                }
                clientPtr = clientPtr -> refNext();
            }
        }

        // And then we delete the wedding from the list

        Wedding* listPtr = weddings;
        Wedding* tempWedding;

        if(weddings == weddingPtr)
        {
            tempWedding = weddings;
            weddings = weddings -> refNext();

            //  At first we delete all elements from it
            Guest* delGuestPtr = tempWedding->refGuestList();
            while(delGuestPtr)
            {
                delGuestPtr = delGuestPtr->refNext();
                delete tempWedding->refGuestList();
                tempWedding->refGuestList() = delGuestPtr;
            }

            // settings

            Wedding_Setting* delSettingPtr = tempWedding->refWeddingSettingList();
            while(delSettingPtr)
            {
                delSettingPtr = delSettingPtr->refNext();
                delete tempWedding->refWeddingSettingList();
                tempWedding->refWeddingSettingList() = delSettingPtr;
            }

            // locations

            Location* delLocationPtr = tempWedding->refLocationsList();
            while(delLocationPtr)
            {
                delLocationPtr = delLocationPtr->refNext();
                delete tempWedding->refLocationsList();
                tempWedding->refLocationsList() = delLocationPtr;
            }

            // schedule

            Schedule* delPeriodPtr = tempWedding->refSchedule();
            while(delPeriodPtr)
            {
                delPeriodPtr = delPeriodPtr->refNext();
                delete tempWedding->refSchedule();
                tempWedding->refSchedule() = delPeriodPtr;
            }

            // notes

            Note* delNotePtr = tempWedding->refNotes();
            while(delNotePtr)
            {
                delNotePtr = delNotePtr->refNext();
                delete tempWedding->refNotes();
                tempWedding->refNotes() = delNotePtr;
            }


            // Now we delete wedding

            delete tempClient;

            return;
        }
        else
        {
            while(listPtr)
            {
                if(listPtr ->refNext() == weddingPtr)
                {
                    tempWedding = listPtr->refNext();
                    listPtr->refNext() = listPtr->refNext()->refNext();

                    //  At first we delete all elements from it
                    Guest* delGuestPtr = tempWedding->refGuestList();
                    while(delGuestPtr)
                    {
                        delGuestPtr = delGuestPtr->refNext();
                        delete tempWedding->refGuestList();
                        tempWedding->refGuestList() = delGuestPtr;
                    }

                    // settings

                    Wedding_Setting* delSettingPtr = tempWedding->refWeddingSettingList();
                    while(delSettingPtr)
                    {
                        delSettingPtr = delSettingPtr->refNext();
                        delete tempWedding->refWeddingSettingList();
                        tempWedding->refWeddingSettingList() = delSettingPtr;
                    }

                    // locations

                    Location* delLocationPtr = tempWedding->refLocationsList();
                    while(delLocationPtr)
                    {
                        delLocationPtr = delLocationPtr->refNext();
                        delete tempWedding->refLocationsList();
                        tempWedding->refLocationsList() = delLocationPtr;
                    }

                    // schedule

                    Schedule* delPeriodPtr = tempWedding->refSchedule();
                    while(delPeriodPtr)
                    {
                        delPeriodPtr = delPeriodPtr->refNext();
                        delete tempWedding->refSchedule();
                        tempWedding->refSchedule() = delPeriodPtr;
                    }

                    // notes

                    Note* delNotePtr = tempWedding->refNotes();
                    while(delNotePtr)
                    {
                        delNotePtr = delNotePtr->refNext();
                        delete tempWedding->refNotes();
                        tempWedding->refNotes() = delNotePtr;
                    }

                    // Now we delete wedding

                    delete tempWedding;
                    return;
                }
                listPtr = listPtr->refNext();
            }
        }
    }
    return;
}

template <typename searchMethod>
void Wedding_Agency::addGuest(searchMethod method, string guestSurname, string guestName, food_preference fp)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(!isGuest(method, guestSurname, guestName))
            *weddingPtr + *new Guest(guestSurname, guestName, fp);
    }
}

template <typename searchMethod>
void Wedding_Agency::removeGuest(searchMethod method, string guestSurname, string guestName)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(isGuest(method, guestSurname, guestName))
        {
            Guest* guestPtr = weddingPtr -> refGuestList();
            Guest* tempGuest;

            // Removing if Guest is head
            if(guestPtr->refSurname() == guestSurname && guestPtr->refName() == guestName)
            {
                tempGuest = guestPtr;
                weddingPtr -> refGuestList() = weddingPtr -> refGuestList() -> refNext();
                delete tempGuest;
                return;
            }
            // Removing element from the list
            else
            {
                while (guestPtr)
                {
                    if(guestPtr->refNext()->refSurname() == guestSurname && guestPtr->refNext()->refName() == guestName)
                    {
                        tempGuest = guestPtr->refNext();
                        guestPtr->refNext() = guestPtr->refNext()->refNext();
                        delete tempGuest;
                        return;
                    }
                    guestPtr = guestPtr->refNext();
                }
            }
        }
    }
    return;
}

template <typename searchMethod>
void Wedding_Agency::removeGuest(searchMethod method, string guestSurname)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        bool located = false;

        Guest* guestPtr = weddingPtr -> refGuestList();
        while(guestPtr)
        {
            if(guestPtr->refSurname() == guestSurname)
                located = true;
            guestPtr = guestPtr->refNext();
        }

        if(located)
        {
            guestPtr = weddingPtr -> refGuestList();
            Guest* tempGuest;
            bool removed = false;

            // Removing element from the list

            while (guestPtr)
            {
                removed = false;
                if(guestPtr->refNext()->refSurname() == guestSurname)
                {
                    tempGuest = guestPtr->refNext();
                    guestPtr->refNext() = guestPtr->refNext()->refNext();
                    delete tempGuest;
                    removed = true;
                }
                if(!removed || guestPtr->refNext() == nullptr)
                    guestPtr = guestPtr->refNext();
            }

            // Removing if Guest is head

            if(weddingPtr -> refGuestList() ->refSurname() == guestSurname)
            {
                tempGuest = weddingPtr -> refGuestList();
                weddingPtr -> refGuestList() = weddingPtr -> refGuestList() -> refNext();
                delete tempGuest;
            }
        }
    }
    return;
}

template <typename searchMethod>
void Wedding_Agency::addLocation(searchMethod method, string title, string address,int guestCapacity, float price)
{
    if(guestCapacity > 0 && price > 0)
    {
        if(Wedding* weddingPtr = findWedding(method))
        {
            if(!isLocation(method, title))
                *weddingPtr + *new Location(title, address, guestCapacity, price);
        }
    }
}

template <typename searchMethod>
void Wedding_Agency::removeLocation(searchMethod method, string title)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(isLocation(method, title))
        {
            Location* locationPtr = weddingPtr -> refLocationsList();
            Location* tempLocation;

            // Removing if Location is head
            if(locationPtr->refTitle() == title)
            {
                tempLocation = locationPtr;
                weddingPtr -> refLocationsList() = weddingPtr -> refLocationsList() -> refNext();
                delete tempLocation;
                return;
            }
            // Removing element from the list
            else
            {
                while (locationPtr)
                {
                    if(locationPtr->refNext()->refTitle() == title)
                    {
                        tempLocation = locationPtr->refNext();
                        locationPtr->refNext() = locationPtr->refNext()->refNext();
                        delete tempLocation;
                        return;
                    }
                    locationPtr = locationPtr->refNext();
                }
            }
        }
    }
    return;
}

template <typename searchMethod>
void Wedding_Agency::addWeddingSetting(searchMethod method, string title, float price, string description)
{
    if (price > 0)
    {
        if(Wedding* weddingPtr = findWedding(method))
        {
            if(!isSetting(method, title))
                *weddingPtr + *new Wedding_Setting(title, description, price);
        }
    }
}

template <typename searchMethod>
void Wedding_Agency::removeWeddingSetting(searchMethod method, string title)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(isSetting(method, title))
        {
            Wedding_Setting* settingPtr = weddingPtr -> refWeddingSettingList();
            Wedding_Setting* tempSetting;

            // Removing if Setting is head
            if(settingPtr->refTitle() == title)
            {
                tempSetting = settingPtr;
                weddingPtr -> refWeddingSettingList() = weddingPtr -> refWeddingSettingList() -> refNext();
                delete tempSetting;
                return;
            }
            // Removing element from the list
            else
            {
                while (settingPtr)
                {
                    if(settingPtr->refNext()->refTitle() == title)
                    {
                        tempSetting = settingPtr->refNext();
                        settingPtr->refNext() = settingPtr->refNext()->refNext();
                        delete tempSetting;
                        return;
                    }
                    settingPtr = settingPtr->refNext();
                }
            }
        }
    }
    return;
}

template <typename searchMethod>
void Wedding_Agency::addSchedulePeriod(searchMethod method, period beginning, period ending, string description)
{
    if(beginning.hour >= 0 && beginning.hour < 24 &&
            beginning.minute >= 0 && beginning.minute < 60 &&
            ending.hour >= 0 && ending.hour < 24 &&
            ending.minute >= 0 && ending.minute < 60 &&
            beginning < ending)
    {
        if(Wedding* weddingPtr = findWedding(method))

        {
            if(!isPeriod(method, beginning, ending))
                *weddingPtr + *new Schedule(beginning, ending, description);
        }
    }
}

template <typename searchMethod>
void Wedding_Agency::removeSchedulePeriod(searchMethod method, period beginning, period ending)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(isPeriod(method, beginning, ending))
        {
            Schedule* periodPtr = weddingPtr -> refSchedule();
            Schedule* tempPeriod;

            // Removing if Period is head
            if(periodPtr->refBeginning() == beginning && periodPtr->refEnding() == ending)
            {
                tempPeriod = periodPtr;
                weddingPtr -> refSchedule() = weddingPtr -> refSchedule() -> refNext();
                delete tempPeriod;
                return;
            }
            // Removing element from the list
            else
            {
                while (periodPtr)
                {
                    if(periodPtr->refNext()->refBeginning() == beginning && periodPtr->refNext()->refEnding() == ending)
                    {
                        tempPeriod = periodPtr->refNext();
                        periodPtr->refNext() = periodPtr->refNext()->refNext();
                        delete tempPeriod;
                        return;
                    }
                    periodPtr = periodPtr->refNext();
                }
            }
        }
    }
    return;
}

template <typename searchMethod>
void Wedding_Agency::addNote(searchMethod method, string title, string scribble)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(!isNote(method, title))
            *weddingPtr + *new Note(title, scribble);
    }
}

template <typename searchMethod>
void Wedding_Agency::removeNote(searchMethod method, string title)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(isNote(method, title))
        {
            Note* notePtr = weddingPtr -> refNotes();
            Note* tempNote;

            // Removing if note is head
            if(notePtr->refTitle() == title)
            {
                tempNote = notePtr;
                weddingPtr -> refNotes() = weddingPtr -> refNotes() -> refNext();
                delete tempNote;
                return;
            }
            // Removing element from the list
            else
            {
                while (notePtr)
                {
                    if(notePtr->refNext()->refTitle() == title)
                    {
                        tempNote = notePtr->refNext();
                        notePtr->refNext() = notePtr->refNext()->refNext();
                        delete tempNote;
                        return;
                    }
                    notePtr = notePtr->refNext();
                }
            }
        }
    }
    return;
}

template <typename searchMethod>
void Wedding_Agency::changeClientsFoodPreferences(searchMethod method, food_preference groomFP, food_preference bridesFP)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        weddingPtr->refGroomAndBride()->refFoodPreference() = groomFP;
        weddingPtr->refGroomAndBride()->refBridesFoodPreference() = bridesFP;
    }
}

template <typename searchMethod>
void Wedding_Agency::changeClientsBudget(searchMethod method, float budget)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if (budget > 0)
            weddingPtr->refGroomAndBride()->refBudget() = budget;
    }
}

template <typename searchMethod>
void Wedding_Agency::confirmPresence(searchMethod method, string guestSurname, string guestName)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(isGuest(method, guestSurname, guestName))
        {
            Guest* guestPtr = weddingPtr->refGuestList();
            while (guestPtr)
            {
                if(guestPtr->refName() == guestName && guestPtr->refSurname() == guestSurname)
                    guestPtr->refConfirmation() = !guestPtr->refConfirmation();
                guestPtr = guestPtr->refNext();
            }
        }
    }
}

template <typename searchMethod>
void Wedding_Agency::changeFoodPreferenceGuest(searchMethod method, string guestSurname, string guestName, food_preference fp)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(isGuest(method, guestSurname, guestName))
        {
            Guest* guestPtr = weddingPtr->refGuestList();
            while (guestPtr)
            {
                if(guestPtr->refName() == guestName && guestPtr->refSurname() == guestSurname)
                    guestPtr->refFoodPreference() = fp;
                guestPtr = guestPtr->refNext();
            }
        }
    }
}

template <typename searchMethod>
void Wedding_Agency::changeReservationStateLocation(searchMethod method, string title)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(isLocation(method, title))
        {
            Location* locationPtr = weddingPtr->refLocationsList();
            while (locationPtr)
            {
                if(locationPtr->refTitle() == title)
                    locationPtr->refToDo() = !locationPtr->refToDo();
                locationPtr = locationPtr->refNext();
            }
        }
    }
}

template <typename searchMethod>
void Wedding_Agency::changeReservationStateWeddingSetting(searchMethod method, string title)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(isSetting(method, title))
        {
            Wedding_Setting* settingPtr = weddingPtr->refWeddingSettingList();
            while (settingPtr)
            {
                if(settingPtr->refTitle() == title)
                    settingPtr->refToDo() = !settingPtr->refToDo();
                settingPtr = settingPtr->refNext();
            }
        }
    }
}

template <typename searchMethod>
void Wedding_Agency::changeScheduleDescription(searchMethod method, period beginning, period ending, string description)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(isPeriod(method, beginning, ending))
        {
            Schedule* periodPtr = weddingPtr->refSchedule();
            while (periodPtr)
            {
                if(periodPtr->refBeginning() == beginning && periodPtr->refEnding() == ending)
                    periodPtr->refDescription() = description;
                periodPtr = periodPtr->refNext();
            }
        }
    }
}

template <typename searchMethod>
void Wedding_Agency::changeNote(searchMethod method, string title, string scribble)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(isNote(method, title))
        {
            Note* notePtr = weddingPtr->refNotes();
            while (notePtr)
            {
                if(notePtr->refTitle() == title)
                    notePtr->refScribble() = scribble;
                notePtr = notePtr->refNext();
            }
        }
    }
}

ostream& operator << (ostream& os, const Wedding_Agency& wa)
{
    Wedding* weddingPtr = wa.weddings;
    int number = 0;
    while (weddingPtr)
    {
        os << "Wedding nr."<< ++number << ":" <<endl << endl;
        os << *weddingPtr << endl;
        weddingPtr = weddingPtr->refNext();
    }
    return os;
}

template <typename searchMethod>
void Wedding_Agency::displayWedding(searchMethod method)
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        cout << *weddingPtr;
    }
    else
    {
        cout << "Such wedding doesn't exist" << endl;
    }
}

bool Wedding_Agency::ifSorted()
{
    if(!weddings)
        return true;

    Wedding* weddingPtr = weddings;

    while(weddingPtr->refNext())
    {
        if(weddingPtr->refDateOfWedding() > weddingPtr->refNext()->refDateOfWedding())
            return false;
        weddingPtr = weddingPtr->refNext();
    }
    return true;
}

int Wedding_Agency::countClients()
{

    if (!clients)
        return 0;

    int numberOfClients = 0;
    Engaged* clientPtr = clients;

    while(clientPtr)
    {
        ++numberOfClients;
        clientPtr = clientPtr->refNext();
    }
    return numberOfClients;
}

int Wedding_Agency::countWeddings()
{
    if(!weddings)
        return 0;

    int numberOfWeddings = 0;
    Wedding* weddingPtr = weddings;

    while(weddingPtr)
    {
        ++numberOfWeddings;
        weddingPtr = weddingPtr->refNext();
    }
    return numberOfWeddings;
}

template <typename searchMethod>
bool Wedding_Agency::checkCost(searchMethod method)const
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        float cost = 0;
        Wedding_Setting* settingPtr = weddingPtr->refWeddingSettingList();
        while(settingPtr)
        {
            cost += settingPtr->refPrice();
            settingPtr = settingPtr->refNext();
        }

        Location* locationPtr = weddingPtr->refLocationsList();
        while(locationPtr)
        {
            cost += (locationPtr->refCostPerGuest() * weddingPtr->countGuest());
            locationPtr = locationPtr->refNext();
        }

        if(!weddingPtr->refGroomAndBride()->refBudget())
        {
            cout << "The cost of the wedding of Mr. and Mrs. " << weddingPtr->refGroomAndBride()->refSurname() << ": " << cost << endl;
        }
        else
        {
            cout << "The budget of Mr. and Mrs. " << weddingPtr->refGroomAndBride()->refSurname() << ": " << weddingPtr->refGroomAndBride()->refBudget() << endl;
            cout << "The cost of the wedding: " << cost << endl;
            switch (weddingPtr->refGroomAndBride()->refBudget() > cost)
            {
            case 0:

                cout << "The cost of the wedding is bigger than the budget by: " << cost - weddingPtr->refGroomAndBride()->refBudget() << endl;

                break;
            case 1:

                cout << "The budget is sufficient and pair can still spend: " << weddingPtr->refGroomAndBride()->refBudget() - cost << endl;

                break;
            }
        }
        return true;
    }
    return false;
}

template <typename searchMethod>
bool Wedding_Agency::checkOrganisation(searchMethod method) const
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        // Checking Locations
        if(weddingPtr->refLocationsList())
        {
            if(weddingPtr -> refWeddingSettingList())
            {
                cout << "Elements that still need to be organized for wedding of Mr. and Mrs. " << weddingPtr->refGroomAndBride()->refSurname() << ": " << endl;

                Location* locationPtr = weddingPtr->refLocationsList();

                cout << "Locations: " << endl;

                while(locationPtr)
                {
                    if(!locationPtr->refToDo())
                    {
                        cout << locationPtr->refTitle() << " on ";
                        cout << locationPtr->refAdress() << endl;
                    }
                    locationPtr = locationPtr -> refNext();
                }
                cout << endl;

                // Checking Settings


                Wedding_Setting* settingPtr = weddingPtr -> refWeddingSettingList();

                cout << "Wedding settings: " << endl;

                while(settingPtr)
                {
                    if(!settingPtr->refToDo())
                    {
                        cout << settingPtr->refTitle() << endl;
                        cout << settingPtr->refDescription() << endl;
                    }
                    settingPtr = settingPtr -> refNext();
                }

                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

template <typename searchMethod>
bool Wedding_Agency::checkGuestCapacity(searchMethod method) const
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(weddingPtr->refLocationsList())
        {
            if(weddingPtr->refGuestList())
            {
                Location* locationPtr = weddingPtr->refLocationsList();
                int guestAmount = weddingPtr->countGuest();
                while(locationPtr)
                {
                    if(locationPtr->refToDo())
                    {
                        if(locationPtr->refguestCapacity()<guestAmount)
                        {
                            cout << locationPtr->refTitle() << " on " << locationPtr->refAdress() << " is too small for this amount of guests!" << endl;
                            cout << "Amount of guest: " << guestAmount << endl;
                            cout << "Guest capacity of location: " << locationPtr->refguestCapacity() << endl;
                            cout << "Difference: " << guestAmount - locationPtr->refguestCapacity() << endl;
                        }
                        else
                        {
                            cout << locationPtr->refTitle() << " on " << locationPtr->refAdress() << " is sufficient for this amount of guests!" << endl;
                        }
                    }
                    locationPtr = locationPtr->refNext();
                }
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

template <typename searchMethod>
bool Wedding_Agency::checkGuestConfirmation(searchMethod method) const
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(weddingPtr->refGuestList())
        {
            Guest* guestPtr = weddingPtr->refGuestList();
            int confirmedGuests = 0;
            while(guestPtr)
            {
                if(guestPtr->refConfirmation())
                    confirmedGuests++;
                guestPtr = guestPtr->refNext();
            }

            cout << confirmedGuests << " out of " << weddingPtr->countGuest() << " guests confirmed their presence" << endl;

            return true;
        }
        return false;
    }
    return false;
}

template <typename searchMethod>
bool Wedding_Agency::checkExpensiveElements(searchMethod method) const
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        if(Location* locationPtr = weddingPtr -> refLocationsList())
        {
            if(Wedding_Setting* settingPtr = weddingPtr -> refWeddingSettingList())
            {
                cout << "The most expensive elements form wedding of Mr. and Mrs. " << weddingPtr->refGroomAndBride()->refSurname() << ": " << endl << endl;

                // Checking most expensive location

                cout << "The most expensive location: " << endl;

                Location* expensiveLocation = weddingPtr -> refLocationsList();
                while (locationPtr)
                {
                    if(locationPtr -> refCostPerGuest() > expensiveLocation->refCostPerGuest())
                        expensiveLocation = locationPtr;
                    locationPtr = locationPtr -> refNext();
                }

                cout << *expensiveLocation << endl << endl;

                // Checking most expensive setting

                cout << "The most expensive settings: " << endl;

                if(weddingPtr->countWeddingSettings()>2)
                {
                    Wedding_Setting* first = new Wedding_Setting("First", "First", 0);
                    Wedding_Setting* second = new Wedding_Setting("Second", "Second", 0);
                    Wedding_Setting* third = new Wedding_Setting("Third", "Third", 0);

                    while (settingPtr)
                    {
                        if(settingPtr->refPrice() > first->refPrice())
                        {
                            third = second;
                            second = first;
                            first = settingPtr;
                        }
                        else if(settingPtr->refPrice() > second->refPrice())
                        {
                            third = second;
                            second = settingPtr;
                        }
                        else if(settingPtr->refPrice() > third->refPrice())
                        {
                            third = settingPtr;
                        }

                        settingPtr = settingPtr -> refNext();
                    }

                    cout << *first << endl;
                    cout << *second << endl;
                    cout << *third << endl;

                    return true;

                }
                else
                {
                    switch(weddingPtr->countWeddingSettings())
                    {
                    case 1:
                        cout << *settingPtr << endl;
                        break;
                    case 2:
                        Wedding_Setting* first = settingPtr;
                        Wedding_Setting* second = settingPtr->refNext();

                        if (first->refPrice() > second->refPrice())
                        {
                            cout << *first << endl;
                            cout << *second << endl;
                        }
                        else
                        {
                            cout << *second << endl;
                            cout << *first << endl;
                        }
                        return true;
                        break;
                    }
                }

                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

template <typename searchMethod>
bool Wedding_Agency::checkDishesCount(searchMethod method) const
{
    if(Wedding* weddingPtr = findWedding(method))
    {
        int meatEaters = 0;
        int vegetarians = 0;
        int vegans = 0;
        int diverseEaters = 0;

        // Preferences of clients

        Engaged* engagedPtr = weddingPtr->refGroomAndBride();

        switch (engagedPtr->refFoodPreference())
        {
        case 0:
            meatEaters++;
            break;
        case 1:
            vegetarians++;
            break;
        case 2:
            vegans++;
            break;
        case 3:
            diverseEaters++;
            break;
        }

        switch (engagedPtr->refBridesFoodPreference())
        {
        case 0:
            meatEaters++;
            break;
        case 1:
            vegetarians++;
            break;
        case 2:
            vegans++;
            break;
        case 3:
            diverseEaters++;
            break;
        }

        // Preferences of guests

        Guest* guestPtr = weddingPtr->refGuestList();
        while(guestPtr)
        {
            switch (guestPtr->refFoodPreference())
            {
            case 0:
                meatEaters++;
                break;
            case 1:
                vegetarians++;
                break;
            case 2:
                vegans++;
                break;
            case 3:
                diverseEaters++;
                break;
            }
            guestPtr = guestPtr->refNext();
        }

        cout << "Dishes needed to prepare for wedding of Mr. and Mrs. " << engagedPtr->refSurname() << ": " << endl;
        cout << "Meat dishes: " << meatEaters << endl;
        cout << "Vegetarian dishes: " << vegetarians << endl;
        cout << "Vegan dishes: " << vegans << endl;
        cout << "Diverse dishes: " << diverseEaters << endl;

        return true;
    }
    return false;
}

bool Wedding_Agency::checkDateOfNearestWedding () const
{
    if(weddings)
    {
        cout << "Nearest wedding of Mr. and Mrs. " << weddings->refGroomAndBride()->refSurname() << " is on:" << endl;
        tm* gmDate = gmtime(&weddings->refDateOfWedding());
        switch (gmDate->tm_wday)
        {
        case 0:
            cout << "Sunday";
            break;
        case 1:
            cout << "Monday";
            break;
        case 2:
            cout << "Tuesday";
            break;
        case 3:
            cout << "Wednesday";
            break;
        case 4:
            cout << "Thursday";
            break;
        case 5:
            cout << "Friday";
            break;
        case 6:
            cout << "Saturday";
            break;
        }

        cout << " " << gmDate->tm_mday << "." << gmDate->tm_mon+1 << "." << gmDate->tm_year+1900 << endl;
        return true;
    }
    cout << "There are no weddings on the list!" << endl;
    return false;
}

bool Wedding_Agency::displayWeddingFromTimePeriod(time_t from, time_t to) const
{
    if(weddings)
    {
        if (to > from)
        {
            Wedding* weddingPtr = weddings;
            bool displayed = false;

            cout << "Weddings from ";
            tm* gmDate = gmtime(&from);
            switch (gmDate->tm_wday)
            {
            case 0:
                cout << "Sunday";
                break;
            case 1:
                cout << "Monday";
                break;
            case 2:
                cout << "Tuesday";
                break;
            case 3:
                cout << "Wednesday";
                break;
            case 4:
                cout << "Thursday";
                break;
            case 5:
                cout << "Friday";
                break;
            case 6:
                cout << "Saturday";
                break;
            }

            cout << " " << gmDate->tm_mday << "." << gmDate->tm_mon+1 << "." << gmDate->tm_year+1900;
            cout << " to ";

            gmDate = gmtime(&to);
            switch (gmDate->tm_wday)
            {
            case 0:
                cout << "Sunday";
                break;
            case 1:
                cout << "Monday";
                break;
            case 2:
                cout << "Tuesday";
                break;
            case 3:
                cout << "Wednesday";
                break;
            case 4:
                cout << "Thursday";
                break;
            case 5:
                cout << "Friday";
                break;
            case 6:
                cout << "Saturday";
                break;
            }

            cout << " " << gmDate->tm_mday << "." << gmDate->tm_mon+1 << "." << gmDate->tm_year+1900 << ": " << endl;

            while(weddingPtr)
            {
                if (weddingPtr->refDateOfWedding()>from && weddingPtr->refDateOfWedding()<to)
                {
                    cout << *weddingPtr << endl;
                    displayed = true;
                }
                weddingPtr = weddingPtr->refNext();
            }
            if(displayed)
                return true;
            else
            {
                cout << "There are no weddings in this time period!" << endl;
                return false;
            }
        }
    }
    cout << "There are now weddings on the list!" << endl;
    return false;
}

// Templates

template void Wedding_Agency::addClientInfo<string>(string, string, string, string, string);
template void Wedding_Agency::addClientInfo<char const*>(char const*, string, string, string, string);
template void Wedding_Agency::addClientInfo<time_t>(time_t, string, string, string, string);

template void Wedding_Agency::addGuest<string>(string, string, string, food_preference);
template void Wedding_Agency::addGuest<char const*>(char const*, string, string, food_preference);
template void Wedding_Agency::addGuest<time_t>(time_t, string, string, food_preference);

template void Wedding_Agency::removeGuest<string>(string, string, string);
template void Wedding_Agency::removeGuest<char const*>(char const*, string, string);
template void Wedding_Agency::removeGuest<time_t>(time_t, string, string);

template void Wedding_Agency::removeGuest<string>(string, string);
template void Wedding_Agency::removeGuest<char const*>(char const*, string);
template void Wedding_Agency::removeGuest<time_t>(time_t, string);

template void Wedding_Agency::addLocation<string>(string, string, string, int, float);
template void Wedding_Agency::addLocation<char const*>(char const*, string, string, int, float);
template void Wedding_Agency::addLocation<time_t>(time_t, string, string, int, float);

template void Wedding_Agency::removeLocation<string>(string, string);
template void Wedding_Agency::removeLocation<char const*>(char const*, string);
template void Wedding_Agency::removeLocation<time_t>(time_t, string);

template void Wedding_Agency::addWeddingSetting<string>(string, string, float, string);
template void Wedding_Agency::addWeddingSetting<char const*>(char const*, string, float, string);
template void Wedding_Agency::addWeddingSetting<time_t>(time_t, string, float, string);

template void Wedding_Agency::removeWeddingSetting<string>(string, string);
template void Wedding_Agency::removeWeddingSetting<char const*>(char const*, string);
template void Wedding_Agency::removeWeddingSetting<time_t>(time_t, string);

template void Wedding_Agency::addSchedulePeriod<string>(string, period, period, string);
template void Wedding_Agency::addSchedulePeriod<char const*>(char const*, period, period, string);
template void Wedding_Agency::addSchedulePeriod<time_t>(time_t, period, period, string);

template void Wedding_Agency::removeSchedulePeriod<string>(string, period, period);
template void Wedding_Agency::removeSchedulePeriod<char const*>(char const*, period, period);
template void Wedding_Agency::removeSchedulePeriod<time_t>(time_t, period, period);

template void Wedding_Agency::addNote<string>(string, string, string);
template void Wedding_Agency::addNote<char const*>(char const*, string, string);
template void Wedding_Agency::addNote<time_t>(time_t, string, string);

template void Wedding_Agency::removeNote<string>(string, string);
template void Wedding_Agency::removeNote<char const*>(char const*, string);
template void Wedding_Agency::removeNote<time_t>(time_t, string);

template void Wedding_Agency::changeClientsFoodPreferences<string>(string, food_preference, food_preference);
template void Wedding_Agency::changeClientsFoodPreferences<char const*>(char const*, food_preference, food_preference);
template void Wedding_Agency::changeClientsFoodPreferences<time_t>(time_t, food_preference, food_preference);

template void Wedding_Agency::changeClientsBudget<string>(string, float);
template void Wedding_Agency::changeClientsBudget<char const*>(char const*, float);
template void Wedding_Agency::changeClientsBudget<time_t>(time_t, float);

template void Wedding_Agency::confirmPresence<string>(string, string, string);
template void Wedding_Agency::confirmPresence<char const*>(char const*, string, string);
template void Wedding_Agency::confirmPresence<time_t>(time_t, string, string);

template void Wedding_Agency::changeFoodPreferenceGuest<string>(string, string, string, food_preference);
template void Wedding_Agency::changeFoodPreferenceGuest<char const*>(char const*, string, string, food_preference);
template void Wedding_Agency::changeFoodPreferenceGuest<time_t>(time_t, string, string, food_preference);

template void Wedding_Agency::changeReservationStateLocation<string>(string, string);
template void Wedding_Agency::changeReservationStateLocation<char const*>(char const*, string);
template void Wedding_Agency::changeReservationStateLocation<time_t>(time_t, string);

template void Wedding_Agency::changeReservationStateWeddingSetting<string>(string, string);
template void Wedding_Agency::changeReservationStateWeddingSetting<char const*>(char const*, string);
template void Wedding_Agency::changeReservationStateWeddingSetting<time_t>(time_t, string);

template void Wedding_Agency::changeScheduleDescription<string>(string, period, period, string);
template void Wedding_Agency::changeScheduleDescription<char const*>(char const*, period, period, string);
template void Wedding_Agency::changeScheduleDescription<time_t>(time_t, period, period, string);

template void Wedding_Agency::changeNote<string>(string, string, string);
template void Wedding_Agency::changeNote<char const*>(char const*, string, string);
template void Wedding_Agency::changeNote<time_t>(time_t, string, string);

template void Wedding_Agency::displayWedding<string>(string);
template void Wedding_Agency::displayWedding<char const*>(char const*);
template void Wedding_Agency::displayWedding<time_t>(time_t);

template bool Wedding_Agency::checkCost<string>(string) const;
template bool Wedding_Agency::checkCost<char const*>(char const*) const;
template bool Wedding_Agency::checkCost<time_t>(time_t) const;

template bool Wedding_Agency::checkOrganisation<string>(string) const;
template bool Wedding_Agency::checkOrganisation<char const*>(char const*) const;
template bool Wedding_Agency::checkOrganisation<time_t>(time_t) const;

template bool Wedding_Agency::checkGuestCapacity<string>(string) const;
template bool Wedding_Agency::checkGuestCapacity<char const*>(char const*) const;
template bool Wedding_Agency::checkGuestCapacity<time_t>(time_t) const;

template bool Wedding_Agency::checkGuestConfirmation<string>(string) const;
template bool Wedding_Agency::checkGuestConfirmation<char const*>(char const*) const;
template bool Wedding_Agency::checkGuestConfirmation<time_t>(time_t) const;

template bool Wedding_Agency::checkExpensiveElements<string>(string) const;
template bool Wedding_Agency::checkExpensiveElements<char const*>(char const*) const;
template bool Wedding_Agency::checkExpensiveElements<time_t>(time_t) const;

template bool Wedding_Agency::checkDishesCount<string>(string) const;
template bool Wedding_Agency::checkDishesCount<char const*>(char const*) const;
template bool Wedding_Agency::checkDishesCount<time_t>(time_t) const;
