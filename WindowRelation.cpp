#include "windowrelation.h"
//#include "mainwindow.h"

void WindowRelation::readSettingsRel()  //A utiliser dans le constructeur de MainWindow()
{
    QSettings settings("Equipe2", "Programme Relation");

    settings.beginGroup("WindowRelation");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}


void WindowRelation::writeSettingsRel()  //je dirais à mettre quand on quitte l’application pour sauvegarder
{
    QSettings settings("Equipe2", "Programme Relation");

    settings.beginGroup("WindowRelation");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

WindowRelation::WindowRelation(QWidget *parent) : QMainWindow(parent) { //QTabWidget(parent)
    zoneCentraleRel = new QWidget;
    zoneGaucheRel = new QDockWidget;
    zoneGaucheRel->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //zoneGaucheRel->setWidget();
    addDockWidget(Qt::LeftDockWidgetArea, zoneGaucheRel);

    Titre = new QLineEdit;
    Desc = new QLineEdit;
    contenuRelation= new QTextEdit;
    RelationList = new QListWidget(zoneGaucheRel);
    RelationList->addItem("Reference");
    addDockWidget(Qt::LeftDockWidgetArea, zoneGaucheRel);

    QFormLayout *layoutRel = new QFormLayout;
    layoutRel->addRow("Titre :", Titre);
    layoutRel->addRow("Description :", Desc);
    layoutRel->addRow("Couple :", contenuRelation);
    QObject::connect(RelationList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(seeRelation(QListWidgetItem*)));
    //QObject::connect(boutonAfficherRel,SIGNAL(clicked()),this,SLOT(SeeRelation()));


    boutonCreer = new QPushButton("Creer une Relation");
    boutonEditer = new QPushButton("Editer");
    boutonSupprimer = new QPushButton("Supprimer");
    boutonEnrichir = new QPushButton("Enrichir");

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
    boutonQuitter = new QPushButton("Quitter");
    //QObject::connect(boutonQuitter,SIGNAL(clicked()),this,SLOT(quitter()));

    layoutPrincipalRel = new QVBoxLayout;
    layoutPrincipalRel->addLayout(layoutRel);
    layoutPrincipalRel->addLayout(layoutBouttons);
    layoutPrincipalRel->addWidget(boutonQuitter);

    //this->setLayout(layoutPrincipalRel);

    zoneCentraleRel->setLayout(layoutPrincipalRel);
    setCentralWidget(zoneCentraleRel);

    readSettingsRel();

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
    Relation* r;
    QString titre= Titre->text();
    if (titre=="Reference") r= RelationManager::getInstance().getRef();
    else {
    RelationManager::Iterator itr=RelationManager::getInstance().getIterator();
    while((!itr.isDone()) && (titre!=itr.current().getTitre())) itr.next();
    r=&itr.current();
        }
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
    QString strl = QInputDialog::getText(this, "label ", "Quel label voulez vous pour le couple ?", QLineEdit::Normal, QString(), &ok);
    if (ok && !strl.isEmpty()){
        const char* c= strl.toStdString().c_str(); //pour convertir QString en const char* et ensuite pouvoir appeler atoi
        int l=atoi(c);
        r->addCouple(*n1,*n2,l);
    }
    if (r->getOrient()==false) //rajouter le couple miroir
    {
        QString strl2 = QInputDialog::getText(this, "Couple miroir", "Quel label voulez vous pour le couple miroir ?", QLineEdit::Normal, QString(), &ok);
        if (ok && !strl2.isEmpty()){
            const char* c= strl2.toStdString().c_str(); //pour convertir QString en const char* et ensuite pouvoir appeler atoi
            int l2=atoi(c);
            r->addCouple(*n1,*n2,l2);
    }
    }
}}


void WindowRelation::seeRelation(QListWidgetItem* i)
{
    Relation* r;
    if(i->text()=="Reference") r=RelationManager::getInstance().getRef();
    else {
    RelationManager::Iterator it= RelationManager::getInstance().getIterator();
    while(!it.isDone() && (it.current().getTitre() != i->text()))
        it.next();
    r=&it.current();
        }
    Titre->setText(r->getTitre());
    Desc->setText(r->getDesc());
    contenuRelation->setText(r->SeeRelation());
    RelationList->setCurrentItem(i); //plus facile pour les autres methodes ensuite
}

void WindowRelation::Supprimer()
{
    QString titre= Titre->text();
    if (titre==RelationManager::getInstance().getRef()->getTitre())
        QMessageBox::warning(this, "Erreur suppression", "La relation Reference ne peut être supprimée !");
    else {
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
    if(reponse2 == QMessageBox::Yes)
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

/*
void WindowRelation::quitter()
{
    writeSettingsRel();
    close()
}
*/

