#include "mainwindow.h"
#include "notemanager.h"
#include "note.h"


void MainWindow::readSettings()  //A utiliser dans le constructeur de MainWindow()
{
    QSettings settings("Equipe", "Programme");

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}

void MainWindow::writeSettings()  //je dirais à mettre quand on quitte l’application pour sauvegarder
{
    QSettings settings("Equipe", "Programme");

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}



//Pour l'affichage il faut, dans le dock gauche, 3 parties différentes avec chacune une QLIstWidget
// 1) NoteList  (on peut trier par id grace a sortItems(Qt::SortOrder order = Qt::AscendingOrder) )
// 2) TacheList (trié par ordre de priorité)
// 3) NoteListArchive
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    QMenu *menuFichier = menuBar()->addMenu(tr("&Fichier"));
    QAction *nouvelleFen = new QAction("&Nouvelle Fenêtre", this);
    menuFichier->addAction(nouvelleFen);
    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);
    QAction *actionRelation = new QAction("&Fenetre Relation", this);
    menuFichier->addAction(actionRelation);
    QAction *actionCorbeille= new QAction("&Vider Corbeille", this);
    menuFichier->addAction(actionCorbeille);
    connect(actionQuitter, SIGNAL(triggered()), this, SLOT(quitter()));
    connect(actionRelation, SIGNAL(triggered()), this, SLOT(fenRelation()));
    connect(nouvelleFen, SIGNAL(triggered()), this, SLOT(nouvelleFen()));
    connect(actionCorbeille, SIGNAL(triggered()), this, SLOT(viderLaCorbeille()));


    zoneCentrale = new QWidget;

    zoneGauche = new QDockWidget(tr("Notes actives"), this);
    zoneGauche->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    zoneDroite = new QDockWidget(tr("Arborescence fils"), this);
    zoneDroite->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    


    ///////////////////////////////////////////////

    /*QGroupBox *groupbox = new QGroupBox("Type de note", zoneCentrale);
    QRadioButton *article = new QRadioButton("Article");
    //QObject::connect(article,SIGNAL(clicked()),this,SLOT(articleNote()));
    QRadioButton *tache = new QRadioButton("Tache");
    //QObject::connect(tache,SIGNAL(clicked()),this,SLOT(tacheNote()));
    QRadioButton *media = new QRadioButton("Media");
    //QObject::connect(media,SIGNAL(clicked()),this,SLOT(mediaNote()));
    //article->setChecked(true);
    QVBoxLayout *layoutTypeNote = new QVBoxLayout;
    layoutTypeNote->addWidget(article);
    layoutTypeNote->addWidget(tache);
    layoutTypeNote->addWidget(media);
    groupbox->setLayout(layoutTypeNote);*/

    idNote = new QLineEdit;
    titreNote = new QLineEdit;
    dateCreaNote = new QDateTimeEdit(QDateTime::currentDateTime());
    dateModifNote = new QDateTimeEdit(QDateTime::currentDateTime());
    dateCreaNote->setReadOnly(true);
    contenuNote = new QTextEdit;

    NoteList = new QListWidget();

    //Ajout des notes à la liste

    zoneGauche->setWidget(NoteList);
    addDockWidget(Qt::LeftDockWidgetArea, zoneGauche);

    zoneGauche = new QDockWidget(tr("Taches"), this);

    TacheList = new QListWidget();

    //Ajout des taches à la liste

    zoneGauche->setWidget(TacheList);
    addDockWidget(Qt::LeftDockWidgetArea, zoneGauche);

    zoneGauche = new QDockWidget(tr("Notes archivées"), this);

    NoteListArchive = new QListWidget();

    //Ajout des notes archivées à la liste

    zoneGauche->setWidget(NoteListArchive);
    addDockWidget(Qt::LeftDockWidgetArea, zoneGauche);
    
    //Arborescence
    NoteAbrFils= new QTreeWidget();
    NoteAbrFils->headerItem()->setText(0, "Arbre des fils");
    NoteAbrPeres= new QTreeWidget();
    NoteAbrPeres->headerItem()->setText(0, "Arbre des peres");
    //Ajout de larborescence de note
    zoneDroite->setWidget(NoteAbrFils);
    addDockWidget(Qt::RightDockWidgetArea, zoneDroite);

    zoneDroite = new QDockWidget(tr("Arborescence peres"), this);
    zoneDroite->setWidget(NoteAbrPeres);
    addDockWidget(Qt::RightDockWidgetArea, zoneDroite);


    creer = new QPushButton("Créer");
    QObject::connect(creer,SIGNAL(clicked()),this,SLOT(creerNote()));
    supprimer = new QPushButton("Supprimer");
    QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(supprimerNote()));
    editer = new QPushButton("Editer");
    QObject::connect(editer,SIGNAL(clicked()),this,SLOT(editerNote()));
    restaurer = new QPushButton("Restaurer");
    QObject::connect(restaurer,SIGNAL(clicked()),this,SLOT(restaurerNote()));
    restaurerVersion = new QPushButton("Restaurer Version");
    QObject::connect(restaurerVersion,SIGNAL(clicked()),this,SLOT(RestaurerV()));


    QHBoxLayout* layoutBouton = new QHBoxLayout;
    layoutBouton->addWidget(creer);
    layoutBouton->addWidget(supprimer);
    layoutBouton->addWidget(editer);
    layoutBouton->addWidget(restaurer);
    layoutBouton->addWidget(restaurerVersion);

    layoutAffich = new QFormLayout;
    layoutAffich->addRow("Id", idNote);
    layoutAffich->addRow("Titre", titreNote);
    layoutAffich->addRow("Date de création", dateCreaNote);
    layoutAffich->addRow("Date de dernière modification", dateModifNote);
    layoutAffich->addRow("Contenu", contenuNote);

    layoutAffichage = new QVBoxLayout;
    layoutAffichage->addLayout(layoutAffich);
    layoutAffichage->addLayout(layoutBouton);

    boutonQuitter = new QPushButton("Quitter");
    QObject::connect(boutonQuitter,SIGNAL(clicked()),this,SLOT(quitter()));

    layoutPrincipal = new QVBoxLayout;
    //layoutPrincipal->addLayout(layoutRecherche);
    //layoutPrincipal->addWidget(groupbox);
    layoutPrincipal->addLayout(layoutAffichage);
    layoutPrincipal->addWidget(boutonQuitter);



    //Note note1 = NoteManager::getInstance().addNote("Nouvelle note","quelquechose",QDateTime(),QDateTime(),const Version(QDateTime()));

    /*NoteManager::Iterator it = NoteManager::getInstance().getIterator();
    while (!it.isDone())
    {
        NoteList->addItem(it.current().getId());
        it.next();
    }
    NoteList->addItems(QStringList()
                        << "Note1"
                        << "Note1");
    NoteList->addItem("Note référencée");*/

  QObject::connect(NoteList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(afficherNote(QListWidgetItem*)));
    QObject::connect(NoteList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(arborescencefils(QListWidgetItem*)));
     QObject::connect(NoteList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(arborescencePeres(QListWidgetItem*)));
    QObject::connect(TacheList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(afficherNote(QListWidgetItem*)));
    QObject::connect(TacheList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(arborescencefils(QListWidgetItem*)));
     QObject::connect(TacheList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(arborescencePeres(QListWidgetItem*)));
    QObject::connect(NoteListArchive,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(afficherNote(QListWidgetItem*)));
    QObject::connect(NoteListArchive,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(arborescencefils(QListWidgetItem*)));
    QObject::connect(NoteListArchive,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(arborescencePeres(QListWidgetItem*)));

    zoneCentrale->setLayout(layoutPrincipal);

    setCentralWidget(zoneCentrale);
    ////////////////////////////////////////////////

    /*idNote = new QLineEdit;
    boutonAfficher = new QPushButton("Afficher une note");
    boutonRestaurer = new QPushButton("Restaurer la version");
    layout = new QFormLayout;
    layout->addRow("Id", idNote);
    layoutRecherche = new QVBoxLayout;
    layoutRecherche->addLayout(layout);
    layoutRecherche->addWidget(boutonAfficher);
    layoutRecherche->addWidget(boutonRestaurer);
    QObject::connect(boutonAfficher,SIGNAL(clicked()),this,SLOT(Recherche()));
    layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addLayout(layoutRecherche);
    zoneCentrale->setLayout(layoutPrincipal);
    setCentralWidget(zoneCentrale);*/

    ///////PARAMETRAGE///////////////////////
    readSettings();

}

