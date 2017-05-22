#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>



void NoteManager::addNote(QString id, QString title, tm crea,tm modif,const Version& v)){
	for(unsigned int i=0; i<nbNotes; i++){
		if (notes[i]->getId()==id) throw NoteException("error, creation of an already existent note");
	}
	if (nbNotes==nbMaxNotes){
		Note** newNotes= new Note*[nbMaxNotes+5];
		for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
		Note** oldNotes=notes;
		notes=newNotes;
		nbMaxNotes+=5;
		if (oldNotes) delete[] oldNotes;
	}
	notes[nbNotes++]=new Note(id, title, crea, modif,v);
}

NoteManager::NoteManager(const NoteManager& m):notes(new Note*[m.nbNotes]),nbNotes(m.nbNotes), nbMaxNotes(m .nbMaxNotes){
	for(unsigned int i=0; i<nbNotes; i++) {
		notes[i]=new Note(*m.notes[i]); // si composition
		//notes[i]=m.notes[i]; // si agrégation 
	}
}


NoteManager& NoteManager::operator=(const NoteManager& m){
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
	
void NoteManager::supprimerNote(Note& n){
	Relation& reference=RelationManager::getInstance().getStaticReference();
	Relation::const_iterator iterator=reference.begin();
	Relation::const_iterator it_end=reference.end();
	while ((iterator!=it_end) || ((n.getId() != iterator.courant->getIdNote1) && (n.getId() != iterator.courant->getIdNote2()))
		iterator++;
		
	if (iterator!=it_end)
		n.active=false;
	else
		n.supprime=true;
}

	
void NoteManager::viderCorbeille(){
	NoteManager::Iterator it=getIterator();
	while(!it.isDone()){
		if(it.currentN->supprime)
			supprimerNote(it.currentN);
		it++;
	}
}
	
	
	
	
