#include "arbre.h"

int main()
{
    noeud_t* arbre = NULL;

    ajouter_mot(&arbre, "test", 4);
    ajouter_mot(&arbre, "arbre", 5);
    ajouter_mot(&arbre, "arts", 4);
    ajouter_mot(&arbre, "art", 3);
    ajouter_mot(&arbre, "terre", 5);
    ajouter_mot(&arbre, "titi", 4);
    ajouter_mot(&arbre, "titiar", 6);

    debugArbre(arbre);

    return 0;
}