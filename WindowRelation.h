#ifndef WINDOWRELATION_H
#define WINDOWRELATION_H

#include <QApplication>
#include "relationmanager.h"
#include "notemanager.h"
#include <QMainWindow>
#include <QListWidgetItem>
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QDockWidget>
#include <QInputDialog>
#include <QMessageBox>
#include <QTabWidget> //pour les onglet


/**
 * @brief La classe WindowRelation
 * gère les relations et les affichages de celles ci
 */
class WindowRelation : public QMainWindow //public QTabWidget
{
        Q_OBJECT

    QWidget *zoneCentraleRel;
    QDockWidget *zoneGaucheRel;

    QLineEdit *Titre;
    QLineEdit *Desc;
    QListWidget *RelationList;
    QTextEdit *contenuRelation;

    QPushButton* boutonCreer;
    QPushButton* boutonEditer;
    QPushButton* boutonSupprimer;
    QPushButton* boutonEnrichir;
    QPushButton *boutonSupprimerCouple;
    QPushButton *boutonQuitter;

    //QFormLayout *layoutRel;
    QVBoxLayout* layoutPrincipalRel;
    //QHBoxLayout* layoutBouttons;

    public:
    /**
         * @brief constructeur de WindowRelation
         * @param parent qui prend le widget parent (la fenetre mainwindow dans notre cas)
         */
        explicit WindowRelation(QWidget *parent = 0);
    /**
     * @brief readSettingsRel
     * récupère les settings de la dernière utilisation de l'application
     */
    void readSettingsRel();
    /**
     * @brief writeSettingsRel
     * Sauvegarde l'état de l'application, au moment de quitter celle ci
     */
    void writeSettingsRel();

    public slots:
    /**
         * @brief slot Creer
         * cree une nouvelle relation
         */
        void Creer();
        /**
         * @brief slot ajouterCouple
         * ajoute un couple à la relation actuellement affichée en zone centrale
         */
        void ajouterCouple();
        /**
         * @brief slot Supprimer
         * Supprime la relation actuellement affichee
         */
        void Supprimer();
        /**
         * @brief slot seeRelation
         * @param i le QListWidgetItem sélectionné
         * affiche la relation sélectionnée
         */
        void seeRelation(QListWidgetItem* i);
        /**
         * @brief slot Editer
         * Edite la relation actuellement affichée
         */
        void Editer();
        /**
         * @brief slot supprimerCouple
         * supprime un couple à la relation actuellement affichée en zone centrale
         */
        void supprimerCouple();
};


#endif

