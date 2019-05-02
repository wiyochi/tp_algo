#include "arbre.h"

int main()
{
    noeud_t* arbre = NULL;
    char[] mot = "test";

    ajouter_mot(&arbre, mot, 4);

    debugArbre(arbre);

    return 0;
}