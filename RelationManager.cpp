#include "RelationManager.h"
#include "Relation.h"

//Relation* RelationManager::Reference = new Relation("Reference", "note1 reference note2");
RelationManager* RelationManager::managR = new RelationManager();

void RelationManager::addRelation(QString& t, QString& d, bool orient)
{
    //check si on veut ajouter une relation comme reference

    if(t==RelationManager::getInstance().getRef()->getTitre())
        throw RelationException("error, Reference already exist");
    for(unsigned int i=1; i<nbRelations; i++)
    {
        if (relations[i]->getTitre()==t)
            throw RelationException("error, creation of an already existent Relation");
    }
    if (nbRelations==nbMaxRelations)
    {
        Relation** newRelations= new Relation*[nbMaxRelations+5];
        for(unsigned int i=0; i<nbRelations; i++) newRelations[i]=relations[i];
        Relation** oldRelations=relations;
        relations=newRelations;
        nbMaxRelations+=5;
        if (oldRelations) delete[] oldRelations;
    }
    relations[nbRelations++]=new Relation(t, d, orient);
}


void RelationManager::suppRelation(Relation& r)
{
    if(&r != RelationManager::getInstance().getRef())
    {
        unsigned int i=0;
        while(i<nbRelations && relations[i]->getTitre()!=r.getTitre())
            i++;
        if (i==nbRelations)
            throw RelationException("error, Relation to delete doesn't exist");
        else{
            for(unsigned int k=0; k<r.getnb(); k++)  //on supprime tous les couples de la relation à supprimer
                delete r.tab[k];
            Relation* tmp=relations[i];
            for (unsigned int j=0; j<nbRelations-1; j++)  //on décale les relations dans le tableau pour ne pas laisser de trou
                relations[j]=relations[j+1];
            delete relations[i];  //on supprime l'espace alloué à la relation
        }
    }
    else
        throw RelationException("error, Reference can't be deleted");
}

bool RelationManager::verifNoteRef(const Note* n)  //renvoie true si la note est encore couplée dans une des relations, false sinon (dans ce cas on peut proposer de la supprimer
{
    RelationManager::Iterator it=getIterator();
    while(!it.isDone())  //on parcours l'ensemble des relations
          {
              Relation curr=it.current();
              Relation::const_iterator itr=curr.begin();
              Relation::const_iterator end=curr.end();
              while (itr!=end && const_cast<Couple*>(itr.elementCourant())->getIdNote1()!=const_cast<Note*>(n)->getId() && const_cast<Couple*>(itr.elementCourant())->getIdNote2() != const_cast<Note*>(n)->getId())
                  itr++;
              if (itr!=end) return true; //la note est bien relationnée ailleurs
              it.next();  //sinon on passe à la prochaine relation
          }
    return false;  //on a pas trouvé de couple avec n
}

void RelationManager::save() const {
    QFile newfile("relations.xml");
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw RelationException(QString("erreur sauvegarde relation : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("relations");
    for(unsigned int i=0; i<nbRelations; i++){
        stream.writeStartElement("relation");
        relations[i]->save(&newfile);
     stream.writeEndElement();
    }
        stream.writeStartElement("refrence");
        RelationManager::getInstance().getRef()->save(&newfile);
        stream.writeEndElement();

    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

/*
void RelationManager::load() {
    QFile fin("relations.xml");
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
            if(xml.name() == "relations") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "relation") {
                qDebug()<<"new relation\n";
                QString titre;
                QString description;
                bool orientee;
                unsigned int nbc;
                unisgned int nbcmax;
                Couple** c;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "relation")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found description.
                        if(xml.name() == "description") {
                            xml.readNext(); description=xml.text().toString();
                            qDebug()<<"descritpion="<<description<<"\n";
                        }
                        // We've found orientee
                        if(xml.name() == "orientee") {
                            xml.readNext();
                            orientee=(xml.text().toString()).toInt();
                            qDebug()<<"orientee="<<orientee<<"\n";

                        // We've found nbCouple
                        if(xml.name() == "nbCouple") {
                            xml.readNext();
                            nbc=(xml.text().toString()).toInt();
                            qDebug()<<"nb="<<nbc<<"\n";
                        }
                        // We've found nbMaxVersion
                        if(xml.name() == "nbMaxCouple") {
                            xml.readNext();
                            nbcmax=(xml.text().toString()).toInt();
                            qDebug()<<"max="<<nbcmax<<"\n";
                        }
                        /*
                         while(!(xml.tokenType() == QXmlStreamReader::EndElement && (xml.name() == "article"||xml.name() == "tache"||xml.name() == "multimedia"))) {
                         if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found dateversion
                        if(xml.name() == "date version") {
                            xml.readNext();
                            dateMod.fromString(xml.text().toString());
                            qDebug()<<"dateModif="<<dateMod<<"\n";
                        }
                         }
                         }
                        // We've found versions
                        if(xml.name() == "nb max version") {
                            xml.readNext();
                            nbMV=xml.text().toString();
                            qDebug()<<"nbMaxVersion="<<nbMV<<"\n";
                        }
                        // A COMPLETER POUR REMPLIR VERSION
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
