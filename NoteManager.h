#ifndef NOTESMANAGER_H_INCLUDED
#define NOTESMANAGER_H_INCLUDED
#include <ctime>
#include <QString>
#include "Notes.h"

class NoteManager
{
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    
    NoteManager();
    ~NoteManager(){
        for(unsigned int i=0; i<nbNotes; i++) delete notes[i]; // composition uniquement
        delete[] notes; // composition + agrégation
    }
    NoteManager(const NoteManager& m);
    NoteManager& operator=(const NoteManager& m);
    void addNote(QString id, QString title, tm crea,tm modif);
    void editerArticle(Note* n, QString tittle, tm modif, const QString& text);
    void editerMultimedia(Note* n, QString tittle, tm modif, const QString& desc, const QString& file, Media t);
    void editerTache(Note* n, QString tittle, tm modif, const QString& a, tm dateFin=0, unsigned int prio=0)
    
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


#endif // NOTESMANAGER_H_INCLUDED
