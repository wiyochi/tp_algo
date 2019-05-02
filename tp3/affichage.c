#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"

void affichageLettres( char* lettres, int i)
{
    int j;
    for j=0; j<i; j++
    {
        printf("%c",lettres[j]);

    } 
    printf("\n");
}

void affichage( noeud_t** a)
{
    noeud_t* cour = *a;
    pile_t pile;
    char* lettres[50];
    int i=0; 
    while ((!pileVide(pile)) ||  (cour==NULL))
    {
        empiler(pile, cour);
        lettres[i]=cour->lettre;
        i++;
        cour=cour->lv;
        if (lettres[i] >= 'A' || lettres[i] <='Z')
        {
            affichageLettres(lettres, i);
        }
        while((cour != NULL) && (!pileVide(pile)))
        {
            depiler(pile, &cour);
            i--;
            cour=cour->lh;
        }
    }
}