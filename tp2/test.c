#include "pile.h"
#include "file.h"

int main()
{
    File_t* maFile = NULL;
    Pile_t* maPile = NULL;
    int i, var;

    if(!initPile(&maPile, 10))
        return EXIT_FAILURE;
    if(!initFile(&maFile, 10))
        return EXIT_FAILURE;

    printf("=== Tests dépiler, défiler sur une liste sans éléments ===\n");
    if(!depiler(maPile, &var))
        printf("ERREUR DEPILER\n");
    if(!defiler(maFile, &var))
        printf("ERREUR DEFILER\n");
    debugPile(maPile);
    debugFile(maFile);

    printf("\n=== Tests empiler, enfiler trop d'éléments ===\n");
    var = 89;
    for(i = 0; i < 15; i++)
    {
        if(!empiler(maPile, var))
            printf("ERREUR EMPILER\n");
        if(!enfiler(maFile, var))
            printf("ERREUR ENFILER\n");
    }
    debugPile(maPile);
    debugFile(maFile);

    // Remise à zéro
    while(!pileVide(maPile))
    {
        if(!depiler(maPile, &var))
            printf("ERREUR DEPILER\n");
    }
    while(!fileVide(maFile))
    {
        if(!defiler(maFile, &var))
            printf("ERREUR DEFILER\n");
    }

    printf("\n============== Tests de validité des implémentations de la pile et de la file ==============\n");
    printf("On teste la pile et la file en essayant d'inverser le contenu d'une pile à l'aide d'une file\n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("On remplit la pile (avec les chiffres de 1 à 10 par exemple)\n");
    for(i = 0; i < 10; i++)
    {
        if(!empiler(maPile, i+1))
            printf("ERREUR EMPILER\n");
    }
    debugPile(maPile);
    debugFile(maFile);

    printf("--------------------------------------------------------------------------------------------\n");
    printf("On vide la pile et on enfile chaque élément qu'on dépile\n");
    while(!pileVide(maPile))
    {
        if(!depiler(maPile, &var))
            printf("ERREUR DEPILER\n");
        if(!enfiler(maFile, var))
            printf("ERREUR ENFILER\n");
    }
    debugPile(maPile);
    debugFile(maFile);

    printf("--------------------------------------------------------------------------------------------\n");
    printf("On défile en remettant les éléments dans la pile\n");
    while(!fileVide(maFile))
    {
        if(!defiler(maFile, &var))
            printf("ERREUR DEFILER\n");
        if(!empiler(maPile, var))
            printf("ERREUR EMPILER\n");
    }
    debugPile(maPile);
    debugFile(maFile);

    libererFile(maFile);
    libererPile(maPile);

    return 0;
}