#ifndef VERSION_H
#define VERSION_H

#include <ctime>
#include <QString>
#include <QtXml>
#include <QFile>
#include <QTextCodec>
#include <sstream>

/**
 * @brief la Classe Version
 * Une version peut être un Article, un objet Multimedia ou une Tache
 */
class Version
{
    QDateTime date; /**< attribut de type QDateTime */
    friend class NoteManager;
    /**
     * @brief constructeur par recopie de Version
     */
    Version(const Version&);


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
     * @brief destructeur virtuel de ~Version
     */
    ~Version(){}
    /**
     * @brief methode save
     * methode virtuelle pure, utile pour le design pattern factory method
     * @param l'adresse d'un QFile, fichier ou on va sauvegarder les versions
     */
    virtual void save(QFile* f) const=0;
    /**
     * @brief methode clone
     * methode virtuelle pure, utile pour le design pattern factory method
     */
    virtual Version* clone()const=0;

    /**
     * @brief methode afficher
     * methode virtuelle pure, utilisée pour l'affichage d'une note
     * @return un QString composé de l'ensemble des valeurs des attributs particuliers à chaque classe héritant de Version
     */
    virtual QString afficher() const=0;
    /**
     * @brief methode notetype
     * methode virtuelle pure, utilisée pour connaitre le type d'une note
     * @return un QString composé de l'ensemble des valeurs des attributs particuliers à chaque classe héritant de Version
     */
    virtual QString notetype() const=0;
};

/**
 * @brief La classe Article
 * Herite de la classe virtuelle Version
 */
class Article : public Version
{
    QString texte; /**< Attribut texte de type QString */
    /**
     * @brief constructeur par recopie de Article
     */
    Article(const Article& a):Version(a.getDate()),texte(a.texte){}
public:
    /**
     * @brief constructeur de Article
     * @param d de type QDateTime, date de création de l'article
     * @param s de type QString
     */
    Article(QDateTime d,const QString& s):Version(d),texte(s){}
    /**
      @brief destructeur de Article
      */
    ~Article(){}
    /**
     * @brief accesseur getText
     * @return le texte de l'Article
     */
    QString& getText(){return texte;}
    /**
     * @brief methode clone
     * @return un objet pointeur d'Article cloné de l'article
     */
    Article* clone()const{return new Article(*this);}
    /**
     * @brief methode save
     * @param l'adresse d'un QFile, fichier ou on va sauvegarder les versions
     */
    void save(QFile* f) const
    {
        QXmlStreamWriter stream(f);
        stream.writeStartElement("article");
        stream.writeTextElement("date version",getDate().toString());
        stream.writeTextElement("texte",texte );
    }

    /**
     * @brief methode virtuelle afficher
     * @return un QString& composé du texte de l'article
     */
    QString afficher() const
    {
        std::stringstream s;
        s<<"Texte : "<<this->clone()->getText().toStdString();
        return (QString::fromStdString(s.str()));
    }
    /**
     * @brief methode virtuelle type
     * @return un QString& composé du type
     */
    QString notetype()const{return "article";}

};

/**
 * Enumeration Statut
 * Statuts possibles d'une Tache
 */
