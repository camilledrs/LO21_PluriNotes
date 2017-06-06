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
#include <QMenu>
#include <QAction>
#include <QMdiArea>
#include <QDateTimeEdit>
#include "notemanager.h"
#include "windowrelation.h"
#include "note.h"

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
    void Recherche();
    void nouvelleFen();
    void viderLaCorbeille(){NoteManager::getInstance().viderCorbeille();}
    void quitter();
    void Restaurer();
};

#endif // MAINWINDOW_H
