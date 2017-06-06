#ifndef NOTES_H_INCLUDED
#define NOTES_H_INCLUDED

#include <ctime>
#include <QString>
//#include "notemanager.h"
#include "version.h"
#include <QDateTime>


/**
 * @brief La classe NoteException
 */
class NoteException{
public:
    /**
     * @brief Un constructeur de NoteException
     * Attribut le paramètre message à l'attribut info
     * @param message de type const QString&
     */
    NoteException(const QString& message):info(message){}
    /**
     * @brief accesseur getInfo
     * @return le QString correspondant à l'attribut privé info
     */
    QString getInfo() const {return info;}
private:
    /**
     * @brief info attribut de type QString
     * correspond au message qui sera envoyé lors de l'exception
     */
    QString info;
};


/**
 * @brief La classe Note
 * Les notes sont gérées par l'unique instance de NoteManager
 */
class Note
{
    friend class NoteManager;  //seule classe qui pourra accéder aux attributs et methodes
    QString id; /**< identifiant unique de type QString */
    QString titre;  /**< titre de la note, un QString */
    QDateTime dateCrea; /**< date de Creation de la note de type QDateTime */
    QDateTime dateModif; /**< date de la dernière modification faite à la note */
    bool active;  /**< attribut active boolean, une note est active si elle n'est pas archivée, une note est active par défault */
    bool supprime; /**< attribut supprime à false si la note n'est pas supprimée, à true sinon */
    Version **versions;  /**< tableau de l'ensemble des versions de la note */
    int nbVersion;  /**< attribut entier correspondant au nombre de versions */
    int nbMaxVersion; /**< attribut entier correspondant à la capacité actuelle tu tableau versions */

    /**
     * @brief constructeur de Note
     * constructeur en privé car on veut que seul NoteManager puisse créer des Notes
     * @param id de type QString, id de la note à créer
     * @param title de type QString
     * @param crea de type QDateTime, date de creation de la note
     * @param modif de type QDateTime, date de modification de la Note
     * @param v référence sur objet Version, première version de la note
     */
    Note(QString id, QString title, QDateTime crea,QDateTime modif, const Version& v):id(id), titre(title),dateCrea(crea), dateModif(modif), active(true), supprime(false), nbVersion(1), nbMaxVersion(5)
    {
        versions=new Version*[5];
        versions[0]=v.clone();
    }
    /**
     * @brief constructeur de Note
     * constructeur en privé car on veut que seul NoteManager puisse créer des Notes
     * @param id de type QString, id de la note à créer
     * @param title de type QString
     * @param crea de type QDateTime, date de creation de la note
     * @param modif de type QDateTime, date de modification de la Note
     * @param act de type bool, statut active de la note
     * @param supp de type bool, statut supprime de la Note
     * @param nbV de type unisgned int, nombre de versions de la note
     * @param nbMV de type unisgned int, nombre de versions maximum de la note
     * @param v référence sur un tabelau d'adresses de Version
     */
    Note(QString id, QString title, QDateTime crea,QDateTime modif,bool act, bool supp, unsigned int nbV, unsigned int nbMV,  Version** v):id(id), titre(title),dateCrea(crea), dateModif(modif), active(act), supprime(supp), nbVersion(nbV), nbMaxVersion(nbMV){
        versions=new Version*[nbMV];
        for(unsigned int i=0; i<nbV; i++){
            versions[i]=v[i]->clone();
        }
    }
    /**
     * @brief methode editer
     * @param tittle de type QString, nouveau titre que l'on souhaite donner
     * @param modif de type QDateTime, date de la modification
     * @param v référence de version, nouvelle version créée
     */
    void editer(QString tittle, QDateTime modif,const Version& v); // edition des attributs de note uniquement
    //creation d'une nouvelle version et penser à incrémenter nbVersion, verifiee si elle est active
//    void creerArticle(tm crea, const QString& s);
//    void creerMultimedia(tm crea, const QString& desc, const QString& file, Media t);
//    void creerTache(tm crea, const QString& a, tm dateFin=0, unsigned int prio=0); //j'ai fait trois constructeurs différents pour es trois types de note possibles
    /**
     * @brief constructeur de recopie de Note
     * en privé pour que l'utilisateur de Note ne puisse pas y avoir accès
     */
    Note(const Note& n);

public  :
    /**
     @brief destructeur de Note
      celui par défault suffit */
   ~Note();
    /**
     * @brief accesseur getId
     * @return l'ID de la note, un QString
     */
    QString getId(){return id;}
    /**
     * @brief accesseur getTitre
     * @return le titre actuel (QString) de la note
     */
    QString getTitre(){return titre;}
    /**
     * @brief accesseur getDate
     * @return la valeur (QDateTime) de l'attribut dateCrea
     */
    QDateTime getDate(){return dateCrea;}
    /**
     * @brief accesseur getDateModif
     * @return la valeur de l'attribut dateModif (un QDateTime)
     */
    QDateTime getDateModif(){return dateModif;}
    /**
     * @brief accesseur getActive
     * @return true si la note est active, false sinon
     */
    bool getActive(){return active;}
    /**
     * @brief accesseur getStatutSupp
     * @return true si la note est supprimee, false sinon
     */
    bool getStatutSupp(){return supprime;}
    /**
     * @brief accesseur getNbVersion
     * @return le nombre de versions de la note
     */
    unsigned int getNbVersion(){return nbVersion;}
    /**
     * @brief accesseur getNbMaxVersion
     * @return le nombre de versions de la note
     */
    unsigned int getNbMaxVersion(){return nbMaxVersion;}
    /**
     * @brief methode restaurer
     * On place la version passée en paramètre à la fin du tableau versions, ce sera ainsi la version active
     * @param v pointeur sur la version à restaurer
     */
    void restaurer(Version* v);
    /**
     * @brief methode verifRef
     * cherche si une note est référencée, et créé le couple pour la relation référence si c'est le cas
     * @param s correspond à la chaine dans laquelle on cherche la sous chaine "\ref{idy}"
     */
    void verifRef( const QString s);
    /**
     * @brief methode sucesseurs
     * @param nb un pointeur d'entier, qui contiendra le nombre de successeurs de la note
     * @return un tableau de pointeurs de Note, correspondant aux successeurs de la note actuelle
     */
    Note** sucesseurs(unsigned int* nb);
    /**
     * @brief methode predecesseurs
     * @param nb, pointeur d'entier qui contiendra le nombre de predecesseurs de la note
     * @return un tableau de pointeurs des notes prédecessurs de la note traitée
     */
    Note** predecesseurs(unsigned int* nb);

    Version& getDerniereVersion(){if(nbVersion !=0) return *versions[nbVersion -1];} //prendre le dernier élément du tableau si on considère que l'on ajoute tjrs à la fin du tableau
};

#endif // NOTE_H
