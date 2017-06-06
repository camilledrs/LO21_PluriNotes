#include "mainwindow.h"
#include "notemanager.h"
#include "note.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    zoneCentrale = new QWidget;


    idNote = new QLineEdit;
    boutonAfficher = new QPushButton("Afficher une note");

    layout = new QFormLayout;
    layout->addRow("Id", idNote);

    layoutRecherche = new QVBoxLayout;
    layoutRecherche->addLayout(layout);
    layoutRecherche->addWidget(boutonAfficher);

    QObject::connect(boutonAfficher,SIGNAL(clicked()),this,SLOT(Recherche()));

    layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(layoutRecherche);

    zoneCentrale->setLayout(layoutPrincipal);

    setCentralWidget(zoneCentrale);
}

void MainWindow::Recherche()
{

    // Recherche de la bonne note avec idNote->text();


    Note* note = NoteManager::getInstance().getNote(idNote->text());

    titreNote = new QLineEdit;
    dateCreaNote = new QLineEdit;
    contenuNote = new QTextEdit;

    //titreNote->setText(note->getTitre);
    //dateCreaNote->setText(note->getDate());
    //contenuNote->setText(note->getContenu); //à voir

//    QLabel *titre= new QLabel("Note");
    enregistrer = new QPushButton("Enregistrer");

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
