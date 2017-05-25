#ifndef WINDOWRELATION_H
#define WINDOWRELATION_H

#include <QApplication>
#include "Relation.h"
#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QDockWidget>
#include <QTabWidget> //pour les onglet



class WindowRelation : public QTabWidget
{
        Q_OBJECT
 
    public:
        WindowRelation(QWidget *parent);
 
    public slots:
        void Creer();
        void ajouterCouple();
        void Editer(){Relation::Editer();}
        void Supprimer(){Relation::~Relation();}
        void seeRelation(){Relation::seeRelation();}
    
 
    private:
        //(...)
 
 
};


#endif
