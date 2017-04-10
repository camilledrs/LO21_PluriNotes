#ifndef LO21_H_INCLUDED
#define LO21_H_INCLUDED
#include <ctime>

class NotesException{
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


class Note //Class car on veut tout en privé
{
    friend class NoteManager;  //seule classe qui pourra accéder aux attributs et methodes
    string id;
    string titre;
    tm dateCrea; //normalement tm est un type struct de la bibli ctime
    bool active;
    bool supprime;
    
    Note();
    ~Note();
    virtual editer()=0; //virtuelle pure
    Note(const Note& n);  //constructeur par recopie
    
    public  :            //si on les veut privées alors ça ne sert à rien, à discuter
    int getId(){return id;}
    string getTitre(){return titre;}
    tm getDate(){return dateCrea;}
    bool getActive(){return active;}
    bool getStatutSupp(){return supprime;}
    suppNote();  //à définir dans LO21.cpp  //attention ne supprimer que les archivées + voir autres conditions dans Drive
};

class NoteManager
{
    Note** notes;
    unsigned int nbNotes;
    void addNote(Note* n);
    
    
    NotesManager();
    ~NotesManager();
    NotesManager(const NotesManager& m);
    NotesManager& operator=(const NotesManager& m);
    
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
                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                currentN++;
            }
            Note& current() const {
                if (isDone())
                    throw NotesException("error, indirection on an iterator which is done");
                return **currentN;
            }
};


#endif // LO21_H_INCLUDED
