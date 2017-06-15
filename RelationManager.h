#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H

#include <ctime>
#include <QString>
#include <QtXml>
#include <QFile>
#include "relation.h"

/**
 * @brief la classe RelationManager
 * gère l'ensemble des objets Relation
 */
class RelationManager
{
    static RelationManager* managR; /**< pointeur sur l'unique instance */
    Relation** relations; /**< tableau de l'ensemble des relations */
    unsigned int nbRelations; /**< entier, nombre de relations stockées dans relations */
    Relation* Reference; /**< pointeur sur la relation spéciale Reference */
    unsigned int nbMaxRelations; /**< entier, capacité actuelle du tableau relations */
    /**
     * @brief constructeur sans argument de RelationManager
     */
    RelationManager():nbRelations(0),nbMaxRelations(0),relations(nullptr){
         this->Reference = new Relation("Reference", "Relation speciale reference", true);
    }
    /**
      @brief destructeur de RelationManager
      détruit l'ensemble des objets Relation, et libère
      l'espace mémoire alloué au tableau relations
      */
    ~RelationManager(){
        for(unsigned int i=0; i<nbRelations; i++) delete relations[i]; // composition uniquement
        delete[] relations; // composition + agrégation
    }
    /**
     * @brief constructeur de recopie de RelationManager
     * en privé car on ne veut pas qu'il puisse être utilisé
     */
    RelationManager(const RelationManager& m);
    /**
     * @brief operateur d'affectation de RelationManager
     * en privé car on ne veut pas qu'il puisse être utilisé
     */
    RelationManager& operator=(const RelationManager& m);


public :
    /**
     * @brief methode editerRelation
     * @param r pointeur sur la Relation à éditer
     * @param t le titre que l'on souhaite donner
     * @param d la description que l'on souhaite attribuer à la relation
     */
    void editerRelation(Relation* r, QString& t, QString& d){r->editer(t,d);}
    /**
     * @brief methode suppRelation
     * @param r, reference sur l'objet relation à supprimer
     */
    void suppRelation(Relation& r);
    /**
     * @brief methode addRelation
     * @param t un QString& correspondant au titre que l'on souhaite donner
     * @param d QString& correspondant à la description de la Relation à ajouter
     * @param orient bool mis à true par défaut
     */
    void addRelation(QString& t, QString& d, bool orient=true);

    /**
     * @brief La classe Iterator de RelationManager
     */
    class Iterator
    {
        friend class RelationManager;
        Relation** currentR; /**< le tableau d'objets Relation dans lequel itérer */
        unsigned int nbRemain; /**< entier, nombre de relations à parcourir avant d'atteindre la fin du tableau */
        /**
         * @brief constructeur de Iterator
         * @param r tableau de pointeurs d'objets Reference
         * @param nb entier, nombre d'objets Référence à parcourir avant d'atteindre la fin du tableau
         */
        Iterator(Relation** r, unsigned nb):currentR(r),nbRemain(nb){}

    public:
        /**
         * @brief constructeur sans argument de Iterator
         */
        Iterator():nbRemain(0),currentR(nullptr){}
        /**
         * @brief methode isDone
         * @return true si on a atteint la fin du tableau, false sinon
         */
        bool isDone() const { return nbRemain==0; }
        /**
         * @brief methode next
         * passe à la relation suivante dans le tableau
         */
        void next()
        {
            if (isDone())
                throw NoteException("error, next on an iterator which is done");
            nbRemain--;
            currentR++;
        }
        /**
         * @brief methode current
         * @return une reference sur la Relation actuellement pointée
         */
        Relation& current() const
        {
            if (isDone())
                throw NoteException("error, indirection on an iterator which is done");
            return **currentR;
        }
    };

    /**
     * @brief methode getIterator
     * @return un iterateur sur la debut du tableau relations
     */
    Iterator getIterator() {return Iterator(relations,nbRelations);/*0*/}
    /**
     * @brief methode statique getInstance
     * créé l'unique instance de RelationManager si elle n'existe pas déjà
     * @return une reference sur l'unique instance de RelationManager
     */
    static RelationManager& getInstance()
    {
        if(!managR)
            managR= new RelationManager();
        return *managR;
    }
    /**
     * @brief methode statique free_instance
     */
    static void free_instance(){if (managR) delete managR;}
    /**
     * @brief methode getNbRelations
     * @return le nombre de relation dans RelationManager
     */
    int getNbRelations(){return nbRelations;}
    /**
     * @brief methode getRef
     * @return un pointeur sur la relation spéciale Reference
     */
    Relation* getRef(){return Reference;}
    /**
     * @brief methode verifNoteRef
     * @param n un pointeur sur une note
     * @return true si la note est référencée, false sinon
     */
    bool verifNoteRef(const Note* n);
     /**
     * @brief sauve les relations dans un fichier xml
     */
    void save() const;
    /**
     * @brief telecharge les relations depuis un fichier xml
     */
    void load();

};


#endif // RELATIONMANAGER_H
