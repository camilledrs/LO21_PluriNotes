#include "notemanager.h"

NoteManager* NoteManager::managN = new NoteManager();

void NoteManager::addNote(QString id, QString title, QDateTime crea, QDateTime modif, const Version& v)
{
    for(unsigned int i=0; i<nbNotes; i++)
    {
        if (notes[i]->getId()==id) throw NoteException("error, creation of an already existent note");
    }
    if (nbNotes==nbMaxNotes)
    {
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes++]=new Note(id, title, crea, modif, v);
    notes[nbNotes]->verifRef(title);
}


void NoteManager::addNoteXML(QString id, QString title, QDateTime crea,QDateTime modif,bool act, bool supp, unsigned int nbV, unsigned int nbMV,  Version** v){
    for(unsigned int i=0; i<nbNotes; i++)
    {
        if (notes[i]->getId()==id) throw NoteException("error, creation of an already existent note");
    }
    if (nbNotes==nbMaxNotes)
    {
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes++]=new Note(id, title, crea, modif,act,supp,nbV,nbMV, v);
    //notes[nbNotes]->verifRef(title);
    //la fonction fonctionne mais fait planter l'application à l'affichage
}

NoteManager& NoteManager::operator=(const NoteManager& m)
{
    if (this != &m)
    {
        nbNotes=m.nbNotes;
        nbMaxNotes=m.nbMaxNotes;
        Note** newtab= new Note*[nbMaxNotes];
        for(unsigned int i=0; i<nbNotes; i++)
            newtab[i]=m.notes[i];
        delete[] notes;
        notes=newtab;
    }
    return *this;
}

void NoteManager::supprimerNote(Note& n)
{
    //on ne fait appel ici qu'a des notes actives (dans le sens non archivées ou supprimées)
    Relation* reference=RelationManager::getInstance().getRef();
    if(reference->getnb()!=0)
    {
        Relation::const_iterator it=reference->begin();
        Relation::const_iterator it_end=reference->end();
        while ((it!=it_end) && (n.getId() != (it.elementCourant()->getIdNote2())))
            it++;
        if (it!=it_end)  //note dans la relation reference
            n.ChangeActive();
        else
        {
            Relation::iterator it=reference->ibegin();
            Relation::iterator it_end=reference->iend();
            for(it;it!=it_end;it++)
                if (n.getId() == it.elementCourant()->getIdNote1())  //note fait référence à une note
                    reference->suppCouple(*it.elementCourant());
            RelationManager::Iterator itRelationManager = RelationManager::getInstance().getIterator();
            for(itRelationManager;!itRelationManager.isDone();itRelationManager.next())
            {
                Relation::iterator itRelation=reference->ibegin();
                Relation::iterator itRelation_end=reference->iend();
                for(itRelation;itRelation!=itRelation_end;itRelation++)
                {
                    if (n.getId() == itRelation.elementCourant()->getIdNote1())  //note à une relation avec une autre note
                        itRelationManager.current().suppCouple(*itRelation.elementCourant());
                    if (n.getId() == itRelation.elementCourant()->getIdNote2())  //note à une relation avec une note
                        itRelationManager.current().suppCouple(*it.elementCourant());
                }
            }
            n.changeSupp();
        }
    }
    else
    {
        Relation::iterator it=reference->ibegin();
        Relation::iterator it_end=reference->iend();
        for(it;it!=it_end;it++)
            if (n.getId() == it.elementCourant()->getIdNote1())  //note fait référence à une note
                reference->suppCouple(*it.elementCourant());
        RelationManager::Iterator itRelationManager = RelationManager::getInstance().getIterator();
        for(itRelationManager;!itRelationManager.isDone();itRelationManager.next())
        {
            Relation::iterator itRelation=reference->ibegin();
            Relation::iterator itRelation_end=reference->iend();
            for(itRelation;itRelation!=itRelation_end;itRelation++)
            {
                if (n.getId() == itRelation.elementCourant()->getIdNote1())  //note à une relation avec une autre note
                    itRelationManager.current().suppCouple(*itRelation.elementCourant());
                if (n.getId() == itRelation.elementCourant()->getIdNote2())  //note à une relation avec une note
                    itRelationManager.current().suppCouple(*it.elementCourant());
            }
        }
        n.changeSupp();
    }

}


