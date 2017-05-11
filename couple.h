#ifndef COUPLE_H_INCLUDED
#define COUPLE_H_INCLUDED
#include <ctime>
#include <QString>
#include "Notes.h"



class Couple //Class car on veut tout en privé
{
    
    int label
    Note* note1;
    Note* note2;
 
    Editer(){};
    
    
    
    public  :            //si on les veut privées alors ça ne sert à rien, à discuter
    
    int getLabel(){return label;}
    Couple(const Note& n1, const Note& n2, int l):label(l), note1(new Note(&n1)), note2(new Note(&n2)) {} //pourquoi new ? et pas &n1
//en plus le constructeur par recopie de note est en prive !!
    ~Couple(){delete note1, delete note2;}
    Couple(const Couple& n);  //constructeur par recopie
     
};

#endif //COUPLE_H_INCLUDED
