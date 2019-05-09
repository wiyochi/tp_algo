#include "arbre.h"

noeud_t* creer_cell(char l)
{
    noeud_t* nouv = (noeud_t*)malloc(sizeof(noeud_t));
    if(NULL != nouv)
    {
        nouv->lettre = l;
        nouv->lv = NULL;
        nouv->lh = NULL;
    }
    return nouv;
}

void adj_cell(noeud_t** prec, noeud_t* nouv)
{
    nouv->lh = (*prec);
    *prec = nouv;
}

int rech_prec(noeud_t** liste, char l, noeud_t*** prec)
{
    *prec = liste;
    noeud_t* cour = *liste;

    while(cour != NULL && LOWER(cour->lettre) < LOWER(l))
    {
        *prec = &(cour->lh);
        cour = cour->lh;
    }
    return (cour != NULL && LOWER(cour->lettre) == LOWER(l));
}

int recherche(noeud_t** racine, char* mot, int tailleMot, noeud_t** derCell)
{
    int         i = 0;
    noeud_t**   r = racine;
    noeud_t*    cour = NULL;
    noeud_t**   prec = NULL;

    while(i < tailleMot && rech_prec(r, mot[i], &prec))
    {
        cour = *prec;
        r = &((*prec)->lv);
        i++;
    }

    *derCell = cour;
    return i;
}

// A DEBOGGER
void ajouter_mot(noeud_t** racine, char* mot, int tailleMot)
{
    int         i = 0;
    noeud_t**   prec = racine;
    noeud_t*    nouv = NULL;
    noeud_t*    derCell = NULL;

    i = recherche(racine, mot, tailleMot, &derCell);
    if(derCell == NULL)
        rech_prec(racine, mot[0], &prec);           // Si la 1ere lettre n'existe pas dans le 1er niveau de l'arbre, on recherche la place que doit prendre cette 1ere lettre
    else
        rech_prec(&(derCell->lv), mot[i], &prec);   // Sinon, on recherche la place de la lettre suivante

    while(i < tailleMot)
    {
        nouv = creer_cell(mot[i]);
        adj_cell(prec, nouv);

        derCell = *prec;
        prec = &((*prec)->lv);
        i++;
    }
    
    derCell->lettre = UPPER(derCell->lettre);
}

// TODO: separer la fct en deux -> une qui recherche et une qui modifie
/*void ajouter_mot(noeud_t** racine, char* mot, int tailleMot)
{
    int         i;
    noeud_t**   prec;
    noeud_t**   r = racine;
    noeud_t*    nouv;

    for(i = 0; i < tailleMot; i++)
    {
        if(rech_prec(r, mot[i], &prec))
        {
            if(i == (tailleMot - 1))
            {
                (*prec)->lettre = UPPER((*prec)->lettre);
            }
            else
            {
                r = &((*prec)->lv);
            }
        }
        else
        {
            for(; i < tailleMot-1; i++)
            {
                nouv = creer_cell(mot[i]);
                adj_cell(prec, nouv);
                prec = &((*prec)->lv);
            }
            nouv = creer_cell(UPPER(mot[i]));
            adj_cell(prec, nouv);
        }
    }
}
*/

void debugArbre(noeud_t* racine)
{
    noeud_t*    cour = racine;
    Pile_t*     pile = NULL;
    int         cmp  = 0;
    int         i;

    if(!initPile(&pile, 100))
        exit(EXIT_FAILURE);

    while(!pileVide(pile) || cour != NULL)
    {
        for(i = 0; i < cmp; i++) printf("-");
        printf("%c : %p\n", cour->lettre, cour);
        
        if(!empiler(pile, cour))
            printf("ERREUR EMPILER\n");
        cour = cour->lv;
        cmp++;

        while(cour == NULL && !pileVide(pile))
        {
            if(!depiler(pile, &cour))
                printf("ERREUR DEPILER\n");
            cour = cour->lh;
            cmp--;
        }
    }
}