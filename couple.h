#ifndef COUPLE_H_INCLUDED
#define COUPLE_H_INCLUDED
#include <ctime>
#include <QString>
#include "Notes.h"



class Couple //Class car on veut tout en privé
{
    
    int label
    Notes* note1;
    Notes* note2;
 
    Editer(){};
    
    
    
    public  :            //si on les veut privées alors ça ne sert à rien, à discuter
    
    int getLabel(){return label;}
    Couple(const Note& n1, const Note& n2, int l):label(l), note1(new Notes(&n1)), note2(new Notes(&n2)) {}

    ~Couple(){delete note1, delete note2;}
    Couple(const Couple& n);  //constructeur par recopie
     
};

#endif //COUPLE_H_INCLUDED
