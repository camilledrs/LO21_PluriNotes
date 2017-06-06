#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include "NoteManager.h"


NoteManager* NoteManager::managN=0;

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
	notes[nbNotes]->verifRef(title);
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
	Relation* reference=RelationManager::getInstance().getRef();
	Relation::const_iterator iterator=reference->begin();
	Relation::const_iterator it_end=reference->end();
	while ((iterator!=it_end) || /*((n.getId() != iterator.courant->getIdNote1) && */(n.getId() != iterator.courant->getIdNote2())//)
		iterator++;
		
	if (iterator!=it_end)
		n.active=false;
	else
		n.supprime=true;
}

void NoteManager::restaurerNote(Note* n)
{
	 if(n->getStatutSupp()==True)
		 n->supprime=False;
	if (n->getActive()==False)
		n->active=True;
}
	       
	       
void NoteManager::viderCorbeille(){
	NoteManager::Iterator it=getIterator();
	while(!it.isDone()){ //parcours les notes
		if(it.currentN->supprime)
		{
			RelationManager::Iterator itR=getIterator();  //parcours les relations
			while(!itR.isDone())  //on parcours l'ensemble des relations
	      {
		      Relation* curr=itR.currentR;
		      Relation::const_iterator itrela=begin();  //parcours les couples de la relation
		      Relation::const_iterator end=end();
		      while (itrela!=end)
		      {
			      if (itrela.courant->note1==it.currentN || itrela.courant->note2 == it.currentN)  //on doit supprimer le couple
			      {
				      Couple* tmp= itrela.courant;  
			      	      itrela++;
			      	      delete tmp;
			      }
			      else itrela++;  //on passe au couple suivant
		      		
		      }
		      itR++;  //sinon on passe à la prochaine relation
	      }
		}	
		it++; //on passe à la note suivante
	}
}
	       

	       
	      

Note* NoteManager::getNote(QString id){
	unsigned int i=0;
	while(i<nbNotes && notes[i]->getId()!=id)
		i++;
	if (i<nbNotes)
		return notes[i];
	else
		throw NoteException("error, search of an inexistent note");
}

void NoteManager::editer(Note* n, QString title, tm modif, const Version& v){
	n->editer(title, modif, v);
	n->verifRef(title);
}	       