enum Statut
{
    EnAttente, /**< Enum value EnAttente. */
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
     * @brief constructeur par recopie de Tache
     */
    Tache(const Tache& t):Version(t.getDate()),action(t.action),statut(t.statut),dateTache(t.dateTache),priorite(t.priorite){}
    /**
     * @brief methode clone
     * @return un pointeur de Tache sur le clone de la tache
     */
    Tache* clone()const{return new Tache(*this);}//a voir si prive ou public
    /**
     * @brief methode save
     * @param l'adresse d'un QFile, fichier ou on va sauvegarder les versions
     */
    void save(QFile* f) const
    {
        QXmlStreamWriter stream(f);
        stream.writeStartElement("tache");
        stream.writeTextElement("date version",getDate().toString());
        stream.writeTextElement("action",action );
        stream.writeTextElement("statut",QString::number(statut));
        stream.writeTextElement("date tache",dateTache.toString() );
        stream.writeTextElement("priorite",QString::number(priorite) );
  }

public :
    /**
      @brief destructeur de Tache
      */
    ~Tache(){}
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
     * @brief accesseur getAction
     * @return un QString, l'action de la tache
     */
    QString getAction(){return action;}
    /**
     * @brief accesseur setStatut
     * @param l'indice du nouveau statut
     */
    void setStatut(Statut s){statut=s;}
    /**
     * @brief accesseur getStatut
     * @return un objet de type enum Statut
     */
    std::string getStatut()
    {
        switch(statut){
            case EnAttente :
                return "EnAttente";
                break;
            case EnCours :
                return "EnCours";
                break;
            case Terminee :
                return "Terminee";
                break;
        }
    }
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
    /**
     * @brief methode virtuelle afficher
     * @return un QString& affichant l'action, le statut, la date et la priorité de la tache
     */
    QString afficher() const
    {
        std::stringstream s;
        s<<"Action : "<<this->clone()->getAction().toStdString()<<"\n";
        s<<"Statut :"<<this->clone()->getStatut()<<"\n";
        s<<"Date de la Tache :"<<this->clone()->getDateT().toString("dd.MM.yyyy h:m:s ap").toStdString()<<"\n";
        s<<"Priorite : "<<this->clone()->getPriority()<<"\n";
        return (QString::fromStdString(s.str()));
    }
    /**
     * @brief methode virtuelle type
     * @return un QString& composé du type
     */
    QString notetype()const{ return "tache";}
};

/**
 * Enumeration Media
 * différents types de multimedias possibles
 */
enum Media {
    image, /**< Enum value image.*/
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
     * @brief constructeur par recopie de Multimedia
     */
    Multimedia(const Multimedia& m):Version(m.getDate()),description(m.description),fichier(m.fichier),type(m.type){}
    /**
     * @brief methode clone
     * @return un pointeur sur un objet Multimedia, cloné sur l'actuel
     */
    Multimedia* clone()const{return new Multimedia(*this);}
    /**
     * @brief methode save
     * @param l'adresse d'un QFile, fichier ou on va sauvegarder les versions
     */
    void save(QFile* f) const
    {
        QXmlStreamWriter stream(f);
        stream.writeStartElement("multimedia");
        stream.writeTextElement("date version",getDate().toString());
        stream.writeTextElement("description",description );
        stream.writeTextElement("fichier",fichier );
        stream.writeTextElement("type",QString::number(type) );
   }

public :
    /**
      * @brief destructeur de Multimedia
      */
    ~Multimedia(){}
    /**
     * @brief constructeur de Multimedia
     * @param dv QDateTime date de la version
     * @param d QString (description)
     * @param f const QString& (nom du fichier)
     * @param t enum Media (type)
     */
    Multimedia(QDateTime dv,const QString& d, const QString& f, Media t):Version(dv),description(d), fichier(f), type(t){}
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
     * @return un string correspondant au type de multimedia
     */
    std::string getType()
    {
        switch(type){
                           case image : return "image";
                            break;
                            case audio : return "audio";
                            break;
                            case video : return "video";
                            break;
        }
    }

    /**
     * @brief methode virtuelle afficher
     * @return un QString composé de la description, du nom de fichier et du type du Multimedia
     */
    QString afficher() const
    {
        std::stringstream s;
        s<<"Description : "<<this->clone()->getDescription().toStdString()<<"\n";
        s<<"Fichier :"<<this->clone()->getFichier().toStdString()<<"\n";
        s<<"Type :"<<this->clone()->getType()<<"\n";
        return (QString::fromStdString(s.str()));
    }
    /**
     * @brief methode virtuelle type
     * @return un QString& composé du type
     */
    QString notetype()const{
        return "multimedia";
    }
};




#endif // VERSION_H
