#include <iostream>
#include <string>
#include "Organisation_Element.h"

using namespace std;

// ORGANISATION ELEMENT

Organisation_Element::Organisation_Element()
{
    toDo = false;
}

Organisation_Element::Organisation_Element(string title)
{
    this -> title = title;
    toDo = false;
}

Organisation_Element::~Organisation_Element()
{

}

Organisation_Element::Organisation_Element(const Organisation_Element& oe)
{
    this -> title = oe.title;
    this -> toDo = oe.toDo;
}
Organisation_Element& Organisation_Element::operator= (const Organisation_Element& oe)
{
    //Check for self assignment
    if(this == &oe)
        return *this;

    this -> title = oe.title;
    this -> toDo = oe.toDo;
    return *this;
}

string& Organisation_Element::refTitle()
{
    return title;
}

bool& Organisation_Element::refToDo()
{
    return toDo;
}

ostream& operator<< (ostream& os, const Organisation_Element& oe)
{
    os << oe.title << endl;
    if(oe.toDo)
        os << "Organised";
    else
        os << "Not organized";
    return os;
}

// LOCATION

Location::Location(string title, string address, int guestCapacity, float costPerGuest)
{
    this -> title = title;
    this -> address = address;
    this -> guestCapacity = guestCapacity;
    this -> costPerGuest = costPerGuest;
    next = nullptr;
}

Location::~Location()
{

}

Location::Location(const Location& l)
{
    this -> title = l.title;
    this -> address = l.address;
    this -> guestCapacity = l.guestCapacity;
    this -> costPerGuest = l.costPerGuest;
    this -> toDo = l.toDo;
    next = nullptr;
}
Location& Location::operator= (const Location& l)
{
    if(this == &l)
        return *this;

    this -> title = l.title;
    this -> address = l.address;
    this -> guestCapacity = l.guestCapacity;
    this -> costPerGuest = l.costPerGuest;
    this -> toDo = l.toDo;

    return *this;
}
string& Location::refAdress()
{
    return address;
}
int& Location::refguestCapacity()
{
    return guestCapacity;
}
float& Location::refCostPerGuest()
{
    return costPerGuest;
}

Location*& Location::refNext()
{
    return next;
}

ostream& operator<< (ostream& os, const Location& l)
{
    os << "Name of location: "<< l.title << endl;
    os << "Address: " << l.address << endl;
    os << "Guest capacity: " << l.guestCapacity << endl;
    os << "Cost per guest: "<< l.costPerGuest << endl;
    os << "Status: ";
    if(l.toDo)
        os << "Organised";
    else
        os << "Not organized";
    return os;
}

// WEDDING SETTING

Wedding_Setting::Wedding_Setting(string title, string description, float price)
{
    this -> title = title;
    this -> description = description;
    this -> price = price;
    next = nullptr;
}

Wedding_Setting::~Wedding_Setting()
{

}

Wedding_Setting::Wedding_Setting(const Wedding_Setting& ws)
{
    this -> title = ws.title;
    this -> description = ws.description;
    this -> price = ws.price;
    this -> toDo = ws.toDo;
    next = nullptr;
}
Wedding_Setting& Wedding_Setting::operator=(const Wedding_Setting& ws)
{
    if(this == &ws)
        return *this;

    this -> title = ws.title;
    this -> description = ws.description;
    this -> price = ws.price;
    this -> toDo = ws.toDo;
    return *this;
}

string& Wedding_Setting::refDescription()
{
    return description;
}
float& Wedding_Setting::refPrice()
{
    return price;
}

Wedding_Setting*& Wedding_Setting::refNext()
{
    return next;
}

ostream& operator<< (ostream& os, const Wedding_Setting& ws)
{
    os << "Name of setting: " << ws.title << endl;
    os << "Description: " << ws.description << endl;
    os << "Price: " << ws.price << endl;
    os << "Status: ";
    if(ws.toDo)
        os << "Organised";
    else
        os << "Not organized";
    return os;
}
