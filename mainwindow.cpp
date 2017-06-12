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

    zoneGauche = new QDockWidget;
    zoneGauche->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //zoneGauche->setWidget();
    addDockWidget(Qt::LeftDockWidgetArea, zoneGauche);

    zoneDroite = new QDockWidget;
    zoneDroite->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //zoneDroite->setWidget();
    addDockWidget(Qt::RightDockWidgetArea, zoneDroite);


    ///////////////////////////////////////////////

    QGroupBox *groupbox = new QGroupBox("Type de note", zoneCentrale);

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

    groupbox->setLayout(layoutTypeNote);

    idNote = new QLineEdit;
    titreNote = new QLineEdit;
    dateCreaNote = new QDateTimeEdit(QDateTime::currentDateTime());
    contenuNote = new QTextEdit;
    NoteList = new QListWidget(zoneGauche);

    dateCreaNote->setReadOnly(true);

    creer = new QPushButton("Créer");
    QObject::connect(creer,SIGNAL(clicked()),this,SLOT(creerNote()));
    supprimer = new QPushButton("Supprimer");
    QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(supprimerNote()));
    editer = new QPushButton("Editer");
    QObject::connect(editer,SIGNAL(clicked()),this,SLOT(editerNote()));
    restaurer = new QPushButton("Restaurer");
    QObject::connect(restaurer,SIGNAL(clicked()),this,SLOT(restaurerNote()));


    QHBoxLayout* layoutBouton = new QHBoxLayout;
    layoutBouton->addWidget(creer);
    layoutBouton->addWidget(supprimer);
    layoutBouton->addWidget(editer);
    layoutBouton->addWidget(restaurer);

    layoutAffich = new QFormLayout;
    layoutAffich->addRow("Id", idNote);
    layoutAffich->addRow("Titre", titreNote);
    layoutAffich->addRow("Date de création", dateCreaNote);
    layoutAffich->addRow("Contenu", contenuNote);

    layoutAffichage = new QVBoxLayout;
    layoutAffichage->addLayout(layoutAffich);
    layoutAffichage->addLayout(layoutBouton);

    boutonQuitter = new QPushButton("Quitter");
    QObject::connect(boutonQuitter,SIGNAL(clicked()),this,SLOT(quitter()));

    layoutPrincipal = new QVBoxLayout;
    //layoutPrincipal->addLayout(layoutRecherche);
    layoutPrincipal->addWidget(groupbox);
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

    zoneGauche->setWidget(NoteList);
    addDockWidget(Qt::LeftDockWidgetArea, zoneGauche);

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



//void MainWindow::RestaurerV()
//{
  //  Note::restaurer(/*chercher la version en question*/);
   // boutonRestaurer->setEnabled(False);
//}



void MainWindow::Recherche()
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
}



void MainWindow::afficherNote(QListWidgetItem* item)
{
    QString id= item->text();
    NoteManager::Iterator it=NoteManager::getInstance().getIterator();
    while(it.current().getId() != id) it.next(); //on a trouvé la note
    Note& n=it.current();
    idNote->setText(id);
    titreNote->setText(n.getTitre());
    dateCreaNote->setDateTime(n.getDate());
    contenuNote->setText(n.getDerniereVersion().afficher());

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
        }
    }

    if (type == "Tache")
    {
        bool ok5=false;
        bool ok6=false;
        bool ok7=false;
        QString action = QInputDialog::getText(this, "Action :", "Quelle est l'action de la tache ?", QLineEdit::Normal, QString(), &ok5);
        //QString dateFin = QInputDialog::getText(this, "Date de fin :", "Quelle est la date de fin de la tache (optionnelle) ?", QLineEdit::Normal, QString(), &ok6);
        QString priorite = QInputDialog::getText(this, "Priorité :", "Quelle est la priorité de la tache ? (optionnelle)", QLineEdit::Normal, QString(), &ok7);

        int p=priorite.toInt();
        if (ok1 && ok2 && ok3 && ok5 && /*ok6 &&*/ ok7 && !id.isEmpty() && !titre.isEmpty() && !action.isEmpty())
        {
            NoteManager::getInstance().addNote(id,titre,QDateTime::currentDateTime(),QDateTime::currentDateTime(),Tache(QDateTime::currentDateTime(),action,QDateTime::currentDateTime()/*dateFin*/,p));
            QMessageBox::information(this, "Confirmation creation", "La nouvelle note a bien été créée ! ");
            NoteList->addItem(id);
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

        if (ok1 && ok2 && ok3 && ok8 && ok9 && ok10 && !id.isEmpty() && !titre.isEmpty() && !description.isEmpty() && !fichier.isEmpty())
        {
            if (typeM == "Image")
                NoteManager::getInstance().addNote(id,titre,QDateTime::currentDateTime(),QDateTime::currentDateTime(),Multimedia(QDateTime::currentDateTime(),description,fichier,image));
            if (typeM == "Vidéo")
                NoteManager::getInstance().addNote(id,titre,QDateTime::currentDateTime(),QDateTime::currentDateTime(),Multimedia(QDateTime::currentDateTime(),description,fichier,video));
            if (typeM == "Audio")
                NoteManager::getInstance().addNote(id,titre,QDateTime::currentDateTime(),QDateTime::currentDateTime(),Multimedia(QDateTime::currentDateTime(),description,fichier,audio));
            QMessageBox::information(this, "Confirmation creation", "La nouvelle note a bien été créée ! ");
            NoteList->addItem(id);
        }
    }
}


