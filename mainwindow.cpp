#include "mainwindow.h"
#include "WindowRelation.h"



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    
	
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QAction *nouvelleFen = new QAction("&Nouvelle Fenêtre", this);
    menuFichier->addAction(nouvelleFen);
    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);
    QAction *actionCorbeille= new QAction("&Vider Corbeille", this);
    menuFichier->addAction(actionCorbeille);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quitter()));
    connect(actionQuitter, SIGNAL(triggered()), this, SLOT(nouvelleFen()));
    connect(actionCorbeille, SIGNAL(triggered()), this, SLOT(viderLaCorbeille()));
	
	
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



//SLOTS
 
void MainWindow::nouvelleFen()
{
 
    QMdiArea *zoneCentrale = new QMdiArea;
 
    WindowRelation *ongletRel = new WindowRelation(this);
    QMdiSubWindow *sousFenetre1 = zoneCentrale->addSubWindow(ongletRel);
 
 
    setCentralWidget(zoneCentrale);
    zoneCentrale->setViewMode(QMdiArea::TabbedView)
 
 
}


void MainWindow::quitter() //demander à l'utilisateur si il veut vider la corbeille avant de quitter
{
	int reponse= new QMessageBox::question(???,"Vidage corbeille", "Voulez vous vider la corbeille avant de quitter ?",QMessageBox::Yes | QMessageBox::No);
	if(reponse == QMessageBox::Yes)
		RelationManager::getInstance->viderCorbeille();
	quit();
}


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
