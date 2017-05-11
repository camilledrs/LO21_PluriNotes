#ifndef RELATION_H_INCLUDED
#define RELATION_H_INCLUDED
#include <ctime>
#include <QString>
#include "RelationManager.h"
#include "Couple.h"

class RelationException{
public:
    RelationException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

class Relation{
    friend class RelationManager;
    Couple **tab;
    int nb;
    int max;
    QString titre;
    QString description;
    bool orientee;
    Relation():orientee(True){} //constructeur sans argument, orientee vrai par défaut
    ~Relation() {delete[] tab;}
    void SeeRelation(); //utiliser un const_iterator pour avoir un accès en lecture ?
    Relation(Relation& r);
    Relation& operator=(Relation& r);
    
    public :
    QString getTitre() const {return titre;}
    QString getDesc() const {return description;}
    bool getOrient()const {return orientee;}
    void addCouple(const Couple& c);
    void Editer(); //à voir
};

#endif // RELATION_H_INCLUDED
