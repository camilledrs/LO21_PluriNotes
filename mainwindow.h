#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QDockWidget>
#include <QTabWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWidget *zoneCentrale;
    QDockWidget *zoneGauche;
    QDockWidget *zoneDroite;

    QLineEdit *titreNote;
    QLineEdit *dateCreaNote;
    QTextEdit *contenuNote;
    QPushButton *enregistrer;

    QLineEdit *idNote ;
    QPushButton *boutonAfficher;

    QFormLayout *layoutAffich;
    QVBoxLayout *layoutAffichage;
    QFormLayout *layout;
    QVBoxLayout *layoutRecherche;
    QVBoxLayout *layoutPrincipal;

public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
    void Recherche();
    void nouvelleFen();
    void viderLaCorbeille(){NoteManager::getInstance->viderCorbeille();}
    void quitter();
};

#endif // MAINWINDOW_H
