#include "RelationManager.h"
#include "Relation.h"

#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>


Relation* RelationManager::Reference = new Relation("Reference", "note1 reference note2");

void RelationManager::addRelation(const Relation& r){
	//check si on veut ajouter une relation comme reference
	if(r->getId()==Reference->getId()) throw RelationException("error, Reference already exist");
	for(unsigned int i=0; i<nbRelations; i++){
		if (relations[i]->getId()==r->getId()) throw RelationException("error, creation of an already existent Relation");
	}
	if (nbRelations==nbMaxRelations){
		Relation** newRelations= new Relation*[nbMaxRelations+5];
		for(unsigned int i=0; i<nbRelations; i++) newRelations[i]=relations[i];
		Relation** oldRelations=relations;
		relations=newRelations;
		nbMaxRelations+=5;
		if (oldRelations) delete[] oldRelations;
	}
	relations[nbRelations++]=new Relation(r);
}


RelationManager::RelationManager(const RelationManager& m):relations(new Relation[m.nbRelations]),nbRelations(m.nbRelations), nbMaxRelations(m .nbMaxRelations){
for(unsigned int i=0; i<nbRelations; i++) {
relations[i]=new Relation(*m.relations[i]); // si composition
//relations[i]=m.relations[i]; // si agrégation }
}


RelationManager::NoteManager& operator=(const RelationManager& m){
	if (this != &m)
	{
		nbRelations=m.nbRelations;
		nbMaxRelations=m.nbMaxRelations;
		newtab= new Note[nbMaxRelations];
		for(unisgned int i=0; i<nb; i++) newtab[i]=m.relations[i];
		delete[] relations;
		relations=newtab;
	}
	return *this;
}

	
void RelationManager::suppRelation(Relation& r){
	if(this != Reference)
	{
		unsigned int i=0;
		while(i<nbRelations && relations[i]->getId()!=r->getId())
			i++;
		if (i==nbRelations) throw RelationException("error, Relation to delete doesn't exist");
		else{
			for(unsigned int k=0; k<r.getnb(); k++)  //on supprime tous les couples de la relation à supprimer
				delete r.tab[k];
			Relation* tmp=relations[i];
			for (unsigned int j=0; j<nbRelations-1; j++)  //on décale les relations dans le tableau pour ne pas laisser de trou
				relations[j]=relations[j+1];
			delete relations[i];  //on supprime l'espace alloué à la relation
		}
	}
	else {
		throw RelationException("error, Reference can't be deleted");
	}

}
	
bool RelationManager::verifNoteRef(const Note* n)  //renvoie true si la note est encore couplée dans une des relations, false sinon (dans ce cas on peut proposer de la supprimer
{
	RelationManager::Iterator it=getIterator();
	while(!it.isDone())  //on parcours l'ensemble des relations
	      {
		      Relation* curr=it.currentR;
		      Relation::const_iterator itr=begin();
		      Relation::const_iterator end=end();
		      while (itr!=end && itr->getIdNote1()!=n->getId() && itr->getIdNote2() != n->getId())
			      itr++;
		      if (itr!=end) return True; //la note est bien relationnée ailleurs
		      it++;  //sinon on passe à la prochaine relation
	      }
	return False;  //on a pas trouvé de couple avec n
}