/*void MainWindow::articleNote()
{
    texteNote = new QTextEdit;
    layoutAffich->addRow("Texte", texteNote);
}
void MainWindow::tacheNote()
{
    actionNote = new QLineEdit;
    layoutAffich->addRow("Action", actionNote);
}*/

void MainWindow::nouvelleFen()
{
    QMdiArea *zoneCentrale = new QMdiArea;

    WindowRelation *ongletRel = new WindowRelation(this);
    QMdiSubWindow *sousFenetre1 = zoneCentrale->addSubWindow(ongletRel);


    setCentralWidget(zoneCentrale);
    zoneCentrale->setViewMode(QMdiArea::TabbedView);
}

void MainWindow::quitter() //demander à l'utilisateur si il veut vider la corbeille avant de quitter
{

    QMessageBox::StandardButton reponse;
    reponse= QMessageBox::question(this,"Vidage corbeille", "Voulez vous vider la corbeille avant de quitter ?",QMessageBox::Yes | QMessageBox::No);
    if(reponse == QMessageBox::Yes)
        NoteManager::getInstance().viderCorbeille();
     NoteManager::getInstance().save();
    RelationManager::getInstance().save();
    writeSettings();
    QApplication::quit();
}



void MainWindow::RestaurerV()
{
    QStringList items;
    QString id= idNote->text();
    NoteManager::Iterator it = NoteManager::getInstance().getIterator();
    while(!it.isDone() && it.current().getId()!=id) it.next();
    if(!it.isDone())
    {
        unsigned int i=0;
        while(i<it.current().getNbVersion()){
            items << tr(it.current().getElement(i).getDate().toString("dd.MM.yyyy hh:mm:ss").toStdString().c_str());
            i++;}
        bool ok;
        QString date = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Date de modification:"), items, 0, false,&ok);
        if(ok){
        unsigned int i=0;
        while(i<it.current().getNbVersion() && it.current().getElement(i).getDate().toString("dd.MM.yyyy hh:mm:ss")!=date) i++;
        it.current().restaurer(&it.current().getElement(i));
        }
    }
}



