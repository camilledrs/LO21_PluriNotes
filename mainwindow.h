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

/**
 * @brief La classe MainWindow
 * gère les notes et permet de passer à la fenetre de gestion des relations
 */
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
    /**
     * @brief constructeur de MainWindow
     * @param parent égal à 0 par défaut
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief readSettings
     * restaure les paramètres de avant la dernière fermeture de l'application
     */
    void readSettings();
    /**
     * @brief writeSettings
     * sauvegarde les paramètres de l'application avant de quitter
     */
    void writeSettings();

signals:

public slots:
    //void articleNote();
    //void tacheNote();
    //void mediaNote();
    /**
     * @brief slot Recherche
     */
    void Recherche();
    /**
     * @brief slot nouvelleFen
     * Ouvre une fenetre vide
     */
    void nouvelleFen();
    /**
     * @brief slot fenRelation
     * Ouvre la fenetre gérant les relations
     */
    void fenRelation();
    /**
     * @brief slot viderLaCorbeille
     * vide la corbeille
     */
    void viderLaCorbeille(){NoteManager::getInstance().viderCorbeille();}
    /**
     * @brief slot quitter
     * demande à l'utilisateur si il souhaite vider la corbeille, puis quitte l'application
     */
    void quitter();
    /**
     * @brief slot Restaurer
     * restaure la vesrion sélectionnée
     */
    void Restaurer();
    /**
     * @brief slot afficherNote
     * @param item le QListWidget sélectionné
     * affiche la note dans la zone centrale
     */
    void afficherNote(QListWidgetItem* item);
    /**
     * @brief slot creerNote
     * cree une nouvelle note
     */
    void creerNote();
    /**
     * @brief slot supprimerNote
     * supprime la note actuellement affichée
     */
    void supprimerNote();
    /**
     * @brief slot editerNote
     * Edite la note actuellement affichée
     */
    void editerNote();
    /**
     * @brief slot restaurerNote
     * Rend la note active si celle ci était supprimée ou archivée
     */
    void restaurerNote();  //problème : on n'affiche plus les notes supprimées je crois
    /**
     * @brief slot archiverNote
     * Archive la note actuellement affichée
     */
    void archiverNote();
};


/**
 * @brief La classe fenetreCreationNote
 */
class fenetreCreationNote : public QWidget
{
    QLineEdit *idNote;
    QLineEdit *titreNote;
    QDateTimeEdit *dateCreaNote;
public:
    /**
     * @brief constructeur de fenetreCreationNote
     */
    fenetreCreationNote();
    /**
     * @brief accesseur getId
     * @return l'id de la note rentré dans le champs idNote
     */
    QString getId(){return idNote->text();}
};

/**
 * @brief La classe CreateNoteWidget
 */
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
    QPushButton *ok2_b;
    QPushButton *cancel2_b;
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
    QHBoxLayout *buttons2_hbox;
    QVBoxLayout *fenetre_vbox;
    QVBoxLayout *fenetre_contenubox;

    QWidget *fenetre;

public:
    /**
     * @brief constructeur de CreateNoteWidget
     */
    CreateNoteWidget();
    /**
     * @brief accesseur getId
     * @return le texte entré dans le champ id_t
     */
    QString getId()const {return id_t->text();}

public slots:
    /**
     * @brief slot createNote
     * @param type un QString correspondant au type de la note
     * @return le texte rentré dans le champ id_t
     */
    QString createNote();
    /**
     * @brief slot createContenuNote
     * @param type QString correspondant au type de note à créer
     */
    void createContenuNote();
};

#endif // MAINWINDOW_H
