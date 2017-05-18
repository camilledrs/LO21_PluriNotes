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
