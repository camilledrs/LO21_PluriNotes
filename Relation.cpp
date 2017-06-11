#include "relation.h"
#include <ctime>
#include <QString>
#include "Relation.h"
#include "Couple.h"
#include "NoteManager.h"
#include <iostream>
#include <QMessageBox>


Relation::Relation(Relation& r):tab(new Couple*[r.max]),nb(r.nb), max(r.max), titre(r.titre), description(r.description), orientee(r.orientee)
{
    for(unsigned int i=0; i<nb; i++) tab[i]=r.tab[i];
}


Relation& Relation::operator=(Relation& r)
{
    if(this!=&r)
    {
        nb=r.nb;
        max=r.max;
        titre=r.titre;
        description=r.description;
        orientee=r.orientee;
        Couple** newtab=new Couple*[max];
        for(unsigned int i=0; i<nb; i++) newtab[i]=r.tab[i];
        delete[] tab;
        tab=newtab;
    }
    return *this;
}



void Relation::addCouple(Note &n1, Note &n2, int l)  //verifier ici qu'on veut la dernière version ?
{
    if(!this->getOrient()) //relation pas orientee, faire 2 couples
    {
        int l2;
        std::cout<<"quel nouveau label pour le couple miroir ?\n";
        std::cin>>l2;
        for(unsigned int i=0; i<nb; i++)
            if (tab[i]->getLabel()==l2) throw NoteException("error, creation of an already existent note");
        if (nb==max)
        {
            Couple** newtab= new Couple*[max+5];
            for(unsigned int i=0; i<nb; i++) newtab[i]=this->tab[i];
            Couple** old=this->tab;
            this->tab=newtab;
            max+=5;
            if (old) delete[] old;
        }
        tab[nb++]= new Couple(n2, n1, l2);
    }
    for(unsigned int i=0; i<nb; i++)
        if (tab[i]->getLabel()==l) throw NoteException("error, creation of an already existent note");
    if (nb==max)
    {
        Couple** newtab= new Couple*[max+5];
        for(unsigned int i=0; i<nb; i++) newtab[i]=tab[i];
        Couple** old=tab;
        tab=newtab;
        max+=5;
        if (old) delete[] old;
    }
    //couple[nb++]=c;//attention c'est une compo
    tab[nb++]= new Couple(n1, n2, l);
    if (this->getOrient()==false)
        tab[nb++]= new Couple(n2, n1, l);
}


void Relation::suppCouple(Couple& c)
{
    unsigned int i=0;
    while(i<nb && tab[i]->getLabel()!=c.getLabel())
        i++;
    if (i==nb)
        throw NoteException("error, the item doesn't exist");
    else
    {
        Note* note1=c.getNote1();
        Note* note2=c.getNote2();
        if(this->getOrient() == false) //besoin de supprimer aussi la relation "miroir" (y,x)
        {
            unsigned int j=0;
            while(j<nb && ((tab[j]->getIdNote1() != note2->getId()) || (tab[j]->getIdNote2()!= note1->getId())))
                j++;
            int inij=j;
            if (j==nb)
                throw NoteException("error, the mirror item doesn't exist\n");
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
        }
        //maitenant on supprime le couple (x,y)
        delete tab[i];
        while(i<nb-1)
        {
            tab[i]=tab[i+1];
            i++;
        }
        tab[nb-1]=NULL; //on a décalé, on met l'ancien dernier à NULL vu qu'on diminue la taille du tableau
        nb--;

        if (note1->getActive() == false)
        {
            if(!RelationManager::getInstance().verifNoteRef(note1)) //la note n'est plus en couple nulle part
            {
                QMessageBox::StandardButton reponse;
                reponse=QMessageBox::question(0,"Supprimer de note", "La note est archivée et n'est plus référencée, voulez-vous  la supprimer ?",QMessageBox::Yes|QMessageBox::No);
                if(reponse == QMessageBox::Yes)
                    delete note1;
                // fait apparaitre une fenêtre de dialogue avec l’utilisateur
            }
        }
        if (note2->getActive() == false)
        {
            if(!RelationManager::getInstance().verifNoteRef(note2)) //la note n'est plus en couple nulle part
            {
                QMessageBox::StandardButton reponse;
                reponse=QMessageBox::question(0,"Supprimer de note", "La note note2 est archivée et n'est plus référencée, voulez-vous  la supprimer ?",QMessageBox::Yes|QMessageBox::No);
                if(reponse == QMessageBox::Yes)
                    delete note2;
                // fait apparaitre une fenêtre de dialogue avec l’utilisateur
            }
        }
    }
}



void Relation::SeeRelation()
{
    std::cout<<"titre = "<<titre.toStdString().c_str()<<"\n"<<"description = "<<description.toStdString().c_str()<<"\n"<<"orientation = "<<orientee<<"\n";
    Relation::const_iterator it=begin();
    Relation::const_iterator it_end=end();
    if(it!=it_end)
    {
        do
        {
            std::cout<<"label : "<<const_cast<Couple*>(it.elementCourant())->getLabel()<<"\n"<<"note1 : "<<const_cast<Couple*>(it.elementCourant())->getIdNote1().toStdString().c_str()<<"\n"<<"note 2 : "<<const_cast<Couple*>(it.elementCourant())->getIdNote2().toStdString().c_str()<<"\n";
            it++;
        } while(it!=it_end);
    }
}

void Relation::editer(QString& t, QString& d)
{
    setTitre(t);
    setDesc(d);
}
/*void Relation::editer()
{
    unsigned int rep;
    std::string titre, desc;
    std::cout<<"changer titre ? 1 pour oui\n";
    std::cin>>rep;
    if (rep==1)
    {
        std::cout<<"donner le titre voulu\n";
        std::cin>>titre;
        setTitre(QString::fromStdString(titre));
    }
    std::cout<<"changer la description\n";
    std::cin>>rep;
    if(rep==1)
    {
        std::cout<<"donner la nouvelle description \n";
        std::cin>>desc;
        setDesc(QString::fromStdString(desc));
    }
}*/

void Relation::save(QFile *f) const{
    XmlStreamWriter stream(f);
    stream.writeTextElement("titre",titre );
    stream.writeTextElement("description",description );
    stream.writeTextElement("orientee",QString::number(orientee) );
    stream.writeTextElement("nbCouple",nb );
    stream.writeTextElement("nbMaxCouple",max);
    for(unsigned int j=0; j<nb); j++){
        tab[j]->save(&newfile);
    }
};
