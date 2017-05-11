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
    Couple(const Couple& n);  //constructeur par recopie
    
    
    public  :            //si on les veut privées alors ça ne sert à rien, à discuter
    
    int getLabel(){return label;}
    setLabel(int newl){label=newl;}
    Couple(const Note& n1, const Note& n2, int l):label(l), note1(&n1), note2(&n2) {}
    ~Couple(){delete note1, delete note2;}
    
     
};

#endif //COUPLE_H_INCLUDED
