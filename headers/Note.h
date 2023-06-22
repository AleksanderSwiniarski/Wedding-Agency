#ifndef NOTE
#define NOTE

#include <iostream>
#include <string>

using namespace std;

class Note
{
private:

    string title;
    string scribble;
    // Basic data of the note

    Note* next;
    // Pointer to the next note

public:

    Note(string title, string scribble);
    ~Note();
    Note(const Note& n);
    Note& operator=(const Note& n);
    // Basic methods of a class like Constructor, Destructor, Copy Constructor and Assignment operator

    string& refTitle();
    string& refScribble();
    Note*& refNext();
    // Basic referential methods for access to the data and lists of the object

    friend ostream & operator<< (ostream& os, const Note&  n);
    // Method to display data of the note
};

#endif // NOTE
