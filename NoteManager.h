#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QString>
#include "note.h"
#include "version.h"
#include "relationmanager.h"

/**
 * @brief La classe NotesException
 */

class NotesException{
public:
    /**
     * @brief Un constructeur de NotesException
     * Attribut le paramètre message à l'attribut info
     * @param message de type const QString&
     */
    NotesException(const QString& message):info(message){}
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
 * @brief La classe NoteManager
 * gère les objets Note
 */
class NoteManager
{
    static NoteManager* managN; /**< pointeur sur l'unique instance, statique, de NoteManager */
    Note** notes;  /**< tableau de l'ensemble des Notes */
    unsigned int nbNotes; /**< entier, nombre de Notes existant pour le moment */
    unsigned int nbMaxNotes; /**< entier, capacité actuelle du tableau notes */
    /**
     * @brief constructeur sans argument de NoteManager
     */
    NoteManager():nbNotes(0), nbMaxNotes(5), notes(new Note*[5]){}
    /**
      *@brief Destructeur de NoteManager
      * libère l'espace mémoire alloué au tableau de Notes, et détruit l'ensemble des notes
    */
    ~NoteManager()
    {
        for(unsigned int i=0; i<nbNotes; i++)
            delete notes[i];
    }
    /**
     * @brief constructeur par recopie de NoteManager
     * en privé car on ne veut pas qu'il puisse être utilisé
     */
    NoteManager(const NoteManager& m);
    /**
     * @brief operateur d'affectation
     * en privé car on ne veut pas qu'il puisse être utilisé
    */
    NoteManager& operator=(const NoteManager& m);

public :

    /**
     * @brief La classe Iterator de NoteManager
     */
    class Iterator
    {
        friend class NoteManager;
        Note** currentN; /**< tableau de Note dans lequel on se déplace */
        unsigned int nbRemain; /**< entier, nombre de Notes à parcourir avant d'atteindre la fin du tableau */
        /**
         * @brief constructeur de Iterator
         * @param n tableau de pointeurs de Note
         * @param nb entier correspondant au nombre de notes dans n
         */
        Iterator(Note** n, unsigned nb):currentN(n),nbRemain(nb){}

    public:
        /**
         * @brief constructeur sans argument de Iterator
         */
        Iterator():currentN(nullptr),nbRemain(0){}
        /**
         * @brief methode isDone
         * @return true si on a atteint la fin du tableau, false sinon
         */
        bool isDone() const { return nbRemain==0; }
        /**
         * @brief methode next
         * sert à passer à la note suivante
         */
        void next()
        {
            if (isDone())
                throw NoteException("error, next on an iterator which is done");
            nbRemain--;
            currentN++;
        }
        /**
         * @brief methode current
         * @return une reference sur la Note sur laquelle on est actuellement avec l'iterateur
         */
        Note& current() const
        {
            if (isDone())
                throw NoteException("error, indirection on an iterator which is done");
            return **currentN;
        }
    };

    /**
     * @brief methode getIterator
     * @return un objet Iterator au debut du tableau de notes
     */
    Iterator getIterator()
    {
        return Iterator(notes,nbNotes);
    }

    /**
     * @brief methode statique getInstance
     * @return l'instance unique de NoteManager, et la créé si elle n'existe pas encore
     */
    static NoteManager& getInstance()
    {
        if(!managN)
            managN=new NoteManager();
        return *managN;
    }

    /**
     * @brief methode statique liberer_instance
     * supprime l'unique instance de NoteManager
     */
    static void liberer_instance(){if (managN) delete managN;}
    /**
     * @brief methode addNote
     * créé une note et la range dans le tableau notes
     * @param id de type QString
     * @param title de type QString
     * @param crea de type QDateTime
     * @param modif de type QDateTime
     * @param v une reference sur un objet version
     */
    void addNote(QString id, QString title, QDateTime crea,QDateTime modif, const Version& v);

    /**
     * @brief methode addNote
     * @param id l'id desiré de la note à ajouter
     * @param title le titre de la note à ajouter
     */
    void addNote(QString id, QString title);
    /**
     * @brief methode addNoteXML
     * créé une note et la range dans le tableau notes
     * @param id de type QString
     * @param title de type QString
     * @param crea de type QDateTime
     * @param modif de type QDateTime
     * @param act de type bool, statut active de la note
     * @param supp de type bool, statut supprime de la Note
     * @param nbV de type unisgned int, nombre de versions de la note
     * @param nbMV de type unisgned int, nombre de versions maximum de la note
     * @param a de type QDateTime
     * @param v un tableau d'adresses de versions
     */
    void addNoteXML(QString id, QString title, QDateTime crea,QDateTime modif,bool act, bool supp, unsigned int nbV, unsigned int nbMV,  Version** v);
    /**
     * @brief methode editer
     * @param n pointeur sur la note à éditer
     * @param title de type QString, nouveau titre
     * @param modif de type QDateTime, la date de la modification
     * @param v une reference sur un objet Version
     */
    void editer(Note* n, QString title, QDateTime modif, const Version& v);
    /**
     * @brief methode supprimerNote
     * l'attribut active de l'objet Note est mis à false si la note est référencée
     * l'attribut supprime est mis à true sinon
     * @param n reference sur l'objet Note à supprimer
     */
    void supprimerNote(Note& n);
    /**
     * @brief methode viderCorbeille
     * supprime définitivement tous les objets Note dont l'attribut supprime est à true
     */
    void viderCorbeille();
    /**
     * @brief accesseur getNbNotes
     * @return un entier correspondant aux nombre de notes stockées dans le tableau notes
     */
    unsigned int getNbNotes(){return nbNotes;}
    /**
     * @brief accesseur getNbMaxNotes
     * @return un entier correspondant à la capacité actuelle du tableau notes
     */
    unsigned int getNbMaxNotes(){return nbMaxNotes;}
    /**
     * @brief accesseur getNote
     * @param id de type QString
     * @return un pointeur sur la note dont l'ID est id
     */
    Note* getNote(QString id);
    /**
     * @brief sauve les notes dans un fichier xml
     */
    void save() const;
    /**
     * @brief telecharge les notes depuis un fichier xml
     */
    void load();

};

#endif // NOTEMANAGER_H