/*void MainWindow::Recherche()
{
    // Recherche de la bonne note avec idNote->text();
    Note* note = NoteManager::getInstance().getNote(idNote->text());
    titreNote = new QLineEdit;
    dateCreaNote = new QDateTimeEdit;
    contenuNote = new QTextEdit;
    //titreNote->setText(note->getTitre);
    //dateCreaNote->setText(note->getDate());
    //contenuNote->setText(note->getContenu); //à voir
//    QLabel *titre= new QLabel("Note");
    enregistrer = new QPushButton("Enregistrer");
    boutonRestaurer = new QPushButton("Restaurer la note");
    boutonRestaurer->setEnabled(false);
    layoutAffich = new QFormLayout;
    layoutAffich->addRow("Titre", titreNote);
    layoutAffich->addRow("Date de création", dateCreaNote);
    layoutAffich->addRow("Contenu", contenuNote);
    layoutAffichage = new QVBoxLayout;
//    layoutAffichage->addWidget(titre);
    layoutAffichage->addLayout(layoutAffich);
    layoutAffichage->addWidget(enregistrer);
    layoutAffichage->addWidget(boutonRestaurer);
    layoutPrincipal->addLayout(layoutAffichage);
    if (note->getDerniereVersion().getDate() != dateCreaNote->dateTime())  //si ce n'est pas la dernière version qu'on traite, on peut la restaurer
        boutonRestaurer->setEnabled(true);
    QObject::connect(boutonRestaurer,SIGNAL(clicked()),this,SLOT(RestaurerV()));
}*/



void MainWindow::afficherNote(QListWidgetItem* item)
{
    QString id= item->text();
    NoteManager::Iterator it=NoteManager::getInstance().getIterator();
    while(it.current().getId() != id) it.next(); //on a trouvé la note
    Note& n=it.current();
    idNote->setText(id);
    titreNote->setText(n.getTitre());
    dateCreaNote->setDateTime(n.getDate());
    dateModifNote->setDateTime(n.getDateModif());
    contenuNote->setText(n.getDerniereVersion().afficher());
}

