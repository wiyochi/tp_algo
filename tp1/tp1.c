#include <stdio.h>
#include <time.h>
#include "LC.h"

void    menuModifDate       (Message_t*);
void    menuAfficheMotif    (Message_t*);
int     lireFichier         (Message_t**, const char*);
int     ecrireFichier       (Message_t*, const char*);
void    afficherNonExpire   (Message_t*);
void    supprimerExpire     (Message_t**);
void    modifDateDebut      (Message_t*, int, int);
void    afficherMotif       (Message_t*, const char*);
char*   rechercherMotif     (char*, const char*);
int     dateAj              ();
int     formateChaine       (char*);
void    afficherElement     (Message_t*);
void    afficherListe       (Message_t*);


/*-------------------------------------------------------------------------
 * main   Point d'entree du programme
 *                                                                         
 * Entrées: argc, entier representant le nombre d'arguments passes au programme
 *          argv, tableau de chaine de caractere representants les arguments
 *                  passes au programme (en l'occurence le nom du fichier d'entree
 *                   et le nom du fichier de sortie)
 *
 *  Si on n'a pas de nom de fichier d'entree et de nom de fichier de sortie le
 *      programme affiche simplement "Pas de fichier" et s'arrete.
 *  Sinon on lis le fichier donne, on en creer une liste de message puis
 *      on affiche les messages non expires, on les supprime de la liste et
 *      on ecris dans le fichier de sortie la liste.
 * Puis l'utilisateur peut choisir d'afficher la liste, de modifier la date,
 *      d'afficher les messages avec un motif ou de quitter le programme.
 *
 * Lexique: maListe, pointeur de tete sur la liste chainnee de message
 *          choix, entier representant le choix de l'utilisateur pour les menus
 *-------------------------------------------------------------------------
 */
