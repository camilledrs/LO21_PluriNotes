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
    
    Note(QString id, QString title, tm crea,tm modif):id(id), titre(title),dateCrea(crea), dateModif(modif), active(true), supprime(false), nbVersion(0), nbMaxVersion(0){
        versions=new Version*[5];
        //versions[0]=Version(crea);
        nbMaxVersion=5;
        
        //demande a l'utilisateur qu'elle note il veut faire 
        std::cout<<"quelle type d enote voulez vous editer ( 0 pout article, 1 ppour tache, 2 pour multimedia)";
        unsigned int r;
        std::cin>>r
        switch(r){
            case 0: {Qstring texte;
                    std::cout<<"Entrer le texte de l'article";
                    std::cin>>texte;
                    versions[0]=Article(crea,texte);
                     break;
                    }
             case 1: {Qstring action;
                    std::cout<<"Entrer l'action de la tache";
                    std::cin>>action;
                      datetime eche;
                      unsigned int p;
                       std::cout<<"Entrer la date limite de la tache (0 sinon)";
                    std::cin>>eche;
                       std::cout<<"Entrer la priorite de la tache(0 sinon)";
                    std::cin>>p;
                    versions[0]=Tache(crea,texte,eche,p);
                     break;
                    }
                
                case 2: {Qstring texte;
                    std::cout<<"Entrer la description du multimedia";
                    std::cin>>texte;
                      Media type;
                        std::cout<<"Entrer le type du multimedia (0 pour image, 1 pour audio, 2 pour video)";
                    std::cin>>type; 
                         Qstring fichier;
                         std::cout<<"Entrer le fichier du multimedia";
                    std::cin>>fichier;
                    versions[0]=Multimedia(crea,texte,fichier,type);
                     break;
                    }
        }
        nbVersion=1;
        
    }
    ~Note();
    void editer(QString tittle, tm modif,const Version& v); // edition des attributs de note uniquement 
    //creation d'une nouvelle version et penser à incrémenter nbVersion, verifiee si elle est active
    void creerArticle(tm crea, const QString& s);
    void creerMultimedia(tm crea, const QString& desc, const QString& file, Media t);
    void creerTache(tm crea, const QString& a, tm dateFin=0, unsigned int prio=0); //j'ai fait trois constructeurs différents pour es trois types de note possibles
   
    Note(const Note& n);  //constructeur par recopie
    
    public  :            //si on les veut privées alors ça ne sert à rien, à discuter
    QString getId(){return id;}
    QString getTitre(){return titre;}
    tm getDate(){return dateCrea;}
    tm getDateModif()return dateModif;}
    bool getActive(){return active;}
    bool getStatutSupp(){return supprime;}
    suppNote();  //à définir dans LO21.cpp  //attention ne supprimer que les archivées + voir autres conditions dans Drive
    restaurer(Version* v);   //prendre une ancienne version, décaler les suivantes d'un cran vers la gauche, puis mettre la version en question à la dernière place du tableau
    Version& getDerniereVersion(){if(nbVersion !=0) return *versions[nbVersion -1];} //prendre le dernier élément du tableau si on considère que l'on ajoute tjrs à la fin du tableau  
};

#endif //NOTES_H_INCLUDED

//avec getDerniereVersion dans Note, on pourrait ainsi choisir les dernières versions pour créer les couples, puisque c'est une contrainte imposée
