#include <stdio.h>
#include <time.h>
#include "LC.h"

int     lireFichier         (Message_t**, const char*);
int     ecrireFichier       (Message_t*, const char*);
void    afficherNonExpire   (Message_t*);
void    supprimerExpire     (Message_t**);
void    modifDateDebut      (Message_t*, int, int);
void    afficherMotif       (Message_t*, const char*);
char*   rechercherMotif     (char*, const char*);
int     dateAj              ();
void    formateChaine       (char*);
void    afficherElement     (Message_t*);
void    afficherListe       (Message_t*);
void    menuModifDate       (Message_t*);
void    menuAfficheMotif    (Message_t*);


int main(int argc, char* argv[])
{
    Message_t*  maListe = NULL;
    int         choix = 0;

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

        printf("\n\nEcriture dans le fichier %s...\n", argv[2]);
        if(ecrireFichier(maListe, argv[2]))
            afficherListe(maListe);
        else
            printf("Erreur sur le fichier\n");

        do {
            do {
                printf("\n");
                printf("1 -- Affichage des messages\n");
                printf("2 -- Modification de date\n");
                printf("3 -- Affichage avec motif\n");
                printf("4 -- Quitter\n");
                scanf("%d", &choix);
                printf("\n");
            } while(choix != 1 && choix != 2 && choix != 3 && choix != 4);

            switch(choix)
            {
            case 1:
                printf("Messages:\n");
                afficherListe(maListe);
                break;
            case 2:
                menuModifDate(maListe);
                break;
            case 3:
                menuAfficheMotif(maListe);
                break;
            default:
                break;
            }

        } while(choix != 4);

        libererListe(&maListe);
    }

    return 0;
}

/*-------------------------------------------------------------------------
 * menuModifDate   Permet à l'utilisateur de modifier une date de début           
 *                                                                         
 * Entrées: liste, pointeur de la liste                                    
 *
 *  Permet 
 *
 * Lexique: 
 *-------------------------------------------------------------------------
 */
void menuModifDate(Message_t* liste)
{
    int dateDebut = 0, dateModif = 0;

    printf("-- Modification de date --\n");
    printf("Date à modifier :\n");
    scanf("%d", &dateDebut);
    printf("Date modifiée :\n");
    scanf("%d", &dateModif);
    printf("\nModif de la date %d en %d\n", dateDebut, dateModif);
    modifDateDebut(liste, dateDebut, dateModif);
    afficherListe(liste);
}

void menuAfficheMotif(Message_t* liste)
{
    char motif[255];
    printf("-- Affichage motif --\n");
    printf("Motif à rechercher :\n");
    scanf("%s", motif);
    formateChaine(motif);
    afficherMotif(liste, motif);
}


/*-------------------------------------------------------------------------
 * lireFichier  Lit un fichier texte et stocke sont contenu dans une liste 
 *              de messages                                                
 *                                                                         
 * Entr�es: liste, adresse du pointeur de liste                            
 *          filename, cha�ne de caract�re contenant le nom du fichier      
 *                                                                         
 *  Cette fonction lit le fichier filename ligne par ligne. En effet sur   
 *  une ligne du fichier se trouve dateDebut, dateFin et le message. Une   
 *  fois la ligne lue, on stocke son contenu dans une nouvel �l�ment de    
 *  type Message_t gr�ce � la fonction creerElement et que l'on ins�re     
 *  dans la liste en respectant le tri gr�ce � la proc�dure ajouterElement 
 *-------------------------------------------------------------------------
 */
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
            if(fscanf(file, "%d %d", &ddebut, &dfin) == 2) // On créer un nouvel élément seulement si les 2 valeurs (début et fin) sont lues
            {
                fgetc(file);
                fgets(msg, 100, file);
                formateChaine(msg);

                if((element = creerElement(ddebut, dfin, msg)) != NULL)
                    ajouterElement(liste, element);
            }
        }
        fclose(file);
    }
    else
    {
        erreur = 0;
    }

    return erreur;
}


/*-------------------------------------------------------------------------
 *  ecrireFichier Ecrit le contenu d'une liste de messages dans un fichier 
 *                                                                         
 *  Entr�es: liste, pointeur de la liste                                   
 *           filename, cha�ne de caract�re contenant le nom du fichier     
 *                                                                         
 *  Cette fonction va stocker chaque �l�ments de la liste dans le fichier  
 *  � raison d'une ligne par �l�ments                                      
 *-------------------------------------------------------------------------
 */
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

/*-------------------------------------------------------------------------
 *  afficherNonExpire   Affiche tous les messages dont leur dateFin est    
 *                      sup�rieur ou �gal � la date d'aujourd'hui          
 *                                                                         
 *  Entr�es:    liste, pointeur de la liste                                
 *                                                                         
 *  Cette fonction va stocker dans une variable de type entier la date     
 *  d'aujourd'hui et va comparer cette derni�re avec dateFin de chaque     
 *  �l�ments. Si dateFin est sup�rieur ou �gal � la date d'aujourd'hui     
 *  alors on affiche le message de l'�l�ment.                              
 *-------------------------------------------------------------------------
 */
void afficherNonExpire(Message_t* liste)
{
    Message_t*  cour = liste;
    int         today = dateAj();

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
    Message_t*  cour = *liste;
    Message_t** prec = liste;
    int         aj = dateAj();

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

void afficherMotif(Message_t* liste, const char* motif)
{
    Message_t*  cour = liste;
    char*       avecMotif;

    while(cour != NULL)
    {
        avecMotif = NULL;
        if((avecMotif = rechercherMotif(cour->message, motif)) != NULL)
        {
            afficherElement(cour);
            printf("\n");
        }
        cour = cour->suivant;
    }
}

char* rechercherMotif(char* message, const char* motif)
{
    char* cour      = message;
    const char* courMotif = motif;
    char* debut;

    while(*cour != '\0' && *courMotif != '\0')
    {
        debut = cour;
        while(*courMotif != '\0' && *cour != '\0' && *courMotif == *cour)
        {
            courMotif++;
            cour++;
        }
        if(*courMotif != '\0')
        {
            courMotif = motif;
            cour++;
        }
    }

    if(*courMotif != '\0')
        debut = NULL;

    return debut;
}

int dateAj()
{
    time_t      t;
    struct tm * date;
    char        buffer[10];

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

/*-------------------------------------------------------------------------
 * afficherListe   Affiche tout les �l�ments d'une liste de message        
 *                                                                         
 * Entr�es: liste, pointeur de la liste                                    
 *                                                                         
 *-------------------------------------------------------------------------
 */
void afficherListe(Message_t* liste)
{
    Message_t* cour = liste;

    while(cour != NULL)
    {
        afficherElement(cour);
        cour = cour->suivant;
    }
}

/*-------------------------------------------------------------------------
 * afficherElement   Affiche un �l�ment d'une liste de message             
 *                                                                         
 * Entr�es: element, pointeur sur un structure message                     
 *                                                                         
 *-------------------------------------------------------------------------
 */
void afficherElement(Message_t* element)
{
    printf("%d\t%d\t%s\n", element->dateDebut, element->dateFin, element->message);
}