int main(int argc, char* argv[])
{
    Message_t*  maListe = NULL;
    int         choix   = 0;

    if(argc < 3)
    {
        printf("Pas de fichier\n");
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

        printf("\n\nEcriture dans le fichier %s...\n", argv[2]);
        if(!ecrireFichier(maListe, argv[2]))
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
 *  On recupere de l'utilisateur la date de debut des messages qui seront a
 *    modifies et la date de debut qui la remplacera puis on appelle la fonction
 *    "modifDateDebut".
 *
 * Lexique: dateDebut, entier qui represente la date de debut a modifier
 *          dateModif, entier qui represente la date modifiee
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

/*-------------------------------------------------------------------------
 * menuAfficheMotif   Permet à l'utilisateur d'afficher les messages selon un motif           
 *                                                                         
 * Entrées: liste, pointeur de la liste                                    
 *
 *  On recupere de l'utilisateur le motif, on la formate en chaine de caractere
 *      (finissant par '\0') et on appelle la fonction "afficherMotif".
 *
 * Lexique: motif, un tableau de caracteres contenant le motif (max: 255 caracteres)
 *-------------------------------------------------------------------------
 */
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
 * Entrees: liste, adresse du pointeur de liste                            
 *          filename, chaine de caractere contenant le nom du fichier
 * 
 * Sortie: erreur, un entier que l'on renvoie a la fin de la foncion
 *                  1 -> le fichier a bien ete ouvert
 *                  0 -> le fichier n'a pas pu etre ouvert    
 *                                                                         
 *  Cette fonction lit le fichier filename ligne par ligne. En effet sur   
 *  une ligne du fichier se trouve dateDebut, dateFin et le message. Une   
 *  fois la ligne lue, on stocke son contenu dans un nouvel element de    
 *  type Message_t grace a la fonction creerElement et que l'on insere     
 *  dans la liste en respectant le tri grace a la procedure ajouterElement 
 * 
 * Lexique: file, un pointeur sur le fichier
 *          ddebut, dfin, 2 entiers contenant les dates du message lu dans le fichier
 *          msg, un tableau de caractere contenant la chaine de caractere du message
 *                  lu dans le fichier (max: 100 caracteres)
 *          element, pointeur du nouvel element cree a chaque message lu dans le fichier
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
                fgetc(file); // On ignore l'espace entre la date de fin et le message
                fgets(msg, 100, file); // Message de 100 caractere maximum
                if(!formateChaine(msg)) // Finis par '\0' donc on doit aller a la ligne suivante
                    while(fgetc(file) != EOF && fgetc(file) != '\n');

                if((element = creerElement(ddebut, dfin, msg)) != NULL)
                    ajouterElement(liste, element);
            }
            else
            {
                while(fgetc(file) != EOF && fgetc(file) != '\n'); // Si je la ligne ne commence pas par 2 entiers (les dates) alors on va a la ligne suivante
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
 *  Entrees: liste, pointeur de la liste                                   
 *           filename, chaine de caractere contenant le nom du fichier     
 * 
 * Sortie: erreur, un entier que l'on renvoie a la fin de la foncion
 *                  1 -> le fichier a bien ete ouvert
 *                  0 -> le fichier n'a pas pu etre ouvert    
 *                                                                         
 *  Cette fonction va stocker chaque elements de la liste dans le fichier  
 *  a raison d'une ligne par elements.               
 * 
 * Lexique: file, un pointeur sur le fichier
 *          cour, un pointeur sur le message de la liste que l'on ecrit        
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
 *  afficherNonExpire   Affiche tous les messages non expires         
 *                                                                         
 *  Entrees:    liste, pointeur de la liste                                
 *                                                                         
 *  Parcours les messages de la liste et n'affiche que ceux dont la date de
 *      fin est superieur ou egal a la date d'aujourd'hui.
 * 
 * Lexique: cour, pointeur parcourant les messages de la liste
 *          today, entier representant la date d'aujourd'hui acquise par
 *                  la fonction "dateAj"       
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

/*-------------------------------------------------------------------------
 *  supprimerExpire   Supprime tous les messages dont leur dateFin est    
 *                      inferieur a la date d'aujourd'hui          
 *                                                                         
 *  Entrees:    liste, adresse du pointeur de la liste                                
 *                                                                         
 *  Parcours les messages de la liste et supprime les messages dont la date 
 *      de fin est inferieur a la date d'aujourd'hui grace a un precedent et
 *      a la fonction "suppressionCellule".
 * 
 * Lexique: cour, pointeur parcourant les messages de la liste
 *          prec, pointeur sur le champs suivant de l'élément précédent à cour
 *          aj, entier representant la date d'aujourd'hui acquise par
 *                  la fonction "dateAj"       
 *-------------------------------------------------------------------------
 */
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

/*-------------------------------------------------------------------------
 *  modifDateDebut   Remplace des dates de debut de messages par une autre
 *                                                                         
 *  Entrees:    liste, pointeur de la liste
 *              dateAModif, entier representant la date de debut a modifier
 *              nDate, entier representant la nouvelle date a mettre dans
 *                  les messages ayant dateAModif en date de debut
 *                                                                         
 *  Parcours la liste de message, teste si la date de debut correspond a
 *      dateAModif et si c'est le cas la change avec nDate.
 * 
 * Lexique: cour, pointeur parcourant les messages de la liste       
 *-------------------------------------------------------------------------
 */
void modifDateDebut(Message_t* liste, int dateAModif, int nDate)
{
    Message_t* cour = liste;

    while(cour != NULL)
    {
        if(cour->dateDebut == dateAModif)
        {
            cour->dateDebut = nDate;
            if(cour->dateFin < nDate)
                cour->dateFin = nDate;
        }
        cour = cour->suivant;
    }
}

/*-------------------------------------------------------------------------
 *  afficherMotif   affiche les messages de la liste ayant un texte avec un
 *                      motif donne
 *                                                                         
 *  Entrees:    liste, pointeur de la liste
 *              motif, tableau de caractere contenant le motif a rechercher
 *                                                                         
 *  Parcours la liste de message, teste si le texte du message contient le
 *     motif grace a la fonction "rechercherMotif" et si c'est le cas l'affiche
 * 
 * Lexique: cour, pointeur parcourant les messages de la liste
 *          avecMotif, pointeur sur le premier caractere du motif dans le
 *                      message si il y en a un, NULL sinon.
 *-------------------------------------------------------------------------
 */
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

/*-------------------------------------------------------------------------
 *  rechercherMotif   recherche la premiere occurence d'un motif dans une
 *                      chaine de caractere
 *                                                                         
 *  Entrees:    message, chaine de caractere dans laquelle on cherche un motif
 *              motif, chaine de caractere contenant le motif a rechercher   
 * 
 * Sortie: debut, pointeur de caractere pointant sur le debut du motif trouve
 *                  dans le message ou NULL si il n'y en a pas
 *                                                                         
 *  Parcours le message, si les caracteres sont en commun avec ceux du
 *      motif on parcours egalement le motif. Si on arrive a la fin du
 *      motif on s'arrete car on a trouve le motif. Si on trouve un caratere
 *      different on continue le parcours du message et on recommence le 
 *      parcours du motif. (Et cela jusqu'a la fin du message)
 * 
 * Lexique: cour, pointeur de caractere parcourant le message
 *          courMotif, pointeur de caractere parcourant le motif
 *-------------------------------------------------------------------------
 */
char* rechercherMotif(char* message, const char* motif)
{
    char*       cour      = message;
    const char* courMotif = motif;
    char*       debut;

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

/*-------------------------------------------------------------------------
 *  dateAj   renvoie la date d'aujourd'hui (date systeme)
 * 
 * Sortie: entier representant la date d'aujourd'hui sous la forme "aaaammjj"
 *                                                                         
 *  Utilise les structures et les fonctions systemes (time_t, struct tm,
 *      time(), localtime() et strftime()) pour ecrire dans lun buffer la date
 *      systeme et la renvoyer sous forme entiere.
 * 
 * Lexique: t, temps systeme
 *          date, structure contenant la date du temps systeme
 *          buffer, tableau de caractere contenant la date sous la forme "aaaammjj"
 *-------------------------------------------------------------------------
 */
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

/*-------------------------------------------------------------------------
 *  formateChaine   formate un tableau de caractere en chaine de caractere
 * 
 * Entrees: chaine, tableau de caractere finissant pas '\0' ou '\n'
 * 
 * Sortie: modif, entier (booleen) 0 -> la chaine n'a pas ete modifiee
 *                                 1 -> la chaine a ete modifiee
 *                                                                         
 *  Parcours le tableau jusqu'au '\0' ou '\n'. Si c'est un '\n',
 *      le remplace par '\0' et renvoie 1 sinon renvoie 0;
 * 
 * Lexique: i, entier permettant de parcourir le tableau
 *-------------------------------------------------------------------------
 */
int formateChaine(char* chaine)
{
    int i = 0;
    int modif = 0;
    while(chaine[i] != '\0' && chaine[i] != '\n')
        i++;

    if(chaine[i] == '\n')
    {
        chaine[i] = '\0';
        modif = 1;
    }
    return modif;
}

/*-------------------------------------------------------------------------
 * afficherListe   Affiche tout les elements d'une liste de message        
 *                                                                         
 * Entrees: liste, pointeur de la liste
 * 
 *  Parcours la liste et en affiche tous les elements
 *  
 * Lexique: cour, pointeur de message parcourant la liste                                                                       
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
 * afficherElement   Affiche un element
 *                                                                         
 * Entrees: element, pointeur sur un structure message
 * 
 * Affiche le contenu d'un element : sa date de debut, sa date de fin et le
 *  texte associé.                                                                        
 *-------------------------------------------------------------------------
 */
void afficherElement(Message_t* element)
{
    printf("%d\t%d\t%s\n", element->dateDebut, element->dateFin, element->message);
}
