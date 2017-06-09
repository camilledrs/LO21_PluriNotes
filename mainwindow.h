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
    QListWidget *NoteList;


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
    void readSettings();
    void writeSettings();

signals:

public slots:
    //void articleNote();
    //void tacheNote();
    //void mediaNote();

    void Recherche();
    void nouvelleFen();
    void fenRelation();
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
    QString getId(){return idNote->text();}
};

class CreateNoteWidget : public QWidget {
    Q_OBJECT
private:
    /* Labels */
    QLabel *id_l;
    QLabel *titre_l;
    QLabel *type_l;
    QLabel *texte_l;
    QLabel *statut_l;
    QLabel *action_l;
    QLabel *dateTache_l;
    QLabel *priorite_l;
    QLabel *description_l;
    QLabel *typeM_l;
    QLabel *fichier_l;
    /* Zones de saisies */
    QLineEdit *id_t;
    QLineEdit *titre_t;
    QComboBox *type_t;
    QTextEdit *texte_t;
    QComboBox *statut_t;
    QLineEdit *action_t;
    QDateTimeEdit *dateTache_t;
    QLineEdit *priorite_t;
    QLineEdit *description_t;
    QComboBox *typeM_t;
    QLineEdit *fichier_t;
    /* Boutons */
    QPushButton *ok_b;
    QPushButton *cancel_b;
    /* Layouts */
    QHBoxLayout *id_hbox;
    QHBoxLayout *titre_hbox;
    QHBoxLayout *type_hbox;
    QHBoxLayout *texte_hbox;
    QHBoxLayout *statut_hbox;
    QHBoxLayout *action_hbox;
    QHBoxLayout *dateTache_hbox;
    QHBoxLayout *priorite_hbox;
    QHBoxLayout *description_hbox;
    QHBoxLayout *typeM_hbox;
    QHBoxLayout *fichier_hbox;
    QHBoxLayout *buttons_hbox;
    QVBoxLayout *fenetre_vbox;

public:
    CreateNoteWidget();
    QString getId()const {return id_t->text();}

public slots:
    QString createNote(QString type);
    QString createContenuNote(QString type);
};

#endif // MAINWINDOW_H
