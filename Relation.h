#ifndef RELATION_H_INCLUDED
#define RELATION_H_INCLUDED
#include <ctime>
#include <QString>
#include "RelationManager.h"

class RelationException{
public:
    RelationException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

class Relation{
    friend class RelationManager;
    QString titre;
    QString description;
    bool orientee;
    Relation():orientee(True){} //constructeur sans argument, orientee vrai par défaut
    ~Relation();
    void SeeRelation();
    Relation(Relation& r);
    
    public :
    QString getTitre(){return titre;}
    QString getDesc(){return description;}
    bool getOrient(){return orientee;}
};

#endif // RELATION_H_INCLUDED
