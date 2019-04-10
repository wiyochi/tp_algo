#ifndef _ARBRE_H_
#define _ARBRE_H_

#include "pile.h"

#define FORMAT_ARBRE "%d"
typedef int T;

struct noeud
{
    T               valeur;
    struct noeud*   lv;
    struct noeud*   lh;
};
typedef struct noeud noeud_t;


#endif // !_ARBRE_H_