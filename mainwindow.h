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
#include <QFileDialog>
#include<QTreeWidget>
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

    QWidget *zoneCentrale; /**< widget de la zone centrale */
    QDockWidget *zoneGauche;  /**< dock gauche */
    QDockWidget *zoneDroite; /**< Dock droit */

    QLineEdit *idNote;   /**< Line edit pour l'id de la note */
    QLineEdit *titreNote;  /**< Line edit pour le titre de la note */
    QDateTimeEdit *dateCreaNote;  /**< DateTime edit pour la date de création de la note */
    QDateTimeEdit *dateModifNote;  /**< DateTime edit pour la date de derniere modification de la note */
    QTextEdit *contenuNote;  /**< Texte edit pour l'ensemble des caractéristiques de la note */

    QLabel *NoteList_l;   /**< Titre de la liste des notes */
    QLabel *TacheList_l;  /**< Titre de la liste des taches */
    QLabel *NoteListArchive_l;  /**< Titre de la liste des notes archivées */
    QListWidget *NoteList;  /**< liste des notes */
    QListWidget *TacheList;  /**< liste des taches */
    QListWidget *NoteListArchive;  /**< liste des notes archivees */
    QTreeWidget *NoteAbrFils;  /**< arbre des successeurs */
    QTreeWidget *NoteAbrPeres;  /**< arbre des prédecesseurs */

    QPushButton *enregistrer;  /**< bouton enregistrer */

    QPushButton *creer;   /**< bouton creer */
    QPushButton *supprimer;   /**< bouton supprimer */
    QPushButton *editer;   /**< bouton editer */
    QPushButton *restaurer;   /**< bouton restaurer */
    QPushButton *boutonQuitter;   /**< bouton quitter */
    QPushButton *restaurerVersion;   /**< bouton restaurer version */

    QFormLayout *layoutAffich;    /**< Layout pour l'affichage d'une note */
    QVBoxLayout *layoutAffichage;  /**< Layout vertical pour l'affichage d'une note */
    QVBoxLayout *layoutList;  /**< Layout vertical pour l'affichage des listes */
    QVBoxLayout *layoutPrincipal;  /**< Layout vertical pour l'affichage de toute la fenêtre principale */

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
    /**
     * @brief afficherNote
     * affiche la note sélectionnée
     *  @param id de la note à afficher
     */
    void afficherNote(QString id);

signals:

public slots:
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
     * @brief slot afficherNote
     * affiche la note sélectionnée depuis les liste à gauche
     */
    void afficherNote(QListWidgetItem* item);
    /**
     * @brief slot afficherNote
     * affiche la vesrion sélectionnée depuis l'arborescence
     */
    void afficherNote(QTreeWidgetItem* item);
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
     * @brief slot RestaurerV
     * Permet de choisir la version à restaurer et la restaure
     */
    void RestaurerV();
     /**
     * @brief slot arborescencefils
     * affiche les descendants de la note selectionnee
     */
    void arborescencefils(QListWidgetItem* item);
    /**
     * @brief slot arborescencePeres
     * affiche les ascendants de la note selectionnee
     */
    void arborescencePeres(QListWidgetItem* item);
};


#endif // MAINWINDOW_H
