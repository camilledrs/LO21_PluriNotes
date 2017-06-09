#include "windowrelation.h"
//#include "mainwindow.h"

WindowRelation::WindowRelation(QWidget *parent) : QMainWindow(parent) { //QTabWidget(parent)
    zoneCentraleRel = new QWidget;
    zoneGaucheRel = new QDockWidget;
    zoneGaucheRel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //zoneGaucheRel->setWidget();
    addDockWidget(Qt::LeftDockWidgetArea, zoneGaucheRel);

    Titre = new QLineEdit;
    Desc = new QLineEdit;
    RelationList = new QListWidget(zoneGaucheRel);
    addDockWidget(Qt::LeftDockWidgetArea, zoneGaucheRel);

    QFormLayout *layoutRel = new QFormLayout;
    layoutRel->addRow("Titre :", Titre);
    layoutRel->addRow("Description :", Desc);
    QObject::connect(RelationList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(seeRelation(QListWidgetItem*)));
    //QObject::connect(boutonAfficherRel,SIGNAL(clicked()),this,SLOT(SeeRelation()));


    boutonCreer = new QPushButton("Creer une Relation");
    boutonEditer = new QPushButton("Editer une Relation");
    boutonSupprimer = new QPushButton("Supprimer une Relation");
    boutonEnrichir = new QPushButton("Enrichir une Relation");

    QHBoxLayout *layoutBouttons = new QHBoxLayout;
    layoutBouttons= new QHBoxLayout;
    layoutBouttons->addWidget(boutonCreer);
    QObject::connect(boutonCreer,SIGNAL(clicked()),this,SLOT(Creer())); //mettre des parametres, les récuperer des champs titre et description
    layoutBouttons->addWidget(boutonEditer);
    QObject::connect(boutonEditer,SIGNAL(clicked()),this,SLOT(Editer()));
    layoutBouttons->addWidget(boutonSupprimer);
    QObject::connect(boutonSupprimer,SIGNAL(clicked()),this,SLOT(Supprimer()));
    layoutBouttons->addWidget(boutonEnrichir);
    QObject::connect(boutonEnrichir,SIGNAL(clicked()),this,SLOT(ajouterCouple()));

    layoutPrincipalRel = new QVBoxLayout;
    layoutPrincipalRel->addLayout(layoutRel);
    layoutPrincipalRel->addLayout(layoutBouttons);

    //this->setLayout(layoutPrincipalRel);

    zoneCentraleRel->setLayout(layoutPrincipalRel);
    setCentralWidget(zoneCentraleRel);

}




void WindowRelation::Creer()
{
    bool ok1=false;
    bool ok2=false;
    bool orient=true;
    QString titre = QInputDialog::getText(this, "Titre :", "Quel titre voulez vous ?", QLineEdit::Normal, QString(), &ok1);
    QString desc = QInputDialog::getText(this, "Titre :", "Quel description voulez vous ?", QLineEdit::Normal, QString(), &ok2);
    QMessageBox::StandardButton reponse;
    reponse= QMessageBox::question(this,"Orientation", "La relation est elle orientee ?",QMessageBox::Yes | QMessageBox::No);
    if(reponse == QMessageBox::No)
        orient=false;
    if (ok1 && ok2 && !titre.isEmpty() && !desc.isEmpty())
    {

        RelationManager::getInstance().addRelation(titre, desc, orient);
        QMessageBox::information(this, "Confirmation creation", "La nouvelle relation a bien été créée ! ");
    }
        RelationList->addItem(titre);
}



