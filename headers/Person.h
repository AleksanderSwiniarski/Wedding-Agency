#ifndef PERSON
#define PERSON

#include <iostream>
#include <string>
class Wedding; //Forward declaration without defining a type

using namespace std;

enum food_preference {
    meatEater,  // 0
    vegetarian, // 1
    vegan,      // 2
    diverse     // 3
};
class Person
{
protected:

    string surname;
    string name;
    food_preference foodPreference;
    // Data of each person

public:

    Person();
    Person(string surname, string name, food_preference fp);
    ~Person();
    Person(const Person& p);
    Person& operator= (const Person& p);
    // Basic methods of a class like Constructor, Destructor, Copy Constructor and Assignment operator

    string& refSurname();
    string& refName();
    food_preference& refFoodPreference();
    // Basic referential methods for access to the data of the object

    friend ostream& operator<<(ostream& os, const Person& p);
    // Method to display data of the person

};

class Engaged: public Person
{
private:

    string bridesName;
    food_preference bridesFoodPreference;
    float budget;
    string contactNumber;
    string email;
    // Data of each Engaged couple

    Engaged* next;
    // Pointer to the next engaged pair in the list

    Wedding* ownWedding;
    // Pointer to own wedding from the list

public:

    Engaged(string surname);
    ~Engaged();
    Engaged(const Engaged& e);
    Engaged& operator= (const Engaged& e);
    // Basic methods of a class like Constructor, Destructor, Copy Constructor and Assignment operator

    string& refBridesName();
    food_preference& refBridesFoodPreference();
    float& refBudget();
    string& refContactNumber();
    string& refEmail();
    Wedding*& refOwnWedding();
    Engaged*& refNext();
    // Basic referential methods for access to the data of the object

    friend ostream& operator<<(ostream& os, const Engaged& p);
    // Method to display data of the couple

};

class Guest : public Person
{
private:

    bool confirmation;
    // Additional data of a guest describing its confirmation of the presence

    Guest* next;
    // Pointer to the next Guest in the list

public:

    Guest(string surname, string name, food_preference fp);
    ~Guest();
    Guest(const Guest& g);
    Guest& operator= (const Guest& g);
    // Basic methods of a class like Constructor, Destructor, Copy Constructor and Assignment operator

    bool& refConfirmation();
    Guest*& refNext();
    // Basic referential method for access to the data of the object

    friend ostream& operator<<(ostream& os, const Guest& g);
    // Method to display data of the guest

};

#endif // PERSON
