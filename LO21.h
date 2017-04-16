#ifndef LO21_H_INCLUDED
#define LO21_H_INCLUDED
#include <ctime>
#include <QString>

enum Statut { En attente, En cours, terminée};

enum Media {image, audio, video};


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

class NoteManager
{
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    void addNote(Note* n);
    
    
    NoteManager();
    ~NoteManager();
    NoteManager(const NoteManager& m);
    NoteManager& operator=(const NoteManager& m);
    
    public :
    class Iterator {
            friend class NoteManager;
            Note** currentN;
            unsigned int nbRemain;
            Iterator(Note** n, unsigned nb):currentN(n),nbRemain(nb){}
        public:
            Iterator():nbRemain(0),currentN(nullptr){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NoteException("error, next on an iterator which is done");
                nbRemain--;
                currentN++;
            }
            Note& current() const {
                if (isDone())
                    throw NoteException("error, indirection on an iterator which is done");
                return **currentN;
            }
};
    
    Iterator getIterator() {
            return Iterator(notes,nbNotes);
        }
};
    
    
class Relation{
    friend class RelationManager;
    QString titre;
    QString description;
    bool orientee;
    Relation():orientee(True){} //constructeur sans argument, orientee vrai par défaut
    ~Relation();
    void SeeRelation();
    Relation(Relation& r);
    
    public :
    QString getTitre(){return titre;}
    QString getDesc(){return description;}
    bool getOrient(){return orientee;}
};



class RelationManager
{
    Relation** relations;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;
    void addRelation(Relation* r);
    
    
    RelationManager();
    ~RelationManager();
    RelationManager(const RelationManager& m);
    RelationManager& operator=(const RelationManager& m);
    
    public :
    class Iterator {
            friend class RelationManager;
            Relation** currentR;
            unsigned int nbRemain;
            Iterator(Relation** r, unsigned nb):currentR(r),nbRemain(nb){}
        public:
            Iterator():nbRemain(0),currentR(nullptr){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NoteException("error, next on an iterator which is done");
                nbRemain--;
                currentR++;
            }
            Relation& current() const {
                if (isDone())
                    throw NoteException("error, indirection on an iterator which is done");
                return **currentR;
            }
};
    
    Iterator getIterator() {
            return Iterator(relations,nbRelations);
        }
};

#endif // LO21_H_INCLUDED
