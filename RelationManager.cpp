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
		Relation** oldRelations=relation;
		relation=newRelations;
		nbMaxRelations+=5;
		if (oldRelations) delete[] oldRelations;
	}
	relation[nbRelations++]=r;
}
