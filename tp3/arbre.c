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
    nouv->lh = (*prec)->lh;
    (*prec)->lh = nouv;
}

int rech_prec(noeud_t** liste, char l, noeud_t*** prec)
{
    *prec = liste;
    noeud_t*  cour = *liste;

    while(cour != NULL && cour->lettre <= l)
    {
        *prec = &(cour->lh);
        cour = cour->lh;
    }
    return (cour->lettre == l);
}

void ajouter_mot(noeud_t** racine, char* mot, int tailleMot)
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
                if((*prec)->lettre >= 'a' && (*prec)->lettre <= 'z')
                    (*prec)->lettre = (*prec)->lettre - 'a' + 'A';
            }
            else
            {
                r = &((*r)->lv);
            }
        }
        else
        {
            for(; i < tailleMot; i++)
            {
                nouv = creer_cell(mot[i]);
                adj_cell(prec, nouv);
                prec = &(*(prec)->lv);
            }
        }
    }
}

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
        if(!empiler(pile, cour))
            printf("ERREUR EMPILER\n");
        cour = cour->lv;
        cmp++;

        for(i = 0; i < cmp; i++) printf("\t");
        printf("%c\n", cour->lettre);

        while(cour == NULL && !pileVide(pile))
        {
            if(!depiler(pile, &cour))
                printf("ERREUR DEPILER\n");
            cour = cour->lh;
        }
    }
}