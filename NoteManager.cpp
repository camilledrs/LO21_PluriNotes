#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>



void NoteManager::addNote(QString id, QString title, tm crea,tm modif){
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
	notes[nbNotes++]=new Note(id, title, crea, modif);
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

void NoteManager::editerArticle(Note* n, QString tittle, tm modif, const QString& text){
	if (tittle)
		editer(QString tittle, tm modif);
	if (text)
		creerArticle(modif, text);
}

void NoteManager::editerMultimedia(Note* n, QString tittle, tm modif, const QString& desc, const QString& file, Media t){
	if (tittle)
		editer(QString tittle, tm modif);
	if (desc)
		creerMultimedia(modif, desc, file, t);
}

void NoteManager::editerTache(Note* n, QString tittle, tm modif, const QString& a, tm dateFin=0, unsigned int prio=0){
	if (tittle)
		editer(QString tittle, tm modif);
	if (a)
		creerArticle(modif, a, dateFin, prio);
}	
	
	
