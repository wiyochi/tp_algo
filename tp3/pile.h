#ifndef _PILE_H_
#define _PILE_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FORMAT_PILE "%p"
typedef void* T;

struct Pile
{
    int tailleMax;
    int rangSommet;
    T*  tab;
};
typedef struct Pile Pile_t;

int     initPile    (Pile_t** pile, int taille);
int     pileVide    (Pile_t* pile);
int     pilePleine  (Pile_t* pile);
int     empiler     (Pile_t* pile, T element);
int     depiler     (Pile_t* pile, T* element);
int     sommet      (Pile_t* pile, T* element);
void    libererPile (Pile_t* pile);
void    debugPile   (Pile_t* pile);

#endif // !_PILE_H_