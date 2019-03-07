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

    debugFile(maFile);
    printf("Defile 1 element\n");
    if(!defiler(maFile, &var))
        printf("ERREUR DEFILAGE\n");
    else
        printf("var: %d\n", var);
    printf("Enfile 1 element\n");
    if(!enfiler(maFile, 54))
        printf("ERREUR ENFILAGE\n");
    debugFile(maFile);
    printf("Enfile 1 element\n");
    if(!enfiler(maFile, 62))
        printf("ERREUR ENFILAGE\n");
    debugFile(maFile);
    printf("Defile 1 element\n");
    if(!defiler(maFile, &var))
        printf("ERREUR DEFILAGE\n");
    else
        printf("var: %d\n", var);
    debugFile(maFile);

    printf("Ajout de 10 element\n");
    for(i = 0; i < 10; i++)
    {
        if(!enfiler(maFile, i))
            printf("ERREUR ENFILAGE\n");
    }
    debugFile(maFile);

/*
    debugPile(maPile);
    printf("Depile 1 element\n");
    if(!depiler(maPile, &var))
        printf("ERREUR DEPILER\n");
    else
        printf("var: %d\n", var);
    debugPile(maPile);
    printf("Ajout de 1 element\n");
    if(!empiler(maPile, 54))
        printf("ERREUR\n");
    debugPile(maPile);
    printf("Ajout de 1 element\n");
    if(!empiler(maPile, 62))
        printf("ERREUR\n");
    debugPile(maPile);
    printf("Depile 1 element\n");
    if(!depiler(maPile, &var))
        printf("ERREUR DEPILER\n");
    else
        printf("var: %d\n", var);
    debugPile(maPile);
    
    printf("Ajout de 10 element\n");
    for(i = 0; i < 10; i++)
    {
        if(!empiler(maPile, i))
            printf("ERREUR\n");
    }
    debugPile(maPile);
*/
    libererFile(maFile);
    libererPile(maPile);

    return 0;
}