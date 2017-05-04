
#ifndef NOTES_H_INCLUDED
#define NOTES_H_INCLUDED
#include <ctime>
#include <QString>
#include "Notes.h"

class Version
{
    datetime date;
    friend class Note;
    
    public :
        Version(Version&);
        Version(datetime d):Date(d);
        virtual void editer()=0;   //class abstraite
        datetime getDate(){return date;}

};