void MainWindow::afficherNote(QString id)
{
    NoteManager::Iterator it=NoteManager::getInstance().getIterator();
    while(it.current().getId() != id) it.next(); //on a trouvé la note
    Note& n=it.current();
    idNote->setText(id);
    titreNote->setText(n.getTitre());
    dateCreaNote->setDateTime(n.getDate());
    dateModifNote->setDateTime(n.getDateModif());
    contenuNote->setText(n.getDerniereVersion().afficher());
}


void MainWindow::arborescencefils(QListWidgetItem *item)
{   NoteAbrFils->clear();
    QString id= item->text();
    NoteManager::Iterator it=NoteManager::getInstance().getIterator();
    while(it.current().getId() != id) it.next(); //on a trouvé la note
    Note& n=it.current();
    QTreeWidgetItem* note_item = new QTreeWidgetItem(NoteAbrFils,QTreeWidgetItem::Type);
    note_item->setText(0, n.getId());
    n.enfant(note_item,NoteAbrFils);
    NoteAbrFils->expandAll();
}
void MainWindow::arborescencePeres(QListWidgetItem *item)
{   NoteAbrPeres->clear();
    QString id= item->text();
    NoteManager::Iterator it=NoteManager::getInstance().getIterator();
    while(it.current().getId() != id) it.next(); //on a trouvé la note
    Note& n=it.current();
    QTreeWidgetItem* note_item = new QTreeWidgetItem(NoteAbrPeres,QTreeWidgetItem::Type);
    note_item->setText(0, n.getId());
    n.parent(note_item);
    NoteAbrPeres->expandAll();
}

