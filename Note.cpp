#include "notemanager.h"
#include <iostream>



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

void Note::editer(QString title, QDateTime modif, const Version& v)
{
    if (active && !supprime)
    {
        titre=title;
        dateModif= modif;
        if (nbVersion==nbMaxVersion)
        {
            Version ** newVersions= new Version*[nbMaxVersion+5];
            for(unsigned int i=0; i<nbVersion; i++)
                newVersions[i]=versions[i];
            Version** oldVersions=versions;
            versions=newVersions;
            nbMaxVersion+=5;
            delete[] oldVersions;
        }
        versions[nbVersion++]=v.clone();
    }
}

void Note::verifRef( const QString s)
{
    if(s.contains("\ref{"))
    {
        const QChar *data = s.data();
        while(*data!= '\\')
              data++;
        for (unsigned int i=0; i<5; i++)
            data++;
        QString idy;
        while(*data!='}')
        {
            idy.append(*data);
            data++;
        }
        NoteManager::Iterator it=NoteManager::getInstance().getIterator();
        while(it.current().getId()!=idy)
        {
            it.next();
        }
        int l2;
        std::cout<<"quel nouveau label pour la reference ?\n";
        std::cin>>l2;
        for(unsigned int i=0; i<RelationManager::getInstance().getRef()->getnb(); i++)
        {
            if (const_cast<Couple*>(RelationManager::getInstance().getRef()->elem(i).elementCourant())->getLabel()==l2) throw NoteException("error, creation of an already existent label");
        }
        RelationManager::getInstance().getRef()->addCouple(*this,it.current(),l2);
    }
}

Note** Note::sucesseurs( unsigned int* nb)
{
    Note** succ=new Note*[NoteManager::getInstance().getNbNotes()];
    unsigned int i=0;
    RelationManager::Iterator it=RelationManager::getInstance().getIterator();
    while(!it.isDone())  //on parcours l'ensemble des relations
    {
        Relation* curr=(&it.current());
        Relation::const_iterator itr=curr->begin();
        Relation::const_iterator end=curr->end();
        while (itr!=end)
        {
            if(itr.elementCourant()->getIdNote1() == this->getId())
            {
                succ[i]= const_cast<Couple*>(itr.elementCourant())->getNote2();
                i++;
            }
            itr++;
        }
        it.next();  //sinon on passe à la prochaine relation
    }
    *nb=i;
    return succ;
}

Note** Note::predecesseurs( unsigned int* nb)
{
    Note** pred=new Note*[NoteManager::getInstance().getNbNotes()];
    unsigned int i=0;
    RelationManager::Iterator it=RelationManager::getInstance().getIterator();
    while(!it.isDone())  //on parcours l'ensemble des relations
    {
        Relation* curr=(&it.current());
        Relation::const_iterator itr=curr->begin();
        Relation::const_iterator end=curr->end();
        while (itr!=end)
        {
            if(itr.elementCourant()->getIdNote2()==this->getId())
            {
                pred[i]=const_cast<Couple*>(itr.elementCourant())->getNote1();
                i++;
            }
            itr++;
        }
        it.next();  //sinon on passe à la prochaine relation
    }
    *nb=i;
    return pred;
}


