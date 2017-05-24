#ifndef NOTESMANAGER_H_INCLUDED
#define NOTESMANAGER_H_INCLUDED
#include <ctime>
#include <QString>
#include "Notes.h"

class NoteManager
{
    friend class Note;
    static NoteManager* managN;
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    
    NoteManager():notes(nullptr), nbNotes(0), nbMaxNotes(0){}
    ~NoteManager(){
        for(unsigned int i=0; i<nbNotes; i++) delete notes[i]; // composition uniquement
        delete[] notes; // composition + agrégation
    }
    NoteManager(const NoteManager& m);
    NoteManager& operator=(const NoteManager& m);
    void addNote(QString id, QString title, tm crea,tm modif);
    void editer(Note* n, QString title, tm modif, const Version& v);
    void supprimerNote(Note& n);
    void viderCorbeille();
    
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
    
    
    public :
        static NoteManager& getInstance(){
            if(!managN) managN=new NoteManager();
            return managN;
        }
    
        static void liberer_instance(){if (managN) delete managN;}
        
        unsigned int getNbNotes(){return nbNotes;}
        unsigned int getNbMaxNotes(){return nbMaxNotes;}
        Note* getNote(QString id);
};

#endif // NOTESMANAGER_H_INCLUDED
