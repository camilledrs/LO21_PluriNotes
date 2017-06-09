#ifndef WINDOWRELATION_H
#define WINDOWRELATION_H

#include <QApplication>
#include "relationmanager.h"
#include "notemanager.h"
#include <QMainWindow>
#include <QListWidgetItem>
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
    QListWidget *RelationList;

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

        void ajouterCouple();
        /*void Editer(QListWidgetItem* i)
        {
            //RelationManager manag = getInstance();
            RelationManager::getInstance().editerRelation(r);
        }*/
        void Supprimer();

        void seeRelation(QListWidgetItem* i);

        void Editer();



    private:
        //(...)


};


#endif
