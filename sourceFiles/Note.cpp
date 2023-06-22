#include <iostream>
#include "Note.h"

using namespace std;

Note::Note(string title, string scribble)
{
    this -> title = title;
    this -> scribble = scribble;
    Note* next = nullptr;
}

Note::~Note()
{

}

Note::Note(const Note& n)
{
    this -> title = n.title;
    this -> scribble = n.scribble;
    next = nullptr;
}

Note& Note::operator=(const Note& n)
{
    //Check for self assignment
    if(this == &n)
        return *this;

    this -> title = n.title;
    this -> scribble = n.scribble;

    return *this;
}

string& Note::refTitle()
{
    return title;
}

string& Note::refScribble()
{
    return scribble;
}

Note*& Note::refNext()
{
    return next;
}

ostream & operator<< (ostream& os, const Note& n)
{
    os << "Note: " << n.title << endl;
    os << n.scribble;
    return os;
}
