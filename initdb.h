#ifndef INITDB_H
#define INITDB_H

#include <QtSql>


//Create new Qt project. In .pro file you need to add:QT += sql


QVariant addNote(QSqlQuery &q, const Note& note)
{
    q.addBindValue(note.id);
    q.addBindValue(note.titre);
    q.addBindValue(note.dateCrea);
    q.addBindValue(note.DateModif);
    q.addBindValue(note.active);
    q.addBindValue(note.supprime);
    q.addBindValue(note.nbVersion);
    q.addBindValue(note.nbMaxVersion);
    q.exec();
    return q.lastInsertId();
}

QVariant addTache(QSqlQuery &q, const Tache& t, const QVariant &noteId)
{
    q.addBindValue(t.date);
    q.addBindValue(t.action);
    q.addBindValue(t.statut);
    q.addBindValue(t.dateTache);
    q.addBindValue(t.priorite);
    q.addBindValue(noteId);
    q.exec();
    return q.lastInsertId();
}
QVariant addArticle(QSqlQuery &q, const Article& a, const QVariant &noteId)
{
    q.addBindValue(a.date);
    q.addBindValue(a.texte);
    q.addBindValue(noteId);
    q.exec();
    return q.lastInsertId();
}
QVariant addMultimedia(QSqlQuery &q, const Multimedia& m, const QVariant &noteId)
{
    q.addBindValue(m.date);
    q.addBindValue(m.description);
    q.addBindValue(m.fichier);
    q.addBindValue(m.type);
    q.addBindValue(noteId);
    q.exec();
    return q.lastInsertId();
}

QVariant addCouple(QSqlQuery &q, const Couple& c,const QVariant &relationId )
{
    q.addBindValue(c.label);
    q.addBindValue(c.note1);
    q.addBindValue(c.note2);
    q.addBindValue(relatinId);
    q.exec();
    return q.lastInsertId();
}

QVariant addRelation(QSqlQuery &q, const Relation& r)
{
    q.addBindValue(r.titre);
    q.addBindValue(r.nb);
    q.addBindValue(r.max);
    q.addBindValue(r.description);
    q.addBindValue(r.orientee);
    q.exec();
    return q.lastInsertId();
}

QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if (tables.contains("notes", Qt::CaseInsensitive)
        && tables.contains("relations", Qt::CaseInsensitive))
        return QSqlError();

    QSqlQuery q;
    if (!q.exec(QLatin1String("create table notes(id integer primary key, titre varchar, datecrea date, datemodif date, active bool, supprime bool,nbversion integer, nbmaxversion integer)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table relations(id integer primary key, titre varchar, nb integer, max integer,description varchar, orientee bool)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table couples(id integer primary key, label varchar, note1 integer, note2 integer, relation integer)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table taches(id integer primary key, date date, action varchar, statut varchar, datetache date, priorite integer, note integer)")))
        return q.lastError();
     if (!q.exec(QLatin1String("create table articles(id integer primary key, date date, texte varchar, note integer)")))
        return q.lastError();
      if (!q.exec(QLatin1String("create table multimedias(id integer primary key, date date, description varchar, fichier varchar, type varchar, note integer)")))
        return q.lastError();
        
    if (!q.prepare(QLatin1String("insert into authors(name, birthdate) values(?, ?)")))
        return q.lastError();
    QVariant asimovId = addAuthor(q, QLatin1String("Isaac Asimov"), QDate(1920, 2, 1));
    QVariant greeneId = addAuthor(q, QLatin1String("Graham Greene"), QDate(1904, 10, 2));
    QVariant pratchettId = addAuthor(q, QLatin1String("Terry Pratchett"), QDate(1948, 4, 28));

    if (!q.prepare(QLatin1String("insert into genres(name) values(?)")))
        return q.lastError();
    QVariant sfiction = addGenre(q, QLatin1String("Science Fiction"));
    QVariant fiction = addGenre(q, QLatin1String("Fiction"));
    QVariant fantasy = addGenre(q, QLatin1String("Fantasy"));

    if (!q.prepare(QLatin1String("insert into books(title, year, author, genre, rating) values(?, ?, ?, ?, ?)")))
        return q.lastError();
    addBook(q, QLatin1String("Foundation"), 1951, asimovId, sfiction, 3);
    addBook(q, QLatin1String("Foundation and Empire"), 1952, asimovId, sfiction, 4);
    addBook(q, QLatin1String("Second Foundation"), 1953, asimovId, sfiction, 3);
    addBook(q, QLatin1String("Foundation's Edge"), 1982, asimovId, sfiction, 3);
    addBook(q, QLatin1String("Foundation and Earth"), 1986, asimovId, sfiction, 4);
    addBook(q, QLatin1String("Prelude to Foundation"), 1988, asimovId, sfiction, 3);
    addBook(q, QLatin1String("Forward the Foundation"), 1993, asimovId, sfiction, 3);
    addBook(q, QLatin1String("The Power and the Glory"), 1940, greeneId, fiction, 4);
    addBook(q, QLatin1String("The Third Man"), 1950, greeneId, fiction, 5);
    addBook(q, QLatin1String("Our Man in Havana"), 1958, greeneId, fiction, 4);
    addBook(q, QLatin1String("Guards! Guards!"), 1989, pratchettId, fantasy, 3);
    addBook(q, QLatin1String("Night Watch"), 2002, pratchettId, fantasy, 3);
    addBook(q, QLatin1String("Going Postal"), 2004, pratchettId, fantasy, 3);

    return QSqlError();
}

#endif
