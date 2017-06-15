#ifndef COUPLE_H
#define COUPLE_H

#include <ctime>
#include <QString>
#include <QtXml>
#include <QFile>
#include "note.h"


/*! Classe Couple*/

//! La classe Couple regroupe deux pointeurs de Note ainsi qu'un label


class Couple //Class car on veut tout en privé
{

    int label; /*< Attribut label entier, unique */
    Note* note1;  /*< Pointeur sur un objet de classe Note, premier élément du couple*/
    Note* note2;  /*< Pointeur sur un objet de classe Note, deuxième élément du couple*/
    Couple(const Couple& n);  //! constructeur par recopie

    public  :
    //! acceseur pour permettre d'obtenir le label
    //! \return le label du Couple
    int getLabel(){return label;}
    //! accesseur pour la note 1
    //! \return un poiteur sur la note 1
    Note* getNote1(){return note1;}
    //! accesseur pour la note 2
    //! \return un poiteur sur la note 2
    Note* getNote2(){return note2;}
    //! acceseur pour permettre d'obtenir l'ID de la note 1
    //! \return le l'ID de la première note du couple
    QString getIdNote1()const {return note1->getId();}
    //! acceseur pour permettre d'obtenir l'ID de la note 2
    //! \return le l'ID de la deuxième note du couple
    QString getIdNote2()const {return note2->getId();}
    //! methode pour modifier le label du couple
    //! \param newl un entier correspondant au nouveau label
    void setLabel(int newl){label=newl;}
    //! Un constructeur avec 3 arguments
    //! \param n1 une référence sur une note, que l'on veut en note 1
    //! \param n2 une reference sur une note que l'on veut en note 2
    //! \param l l'entier correspondant au label voulu
    Couple(Note& n1, Note& n2, int l):label(l), note1(&n1), note2(&n2) {}
   //! un destructeur, qui libère l'espace mémoire alloué aux deux pointeurs de note
    ~Couple(){}
    /**
     * @brief methode save
     * @param l'adresse d'un QFile, fichier ou on va sauvegarder les couples
     */
    void save(QFile* f) const {    QXmlStreamWriter stream(f);
                                   stream.writeStartElement("couple");
                                   stream.writeTextElement("label",QString::number(label));
                                   stream.writeTextElement("id note1",getIdNote1() );
                                   stream.writeTextElement("id note 2",getIdNote2());
                                   stream.writeEndElement();

                              }
};

#endif // COUPLE_H
