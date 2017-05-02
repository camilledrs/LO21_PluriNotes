#include "Notes.h"
#include "NoteManager.h"
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
		Note** oldNotes=notes;
		notes=newNotes;
		nbMaxNotes+=5;
		if (oldNotes) delete[] oldNotes;
	}
	notes[nbNotes++]=n;
}

NoteManager::NoteManager(const NoteManager& m):notes(new Note[m.nbNotes]),nbNotes(m.nbNotes), nbMaxNotes(m .nbMaxNotes){
for(unsigned int i=0; i<nbNotes; i++) {
notes[i]=new Note(*m.notes[i]); // si composition
//notes[i]=m.notes[i]; // si agrégation }
}


NoteManager::NoteManager& operator=(const NoteManager& m){
	if (this != &m)
	{
		nbNotes=m.nbNotes;
		nbMaxNotes=m.nbMaxNotes;
		newtab= new Note[nbMaxNotes];
		for(unisgned int i=0; i<nb; i++) newtab[i]=m.notes[i];
		delete[] notes;
		notes=newtab;
	}
	return *this;
}
