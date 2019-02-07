#include "LC.h"

/*---------------------------------------------------------------*/
/* creerElement         Creer une cellule "Message"              */
/*                                                               */
/* Entrées: ddebut, dfin 2 entiers représentant des dates        */
/*          msg, une chaîne de caractères                         */
/*                                                               */
/* Sortie:  adresse d'une nouvelle cellule allouée               */
/*                                                               */
/*---------------------------------------------------------------*/
Message_t* creerElement(int ddebut, int dfin, const char* msg)
{
    Message_t * element;
    
    element = (Message_t*)malloc(sizeof(Message_t));
    if(element != NULL)
    {
        element->dateDebut = ddebut;
        element->dateFin = dfin;
        element->message = (char*)malloc(sizeof(char) * strlen(msg));
        strcpy(element->message, msg);
        element->suivant = NULL;
    }
    return element;
}

/*-------------------------------------------------------------------------*/
/* rechercherPrecedent   Recherche le précedent d'une cellule donnée       */
/*                                                                         */
/* Entrées: liste, adresse du pointeur de liste                            */
/*          element, adresse de la cellule dont il faut le précedent       */
/*                                                                         */
/* Sortie:  adresse de la case "suivant" de la cellule precedente          */
/*                                                                         */
/*   En l'occurence, le précedent pointe sur la cellule dont la date       */
/*   de début est égale ou supérieur a la date de début de l'élement donné */
/*                                                                         */
/*-------------------------------------------------------------------------*/
Message_t** rechercherPrecedent(Message_t** liste, Message_t* element)
{
    Message_t* cour = *liste;
    Message_t** prec = liste;

    while(cour != NULL && cour->dateDebut < element->dateDebut)
    {
        prec = &(cour->suivant);
        cour = cour->suivant;
    }
    return prec;
}

/*-------------------------------------------------------------------------*/
/* ajouterElement   Ajoute une cellule à la liste de message               */
/*                                                                         */
/* Entrées: liste, adresse du pointeur de liste                            */
/*          element, adresse de la cellule qu'il faut ajouter à la liste   */
/*                                                                         */
/*   Fonction uniquement pour "simplifier" dans le programme principal     */
/*   Recherche le precedent avec recherchePrecedent et appelle             */
/*    adjonctionCellule avec celui-ci                                      */
/*                                                                         */
/*-------------------------------------------------------------------------*/
void ajouterElement(Message_t** liste, Message_t* element)
{
    Message_t** prec = rechercherPrecedent(liste, element);
    adjonctionCellule(prec, element);
}

/*-------------------------------------------------------------------------*/
/* adjonctionCellule   Ajoute une cellule à la liste de message            */
/*                                                                         */
/* Entrées: prec, adresse du champs "suivant" de la cellule précedente     */
/*          element, adresse de la cellule qu'il faut ajouter à la liste   */
/*                                                                         */
/*   Edite les liens du précédent et de l'élément pour l'ajouter dans la   */
/*    liste chaînée                                                        */
/*                                                                         */
/*-------------------------------------------------------------------------*/
void adjonctionCellule (Message_t** prec, Message_t* element)
{
    element->suivant = *prec;
    *prec = element;
}

/*-------------------------------------------------------------------------*/
/* afficherListe   Affiche tout les éléments d'une liste de message        */
/*                                                                         */
/* Entrées: liste, pointeur de la liste                                    */
/*                                                                         */
/*-------------------------------------------------------------------------*/
void afficherListe(Message_t* liste)
{
    Message_t* cour = liste;
    int cpt = 1;

    while(cour != NULL)
    {
        printf("Message %d:\n", cpt);
        afficherElement(cour);
        cour = cour->suivant;
        cpt++;
    }
}

void afficherElement(Message_t* element)
{
    printf("\tpt: %p\n", element);
    printf("\tDate debut: %d\n", element->dateDebut);
    printf("\tDate fin: %d\n", element->dateFin);
    printf("\tMessage: %s\n", element->message);
    printf("\tSuivant: %p\n", element->suivant);
}