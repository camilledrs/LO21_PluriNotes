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
#include <QInputDialog>
#include <QMessageBox>
#include <QTabWidget> //pour les onglet



class WindowRelation : public QTabWidget
{
        Q_OBJECT
        
    QWidget *zoneCentraleRel;
    QDockWidget *zoneGaucheRel;

    QLineEdit *Titre;
    QLineEdit *Desc;
    QPushButton* boutonAfficherRel;
    QPushButton* boutonCreer;
    QPushButton* boutonEditer;
    QPushButton* boutonSupprimer;
    QPushButton* boutonEnrichir;

    QFormLayout *layoutRel;
    QVBoxLayout* layoutPrincipalRel
    QHBox* layoutBouttons;
 
    public:
        explicit WindowRelation(QWidget *parent=MainWindow);
 
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
