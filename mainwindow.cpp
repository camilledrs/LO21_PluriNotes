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
    archiver = new QPushButton("Archiver");
    QObject::connect(archiver,SIGNAL(clicked()),this,SLOT(archiverNote()));

    QHBoxLayout* layoutBouton = new QHBoxLayout;
    layoutBouton->addWidget(creer);
    layoutBouton->addWidget(supprimer);
    layoutBouton->addWidget(editer);
    layoutBouton->addWidget(restaurer);
    layoutBouton->addWidget(archiver);

    layoutAffich = new QFormLayout;
    layoutAffich->addRow("Id", idNote);
    layoutAffich->addRow("Titre", titreNote);
    layoutAffich->addRow("Date de création", dateCreaNote);

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


CreateNoteWidget::CreateNoteWidget()
{
    id_l = new QLabel("ID : ");
    titre_l = new QLabel("Titre : ");
    type_l = new QLabel("Type : ");

    id_t = new QLineEdit();
    titre_t = new QLineEdit();
    type_t = new QComboBox();

    ok_b = new QPushButton("OK");
    cancel_b = new QPushButton("Annuler");

    id_hbox = new QHBoxLayout();
    titre_hbox = new QHBoxLayout();
    type_hbox = new QHBoxLayout();
    buttons_hbox = new QHBoxLayout();
    fenetre_vbox = new QVBoxLayout();

    id_hbox->addWidget(id_l);
    id_hbox->addWidget(id_t);
    titre_hbox->addWidget(titre_l);
    titre_hbox->addWidget(titre_t);
    type_hbox->addWidget(type_l);
    type_hbox->addWidget(type_t);
    buttons_hbox->addWidget(ok_b);
    buttons_hbox->addWidget(cancel_b);

    fenetre_vbox->addLayout(id_hbox);
    fenetre_vbox->addLayout(titre_hbox);
    fenetre_vbox->addLayout(type_hbox);
    fenetre_vbox->addLayout(buttons_hbox);

    this->setLayout(fenetre_vbox);

    type_t->addItem("Article");
    type_t->addItem("Tache");
    type_t->addItem("Média");

    QObject::connect(ok_b,SIGNAL(clicked()),this,SLOT(createContenuNote()));
    QObject::connect(cancel_b,SIGNAL(clicked()),this,SLOT(close()));

    this->setWindowModality(Qt::ApplicationModal);
}

/////
void CreateNoteWidget::createContenuNote()
{
    close();
    fenetre = new QWidget();
    QString type=type_t->currentText();
    if (type == "Article")
    {
        texte_l = new QLabel("Texte :");
        texte_t = new QTextEdit();

        ok2_b = new QPushButton("OK");
        cancel2_b = new QPushButton("Annuler");

        texte_hbox = new QHBoxLayout();
        buttons2_hbox = new QHBoxLayout();
        fenetre_contenubox = new QVBoxLayout();

        texte_hbox->addWidget(texte_l);
        texte_hbox->addWidget(texte_t);
        buttons2_hbox->addWidget(ok2_b);
        buttons2_hbox->addWidget(cancel2_b);

        fenetre_contenubox->addLayout(texte_hbox);
        fenetre_contenubox->addLayout(buttons2_hbox);
    }
    else
        if (type == "Tache")
        {
            statut_l = new QLabel("Statut :");
            action_l = new QLabel("Action :");
            priorite_l = new QLabel("Priorité :");
            dateTache_l = new QLabel("Date de fin :");

            statut_t = new QComboBox();
            action_t = new QLineEdit();
            priorite_t = new QLineEdit();
            dateTache_t = new QDateTimeEdit();

            ok2_b = new QPushButton("OK");
            cancel2_b = new QPushButton("Annuler");

            statut_hbox = new QHBoxLayout();
            action_hbox = new QHBoxLayout();
            priorite_hbox = new QHBoxLayout();
            dateTache_hbox = new QHBoxLayout();
            buttons2_hbox = new QHBoxLayout();
            fenetre_contenubox = new QVBoxLayout();

            statut_hbox->addWidget(statut_l);
            statut_hbox->addWidget(statut_t);
            action_hbox->addWidget(action_l);
            action_hbox->addWidget(action_t);
            priorite_hbox->addWidget(priorite_l);
            priorite_hbox->addWidget(priorite_t);
            dateTache_hbox->addWidget(dateTache_l);
            dateTache_hbox->addWidget(dateTache_t);
            buttons2_hbox->addWidget(ok2_b);
            buttons2_hbox->addWidget(cancel2_b);

            fenetre_contenubox->addLayout(statut_hbox);
            fenetre_contenubox->addLayout(action_hbox);
            fenetre_contenubox->addLayout(priorite_hbox);
            fenetre_contenubox->addLayout(dateTache_hbox);
            fenetre_contenubox->addLayout(buttons2_hbox);

            statut_t->addItem("En cours");
            statut_t->addItem("En attente");
            statut_t->addItem("Terminée");
        }
        else
            if (type == "Média")
            {
                description_l = new QLabel("Description :");
                fichier_l = new QLabel("Fichier :");
                typeM_l = new QLabel("Type de média :");

                description_t = new QLineEdit();
                fichier_t = new QLineEdit();
                typeM_t = new QComboBox();

                ok2_b = new QPushButton("OK");
                cancel2_b = new QPushButton("Annuler");

                description_hbox = new QHBoxLayout();
                fichier_hbox = new QHBoxLayout();
                typeM_hbox = new QHBoxLayout();
                buttons2_hbox = new QHBoxLayout();
                fenetre_contenubox = new QVBoxLayout();

                description_hbox->addWidget(description_l);
                description_hbox->addWidget(description_t);
                fichier_hbox->addWidget(fichier_l);
                fichier_hbox->addWidget(fichier_t);
                typeM_hbox->addWidget(typeM_l);
                typeM_hbox->addWidget(typeM_t);
                buttons2_hbox->addWidget(ok2_b);
                buttons2_hbox->addWidget(cancel2_b);

                fenetre_contenubox->addLayout(description_hbox);
                fenetre_contenubox->addLayout(fichier_hbox);
                fenetre_contenubox->addLayout(typeM_hbox);
                fenetre_contenubox->addLayout(buttons2_hbox);

                typeM_t->addItem("Image");
                typeM_t->addItem("Audio");
                typeM_t->addItem("Vidéo");
            }

    fenetre->setLayout(fenetre_contenubox);
    fenetre->show();

    QObject::connect(ok2_b,SIGNAL(clicked()),this,SLOT(createNote()));
    QObject::connect(cancel_b,SIGNAL(clicked()),fenetre,SLOT(close()));

    //fenetre->setWindowModality(Qt::ApplicationModal);
}
///////

