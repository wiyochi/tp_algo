#include <stdio.h>
#include "pile.h"

#define TAILLE 3

void truc   (int i, int n, int* T);
void truc_it(int i, int n, int* T);

int main()
{
    int T[TAILLE]   = { 1, 2, 3 };
    int T2[TAILLE]  = { 1, 2, 3 };

    truc(0, TAILLE, T);
    printf("--------------------------------\n");
    truc_it(0, TAILLE, T2);

    return 0;
}

void truc_it(int i, int n, int* T)
{
    int j  = i;
    int iL = i;
    int tmp, k;
    int fin = 0;
    Pile_t* pile = NULL;
    
    if(!initPile(&pile, 100))
        exit(EXIT_FAILURE);

    while(!fin)
    {
        while(iL < n)
        {
            tmp = T[iL];
            T[iL] = T[j];
            T[j] = tmp;

            if(!empiler(pile, iL))
                printf("ERREUR EMPILER\n");
            if(!empiler(pile, j))
                printf("ERREUR EMPILER\n");

            iL += 1;
            j = iL;
        }

        printf("[ ");
        for(k = 0; k < n; k++)
            printf("%d ", T[k]);
        printf("]\n");

        while(j >= n && !fin)
        {
            if(!pileVide(pile))
            {
                if(!depiler(pile, &j))
                    printf("ERREUR DEPILER\n");
                if(!depiler(pile, &iL))
                    printf("ERREUR DEPILER\n");

                tmp = T[iL];
                T[iL] = T[j];
                T[j] = tmp;

                j += 1;
            }
            else
            {
                fin = 1;
            }
        }
    }
    libererPile(pile);
}

void truc(int i, int n, int* T)
{
    int j, tmp;

    if(i == (n-1))
    {
        printf("[ ");
        for(j = 0; j < n; j++)
        {
            printf("%d ", T[j]);
        }
        printf("]\n");
    }
    else
    {
        for(j = i; j < n; j++)
        {
            tmp = T[i];
            T[i] = T[j];
            T[j] = tmp;
            truc(i + 1, n, T);
            tmp = T[i];
            T[i] = T[j];
            T[j] = tmp;
        }
    }
}