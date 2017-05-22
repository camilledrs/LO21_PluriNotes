#include <ctime>
#include <QString>
#include "Relation.h"
#include "Couple.h"
#include "NoteManager.h"


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
      


void Relation::addCouple(const Note& n1, const Note& n2, int l){  //verifier ici qu'on veut la dernière version ?
	for(unsigned int i=0; i<nb; i++){
		if (tab[i]->getLabel()==l) throw NoteException("error, creation of an already existent note");
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
	couple[nb++]= new Couple(n1, n2, l);
	if (this.orientee==false)
		couple[nb++]= new Couple(n2, n1, l);
}


void Relation::suppCouple(const Couple& c)
{
	unsigned int i=0;
	while(i<nb && tab->getLabel()!=c.getLabel())
		i++;
	if (i==nb) throw NoteException("error, the item doesn't exist");
	else 
	{
		Note* note1=c.getNote1;
		Note* note2=c.getNote2;
		delete tab[i];
		while(i<nb-1) tab[i]=tab[i+1];
		tab[nb-1]=NULL; //on a décalé, on met l'ancien dernier à NULL vu qu'on diminue la taille du tableau
		nb--;
		//if (note1.getActive == 0){
		//	const_iterator iterator=begin();
		//	while (iterator*!=end() && (iterator*->getNote1->getId() !=note1->getId() || iterator*->getNote2->getId() !=note1->getId()))
		//		iterator++;
		//	if (iterator*== end() && (iterator*->getNote1->getId() !=note1->getId() && iterator*->getNote2->getId() !=note1->getId()))
		//		int reponse=QMessageBox::question(???,"Supprimer de note", "La note " note1->getId() " est archivée et n'est plus référencée, voulez-vous  la supprimer ?");
		//		if(reponse == QMessageBox::Yes)
		//			delete note1;
		//			//appel à la fonction de suppression de la note
		// 		// fait apparaitre une fenêtre de dialogue avec l’utilisateur
		//}
		//if (note2->getActive == 0){
		//	const_iterator iterator=begin();
		//	while (iterator*!=end() && (iterator*->getNote1->getId() !=note2->getId() || iterator*->getNote2->getId() !=note2->getId()))
		//		iterator++;
		//	if (iterator*== end() && (iterator*->getNote1->getId() !=note2->getId() && iterator*->getNote2->getId() !=note2->getId()))
		//		int reponse=QMessageBox::question(???,"Supprimer de note", "La note " note2->getId() " est archivée et n'est plus référencée, voulez-vous  la supprimer ?");
		//		if(reponse == QMessageBox::Yes)
		//			delete note2;
		//			//appel à la fonction de suppression de la note
		// 		// fait apparaitre une fenêtre de dialogue avec l’utilisateur
		//}
}


void Relation::seeRelation(){
	std::cout<<"titre = "<<titre<<"\n"<<"description = "<<description<<"\n"<<"orientation = "<<orientee<<"\n";
	Relation::const_iterator it=begin();
	Relation::const_iterator end=end();
	if(it!=end){
	do
	{
		cout<<"label : "<<it.courant->getLabel()<<"\n"<<"note1 : "<<it.courant->getIdNote1()<<"\n"<<"note 2 : "<<it.courant->getIdNote2()<<"\n";);
		it++;
	} while(it!=end);
	}
}
	
	
	
void Relation::editer(){
	unsigned int rep;
	QString titre, desc;
	cout<<"changer titre ? 1 pour oui\n";
	cin<<rep;
	if (rep==1)
	{
		cout<<"donner le titre voulu\n";
		cin<<titre;
		setTitre(titre);
	}
	cout<<"changer la description\n";
	cin<<rep;
	if(rep==1)
	{
		cout<<"donner la nouvelle description \n";
		cin<<desc;
		setDesc(desc);
	}
}
