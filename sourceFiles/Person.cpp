#include <iostream>
#include <string>
#include "Person.h"

using namespace std;

// PERSON

Person::Person()
{
    foodPreference = meatEater;
}
Person::Person(string surname, string name, food_preference fp)
{
    this -> surname = surname;
    this -> name = name;
    this -> foodPreference = fp;
}
Person::~Person()
{

}
Person::Person(const Person& p)
{
    this -> surname = p.surname;
    this -> name = p.name;
    this -> foodPreference = p.foodPreference;
}
Person& Person::operator= (const Person& p)
{
    //Check for self assignment
    if(this == &p)
        return *this;

    this -> surname = p.surname;
    this -> name = p.name;
    this -> foodPreference = p.foodPreference;
    return *this;
}

string& Person::refSurname()
{
    return surname;
}
string& Person::refName()
{
    return name;
}
food_preference& Person::refFoodPreference()
{
    return foodPreference;
}

ostream& operator<<(ostream& os, const Person& p)
{
    os << "Name: " << p.name << endl;
    os << "Surname: " << p.surname << endl;
    os << "Food preference: ";

    switch(p.foodPreference){
    case meatEater:     // 0
    os << "meat eater";
    break;
    case vegetarian:    // 1
    os << "vegetarian";
    break;
    case vegan:         // 2
    os << "vegan";
    break;
    case diverse:       // 3
    os << "diverse";
    break;
    }

    return os;
}

// ENGAGED

Engaged::Engaged(string surname)
{
    this -> surname = surname;
    budget = 0;
    ownWedding = nullptr;
    next = nullptr;
}
Engaged::~Engaged()
{

}
Engaged::Engaged(const Engaged& e)
{
    this -> surname = e.surname;
    this -> name = e.name;
    this -> foodPreference = e.foodPreference;
    this -> bridesName = e.bridesName;
    this -> bridesFoodPreference = e.bridesFoodPreference;
    this -> budget = e.budget;
    this -> contactNumber = e.contactNumber;
    this -> email = e.email;
    next = nullptr;
    ownWedding = nullptr;
}
Engaged& Engaged::operator= (const Engaged& e)
{
    //Check for self assignment
    if(this == &e)
        return *this;

    this -> surname = e.surname;
    this -> name = e.name;
    this -> foodPreference = e.foodPreference;
    this -> bridesName = e.bridesName;
    this -> bridesFoodPreference = e.bridesFoodPreference;
    this -> budget = e.budget;
    this -> contactNumber = e.contactNumber;
    this -> email = e.email;
    return *this;
}

string& Engaged::refBridesName()
{
    return bridesName;
}
food_preference& Engaged::refBridesFoodPreference()
{
    return bridesFoodPreference;
}
float& Engaged::refBudget()
{
    return budget;
}
string& Engaged::refContactNumber()
{
    return contactNumber;
}
string& Engaged::refEmail()
{
    return email;
}

Wedding*& Engaged::refOwnWedding()
{
    return ownWedding;
}

Engaged*& Engaged::refNext()
{
    return next;
}

ostream& operator<<(ostream& os, const Engaged& p)
{
    if(((p.name!="\0") && (p.bridesName!="\0")) == true)
    {
        os << "Groom: " << p.name << " " << p.surname << endl;
        os << "Bride: " << p.bridesName << " " << p.surname << endl;
    }
    else
    {
        os << "Engaged's pair surname: " << p.surname << endl;
    }
    os << "Groom's food preference: ";
    switch(p.foodPreference){
    case meatEater:     // 0
    os << "Meat eater";
    break;
    case vegetarian:    // 1
    os << "Vegetarian";
    break;
    case vegan:         // 2
    os << "Vegan";
    break;
    case diverse:       // 3
    os << "Diverse";
    break;
    }
    os << endl;
    os << "Bride's food preference: ";
    switch(p.bridesFoodPreference){
    case meatEater:     // 0
    os << "Meat eater";
    break;
    case vegetarian:    // 1
    os << "Vegetarian";
    break;
    case vegan:         // 2
    os << "Vegan";
    break;
    case diverse:       // 3
    os << "Diverse";
    break;
    }
    os << endl;
    os << "Budget: " << p.budget << endl;
    os << "Contact information: " << endl;
    os << "Telephone number: ";
    if (p.contactNumber != "\0")
        os << p.contactNumber << endl;
    else
        os << "Not added!" << endl;

    os << "Email: ";
    if (p.email != "\0")
        os << p.email;
    else
        os << "Not added!";

    return os;
}

// GUEST

Guest::Guest(string surname, string name, food_preference fp)
{
    this -> surname = surname;
    this -> name = name;
    this -> foodPreference = fp;
    confirmation = false;
    next = nullptr;
}
Guest::~Guest()
{

}
Guest::Guest(const Guest& g)
{
    this -> surname = g.surname;
    this -> name = g.name;
    this -> foodPreference = g.foodPreference;
    this -> confirmation = g.confirmation;
    next = nullptr;
}
Guest& Guest::operator= (const Guest& g)
{
    //Check for self assignment
    if(this == &g)
        return *this;

    this -> surname = g.surname;
    this -> name = g.name;
    this -> foodPreference = g.foodPreference;
    this -> confirmation = g.confirmation;
    return *this;
}

bool& Guest::refConfirmation()
{
    return confirmation;
}

Guest*& Guest::refNext()
{
    return next;
}

ostream& operator<<(ostream& os, const Guest& g)
{
    os << "Name and Surname: " << g.name << " " << g.surname << endl;
    os << "Food preference: ";
    switch(g.foodPreference)
    {
    case meatEater:     // 0
        os << "meat eater";
        break;
    case vegetarian:    // 1
        os << "vegetarian";
        break;
    case vegan:         // 2
        os << "vegan";
        break;
    case diverse:       // 3
        os << "diverse";
        break;
    }
    os << endl;
    switch(g.confirmation){
    case true:
    os << "Confirmed";
    break;
    case false:
    os << "Not confirmed";
    break;
    }
    return os;
}
