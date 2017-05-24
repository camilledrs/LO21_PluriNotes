#ifndef RELATION_H_INCLUDED
#define RELATION_H_INCLUDED
#include <ctime>
#include <QString>
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
    Relation(QString t, Qstring d):orientee(True), titre(t), description(d), nb(0), max(0), tab(null){}
    ~Relation() {
                    for (unsigned int i=0; i<nb; i++) delete tab[i]; 
                    delete[] tab;
                }
    void SeeRelation(); 
    Relation(Relation& r);
    Relation& operator=(Relation& r);
    setTitre(QString newt){titre=newt;}
    setDesc(QString newd){description=newd;}
    void Editer(); //à voir
 /*J'ai mis la classe const_iterator en privée car je ne veux qu'on y ai accès que 
 grâce à la méthode public seeRelation()
 A discuter */
    
        class const_iterator {
        friend class Relation;
        const Couple * courant;
        const_iterator(const Couple* deb):courant(deb){}
        
      public :
        const_iterator():courant(0){}
        const Couple& operator*() const {return *courant;}
        const_iterator& operator++(){++courant; return *this;}
        const_it operator operator++(int) {const_iterator old=*this; ++courant; return old;}
        bool operator==(const_iterator it) const {return courant==it.courant;}
        bool operator!=(const_iterator it) const {return courant!=it.courant;}
    };
    const_iterator begin() const {return const_iterator(tab);}
    const_iterator end() const {return const_iterator(tab+nb);}
    
    
    QString getTitre() const {return titre;}
    QString getDesc() const {return description;}
    bool getOrient()const {return orientee;}
    void addCouple(const Note& n1, const Note& n2, int l); 
    void suppCouple(const Couple& c); //pas plutôt const Couple& c en argument ?
    int getnb(){return nb;}
       
};

#endif // RELATION_H_INCLUDED
