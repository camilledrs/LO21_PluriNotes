#include "mainwindow.h"
#include "fensecondaire.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//NoteManager::getInstance().load();
     //RelationManager::getInstance().load();
    
    MainWindow fenetre;
    fenetre.show();
//NoteManager::getInstance().save();
    return app.exec();
  
    
}
