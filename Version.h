
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
        virtual ~Version();
        Version(datetime d):Date(d);
        virtual void editer()=0;   //class abstraite
        datetime getDate(){return date;}

};


class Article : public Version
{
        QString texte;
        
    public :
        Article(datetime d,const QString& s):Version(d),texte(s){}
        void editer();  //à voir, parce que ça veut dire créer une nouvelle version, on est obligés de la définir pour que ce ne soit plus une classe abstraite

};

enum Statut{'En attente', 'En cours', 'Terminee'};

class Tache : public Version
{
        QString action;
        Statut statut;
        datetime dateTache;
        unsigned int priorite;
        
     public :
        Tachee(datetime dv,const QString a, datetime d=0, unsigned int p=0) :Version(dv),action(a), statut('En attente'), dateTache(d), priorite(p){}
        editer(); //a voir
        QString getAction(){return action;}
        Statut getStatut(){return statut;}
        unsigned int getPriority(){return priorite;}
        datetime getDate() {return dateTache;}

};


enum Media {'image', 'audio', 'video'};


class Multimedia : public Version
{
        QString description;
        QString fichier;
        Media type;
        
     public :
        Multimedia(datetime dv,const QString& d, const QString& f, Media t):Version(dv),description(d), fichier(f), type(t){}
        editer(); //a voir
        QString getDescription() {return description;}
        QString getFichier() {return fichier;}
        Media getType() {return type;}

};



