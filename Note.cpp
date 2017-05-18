#include <ctime>
#include <QString>
#include "Notes.h"

void Note::restaurer(Version* v)
{
    unsigned int i=0;
    while(i<nbVersion && versions[i]!=v) i++;
    Version* tmp=versions[i];
    while(i<nbVersion-1) 
    {
      versions[i]=versions[i+1];
      i++;
    }
    versions[i]=tmp; //on met la version à restaurer au niveau de la dernière case du tableau (versions[nbVersion-1]) 
}

void Note::editer(QString tittle, tm modif, const Version& v){
	if (active && !supprime){
		titre=tittle;
		dateModif= modif;
		if (nbVersion==nbMaxVersion){
			Version ** newVersions= new Version*[nbMaxVersions+5];
			for(unsigned int i=0; i<nbVersion; i++)
				newVersions[i]=versions[i];
			Version** oldVersions=versions;
			versions=newVersions;
			nbMaxVerions+=5;
			delete[] oldVersions;
		}
		versions[nbVersion++]=v.clone();
		
	}
}

void Note::creerArticle(tm crea, const QString& text){
	if (active && !supprime){
		if (nbVersion==nbMaxVersion){
			Version ** newVersions= new Version*[nbMaxVersions+5];
			for(unsigned int i=0; i<nbVersion; i++)
				newVersions[i]=versions[i];
			Version** oldVersions=versions;
			versions=newVersions;
			nbMaxVerions+=5;
			delete[] oldVersions;
		}
		versions[nbVersion++]= new Article(crea, s);
		dateModif=crea;
	}
}


void Note::creerMultimedia(tm crea, const QString& desc, const QString& file, Media t){
	if (active && !supprime){
		if (nbVersion==nbMaxVersion){
			Version ** newVersions= new Version*[nbMaxVersions+5];
			for(unsigned int i=0; i<nbVersion; i++)
				newVersions[i]=versions[i];
			Version** oldVersions=versions;
			versions=newVersions;
			nbMaxVerions+=5;
			delete[] oldVersions;
		}
		versions[nbVersion++]= new Multimedia(crea, desc, file, t);
	dateModif=crea;
	}
}


void Note::creerTache(tm crea, const QString& a, tm dateFin=0, unsigned int prio=0){
	if (active && !supprime){
		if (nbVersion==nbMaxVersion){
			Version ** newVersions= new Version*[nbMaxVersions+5];
			for(unsigned int i=0; i<nbVersion; i++)
				newVersions[i]=versions[i];
			Version** oldVersions=versions;
			versions=newVersions;
			nbMaxVerions+=5;
			delete[] oldVersions;
		}
		versions[nbVersion++]= new Tache(crea, a, dateFin, pris);
		dateModif=crea;
	}
}
