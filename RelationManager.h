#ifndef RELATIONMANAGER_H_INCLUDED
#define RELATIONMANAGER_H_INCLUDED
#include <ctime>
#include <QString>


class RelationManager
{
    Relation** relations;
    static Relation* Reference;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;
    void addRelation(Relation* r);
    
    
    RelationManager():nbRelations(1),nbMaxRelations(5),relations(new Relation*[5]){}
    ~RelationManager(){
for(unsigned int i=0; i<nbRelations; i++) delete relations[i]; // composition uniquement
delete[] relations; // composition + agrégation
    }
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
            return Iterator(relations,nbRelations);//0
        }
};

#endif // RELATIONMANAGER_H_INCLUDED
