#ifndef NOTES_H_INCLUDED
#define NOTES_H_INCLUDED
#include <ctime>
#include <QString>
#include "NoteManager.h"

class Note //Class car on veut tout en privé
{
    friend class NoteManager;  //seule classe qui pourra accéder aux attributs et methodes
    QString id;
    QString titre;
    tm dateCrea; //normalement tm est un type struct de la bibli ctime
    bool active;
    bool supprime;
    
    Note();
    ~Note();
    virtual editer()=0; //virtuelle pure
    Note(const Note& n);  //constructeur par recopie
    
    public  :            //si on les veut privées alors ça ne sert à rien, à discuter
    QString getId(){return id;}
    QString getTitre(){return titre;}
    tm getDate(){return dateCrea;}
    bool getActive(){return active;}
    bool getStatutSupp(){return supprime;}
    suppNote();  //à définir dans LO21.cpp  //attention ne supprimer que les archivées + voir autres conditions dans Drive
};
