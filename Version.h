
#ifndef NOTES_H_INCLUDED
#define NOTES_H_INCLUDED
#include <ctime>
#include <QString>
#include "Notes.h"

class Version
{
        datetime date;
        friend class Note;
    
       Version(const Version&);
        virtual ~Version()=0;
        Version(datetime d):Date(d);
        virtual Version* clone()const=0;
        
        // j'ai mis ses méthodes en privée pour qu'elles ne puissent être utilisée que par les classes friend
    
    public :
        
        datetime getDate(){return date;}
};


class Article : public Version
{
        QString texte;
        Article (const Article& );
        Article(datetime d,const QString& s):Version(d),texte(s){} // en privé pour qu'un article ne puisse être construit que par une classe friend
        Article* clone()const{return new Article(*this);}
    public :
        
      
};

enum Statut{'En attente', 'En cours', 'Terminee'};

class Tache : public Version
{
        QString action;
        Statut statut;
        datetime dateTache;
        unsigned int priorite;
        Tache(const Tache& );
        Tache(datetime dv,const QString a, datetime d=0, unsigned int p=0) :Version(dv),action(a), statut('En attente'), dateTache(d), priorite(p){} // en privé pour qu'une tache ne puisse être construite que par une classe friend
        Tache* clone()const{return new Tache(*this);}
     public :
        
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
        Multimedia(const Multimedia& );
        Multimedia(datetime dv,const QString& d, const QString& f, Media t):Version(dv),description(d), fichier(f), type(t){} // en privé pour qu'un multimedia ne puisse être construit que par une classe friend
        Multimedia* clone()const{return new Multimedia(*this);} 
     public :
        
       
        QString getDescription() {return description;}
        QString getFichier() {return fichier;}
        Media getType() {return type;}
        

};



