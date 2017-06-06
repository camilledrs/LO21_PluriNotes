#ifndef VERSION_H
#define VERSION_H

#include <ctime>
#include <QString>
#include <QtXml>
#include <QFile>
#include <QTextCodec>
//#include "note.h"

/**
 * @brief la Classe Version
 * Une version peut être un Article, un objet Multimedia ou une Tache
 */
class Version
{
    QDateTime date; /**< attribut de type QDateTime */
    friend class Note;
    /**
     * @brief constructeur par recopie de Version
     */
    Version(const Version&);
    /**
     * @brief methode clone
     * methode virtuelle pure, utile pour le design pattern factory method
     */
    virtual Version* clone()const=0;



public :
    /**
     * @brief accesseur getDate
     * @return un QDateTime correspondant à la date de la version
     */
    QDateTime getDate()const{return date;}
    /**
     * @brief constructeur de Version
     * @param d un QDateTime correspondant à la date de création de la version
     */
    Version(QDateTime d):date(d){}
    /**
     * @brief destructeur virtuel pur de ~Version
     */
    virtual ~Version()=0;
    /**
     * @brief methode save
     * methode virtuelle pure, utile pour le design pattern factory method
     * @param l'adresse d'un QFile, fichier ou on va sauvegarder les versions
     */
    virtual void save(QFile* f) const=0;

};

/**
 * @brief La classe Article
 * Herite de la classe virtuelle Version
 */
class Article : public Version
{
    QString texte; /**< Attribut texte de type QString */
    /**
     * @brief constructeur de Article
     * @param d de type QDateTime, date de création de l'article
     * @param s de type QString
     */
    Article(QDateTime d,const QString& s):Version(d),texte(s){}
    /**
     * @brief constructeur par recopie de Article
     */
    Article(const Article&);
    /**
      @brief destructeur de Article
      */
    ~Article();
    /**
     * @brief methode clone
     * @return un objet pointeur d'Article cloné de l'article
     */
    Article* clone()const{return new Article(*this);}
    /**
     * @brief methode save
     * @param l'adresse d'un QFile, fichier ou on va sauvegarder les versions
     */
    void save(QFile* f) const {QXmlStreamWriter stream(f);
                               stream.writeStartElement("article");
                               stream.writeTextElement("date version",getDate().toString());
                               stream.writeTextElement("texte",texte );
                              }

};

/**
 * Enumeration Statut
 * Statuts possibles d'une Tache
 */
enum Statut{EnAttente, /**< Enum value EnAttente. */
            EnCours, /**< Enum value EnCours. */
            Terminee /**< Enum value Terminee. */
           };

/**
 * @brief La classe Tache
 * herite de la classe virtuelle Version
 */
class Tache : public Version
{
    QString action; /**< attribut de type QString */
    Statut statut; /**< statut de la tache, de type enum Statut*/
    QDateTime dateTache; /**< attribut QDateTime de la date de la tache */
    unsigned int priorite; /**< entier, priorité de la tache */
    /**
      @brief destructeur de Tache
      */
    ~Tache();
    /**
     * @brief constructeur de Tache
     * Une tache est initialement en attente
     * @param dv un QDateTime (date de création de la version)
     * @param a Qstring (action)
     * @param d QdateTime(date de la tache)
     * @param p entier (priorité)
     */
    Tache(QDateTime dv,const QString a, QDateTime d, unsigned int p=0) :Version(dv),action(a), statut(EnAttente), dateTache(d), priorite(p){} // en privé pour qu'une tache ne puisse être construite que par une classe friend
    /**
     * @brief constructeur par recopie de Tache
     */
    Tache(const Tache&);
    /**
     * @brief methode clone
     * @return un pointeur de Tache sur le clone de la tache
     */
    Tache* clone()const{return new Tache(*this);}//a voir si prive ou public
    /**
     * @brief methode save
     * @param l'adresse d'un QFile, fichier ou on va sauvegarder les versions
     */
    void save(QFile* f) const {    QXmlStreamWriter stream(f);
                                   stream.writeStartElement("tache");
                                   stream.writeTextElement("date version",getDate().toString());
                                   stream.writeTextElement("action",action );
                                   //stream.writeTextElement("statut",statut );
                                   stream.writeTextElement("date tache",dateTache.toString() );
                                   stream.writeTextElement("priorite",QString::number(priorite) );
                              }

public :
    /**
     * @brief accesseur getAction
     * @return un QString, l'action de la tache
     */
    QString getAction(){return action;}
    /**
     * @brief accesseur getStatut
     * @return un objet de type enum Statut
     */
    Statut getStatut(){return statut;}
    /**
     * @brief accesseur getPriority
     * @return un entier, la priorité de la tache
     */
    unsigned int getPriority(){return priorite;}
    /**
     * @brief accesseur getDate
     * @return un QDateTime, la date de la tache
     */
    QDateTime getDateT() const{return dateTache;}

};

/**
 * Enumeration Media
 * différents types de multimedias possibles
 */
enum Media {image, /**< Enum value image.*/
            audio, /**< Enum value audio. */
            video  /**< Enum value video. */
           };


/**
 * @brief la classe Multimedia
 * herite de la classe abstraite Version
 */
class Multimedia : public Version
{
    QString description; /**< attribut QString, description du multimedia */
    QString fichier; /**< QString, nom du fichier */
    Media type; /**< de type enum Media, type de multimedia */
    /**
      @brief destructeur de Multimedia
      */
    ~Multimedia();
    /**
     * @brief constructeur de Multimedia
     * @param dv QDateTime date de la version
     * @param d QString (description)
     * @param f const QString& (nom du fichier)
     * @param t enum Media (type)
     */
    Multimedia(QDateTime dv,const QString& d, const QString& f, Media t):Version(dv),description(d), fichier(f), type(t){}
    /**
     * @brief constructeur par recopie de Multimedia
     */
    Multimedia(const Multimedia&);
    /**
     * @brief methode clone
     * @return un pointeur sur un objet Multimedia, cloné sur l'actuel
     */
    Multimedia* clone()const{return new Multimedia(*this);}
    /**
     * @brief methode save
     * @param l'adresse d'un QFile, fichier ou on va sauvegarder les versions
     */
    void save(QFile* f) const {    QXmlStreamWriter stream(f);
                                   stream.writeStartElement("multimedia");
                                   stream.writeTextElement("date version",getDate().toString());
                                   stream.writeTextElement("description",description );
                                   stream.writeTextElement("fichier",fichier );
                                   //stream.writeTextElement("type",type );
                              }

public :
    /**
     * @brief accesseur getDescription
     * @return un QString, la description du multimedia
     */
    QString getDescription() {return description;}
    /**
     * @brief accesseur getFichier
     * @return un QString, le nom du fichier
     */
    QString getFichier() {return fichier;}
    /**
     * @brief accesseur getType
     * @return un objet de type enum Media, le type de multimedia
     */
    Media getType() {return type;}

};




#endif // VERSION_H
