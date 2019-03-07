#include "pile.h"


int initPile(Pile_t** pile, int taille)
{
    if((*pile = (Pile_t*)malloc(sizeof(Pile_t))) != NULL)
    {
        if(((*pile)->tab = (T*)malloc(sizeof(T) * taille)) == NULL)
        {
            free(*pile);
            *pile = NULL;
        }
        else
        {
            (*pile)->tailleMax = taille;
            (*pile)->rangSommet = -1;
        }
    }
    return *pile != NULL;
}

int pileVide(Pile_t* pile)
{
    return (pile->rangSommet == -1);
}

int pilePleine(Pile_t* pile)
{
    return (pile->rangSommet == (pile->tailleMax - 1));
}

int empiler(Pile_t* pile, T element)
{
    int ok = !pilePleine(pile);
    if(ok)
    {
        pile->rangSommet += 1;
        (pile->tab)[pile->rangSommet] = element;
    }
    return ok;
}

int depiler(Pile_t* pile, T* element)
{
    int ok = !pileVide(pile);
    if(ok)
    {
        *element = (pile->tab)[pile->rangSommet];
        pile->rangSommet -= 1;
    }
    return ok;
}

int sommet(Pile_t* pile, T* element)
{
    int ok = !pileVide(pile);
    if(ok)
        *element = (pile->tab)[pile->rangSommet];
    return ok;
}

void libererPile(Pile_t* pile)
{
    free(pile->tab);
    free(pile);
}

void debugPile(Pile_t* pile)
{
    int i;

    printf("Pile:\n");
    printf("\tTaille max: %d\n", pile->tailleMax);
    printf("\tRang sommet: %d\n", pile->rangSommet);
    for(i = 0; i <= pile->rangSommet; i++)
    {
        printf("\t"FORMAT, (pile->tab)[i]);
    }
}