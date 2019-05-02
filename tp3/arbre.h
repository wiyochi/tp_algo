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

noeud_t*    creer_cell  (char l);
void        adj_cell    (noeud_t** prec, noeud_t* nouv);
int         rech_prec   (noeud_t** liste, char l, noeud_t*** prec);
void        ajouter_mot (noeud_t** racine, char* mot, int tailleMot);
void        debugArbre  (noeud_t* racine);
#endif // !_ARBRE_H_