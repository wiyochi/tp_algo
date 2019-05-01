#ifndef _ARBRE_H_
#define _ARBRE_H_

#include "pile.h"

struct noeud
{
    char            lettre;
    struct noeud*   lv;
    struct noeud*   lh;
};
typedef struct noeud noeud_t;


#endif // !_ARBRE_H_