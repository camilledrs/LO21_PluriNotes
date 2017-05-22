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

void Note::editer(QString title, tm modif, const Version& v){
	if (active && !supprime){
		titre=title;
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
