#include "WindowRelation.h"

WindowRelation::WindowRelation(QWidget *parent) : MainWindow(parent)  //pour dire que c'est la fenetre principale MainWindow le parent de notre fenetre
//pas sure du tout
{
    QWidget* zoneCentraleRel = new QWidget;  
    QDockWidget* zoneGaucheRel = new QDockWidget;
    zoneGaucheRel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //zoneGaucheRel->setWidget();
    addDockWidget(Qt::LeftDockWidgetArea, zoneGaucheRel);
    
    QLineEdit* Titre = new QLineEdit;
    QLineEdit* Desc = new QLineEdit;
    
    QFormLayout* layoutRel = new QFormLayout;
    layoutRel->addRow("Titre :", Titre);
    layoutRel->addRow("Description :", Desc);
    QPushButton* boutonAfficherRel = new QPushButton("Afficher une Relation");
    QObject::connect(boutonAfficherRel,SIGNAL(clicked()),this,SLOT(SeeRelation()));
    layoutRel->addWidget(boutonAfficherRel);
    
    
    QPushButton* boutonCreer = new QPushButton("Creer une note");
    QPushButton* boutonEditer = new QPushButton("Editer une note");
    QPushButton* boutonSupprimer = new QPushButton("Supprimer une note");
    QPushButton* boutonEnrichir = new QPushButton("Enrichir une note");
    QHBox* layoutBouttons= new QHBoxLayout;
    layoutBouttons->addWidget(boutonCreer);
    QObject::connect(boutonCreer,SIGNAL(clicked()),this,SLOT(Creer())); //mettre des parametres, les récuperer des champs titre et description
    layoutBouttons->addWidget(boutonEditer);
    QObject::connect(boutonEditer,SIGNAL(clicked()),this,SLOT(Editer()));  //Creer le slot avec Relation::creer
    layoutBouttons->addWidget(boutonSupprimer);
    QObject::connect(boutonSupprimer,SIGNAL(clicked()),this,SLOT(Relation::~Relation()));
    layoutBouttons->addWidget(boutonEnrichir);
    QObject::connect(boutonEnrichir,SIGNAL(clicked()),this,SLOT(ajouterCouple()));
    //slot à creer, faire choisir 2 notes et un label et faire appel à addcouple()
    
    QVBoxLayout* layoutPrincipalRel = new QVBoxLayout;
    layoutPrincipalRel->addLayout(layoutRel);
    layoutPrincipalRel->addLayouy(layoutBouttons);
    
    zoneCentraleRel->setLayout(layoutPrincipalRel)
    


}
