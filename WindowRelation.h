#ifndef WINDOWRELATION_H
#define WINDOWRELATION_H

#include <QApplication>
#include "relationmanager.h"
#include "notemanager.h"
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



class WindowRelation : public QMainWindow //public QTabWidget
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

    //QFormLayout *layoutRel;
    QVBoxLayout* layoutPrincipalRel;
    //QHBoxLayout* layoutBouttons;

    public:
        explicit WindowRelation(QWidget *parent = 0);

    public slots:
        void Creer();
        void ajouterCouple(Relation* r);
        void Editer(Relation *r)
        {
            //RelationManager manag = getInstance();
            RelationManager::getInstance().editerRelation(r);
        }
        void Supprimer(Relation* r)
        {
            //RelationManager manag = getInstance();
            RelationManager::getInstance().suppRelation(*r);
        }
        void seeRelation(Relation* r)
        {
            //RelationManager manag = getInstance();
            RelationManager::Iterator it= RelationManager::getInstance().getIterator();
            while(!it.isDone() && (it.current().getTitre() != r->getTitre()))
                it.next();
            it.current().SeeRelation();
        }


    private:
        //(...)


};


#endif
