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
		Note** oldNotes=note;
		note=newNotes;
		nbMaxNotes+=5;
		if (oldNotes) delete[] oldNotes;
	}
	note[nbNotes++]=n;
}
