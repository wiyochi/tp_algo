#ifndef _ARBRE_H_
#define _ARBRE_H_

#include <stdio.h>
#include <ctype.h>
#include "pile.h"

#define UPPER(l) (((l)>='a'&&(l)<='z')?((l)-'a'+'A'):(l))
#define LOWER(l) (((l)>='A'&&(l)<='Z')?((l)-'A'+'a'):(l))
#define LOG(x) printf("# "x"\n");
#define TAILLE_MAX 20

struct noeud
{
    char            lettre;
    struct noeud*   lv;
    struct noeud*   lh;
};
typedef struct noeud noeud_t;

noeud_t*    creer_cell      (char l);
void        adj_cell        (noeud_t** prec, noeud_t* nouv);
int         rech_prec       (noeud_t** liste, char l, noeud_t*** prec);
int         recherche       (noeud_t** racine, char* mot, int tailleMot, noeud_t** derCell);
void        ajouter_mot     (noeud_t** racine, char* mot, int tailleMot);
void        affichage_arbre (noeud_t* a, char* prefixe);
void        affichage_motif (noeud_t* racine, char* motif, int tailleMotif);
void        liberer_arbre   (noeud_t** racine);
void        debug_arbre     (noeud_t* racine);

#endif // !_ARBRE_H_