QString CreateNoteWidget::createNote()
{
    QMessageBox::information(this, "OK", "ID ok,"+type_t->currentText());
    fenetre->close();
    //if(id_t->text()!="") {
        try
        {
            QString type=typeM_t->currentText();
            if (type == "Article")
            {
                NoteManager::getInstance().addNote(id_t->text(),titre_t->text(),QDateTime::currentDateTime(),QDateTime::currentDateTime(),Article(QDateTime::currentDateTime(),texte_t->toPlainText()));
                QMessageBox::information(this, "OK", "ID ok,"+type_t->currentText());
                //MainWindow::getMainWindow().openNote(id_t->text());
                close();
            }
            else
                if (type == "Tache")
                {
                    bool ok = false;
                    int nombre = priorite_t->text().toInt(&ok, 10);
                    NoteManager::getInstance().addNote(id_t->text(), titre_t->text(),QDateTime::currentDateTime(),QDateTime::currentDateTime(),Tache(QDateTime::currentDateTime(),action_t->text(),dateTache_t->dateTime(),nombre));
                    QMessageBox::information(this, "OK", "ID ok,"+type_t->currentText());
                    //MainWindow::getMainWindow().openNote(id_t->text());
                    close();
                }
                else  //faire des radiobutton pour avoir le type de multimedia, sinon c'est trop compliqué
                    {
                        if (type_t->currentText() == "Image")
                            NoteManager::getInstance().addNote(id_t->text(),titre_t->text(),QDateTime::currentDateTime(),QDateTime::currentDateTime(),Multimedia(QDateTime::currentDateTime(),description_t->text(),fichier_t->text(),image));
                        if (type_t->currentText() == "Vidéo")
                            NoteManager::getInstance().addNote(id_t->text(),titre_t->text(),QDateTime::currentDateTime(),QDateTime::currentDateTime(),Multimedia(QDateTime::currentDateTime(),description_t->text(),fichier_t->text(),video));
                        if (type_t->currentText() == "Audio")
                            NoteManager::getInstance().addNote(id_t->text(),titre_t->text(),QDateTime::currentDateTime(),QDateTime::currentDateTime(),Multimedia(QDateTime::currentDateTime(),description_t->text(),fichier_t->text(),audio));
                        QMessageBox::information(this, "OK", "ID ok,"+type_t->currentText());
                        //MainWindow::getMainWindow().openNote(id_t->text());
                        close();
                    }
            /*NoteManager::getInstance().addNote(id_t->text(),titre_t->text());
            QMessageBox::information(this, "OK", "ID ok,"+type_t->currentText());
            //MainWindow::getMainWindow().openNote(id_t->text());
            close();*/
        }
        catch (NoteException& e)
        {
            QMessageBox::information(this,"Erreur",e.getInfo());
        }
        return id_t->text();
    /*}
    else
        QMessageBox::information(this, "Erreur", "Vous devez entrer un id !");*/
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
    writeSettings();
    QApplication::quit();
}



//void MainWindow::RestaurerV()
//{
  //  Note::restaurer(/*chercher la version en question*/);
   // boutonRestaurer->setEnabled(False);
//}


void MainWindow::Restaurer()
{

}

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
    QMessageBox::information(this, "OK", "ok");
    while(it.current().getId() != id) it.next(); //on a trouvé la note
    Note& n=it.current();
    titreNote->setText(n.getTitre());
    dateCreaNote->setDateTime(n.getDate());
    contenuNote->setText(n.getDerniereVersion().afficher());
}


fenetreCreationNote::fenetreCreationNote()
{
    idNote = new QLineEdit;
    titreNote = new QLineEdit;
    dateCreaNote = new QDateTimeEdit;
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(idNote);
    layout->addWidget(titreNote);
    layout->addWidget(dateCreaNote);
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
        //if (item=="Article")*/
    //QMessageBox::StandardButton reponse= QMessageBox::question(this,"OK", "ça marche",QMessageBox::Yes | QMessageBox::No);
    CreateNoteWidget *cw = new CreateNoteWidget();
    cw->show();
    NoteList->addItem(cw->getId());
    //On crée bien un nouvel item mais l'id n'est pas récupéré
}


void MainWindow::supprimerNote()
{
    //retrouver le QListWidgetItem i correspondant dans NoteListe grace à l'id
    //mettre l'attribut supprime à true
    //delete i
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
}

void MainWindow::archiverNote()
{
    //retrouver le QListWidgetItem i correspondant dans NoteListe grace à l'id
    //mettre active à false
    //delete i
    //NoteListeArchive->addItem(id)
}

void MainWindow::fenRelation()
{
    WindowRelation* fen= new WindowRelation(this);

    fen->show();
}
