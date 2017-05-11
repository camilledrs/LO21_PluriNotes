#include <ctime>
#include <QString>
#include "Relation.h"


Relation::Relation(Relation& r):tab(new *Couple[r.max]),nb(r.nb), max(r.max), titre(r.titre), description(r.description), orientee(r.orientee){
  for(unsigned int i=0; i<nb; i++) tab[i]=r.tab[i];
  }
  

Relation::Relation& Relation::operator=(const Relation& r){
  if(this!=&r)
  {
      nb=r.nb;
      max=r.max;
      titre=r.titre;
      description=r.description;
      orientee=r.orientee;
      newtab=new Couple*[max];
      for(unsigned int i=0; i<nb; i++) newtab[i]=r.tab[i];
      delete[] tab;
      tab=newtab;
   }
   return *this;
}
      


void Relation::addCouple(const Couple& c){
	for(unsigned int i=0; i<nb; i++){
		if (tab[i]->getLabel()==c.getLabel()) throw NoteException("error, creation of an already existent note");
	}
	if (nb==max){
		Couple** newtab= new Couple*[max+5];
		for(unsigned int i=0; i<nb; i++) newtab[i]=couple[i];
		Couple** old=couple;
		couple=newtab;
		max+=5;
		if (old) delete[] old;
	}
	//couple[nb++]=c;//attention c'est une compo
	couple[nb++]= new Couple(c);
}




void Relation::seeRelation(){
	std::cout<<"titre = "<<titre<<"\n"<<"description = "<<description<<"\n"<<"orientation = "<<orientee<<"\n";
	Relation::const_iterator it=begin();
	Relation::const_iterator end=end();
	if(it!=end){
	do
	{
		cout<<"label : "<<it.courant->getLabel()<<"\n"<<"note1 : "<<it.courant->getIdNote1()<<"\n"<<"note 2 : "<<it.courant->getIdNote2<<"\n";);
		it++;
	} while(it!=end);
	}
}
