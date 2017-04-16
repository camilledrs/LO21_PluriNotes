#include "LO21.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>



void NoteManager::addNote(Note* n){
	for(unsigned int i=0; i<nbNotes; i++){
		if (notes[i]->getId()==n->getId()) throw NoteException("error, creation of an already existent note");
	}
	if (nbNotes==nbMaxNotes){
		Note** newNotes= new Note*[nbMaxNotes+5];
		for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
		Note** oldNotes=note;
		note=newNotes;
		nbMaxNotes+=5;
		if (oldNotes) delete[] oldNotes;
	}
	note[nbNotes++]=n;
}


void RelationManager::addRelation(Relation* r){
	for(unsigned int i=0; i<nbRelations; i++){
		if (relations[i]->getId()==r->getId()) throw NoteException("error, creation of an already existent note");
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