void WindowRelation::ajouterCouple()
{
    QString titre= Titre->text();
    RelationManager::Iterator itr=RelationManager::getInstance().getIterator();
    while((!itr.isDone()) && (titre!=itr.current().getTitre())) itr.next();
    Relation& r=itr.current();
    bool ok=false;
    Note* n1;
    Note* n2;
    //while(!ok)
        QString id1 = QInputDialog::getText(this, "ID Note1 :", "Entrez l'id de la premiere note à mettre dans le couple", QLineEdit::Normal, QString(), &ok);
    NoteManager::Iterator it=NoteManager::getInstance().getIterator();
    while ((!it.isDone()) && (id1 != it.current().getId())) //parcours les notes
        it.next();
    if (!it.isDone())
    {
        n1=(&it.current());
        ok=true;
    }
    else
        QMessageBox::critical(this, "Note non existante", "L'id ne correspond à aucune note, ressaisir un nouvel Id");
    ok=false;
    //while(!ok)
        QString id2 = QInputDialog::getText(this, "ID Note2 :", "Entrez l'id de la seconde note à mettre dans le couple", QLineEdit::Normal, QString(), &ok);
    NoteManager::Iterator itN=NoteManager::getInstance().getIterator();
    while ((!itN.isDone()) && (id2 != itN.current().getId())) //parcours les notes
        itN.next();
    if (!itN.isDone())
    {
        n2=&itN.current();
        ok=true;
    }
    else
        QMessageBox::critical(this, "Note non existante", "L'id ne correspond à aucune note, ressaisir un nouvel Id");
    if (n2 && n1){
    QString strl = QInputDialog::getText(this, "Couple miroir", "Quel label voulez vous pour le couple miroir ?", QLineEdit::Normal, QString(), &ok);
    if (ok && !strl.isEmpty()){
        const char* c= strl.toStdString().c_str(); //pour convertir QString en const char* et ensuite pouvoir appeler atoi
        int l=atoi(c);
        r.addCouple(*n1,*n2,l);
    }
    }
}


void WindowRelation::seeRelation(QListWidgetItem* i)
{
    RelationManager::Iterator it= RelationManager::getInstance().getIterator();
    while(!it.isDone() && (it.current().getTitre() != i->text()))
        it.next();
    Relation& r=it.current();
    Titre->setText(r.getTitre());
    Desc->setText(r.getDesc());
    RelationList->setCurrentItem(i); //plus facile pour les autres methodes ensuite
}

void WindowRelation::Supprimer()
{
    QString titre= Titre->text();
    RelationManager::Iterator itr=RelationManager::getInstance().getIterator();
    while((!itr.isDone()) && (titre!=itr.current().getTitre())) itr.next();
    Relation& r=itr.current();
    QMessageBox::StandardButton reponse;
    reponse= QMessageBox::question(this,"Confirmation Suppression", "Voulez vous vraiment supprimer la relation ?",QMessageBox::Yes | QMessageBox::No);
    if(reponse == QMessageBox::Yes)
       { RelationManager::getInstance().suppRelation(r);
    delete RelationList->currentItem();
    Titre->setText("");
    Desc->setText("");
    }

}


void WindowRelation::Editer()
{
    QMessageBox::StandardButton reponse;
    reponse= QMessageBox::question(this,"Modifier Titre", "Voulez vous modifier le titre ?",QMessageBox::Yes | QMessageBox::No);
    QString titre=Titre->text();
    QString desc=Desc->text();
    if(reponse == QMessageBox::Yes)
    {
        bool ok;
        titre=QInputDialog::getText(this, "Titre :", "Quel titre voulez vous ?", QLineEdit::Normal, QString(), &ok);
        if (ok && !titre.isEmpty())
        Titre->setText(titre);
    }
    QMessageBox::StandardButton reponse2;
    reponse2= QMessageBox::question(this,"Modifier Description", "Voulez vous modifier la description ?",QMessageBox::Yes | QMessageBox::No);
    if(reponse == QMessageBox::Yes)
    {
        bool ok;
        desc = QInputDialog::getText(this, "Description :", "Quel description voulez vous ?", QLineEdit::Normal, QString(), &ok);
        if (ok && !desc.isEmpty())
        Desc->setText(desc);
    }
    QListWidgetItem* i= RelationList->currentItem();
    RelationManager::Iterator it = RelationManager::getInstance().getIterator();
    while(it.current().getTitre() != i->text())
        it.next();
    Relation& r=it.current();
    RelationManager::getInstance().editerRelation(&r,titre, desc);
    i->setText(titre);


}
