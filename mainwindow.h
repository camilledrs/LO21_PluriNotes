#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QFormLayout>
#include <QLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QDockWidget>
#include <QTabWidget>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMdiArea>
#include <QListWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QComboBox>
#include "notemanager.h"
#include "windowrelation.h"
#include "note.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWidget *zoneCentrale;
    QDockWidget *zoneGauche;
    QDockWidget *zoneDroite;

    //QLineEdit *idNote;
    QLineEdit *titreNote;
    QDateTimeEdit *dateCreaNote;
    QTextEdit *contenuNote;


    /*QTextEdit *texteNote;
    QLineEdit *actionNote;
    QLineEdit *descriptionNote;
    QLineEdit *fichier;*/


    QPushButton *enregistrer;

    QPushButton *creer;
    QPushButton *supprimer;
    QPushButton *editer;
    QPushButton *restaurer;
    QPushButton *archiver;
    QPushButton *boutonQuitter;

    QLineEdit *idNote ;
    QPushButton *boutonAfficher;
    QPushButton *boutonRestaurer;

    QFormLayout *layoutAffich;
    QVBoxLayout *layoutAffichage;
    QFormLayout *layout;
    QVBoxLayout *layoutRecherche;
    QVBoxLayout *layoutPrincipal;

public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
    //void articleNote();
    //void tacheNote();
    //void mediaNote();

    void Recherche();
    void nouvelleFen();
    void viderLaCorbeille(){NoteManager::getInstance().viderCorbeille();}
    void quitter();
    void Restaurer();
    void afficherNote(QListWidgetItem* item);
    void creerNote();
    void supprimerNote();
    void editerNote();
    void restaurerNote();
    void archiverNote();
};

class fenetreCreationNote : public QWidget
{
    QLineEdit *idNote;
    QLineEdit *titreNote;
    QDateTimeEdit *dateCreaNote;
public:
    fenetreCreationNote();
};

class CreateNoteWidget : public QWidget {
    Q_OBJECT
private:
    /* Labels */
    QLabel *id_l;
    QLabel *titre_l;
    QLabel *type_l;
    /* Zones de saisies */
    QLineEdit *id_t;
    QLineEdit *titre_t;
    QComboBox *type_t;
    /* Boutons */
    QPushButton *ok_b;
    QPushButton *cancel_b;
    /* Layouts */
    QHBoxLayout *id_hbox;
    QHBoxLayout *titre_hbox;
    QHBoxLayout *type_hbox;
    QHBoxLayout *buttons_hbox;
    QVBoxLayout *fenetre_vbox;

public:
    CreateNoteWidget();

public slots:
    void createNote();
};

#endif // MAINWINDOW_H