void MainWindow::creerNote()
{
    /*bool ok;
    QStringList items;
    items << tr("Article") << tr("Tache") << tr("Media");
    QString reponse= QInputDialog::getitem(this, "Type de note", "Quel type de note voulez-vous créer ?", QLineEdit::Normal, QString(), &ok);
    //fenetreCreationNote();
    //QString item = fenetreCreationNote::getItem(this, tr("Création d'une note"),tr("Type de note"), items, 0, false, &ok);
    //if (ok && !item.isEmpty())
        //if (item=="Article")
    //QMessageBox::StandardButton reponse= QMessageBox::question(this,"OK", "ça marche",QMessageBox::Yes | QMessageBox::No);
    CreateNoteWidget *cw = new CreateNoteWidget();
    cw->show();
    NoteList->addItem(cw->getId());
    //On crée bien un nouvel item mais l'id n'est pas récupéré*/

    bool ok1=false;
    bool ok2=false;
    bool ok3=false;
    QString id = QInputDialog::getText(this, "Id :", "Quel id voulez vous ?", QLineEdit::Normal, QString(), &ok1);
    QString titre = QInputDialog::getText(this, "Titre :", "Quel titre voulez vous ?", QLineEdit::Normal, QString(), &ok2);

    QStringList items;
    items << tr("Article") << tr("Tache") << tr("Media");

    QString type = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Type de note:"), items, 0, false, &ok3);

    if (type == "Article")
    {
        bool ok4=false;
        QString texte = QInputDialog::getText(this, "Texte :", "Quel est le texte de l'article ?", QLineEdit::Normal, QString(), &ok4);

        if (ok1 && ok2 && ok3 && ok4 && !id.isEmpty() && !titre.isEmpty() && !texte.isEmpty())
        {
            NoteManager::getInstance().addNote(id,titre,QDateTime::currentDateTime(),QDateTime::currentDateTime(),Article(QDateTime::currentDateTime(),texte));
            QMessageBox::information(this, "Confirmation creation", "La nouvelle note a bien été créée ! ");
            NoteList->addItem(id);
            NoteList->sortItems(Qt::AscendingOrder);
            afficherNote(id);
        }
    }

    if (type == "Tache")
    {
        bool ok5=false;
        bool ok6=false;
        bool ok7=false;

        QString action = QInputDialog::getText(this, "Action :", "Quelle est l'action de la tache ?", QLineEdit::Normal, QString(), &ok5);

        int anneeFin = QInputDialog::getInt(this, tr("Date de fin de tache (optionnelle)"),tr("Annee:"), 2000, 2000, 3000, 1, &ok6);
        int moisFin = QInputDialog::getInt(this, tr("Date de fin de tache (optionnelle)"),tr("Mois:"), 01, 01, 12, 1, &ok6);
        int jourFin = QInputDialog::getInt(this, tr("Date de fin de tache (optionnelle)"),tr("Jour:"), 01, 01, 31, 1, &ok6);
        int heureFin = QInputDialog::getInt(this, tr("Date de fin de tache (optionnelle)"),tr("Heure:"), 01, 01, 24, 1, &ok6);
        int minuteFin = QInputDialog::getInt(this, tr("Date de fin de tache (optionnelle)"),tr("Minute:"), 00, 01, 59, 1, &ok6);

        QString priorite = QInputDialog::getText(this, "Priorité :", "Quelle est la priorité de la tache ? (optionnelle)", QLineEdit::Normal, QString(), &ok7);

        int p=priorite.toInt();
        if (ok1 && ok2 && ok3 && ok5 && /*ok6 &&*/ ok7 && !id.isEmpty() && !titre.isEmpty() && !action.isEmpty())
        {

            NoteManager::getInstance().addNote(id,titre,QDateTime::currentDateTime(),QDateTime::currentDateTime(),Tache(QDateTime::currentDateTime(),action,QDateTime(QDate(anneeFin,moisFin,jourFin),QTime(heureFin,minuteFin)),p));
            QMessageBox::information(this, "Confirmation creation", "La nouvelle note a bien été créée ! ");
            NoteList->addItem(id);
            NoteList->sortItems(Qt::AscendingOrder);
            TacheList->addItem(id);
            //TacheList->sortItems(Qt::AscendingOrder); trier par priorite et date echue
            afficherNote(id);
        }
    }

    if (type == "Media")
    {
        bool ok8=false;
        bool ok9=false;
        bool ok10=false;

        QStringList items;
        items << tr("Image") << tr("Vidéo") << tr("Audio");

        QString typeM = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Type de média:"), items, 0, false, &ok8);

        QString description = QInputDialog::getText(this, "Description :", "Quelle description voulez-vous ?", QLineEdit::Normal, QString(), &ok9);
        QString fichier = QInputDialog::getText(this, "Fichier :", "Quel fichier voulez-vous ? (optionnelle)", QLineEdit::Normal, QString(), &ok10);

        if (ok1 && ok2 && ok3 && ok8 && ok9 && ok10 && !id.isEmpty() && !titre.isEmpty() && !description.isEmpty())
        {
            if (typeM == "Image")
                NoteManager::getInstance().addNote(id,titre,QDateTime::currentDateTime(),QDateTime::currentDateTime(),Multimedia(QDateTime::currentDateTime(),description,fichier,image));
            if (typeM == "Vidéo")
                NoteManager::getInstance().addNote(id,titre,QDateTime::currentDateTime(),QDateTime::currentDateTime(),Multimedia(QDateTime::currentDateTime(),description,fichier,video));
            if (typeM == "Audio")
                NoteManager::getInstance().addNote(id,titre,QDateTime::currentDateTime(),QDateTime::currentDateTime(),Multimedia(QDateTime::currentDateTime(),description,fichier,audio));
            QMessageBox::information(this, "Confirmation creation", "La nouvelle note a bien été créée ! ");
            NoteList->addItem(id);
            NoteList->sortItems(Qt::AscendingOrder);
            afficherNote(id);
        }
    }
}


