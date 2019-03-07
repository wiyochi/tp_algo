#include "pile.h"

int main()
{
    Pile_t* maPile = NULL;
    int i, var;

    if(!initPile(&maPile, 10))
        return EXIT_FAILURE;

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

    libererPile(maPile);

    return 0;
}