#include "WindowRelation.h"
#include "mainwindow.h"

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
    QObject::connect(boutonEditer,SIGNAL(clicked()),this,SLOT(Editer()));  
    layoutBouttons->addWidget(boutonSupprimer);
    QObject::connect(boutonSupprimer,SIGNAL(clicked()),this,SLOT(Supprimer()));
    layoutBouttons->addWidget(boutonEnrichir);
    QObject::connect(boutonEnrichir,SIGNAL(clicked()),this,SLOT(ajouterCouple()));
    //slot à creer, faire choisir 2 notes et un label et faire appel à addcouple()
    
    QVBoxLayout* layoutPrincipalRel = new QVBoxLayout;
    layoutPrincipalRel->addLayout(layoutRel);
    layoutPrincipalRel->addLayouy(layoutBouttons);
    
    zoneCentraleRel->setLayout(layoutPrincipalRel)
    


}




void WindowRelation::Creer()
{
    
    QString titre = new QInputDialog::getText(this, "Titre :", "Quel titre voulez vous ?", QLineEdit::Normal, QString(), &ok1);
    QString desc = new QInputDialog::getText(this, "Titre :", "Quel titre voulez vous ?", QLineEdit::Normal, QString(), &ok2);
    			if (ok1 && ok2 && !titre.isEmpty() && !desc.isEmpty())
    				{
       					 Relation::Relation(titre, desc);
                         QMessageBox::information(this, "Confirmation creation", "La nouvelle relation a bien été créée ! ");
                    }

}



void WindowRelation::ajouterCouple()
{
    	bool ok=False;
	while(!ok){
	NoteManager::Iterator it=getIterator();
	while(!it.isDone()){ //parcours les notes
    QString id1 = new QInputDialog::getText(this, "ID Note1 :", "Entrez l'id de la premiere note à mettre dans le couple", QLineEdit::Normal, QString(), &ok1);
    while ((!it.isDone()) && (id1 != it.currentN->getId()))
		it++;
    if (!it.isDone())
    {
	Note* n1=iterator.currentN;
	 ok=True;
    else 
	    QMessageBox::critical(this, "Note non existante", "L'id ne correspond à aucune note, ressaisir un nouvel Id");
    }	
   ok=False;
	while(!ok){
	NoteManager::Iterator it=getIterator();
	while(!it.isDone()){ //parcours les notes
    QString id2 = new QInputDialog::getText(this, "ID Note2 :", "Entrez l'id de la seconde note à mettre dans le couple", QLineEdit::Normal, QString(), &ok1);
    while ((!it.isDone()) && (id2 != it.currentN->getId()))
		it++;
    if (!it.isDone())
    {
	Note* n2=iterator.currentN;
	 ok=True;
    else 
	    QMessageBox::critical(this, "Note non existante", "L'id ne correspond à aucune note, ressaisir un nouvel Id");
    }
   QString strl = new QInputDialog::getText(this, "Couple miroir", "Quellabel voulez vous pour le couple miroir ?", QLineEdit::Normal, QString(), &ok);	
    if (ok && !strl.isEmpty())
    				{
       					 int l=atoi(strl);
				}
    RelationManager::getInstance()->addCouple(*n1, *n2,l);	
}




