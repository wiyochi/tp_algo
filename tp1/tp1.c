#include <stdio.h>
#include "LC.h"

int lireFichier(Message_t**, const char*);
void formateChaine(char*);

int main(int argc, char* argv[])
{
    Message_t* maListe = NULL;

    if(argc < 2)
    {
        printf("pas de fichier\n");
    }
    else
    {
        if(lireFichier(&maListe, argv[1]))
            afficherListe(maListe);
        else
            printf("Erreur sur le fichier\n");
    }

    return 0;
}

int lireFichier(Message_t** liste, const char* filename)
{
    int         erreur = 1;
    FILE*       file = fopen(filename, "r");
    int         ddebut, dfin;
    char        msg[100];
    Message_t*  element;

    if(file != NULL)
    {
        while(!feof(file))
        {
            fscanf(file, "%d %d", &ddebut, &dfin);
            fgets(msg, 100, file);
            formateChaine(msg);

            if((element = creerElement(ddebut, dfin, msg)) != NULL)
                ajouterElement(liste, element);
        }
        fclose(file);
    }
    else
    {
        erreur = 0;
    }

    return erreur;
}

void formateChaine(char* chaine)
{
    int i = 0;
    while(chaine[i] != '\0' && chaine[i] != '\n')
        i++;

    chaine[i] = '\0';
}