void NoteManager::viderCorbeille()
{
   NoteManager::Iterator it=getIterator();
   while(!it.isDone()) //parcours les notes
   {
       if(it.current().supprime)
       {
           RelationManager::Iterator itR=RelationManager::getInstance().getIterator();  //parcours les relations
           while(!itR.isDone())  //on parcours l'ensemble des relations
         {
             Relation::const_iterator itrela=itR.current().begin();  //parcours les couples de la relation
             Relation::const_iterator end=itR.current().end();
             while (itrela!=end)
             {
                 if (const_cast<Couple*>(itrela.elementCourant())->getIdNote1()==it.current().getId() || const_cast<Couple*>(itrela.elementCourant())->getIdNote2() == it.current().getId())  //on doit supprimer le couple
                 {
                     const Couple* tmp= itrela.elementCourant();
                     itrela++;
                     delete tmp;
                 }
                 else
                     itrela++;  //on passe au couple suivant
             }
             itR.next();  //sinon on passe à la prochaine relation
         }
       }
       it.next(); //on passe à la note suivante
   }
}

Note* NoteManager::getNote(QString id)
{
   unsigned int i=0;
   while(i<nbNotes && notes[i]->getId()!=id)
       i++;
   if (i<nbNotes)
       return notes[i];
   else
       throw NoteException("error, search of an inexistent note");
}

void NoteManager::editer(Note* n, QString title, QDateTime modif, const Version& v)
{
   n->editer(title, modif, v);
   n->verifRef(title);
}


void NoteManager::save() const
{
    QFile newfile("notes.xml");
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    for(unsigned int i=0; i<nbNotes; i++)
    {
        stream.writeStartElement("note");
        stream.writeTextElement("id",notes[i]->getId());
        stream.writeTextElement("title",notes[i]->getTitre());
        stream.writeTextElement("date crea",notes[i]->getDate().toString());
        stream.writeTextElement("date modif",notes[i]->getDateModif().toString());
        stream.writeTextElement("active",QString::number(notes[i]->getActive()));
        stream.writeTextElement("supprime",QString::number(notes[i]->getStatutSupp()));
        stream.writeTextElement("nb version",QString::number(notes[i]->getNbVersion()));
        stream.writeTextElement("nb max version",QString::number(notes[i]->getNbMaxVersion()));
        for(unsigned int j=0; j<notes[i]->getNbVersion(); j++)
        {
            notes[i]->versions[j]->save(&newfile);
             stream.writeEndElement();
        }
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

/*
void NoteManager::load() {
    QFile fin("notes.xml");
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "notes") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "note") {
                qDebug()<<"new note\n";
                QString identificateur;
                QString titre;
                QDateTime dateC;
                QDateTime dateMod;
                bool act;
                bool supp;
                Version** v= new  Version*[1];
                unsigned int nbV;
                unsigned int nbMV;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "note")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }
                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found datecrea
                        if(xml.name() == "date crea") {
                            xml.readNext();
                            dateC.fromString(xml.text().toString());
                            qDebug()<<"dateCrea="<<dateC<<"\n";
                        }
                        // We've found datemodif
                        if(xml.name() == "date modif") {
                            xml.readNext();
                            dateMod.fromString(xml.text().toString());
                            qDebug()<<"dateModif="<<dateMod<<"\n";
                        }
                        // We've found active
                        if(xml.name() == "active") {
                            xml.readNext();
                            act=(xml.text().toString()).toInt();
                            qDebug()<<"active="<<act<<"\n";
                        }
                        // We've found supprime
                        if(xml.name() == "supprime") {
                            xml.readNext();
                            supp=(xml.text().toString()).toInt();
                            qDebug()<<"supprime="<<supp<<"\n";
                        }
                        // We've found nbVersion
                        if(xml.name() == "nb version") {
                            xml.readNext();
                            nbV=(xml.text().toString()).toInt();
                            qDebug()<<"nbVersion="<<nbV<<"\n";
                        }
                        // We've found nbMaxVersion
                        if(xml.name() == "nb max version") {
                            xml.readNext();
                            nbMV=(xml.text().toString()).toInt();
                            qDebug()<<"nbMaxVersion="<<nbMV<<"\n";
                        }
                         if(xml.name() == "article") {
                             qDebug()<<"new article\n";
                             QDateTime dateV;
                             QString texte;
                             QXmlStreamAttributes attributesV = xml.attributes();
                             xml.readNext();
                             while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
                             if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                // We've found dateversion
                            if(xml.name() == "date version") {
                                xml.readNext();
                                dateV.fromString(xml.text().toString());
                                qDebug()<<"date="<<dateV<<"\n";
                        }
                        // We've found texte article
                        if(xml.name() == "texte") {
                            xml.readNext();
                            texte=xml.text().toString();
                            qDebug()<<"texte="<<texte<<"\n";
                        }
                         }
                             xml.readNext();
                         }
                             qDebug()<<"ajout version "<<dateV<<"\n";
                             editer()
                         }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                addNoteXML(identificateur,titre,dateC,dateMod,act,supp,nbV,nbMV,v);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}
*/
