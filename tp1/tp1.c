#include <stdio.h>
#include <time.h>
#include "LC.h"

int     lireFichier         (Message_t**, const char*);
int     ecrireFichier       (Message_t*, const char*);
void    afficherNonExpire   (Message_t*);
void    supprimerExpire     (Message_t**);
void    modifDateDebut      (Message_t*, int, int);
int     dateAj              ();
void    formateChaine       (char*);


int main(int argc, char* argv[])
{
    Message_t* maListe = NULL;

    if(argc < 3)
    {
        printf("pas de fichier\n");
    }
    else
    {
        printf("Lecture du fichier\n");
        if(lireFichier(&maListe, argv[1]))
            afficherListe(maListe);
        else
            printf("Erreur sur le fichier\n");
            
        printf("\n\nAffichage des messages non expires\n");
        afficherNonExpire(maListe);
        
        printf("\n\nSupression des messages expires...\n");
        supprimerExpire(&maListe);
        afficherListe(maListe);

        printf("\n\nEcriture du fichier\n");
        if(!ecrireFichier(maListe, argv[2]))
            printf("Erreur sur le fichier\n");

        printf("Modif de la date 20190120\n");
        modifDateDebut(maListe, 20190120, 20190204);
        afficherListe(maListe);
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

int ecrireFichier(Message_t* liste, const char* filename)
{
    int         erreur = 1;
    FILE*       file = fopen(filename, "w");
    Message_t*  cour = liste;

    if(file != NULL)
    {
        while(cour != NULL)
        {
            fprintf(file, "%d %d %s\n", cour->dateDebut, cour->dateFin, cour->message);
            cour = cour->suivant;
        }
        fclose(file);
    }
    else
    {
        erreur = 0;
    }

    return erreur;
}

void afficherNonExpire(Message_t* liste)
{
    Message_t* cour = liste;
    int today = dateAj();
    printf("aj = %d\n", today);

    while(cour != NULL)
    {
        if(cour->dateFin >= today)
        {
            afficherElement(cour);
        }
        cour = cour->suivant;
    }
}

void supprimerExpire(Message_t** liste)
{
    Message_t* cour = *liste;
    Message_t** prec = liste;
    int aj = dateAj();

    while(cour != NULL)
    {
        if(cour->dateFin < aj)
        {
            suppressionCellule(prec);
            cour = (*prec);
        }
        else
        {
            prec = &(cour->suivant);
            cour = cour->suivant;
        }
    }
}

void modifDateDebut(Message_t* liste, int dateAModif, int nDate)
{
    Message_t* cour = liste;

    while(cour != NULL)
    {
        if(cour->dateDebut == dateAModif)
        {
            cour->dateDebut = nDate;
        }
        cour = cour->suivant;
    }
}

int dateAj()
{
    time_t t;
    struct tm * date;
    char buffer[10];

    time(&t);
    date = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y%m%d", date);

    return atoi(buffer);
}

void formateChaine(char* chaine)
{
    int i = 0;
    while(chaine[i] != '\0' && chaine[i] != '\n')
        i++;

    chaine[i] = '\0';
}