void MainWindow::supprimerNote()
{
    QString id= idNote->text();
    NoteManager::Iterator itn=NoteManager::getInstance().getIterator();
    while((!itn.isDone()) && (id!=itn.current().getId())) itn.next();
    Note& n=itn.current();
    QMessageBox::StandardButton reponse;
    reponse= QMessageBox::question(this,"Confirmation Suppression", "Voulez vous vraiment supprimer la note ?",QMessageBox::Yes | QMessageBox::No);
    if(reponse == QMessageBox::Yes)
       {
        NoteManager::getInstance().supprimerNote(n);
        if(n.getActive()==false)
            QMessageBox::information(this, "Confirmation creation", "");
        delete NoteList->currentItem();
        if (n.getDerniereVersion().notetype()=="tache")
            delete TacheList->currentItem();
        idNote->setText("");
        titreNote->setText("");
        dateCreaNote->setDateTime(QDateTime::currentDateTime());
        contenuNote->setText("");
        QMessageBox::information(this, "Confirmation creation", "ok");
        if(!n.getActive())
        {
            NoteListArchive->addItem(id); //la note etait referencee, elle est maintenant archivee, on l'ajoute dans la liste des archivees
            NoteListArchive->sortItems(Qt::AscendingOrder);
        }
        else
            QMessageBox::critical(this, "Erreur", "Vous avez fait une erreur lors de la saisie");
    }
    else
        QMessageBox::critical(this, "Erreur", "Vous avez fait une erreur lors de la saisie");
}



void MainWindow::editerNote()
{    QListWidgetItem* i= NoteList->currentItem();
     NoteManager::Iterator it = NoteManager::getInstance().getIterator();
     while(it.current().getId() != i->text())
         it.next();
     Note& n=it.current();
    //voir comment j'ai fait pour editerRelation
    QMessageBox::StandardButton reponse = QMessageBox::No;
    reponse= QMessageBox::question(this,"Modifier Titre", "Voulez vous modifier le titre ?",QMessageBox::Yes | QMessageBox::No);
    QString titre=titreNote->text();
    if(reponse == QMessageBox::Yes)
    {
        bool ok;
        titre=QInputDialog::getText(this, "Titre :", "Quel titre voulez vous ?", QLineEdit::Normal, QString(), &ok);
        if (ok && !titre.isEmpty())
            n.setTitre(titre);
    }
    QMessageBox::StandardButton reponse2 = QMessageBox::No;

    QString t=n.getDerniereVersion().notetype();
    if(t=="article"){
        QString texteArticle;
        reponse2= QMessageBox::question(this,"Modifier Texte Article", "Voulez vous modifier le texte de l'article ?",QMessageBox::Yes | QMessageBox::No);
        if(reponse2 == QMessageBox::Yes)
        {
            bool ok1;
            texteArticle = QInputDialog::getText(this, "Texte :", "Quel texte voulez vous ?", QLineEdit::Normal, QString(), &ok1);
            if (ok1 && !texteArticle.isEmpty()){
            Article a(QDateTime::currentDateTime(),texteArticle);
            NoteManager::getInstance().editer(&n,titre,QDateTime::currentDateTime(),a);}

        }

    }
    if(t=="tache"){
        QString actionTache;
        QDateTime dateTache;
        unsigned int priorityTache;
        QString statutTache;
        reponse2= QMessageBox::question(this,"Modifier Contenu  Tache", "Voulez vous modifier le contenu de la tache  ?",QMessageBox::Yes | QMessageBox::No);
        bool ok2;
        bool ok3;
        bool ok4;
        bool ok6;
        QStringList items;
        items << tr("En Attente") << tr("En cours") << tr("Terminee");
        if(reponse2 == QMessageBox::Yes)
        {
            actionTache = QInputDialog::getText(this, "Action :", "Quelle action voulez vous ?", QLineEdit::Normal, QString(), &ok2);
            QString priority = QInputDialog::getText(this, "Priorité :", "Quelle est la nouvelle priorité de la tache ? (optionnelle)", QLineEdit::Normal, QString(), &ok3);
            priorityTache=priority.toInt();
            int anneeFin = QInputDialog::getInt(this, tr("Date de fin de tache (optionnelle)"),tr("Annee:"), 2000, 2000, 3000, 1, &ok6);
            int moisFin = QInputDialog::getInt(this, tr("Date de fin de tache (optionnelle)"),tr("Mois:"), 01, 01, 12, 1, &ok6);
            int jourFin = QInputDialog::getInt(this, tr("Date de fin de tache (optionnelle)"),tr("Jour:"), 01, 01, 31, 1, &ok6);
            int heureFin = QInputDialog::getInt(this, tr("Date de fin de tache (optionnelle)"),tr("Heure:"), 01, 01, 24, 1, &ok6);
            int minuteFin = QInputDialog::getInt(this, tr("Date de fin de tache (optionnelle)"),tr("Minute:"), 00, 01, 59, 1, &ok6);
            statutTache = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Statut de la tache:"), items, 0, false, &ok4);

            if (ok2 && ok3 && ok4 && !actionTache.isEmpty() && !statutTache.isEmpty()){
                Tache ta(QDateTime::currentDateTime(),actionTache,QDateTime(QDate(anneeFin,moisFin,jourFin),QTime(heureFin,minuteFin)),priorityTache);
                if(statutTache=="En Attente") ta.setStatut(Statut::EnAttente);
                else if(statutTache=="En cours") ta.setStatut(Statut::EnCours);
                else if (statutTache=="Terminee") ta.setStatut(Statut::Terminee);
            NoteManager::getInstance().editer(&n,titre,QDateTime::currentDateTime(),ta);}

        }

    }
    if(t=="multimedia"){
        QString descriptionM;
        QString fichierM;
        QString typeM;
        bool ok6;
        bool ok7;
        bool ok8;
        QStringList items;
        items << tr("Image") << tr("Vidéo") << tr("Audio");
        reponse2= QMessageBox::question(this,"Modifier Contenu Media", "Voulez vous modifier le contenu du Multimedia  ?",QMessageBox::Yes | QMessageBox::No);
        if(reponse2 == QMessageBox::Yes)
        {
            descriptionM = QInputDialog::getText(this, "description :", "Quelle description voulez vous ?", QLineEdit::Normal, QString(), &ok6);
            fichierM = QInputDialog::getText(this, "nom fichier :", "Quelle est la nom du fichier associe ? ", QLineEdit::Normal, QString(), &ok7);
            typeM = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Statut de la tache:"), items, 0, false, &ok8);

            if (ok6 && ok7 && ok8 && !descriptionM.isEmpty() && !fichierM.isEmpty() && !typeM.isEmpty()){

                if(typeM=="Image") NoteManager::getInstance().editer(&n,titre,QDateTime::currentDateTime(),Multimedia(QDateTime::currentDateTime(),descriptionM,fichierM,image));
                if(typeM=="Vidéo") NoteManager::getInstance().editer(&n,titre,QDateTime::currentDateTime(),Multimedia(QDateTime::currentDateTime(),descriptionM,fichierM,video));
                if(typeM=="Audio") NoteManager::getInstance().editer(&n,titre,QDateTime::currentDateTime(),Multimedia(QDateTime::currentDateTime(),descriptionM,fichierM,audio));
            }

        }
    }
    if(reponse == QMessageBox::Yes || reponse2 == QMessageBox::Yes)
        n.setDateModif(QDateTime::currentDateTime());
}



