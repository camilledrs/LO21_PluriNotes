#ifndef NOTES_H_INCLUDED
#define NOTES_H_INCLUDED
#include <ctime>
#include <QString>
#include "NoteManager.h"
#include "Version.h"

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
    tm dateModif;
    bool active;  //active par défaut ?
    bool supprime;
    Version **versions;  //faire un tableau
    int nbVersion;
    int nbMaxVersion;
    
    Note(QString id, QString title, tm crea,tm modif, const Version& v):id(id), titre(title),dateCrea(crea), dateModif(modif), active(true), supprime(false), nbVersion(1), nbMaxVersion(5){
        versions=new Version*[5];
        versions[0]=v.clone();   
    }
    Note();
    ~Note();
    void editer(QString title, tm modif,const Version& v); // edition des attributs de note uniquement 
    //creation d'une nouvelle version et penser à incrémenter nbVersion, verifiee si elle est active
    //void creerArticle(tm crea, const QString& s);
    //void creerMultimedia(tm crea, const QString& desc, const QString& file, Media t);
    //void creerTache(tm crea, const QString& a, tm dateFin=0, unsigned int prio=0); //j'ai fait trois constructeurs différents pour es trois types de note possibles
   
    Note(const Note& n);  //constructeur par recopie
    
    public  :            //si on les veut privées alors ça ne sert à rien, à discuter
    QString getId(){return id;}
    QString getTitre(){return titre;}
    tm getDate(){return dateCrea;}
    tm getDateModif()return dateModif;}
    bool getActive(){return active;}
    bool getStatutSupp(){return supprime;}
    void suppNote();  //à définir dans LO21.cpp  //attention ne supprimer que les archivées + voir autres conditions dans Drive
    void restaurer(Version* v);   //prendre une ancienne version, décaler les suivantes d'un cran vers la gauche, puis mettre la version en question à la dernière place du tableau
    Version& getDerniereVersion(){if(nbVersion !=0) return *versions[nbVersion -1];} //prendre le dernier élément du tableau si on considère que l'on ajoute tjrs à la fin du tableau  
    void verifRef( const Qstring s);
    void sucesseurs(Note** succ, unsigned int* nb);
    void predecesseurs(Note** pred, unsigned int* nb);
};

#endif //NOTES_H_INCLUDED

//avec getDerniereVersion dans Note, on pourrait ainsi choisir les dernières versions pour créer les couples, puisque c'est une contrainte imposée
