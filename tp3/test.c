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
    ajouter_mot(&arbre, "", 0);
    ajouter_mot(&arbre, "arbre", 5);
    ajouter_mot(&arbre, "arbre", 5);
    ajouter_mot(&arbre, "abouti", 6);

    debug_arbre(arbre);

    printf("=== Arbre ===\n");
    affichage_arbre(arbre, "");
    
    printf("=== Motif vide ===\n");
    affichage_motif(arbre, "", 0);

    printf("=== Motif a ===\n");
    affichage_motif(arbre, "a", 1);

    printf("=== Motif ar ===\n");
    affichage_motif(arbre, "ar", 2);
    
    printf("=== Motif ba ===\n");
    affichage_motif(arbre, "ba", 2);
    
    printf("=== Motif test ===\n");
    affichage_motif(arbre, "test", 4);
    
    printf("=== Motif tests ===\n");
    affichage_motif(arbre, "testsss", 7);

    liberer_arbre(&arbre);

    return 0;
}