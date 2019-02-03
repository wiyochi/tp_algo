#include <stdio.h>
#include "LC.h"

int lireFichier(Message_t**, const char*);
void modifFormat(const char*, int*, int*, char*);

int main(int argc, char* argv[])
{
    Message_t* maListe = NULL;

    if(argc < 2)
    {
        printf("pas de fichier\n");
    }
    else
    {
        lireFichier(&maListe, argv[1]);
        afficherListe(maListe);
        printf("END\n");
    }
    

    /*
    Message_t* maListe = NULL;
    Message_t* e;

    afficherListe(maListe);

    e = creerElement(20170214, 20170215, "bonjour");
    if(e != NULL)
        ajouterElement(&maListe, e);
    afficherListe(maListe);

    printf("###\n");

    e = creerElement(20170101, 20170215, "bonmatin");
    ajouterElement(&maListe, e);
    e = creerElement(20170224, 20170227, "bonsoir");
    ajouterElement(&maListe, e);
    e = creerElement(20180214, 20170215, "yolo");
    ajouterElement(&maListe, e);
    afficherListe(maListe);
    */

    return 0;
}

int lireFichier(Message_t** liste, const char* filename)
{
    int erreur = 1;
    FILE* file = fopen(filename, "r");
    int ddebut, dfin;
    char msg[100];
    char buffer[116];
    Message_t* element;

    if(file != NULL)
    {
        while(fgets(buffer, 116, file))
        {
            printf("buffer: %s\n", buffer);
            modifFormat(buffer, &ddebut, &dfin, msg);
            element = creerElement(ddebut, dfin, msg);
            ajouterElement(liste, element);
            memset(buffer, 0, 116);
        }
        fclose(file);
    }
    else
    {
        erreur = 0;
    }

    return erreur;
}

void modifFormat(const char* buffer, int* ddebut, int* dfin, char* msg)
{
    char integer[8];
    int i;

    for(i = 0; i < 8; i++)
    {
        integer[i] = buffer[i];
    }
    *ddebut = atoi(integer);
    for(i = 9; i < 17; i++)
    {
        integer[i - 9] = buffer[i];
    }
    *dfin = atoi(integer);

    while(buffer[i] != '\n' && buffer[i] != '\0')
    {
        msg[i - 17] = buffer[i];
        i++;
    }
}