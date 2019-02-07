#include "LC.h"

Message_t* creerElement(int ddebut, int dfin, const char* msg)
{
    Message_t * element;
    
    element = (Message_t*)malloc(sizeof(Message_t));
    if(element != NULL)
    {
        element->dateDebut = ddebut;
        element->dateFin = dfin;
        strcpy(element->message, msg);
        element->suivant = NULL;
    }
    return element;
}

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

void ajouterElement(Message_t** liste, Message_t* element)
{
    Message_t** prec = rechercherPrecedent(liste, element);

    element->suivant = *prec;
    *prec = element;
}

void afficherListe(Message_t* liste)
{
    Message_t* cour = liste;
    int cpt = 1;

    while(cour != NULL)
    {
        printf("Message %d:\n", cpt);
        printf("\tpt: %p\n", cour);
        printf("\tDate debut: %d\n", cour->dateDebut);
        printf("\tDate fin: %d\n", cour->dateFin);
        printf("\tMessage: %s\n", cour->message);
        printf("\tSuivant: %p\n", cour->suivant);
        cour = cour->suivant;
        cpt++;
    }
}