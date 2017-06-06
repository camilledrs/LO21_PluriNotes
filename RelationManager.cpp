#include "RelationManager.h"
#include "Relation.h"

//Relation* RelationManager::Reference = new Relation("Reference", "note1 reference note2");
RelationManager* RelationManager::managR = new RelationManager();

void RelationManager::addRelation(Relation& r)
{
    //check si on veut ajouter une relation comme reference
    if(r.getTitre()==Reference->getTitre())
        throw RelationException("error, Reference already exist");
    for(unsigned int i=0; i<nbRelations; i++)
    {
        if (relations[i]->getTitre()==r.getTitre())
            throw RelationException("error, creation of an already existent Relation");
    }
    if (nbRelations==nbMaxRelations)
    {
        Relation** newRelations= new Relation*[nbMaxRelations+5];
        for(unsigned int i=0; i<nbRelations; i++) newRelations[i]=relations[i];
        Relation** oldRelations=relations;
        relations=newRelations;
        nbMaxRelations+=5;
        if (oldRelations) delete[] oldRelations;
    }
    relations[nbRelations++]=new Relation(r);
}


void RelationManager::suppRelation(Relation& r)
{
    if(&r != RelationManager::getInstance().getRef())
    {
        unsigned int i=0;
        while(i<nbRelations && relations[i]->getTitre()!=r.getTitre())
            i++;
        if (i==nbRelations)
            throw RelationException("error, Relation to delete doesn't exist");
        else{
            for(unsigned int k=0; k<r.getnb(); k++)  //on supprime tous les couples de la relation à supprimer
                delete r.tab[k];
            Relation* tmp=relations[i];
            for (unsigned int j=0; j<nbRelations-1; j++)  //on décale les relations dans le tableau pour ne pas laisser de trou
                relations[j]=relations[j+1];
            delete relations[i];  //on supprime l'espace alloué à la relation
        }
    }
    else
        throw RelationException("error, Reference can't be deleted");
}

bool RelationManager::verifNoteRef(const Note* n)  //renvoie true si la note est encore couplée dans une des relations, false sinon (dans ce cas on peut proposer de la supprimer
{
    RelationManager::Iterator it=getIterator();
    while(!it.isDone())  //on parcours l'ensemble des relations
          {
              Relation curr=it.current();
              Relation::const_iterator itr=curr.begin();
              Relation::const_iterator end=curr.end();
              while (itr!=end && const_cast<Couple*>(itr.elementCourant())->getIdNote1()!=const_cast<Note*>(n)->getId() && const_cast<Couple*>(itr.elementCourant())->getIdNote2() != const_cast<Note*>(n)->getId())
                  itr++;
              if (itr!=end) return true; //la note est bien relationnée ailleurs
              it.next();  //sinon on passe à la prochaine relation
          }
    return false;  //on a pas trouvé de couple avec n
}
