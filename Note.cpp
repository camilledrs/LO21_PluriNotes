#include <ctime>
#include <QString>
#include "Notes.h"

void Note::restaurer(Version* v)
{
    unsigned int i=0;
    while(i<nbVersion && versions[i]!=v) i++;
    Version* tmp=versions[i];
    while(i<nbVersion-1) 
    {
      versions[i]=versions[i+1];
      i++;
    }
    versions[i]=tmp; //on met la version à restaurer au niveau de la dernière case du tableau (versions[nbVersion-1]) 
}

void Note::editer(QString title, tm modif, const Version& v){
	if (active && !supprime){
		titre=title;
		dateModif= modif;
		if (nbVersion==nbMaxVersion){
			Version ** newVersions= new Version*[nbMaxVersions+5];
			for(unsigned int i=0; i<nbVersion; i++)
				newVersions[i]=versions[i];
			Version** oldVersions=versions;
			versions=newVersions;
			nbMaxVerions+=5;
			delete[] oldVersions;
		}
		versions[nbVersion++]=v.clone();
		
	}
}
void Note::verifRef( const Qstring s){
if(s.contains("\ref{")){
		QChar *data = s.data();
		while(*data!= '\\')
		      data++;
		for (unsigned int i=0, i<5, i++) data++;
		Qstring idy;
		      while(*data!='}')
		      {idy.append(*data);
		       data++;
		      }
		NoteManager::Iterator it=getIterator();
	while(it->getId()!=idy){
		it++;
	}
		int l2= std::cin<<"quel nouveau label pour la reférence ?\n";
		for(unsigned int i=0; i<nb; i++){
		if (tab[i]->getLabel()==l2) throw NoteException("error, creation of an already existent label");
		}
		RelationManager::getInstance().getRef().addCouple(*this,*it.currentN,l2);
	}
	
Note** Note::sucesseurs( unsigned int* nb){
Note** succ=new Note*[NoteManager::getInstance().nbNotes];
	unsigned int i=0;
RelationManager::Iterator it=getIterator();
	while(!it.isDone())  //on parcours l'ensemble des relations
	      {
		      Relation* curr=it.currentR;
		      Relation::const_iterator itr=begin();
		      Relation::const_iterator end=end();
		      while (itr!=end)
		      {if(itr->getIdNote1()==this.getId()) 
		      		{succ[i]=itr->getNote2();
				 i++;		   
							   }
			itr++;}
		      it++;  //sinon on passe à la prochaine relation
	      }
*nb=i;
	return succ;
}

Note** Note::predecesseurs( unsigned int* nb){
Note** pred=new Note*[NoteManager::getInstance().nbNotes];
	unsigned int i=0;
RelationManager::Iterator it=getIterator();
	while(!it.isDone())  //on parcours l'ensemble des relations
	      {
		      Relation* curr=it.currentR;
		      Relation::const_iterator itr=begin();
		      Relation::const_iterator end=end();
		      while (itr!=end)
		      {if(itr->getIdNote2()==this.getId()) 
		      		{succ[i]=itr->getNote1();
				 i++;		   
							   }
			itr++;}
		      it++;  //sinon on passe à la prochaine relation
	      }
*nb=i;
	return pred;
}