void MainWindow::restaurerNote()
{

    bool ok;
    QString id = QInputDialog::getText(this, "ID Note a restaurer :", "Entrez l'id de la note à restaurer", QLineEdit::Normal, QString(), &ok);
        NoteManager::Iterator it= NoteManager::getInstance().getIterator();
        while((it.current().getId() != id) && !it.isDone()) it.next();
        if(it.isDone()) throw NotesException("Note non existante");
        else if(it.current().getActive() && !it.current().getStatutSupp()) throw NotesException("Note deja active");
        else if(it.current().getStatutSupp())
        {
            it.current().changeSupp();
            NoteList->addItem(id);
         }
        else //note archivee
        {
            it.current().setActive();
            NoteList->addItem(id);

            QList<QListWidgetItem*> temp=NoteListArchive->findItems(id,0);
            QStringList stringList;
            foreach( QListWidgetItem *item, temp )
                stringList << item->text();
            QListWidget ui;
            ui.addItems(stringList);
            unsigned int row=0;
            while(ui.item(row)->text()!=id) {row++;}
            QListWidgetItem* i= NoteListArchive->item(row);//trouver moyen de recuperer le QListWidgetItem grace a l'id;
            delete i;
        }

}

void MainWindow::fenRelation()
{
    WindowRelation* fen= new WindowRelation(this);
    fen->show();
}
