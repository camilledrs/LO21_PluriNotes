#include "RelationManager.h"
#include "Relation.h"

#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>


void RelationManager::addRelation(Relation* r){
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
	relations[nbRelations++]=r;
}


RelationManager::RelationManager(const RelationManager& m):relations(new Relation[m.nbRelations]),nbRelations(m.nbRelations), nbMaxRelations(m .nbMaxRelations){
for(unsigned int i=0; i<nbRelations; i++) {
relations[i]=new Relation(*m.relations[i]); // si composition
//relations[i]=m.relations[i]; // si agrégation }
}
