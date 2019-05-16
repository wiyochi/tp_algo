#include "affichage.h"

void affichagePile(Pile_t* pile)
{
    int j;
    for (j=0; j<=(pile->rangSommet); j++)
    {

        printf("%c",tolower(((pile->tab)[j])->lettre));

    } 
    printf("\n");
}

void affichage( noeud_t* a)
{
    noeud_t* cour = a;
    Pile_t* pile; 
    noeud_t* car_sommet;

    initPile(&pile, TAILLE_MAX);

    while ((!pileVide(pile)) ||  (cour!=NULL))
    {
        empiler(pile, cour);
        cour=cour->lv;
        sommet(pile, &car_sommet);
        if ((car_sommet->lettre>='A') && (car_sommet->lettre<='Z'))
        {
            affichagePile(pile);
        }
        while((cour == NULL) && (!pileVide(pile)))
        {
            depiler(pile, &cour);
            cour=cour->lh;
        }
    }
}