void MainWindow::supprimerNote()
{
    //retrouver le QListWidgetItem i correspondant dans NoteListe grace à l'id
    //mettre l'attribut supprime à true
    //delete i
    QString id= idNote->text();
    NoteManager::Iterator itn=NoteManager::getInstance().getIterator();
    while((!itn.isDone()) && (id!=itn.current().getId())) itn.next();
    Note& n=itn.current();
    QMessageBox::StandardButton reponse;
    reponse= QMessageBox::question(this,"Confirmation Suppression", "Voulez vous vraiment supprimer la note ?",QMessageBox::Yes | QMessageBox::No);
    if(reponse == QMessageBox::Yes)
       { NoteManager::getInstance().supprimerNote(n);
    delete NoteList->currentItem();
    idNote->setText("");
    titreNote->setText("");
    dateCreaNote->setDateTime(QDateTime::currentDateTime());
    contenuNote->setText("");
    //Dès qu'on aura la liste des notes archivées dans le dock gauche
    //if(!n.getActive()) NoteListArchive->addWidget("id"); //la note etait referencee, elle est maintenant archivee, on l'ajoute dans la liste des archivees
    }
}


void MainWindow::editerNote()
{
    //voir comment j'ai fait pour editerRelation
}


void MainWindow::restaurerNote()
{
    /*
    bool ok;
    QString id = QInputDialog::getText(this, "ID Note a restaurer :", "Entrez l'id de la note à restaurer", QLineEdit::Normal, QString(), &ok);
        NoteManager::Iterator it= NoteManager::getInstance().getIterator();
        while((it.current().getId() != id) && !it.isDone()) it.next();
        if(it.isDone()) throw NotesException("Note non existante");
        else if(it.current().getActive() && !it.current().getStatutSupp()) throw NotesException("Note deja active");
        else if(it.current().getStatutSupp())
        {
            it.current().setSuppFalse();
            NoteList->addItem(id);
         }
        else //note archivee
        {
            it.current().setActive();
            NoteList->addItem(id);
            QListWidgetItem* i= NoteListArchive->//trouver moyen de recuperer le QListWidgetItem grace a l'id;
            delete i;
        }
        */

    /*Copier/coller de ce que j'ai mis comme aide dans le ToDo
     * Pour trouver un QListWidgetItem dans une liste QListWidget simplement grace à l’id:
faireNotesListArchive->findItems(“l’id qu’on cherche”, Qt::MatchFlags MatchExactly);
transformer la liste obtenue en liste de QString :
QStringList stringList;
foreach( QListWidgetItem *item, originalFileList->selectedItems() )
    stringList << item->text();
ui->selectedList->addItems(stringList);
chercher l’id dans la liste
recuperer l’indice
faire NotesListArchive->item(row)
 */
}


void MainWindow::fenRelation()
{
    WindowRelation* fen= new WindowRelation(this);
    fen->show();
}
