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

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWidget *zoneCentrale;
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
};

#endif // MAINWINDOW_H
