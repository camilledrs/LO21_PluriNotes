#ifndef NOTES_H_INCLUDED
#define NOTES_H_INCLUDED
#include <ctime>
#include <QString>
#include "NoteManager.h"

class NoteException{
public:
    NoteException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

class Note //Class car on veut tout en privé
{
    friend class NoteManager;  //seule classe qui pourra accéder aux attributs et methodes
    QString id;
    QString titre;
    tm dateCrea; //normalement tm est un type struct de la bibli ctime
    bool active;
    bool supprime;
    Version **versions;  //faire un tableau ou une pile(FILO) serait encore mieux
    
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
    
    //Je pense qu'il faut faire comme un VersionManager mais dans Note, en gros implémenter les fonctiosn nécessaires à la gestion du tableau/de la pile
    Version* getDerniereVersion(); //faire dépiler en gros, ou alors prendre le dernier élément du tableau si on considère que l'on ajoute tjrs à la fin du tableau tableau 
};

#endif //NOTES_H_INCLUDED

//avec getDerniereVersion dans Note, on pourrait ainsi choisir les dernières versions pour créer les couples, puisque c'est une contrainte imposée
