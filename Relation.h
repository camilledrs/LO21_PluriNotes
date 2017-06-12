#ifndef RELATION_H
#define RELATION_H


#include <ctime>
#include <QString>
#include <QtXml>
#include <QFile>
//#include "relationmanager.h"
#include "couple.h"


/**
 * @brief la classe RelationException
 */
class RelationException
{
    QString info; /**< un Qstring qui sera envoyé lors de la detection d'une exception*/

public:
    /**
     * @brief constructeur de RelationException
     * @param message de type const QString&, le message attribué à l'attribut info
     */
    RelationException(const QString& message):info(message){}
    /**
     * @brief accesseur getInfo
     * @return un QString, l'attribut info
     */
    QString getInfo() const { return info; }
};


/**
 * @brief la Classe Relation
 * Représente des objets Relation
 * gérée par l'unique instance de la classe RelationManager
 */
class Relation
{
    Couple **tab; /**< tableau de pointeurs d'objets Couple, ceux dont il existe une relation entre eux*/
    int nb; /**< entier, nombre de couples stockés dans le tableau tab */
    int max; /**< entier, capacité actuelle du tableau tab */
    QString titre; /**< QString correspondant un titre de la relation */
    QString description; /**< Qstring, description de la relation */
    bool orientee; /**< attribut boolean, à true si la relation esr orientée*/
    /**
     * @brief constructeur de Relation
     * l'attribut orientee est mis à true par défaut
     */
    Relation():orientee(true){}
    /**
      *@brief destructeur de Relation
      * en privé pour que seule l'instance de RelationManager puisse y accéder
      */

    friend class RelationManager;

public :
    /**
     * @brief La classe const_iterator de Relation
     * permet un accès en lecture seulement
     */
    class const_iterator
    {
        friend class Relation;
        Couple ** courant; /**< tableau de couples dans lequel on itère */
        /**
         * @brief constructeur de const_iterator
         * @param deb tableau dans lequel on souhaite itérer
         */
        const_iterator(Couple** deb):courant(deb){}

    public :
        /**
         * @brief contructeur sans argument de const_iterator
         */
        const_iterator():courant(0){}
        /**
         * @brief methode elementCourant
         * @return un pointeur sur le Couple pointé par l'iterator
         */
        const Couple* const elementCourant(){return *courant;}
        /**
         * @brief surcharge de l'operator *
         * @return une reference sur le Couple actuellement pointé
         */
        const Couple& operator*() const {return **courant;}
        /**
         * @brief surcharge de l'operator ++
         * @return l'iterateur sur le couple suivant
         */
        const_iterator& operator++(){++courant; return *this;}
        /**
         * @brief surcharge de l'operator ++
         * @return l'iterateur sur le couple actuel, avant l'incrémentation
         */
        const_iterator& operator++(int) {const_iterator old=*this; ++courant; return old;}
        /**
         * @brief surcharge de l'operator ==
         * @param it l'iterateur avec lequel on compare
         * @return true si les deux couples pointés par chaque iterateur sont les mêmes, false sinon
         */
        bool operator==(const_iterator it) const {return courant==it.courant;}
        /**
         * @brief surcharge de l'operator !=
         * @param it l'iterateur avec lequel on compare
         * @return false si les deux couples pointés par chaque iterateur sont les mêmes, true sinon
         */
        bool operator!=(const_iterator it) const {return courant!=it.courant;}
    };
    /**
     * @brief methode begin
     * @return un objet const_iterator au debut du tableau tab
     */
    const_iterator begin() const {return const_iterator(tab);}
    /**
     * @brief methode elem
     * @param i de type entier
     * @return un objet const_iterator au niveau de tab[i]
     */
    const_iterator elem(int i) const {return const_iterator(tab+i);}
    /**
     * @brief methode end
     * @return un objet const_iterator à la fin du tableau tab
     */
    const_iterator end() const {return const_iterator(tab+nb);}

    /**
     * @brief methode setTitre
     * @param newt le titre que l'on veut, QString
     */
    void setTitre(QString newt){titre=newt;}
    /**
     * @brief methode setDesc
     * @param newd la nouvelle description, de type QString
     */
    void setDesc(QString newd){description=newd;}
    /**
     * @brief methode editer
     * @param t le titre que l'on veut
     * @param d la description que l'on souhaite
     * permet de modifier le titre et/ou la description
     */
    void editer(QString& t, QString& d); //à voir
    /**
     * @brief methode suppCouple
     * @param c reference sur le couple à supprimer
     */
    void suppCouple(Couple& c);
    /**
     * @brief accesseur getTitre
     * @return le QString correspondant à l'attribut titre de la relation
     */
    QString getTitre() const {return titre;}
    /**
     * @brief accesseur getDesc
     * @return la description de la relation
     */
    QString getDesc() const {return description;}
    /**
     * @brief accesseur getOrient
     * @return true si la relation est orientee, false sinon
     */
    bool getOrient()const {return orientee;}
    /**
     * @brief accesseur getnb
     * @return le nombre de Couples stockés dans tab
     */
    int getnb(){return nb;}
    /**
     * @brief methode SeeRelation
     * permet la visualisation de la relation et de ses couples
     */
    void SeeRelation();
    /**
     * @brief methode addCouple
     * le Couple est créé si il n'existe pas encore
     * @param n1 référence sur la première note du couple
     * @param n2 référence sur la seconde note du couple
     * @param l labe du couple
     */
    void addCouple(Note& n1,Note& n2, int l);
    /**
      @brief destructeur de Relation
      */
    ~Relation()
    {
        for (unsigned int i=0; i<nb; i++) delete tab[i];
        delete[] tab;
    }
    /**
     * @brief constructeur pas recopie de Relation
     */
    Relation(Relation& r);
    /**
     * @brief operateur d'affectation de Relation
     */
    Relation& operator=(Relation& r);
    /**
     * @brief constructeur de Relation
     * la relation est orientee par défaut
     * @param t Qstring titre
     * @param d QString description
     */
    Relation(QString t, QString d, bool orient=true):orientee(orient), titre(t), description(d), nb(0), max(0), tab(nullptr){}
    /**
     * @brief sauve les relations dans un fichier xml
     */
    void save(QFile* f) const;

};

#endif // RELATION_H
