#ifndef _FILE_H_
#define _FILE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FORMAT "%d\n"
typedef int T;

struct File
{
    int tailleMax;
    int compteur;
    int rangPremier;
    int rangDernier;
    T*  tab;
};
typedef struct File File_t;

int     initFile    (File_t** file, int taille);
int     fileVide    (File_t* file);
int     filePleine  (File_t* file);
int     enfiler     (File_t* file, T element);
int     defiler     (File_t* file, T* element);
void    libererFile (File_t* file);
void    debugFile   (File_t* file);

#endif // !_FILE_H_