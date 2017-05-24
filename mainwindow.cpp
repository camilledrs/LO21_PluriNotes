#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget* zoneCentrale = new QWidget;
    QDockWidget* zoneGauche = new QDockWidget;
    zoneGauche->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //zoneGauche->setWidget();
    addDockWidget(Qt::LeftDockWidgetArea, zoneGauche);

    QDockWidget* zoneDroite = new QDockWidget;
    zoneDroite->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //zoneDroite->setWidget();
    addDockWidget(Qt::RightDockWidgetArea, zoneDroite);

    QLineEdit* idNote = new QLineEdit;
    QPushButton* boutonAfficher = new QPushButton("Afficher une note");


    QFormLayout* layout = new QFormLayout;
    layout->addRow("Id", idNote);

    
    QVBoxLayout* layoutRecherche = new QVBoxLayout;
    layoutRecherche->addLayout(layout);
    layoutRecherche->addWidget(boutonAfficher);

    QObject::connect(boutonAfficher,SIGNAL(clicked()),this,SLOT(Recherche()));

    QVBoxLayout* layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(layoutRecherche);


    //layoutGauche = new QHBoxLayout;


    zoneCentrale->setLayout(layoutPrincipal);

    setCentralWidget(zoneCentrale);
}


/*
    
    QWidget* Relation = new QWidget;
    QWidget* zoneCentraleRel = new QWidget(&Relation);
    QDockWidget* zoneGauche = new QDockWidget;
    
    QLineEdit* Titre = new QLineEdit;
    QLineEdit* Desc = new QLineEdit;
    
    QFormLayout* layoutRel = new QFormLayout;
    layoutRel->addRow("Titre :", Titre);
    layoutRel->addRow("Description :", Desc);
    QPushButton* boutonAfficherRel = new QPushButton("Afficher une Relation");
    QObject::connect(boutonAfficherRel,SIGNAL(clicked()),this,SLOT(Relation::SeeRelation()));
    layoutRel->addWidget(boutonAfficherRel);
    
    
    QPushButton* boutonCreer = new QPushButton("Creer une note");
    QPushButton* boutonEditer = new QPushButton("Editer une note");
    QPushButton* boutonSupprimer = new QPushButton("Supprimer une note");
    QPushButton* boutonEnrichir = new QPushButton("Enrichir une note");
    QHBox* layoutBouttons= new QHBoxLayout;
    layoutBouttons->addWidget(boutonCreer);
    QObject::connect(boutonCreer,SIGNAL(clicked()),this,SLOT(Relation::Relation(.....))); //mettre des parametres, les récuperer des champs titre et description
    layoutBouttons->addWidget(boutonEditer);
    QObject::connect(boutonEditer,SIGNAL(clicked()),this,SLOT(Relation::Editer()));
    layoutBouttons->addWidget(boutonSupprimer);
    QObject::connect(boutonSupprimer,SIGNAL(clicked()),this,SLOT(Relation::~Relation()));
    layoutBouttons->addWidget(boutonEnrichir);
    QObject::connect(boutonEnrichir,SIGNAL(clicked()),this,SLOT(ajouterCouple()));
    //slot à creer, faire choisir 2 notes et un label et faire appel à addcouple()
    
    QVBoxLayout* layoutPrincipalRel = new QVBoxLayout;
    layoutPrincipalRel->addLayout(layoutRel);
    layoutPrincipalRel->addLayouy(layoutBouttons);
    
    zoneCentraleRel->setLayout(layoutPrincipalRel)
    
*/


void MainWindow::Recherche(){

    // Recherche de la bonne note avec idNote->text();
    // Note* note = managN->getNote(idNote->text());


    titreNote = new QLineEdit;
    dateCreaNote = new QLineEdit;
    contenuNote = new QTextEdit;

    //titreNote->setText(note->getTitre);
    //dateCreaNote->setText(note->setDateCrea());
    //contenuNote->setText(note->getContenu); //à voir

//    QLabel *titre= new QLabel("Note");
    QPushButton* enregistrer = new QPushButton("Enregistrer");

    layoutAffich = new QFormLayout;
    layoutAffich->addRow("Titre", titreNote);
    layoutAffich->addRow("Date de création", dateCreaNote);
    layoutAffich->addRow("Contenu", contenuNote);

    layoutAffichage = new QVBoxLayout;
//    layoutAffichage->addWidget(titre);
    layoutAffichage->addLayout(layoutAffich);
    layoutAffichage->addWidget(enregistrer);

    layoutPrincipal->addLayout(layoutAffichage);
}
