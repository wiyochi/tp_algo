#include "file.h"

int initFile(File_t** file, int taille)
{
    if((*file = (File_t*)malloc(sizeof(File_t))) != NULL)
    {
        if(((*file)->tab = (T*)malloc(sizeof(T) * taille)) != NULL)
        {
            (*file)->tailleMax = taille;
            (*file)->compteur = 0;
            (*file)->rangPremier = 0;
            (*file)->rangDernier = taille - 1;
        }
        else
        {
            free(*file);
            *file = NULL;
        }
    }
    return (*file != NULL)
}


int fileVide(File_t* file)
{
    return (file->compteur == 0);
}

int filePleine(File_t* file)
{
    return (file->compteur == file->tailleMax);
}

int enfiler(File_t* file, T element)
{
    int ok = !filePleine(file);
    if(ok)
    {
        file->compteur += 1;
        file->rangDernier = (file->rangDernier + 1) % file->tailleMax;
        (file->tab)[file->rangDernier] = element;
    }
    return ok;
}

int defiler(File_t* file, T* element)
{
    int ok = !fileVide(file);
    if(ok)
    {
        file->compteur += 1;
        *element = (file->tab)[file->rangPremier];
        file->rangPremier = (file->rangPremier + 1) % file->tailleMax;
    }
    return ok;
}

void    libererFile (File_t* file);
void    debugFile   (File_t* file);