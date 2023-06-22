#ifndef ORGANISATION_ELEMENT
#define ORGANISATION_ELEMENT

#include <iostream>
#include <string>

using namespace std;

class Organisation_Element
{
protected:

    string title;
    bool toDo;
    // Basic data of Organisation Element

public:

    Organisation_Element();
    Organisation_Element(string title);
    ~Organisation_Element();
    Organisation_Element(const Organisation_Element& oe);
    Organisation_Element& operator= (const Organisation_Element& oe);
    // Basic methods of a class like Constructor, Destructor, Copy Constructor and Assignment operator

    string& refTitle();
    bool& refToDo();
    // Basic referential methods for access to the data and lists of the object

    friend ostream& operator<< (ostream& os, const Organisation_Element& oe);
    // Method to display data of the Organisation_Element
};

class Location : public Organisation_Element
{
private:

    string address;
    int guestCapacity;
    float costPerGuest;
    // Additional data of Location

    Location* next;
    // Pointer to the next Location

public:

    Location(string title, string address, int guestCapacity, float costPerGuest);
    ~Location();
    Location(const Location& l);
    Location& operator= (const Location& l);
    // Basic methods of a class like Constructor, Destructor, Copy Constructor and Assignment operator

    string& refAdress();
    int& refguestCapacity();
    float& refCostPerGuest();
    Location*& refNext();
    // Basic referential methods for access to the data and lists of the object

    friend ostream& operator<< (ostream& os, const Location& l);
    // Method to display data of the Location

};

class Wedding_Setting : public Organisation_Element
{
private:

    string description;
    float price;
    // Additional data of wedding setting

    Wedding_Setting* next;
    // Pointer to the next Location

public:

    Wedding_Setting(string title, string description, float price);
    ~Wedding_Setting();
    Wedding_Setting(const Wedding_Setting& ws);
    Wedding_Setting& operator=(const Wedding_Setting& ws);
    // Basic methods of a class like Constructor, Destructor, Copy Constructor and Assignment operator

    string& refDescription();
    float& refPrice();
    Wedding_Setting*& refNext();
    // Basic referential methods for access to the data and lists of the object

    friend ostream& operator<< (ostream& os, const Wedding_Setting& ws);
    // Method to display data of the wedding setting

};

#endif // ORGANISATION_ELEMENT
