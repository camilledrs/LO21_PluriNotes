#include "windowrelation.h"
//#include "mainwindow.h"

WindowRelation::WindowRelation(QWidget *parent) : QMainWindow(parent) { //QTabWidget(parent)
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
    QHBoxLayout* layoutBouttons= new QHBoxLayout;
    layoutBouttons->addWidget(boutonCreer);
    QObject::connect(boutonCreer,SIGNAL(clicked()),this,SLOT(Creer())); //mettre des parametres, les récuperer des champs titre et description
    layoutBouttons->addWidget(boutonEditer);
    QObject::connect(boutonEditer,SIGNAL(clicked()),this,SLOT(Editer()));
    layoutBouttons->addWidget(boutonSupprimer);
    QObject::connect(boutonSupprimer,SIGNAL(clicked()),this,SLOT(Supprimer()));
    layoutBouttons->addWidget(boutonEnrichir);
    QObject::connect(boutonEnrichir,SIGNAL(clicked()),this,SLOT(ajouterCouple()));

    QVBoxLayout* layoutPrincipalRel = new QVBoxLayout;
    layoutPrincipalRel->addLayout(layoutRel);
    layoutPrincipalRel->addLayout(layoutBouttons);

    zoneCentraleRel->setLayout(layoutPrincipalRel);
}




void WindowRelation::Creer()
{
    bool ok1=false;
    bool ok2=false;
    QString titre = QInputDialog::getText(this, "Titre :", "Quel titre voulez vous ?", QLineEdit::Normal, QString(), &ok1);
    QString desc = QInputDialog::getText(this, "Titre :", "Quel titre voulez vous ?", QLineEdit::Normal, QString(), &ok2);
    if (ok1 && ok2 && !titre.isEmpty() && !desc.isEmpty())
    {
        Relation *rel=new Relation(titre, desc);
        RelationManager::getInstance().addRelation(*rel);
        //RelationManager::addRelation(titre, desc);
        QMessageBox::information(this, "Confirmation creation", "La nouvelle relation a bien été créée ! ");
    }
}



void WindowRelation::ajouterCouple(Relation *r)
{
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
        r->addCouple(*n1,*n2,l);
    }
    }
}
