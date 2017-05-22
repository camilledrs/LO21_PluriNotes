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
	if(!*this.getOrient()) //relation pas orientee, faire 2 couples
	{
		int l2= std::cin<<"quel nouveau label pour le couple miroir ?\n";
		for(unsigned int i=0; i<nb; i++){
		if (tab[i]->getLabel()==l2) throw NoteException("error, creation of an already existent note");
		}
		if (nb==max){
			Couple** newtab= new Couple*[max+5];
			for(unsigned int i=0; i<nb; i++) newtab[i]=couple[i];
			Couple** old=couple;
			couple=newtab;
			max+=5;
			if (old) delete[] old;
		}
		couple[nb++]= new Couple(n2, n1, l2);
	}
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
}


void Relation::suppCouple(const Couple& c)
{
	unsigned int i=0;
	while(i<nb && tab[i]->getLabel()!=c.getLabel())
		i++;
	if (i==nb) throw NoteException("error, the item doesn't exist");

	else 
	{
		//Note* note1=c.getNote1();
		//Note* note2=c.getNote2();
		/*if(c.getOrient() == false) //besoin de supprimer aussi la relation "miroir" (y,x)
		{
			unsigned int j=0;
			while(j<nb && ((tab[j]->getIdNote1() != note2->getId()) || (tab[j]->getIdNote2()!= note1->getId())))
				j++;
			if (j==nb) throw NoteException("error, the mirror item doesn't exist\n");
			int inij=j;
			else  //on supprime le couple miroir (y,x)
			{
				delete tab[j];
				while(j<nb-1) 
				{
					tab[j]=tab[j+1];
					j++;
				}
				tab[nb-1]=NULL; //on a décalé, on met l'ancien dernier à NULL vu qu'on diminue la taille du tableau
				nb--;
				if (i>inij)  //on a décalé du coup, et le i initial doit être décrémenté de 1 si on veut accéder au bon couple
				{
					i--;
				}
			}
		}*/
		//maitenant on supprime le couple (x,y)
		delete tab[i];
		while(i<nb-1) 
		{
			tab[i]=tab[i+1];
			i++;
		}
		tab[nb-1]=NULL; //on a décalé, on met l'ancien dernier à NULL vu qu'on diminue la taille du tableau
		nb--;
		//if (note1->getActive() == False){
		//	if(!RelationManager::verifNoteRef(note1)) //la note n'est plus en couple nulle part
		//	{
		//		int reponse=QMessageBox::question(???,"Supprimer de note", "La note " note1->getId() " est archivée et n'est plus référencée, voulez-vous  la supprimer ?");
		//		if(reponse == QMessageBox::Yes)
		//			delete note1;
		//			//appel à la fonction de suppression de la note
		// 		// fait apparaitre une fenêtre de dialogue avec l’utilisateur
		//	}
		//}
		//if (note2->getActive() == false){
		//	if(!RelationManager::verifNoteRef(note2)) //la note n'est plus en couple nulle part
		//	{
		//		int reponse=QMessageBox::question(???,"Supprimer de note", "La note " note2->getId() " est archivée et n'est plus référencée, voulez-vous  la supprimer ?");
		//		if(reponse == QMessageBox::Yes)
		//			delete note2;
		//			//appel à la fonction de suppression de la note
		// 		// fait apparaitre une fenêtre de dialogue avec l’utilisateur
		//	}
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
