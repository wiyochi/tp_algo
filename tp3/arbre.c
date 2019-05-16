#include "arbre.h"

/*---------------------------------------------------------------
 * creer_cell      Creer et initialise un point d'arbre
 *                                                               
 * Entree: l, caractere à inserer dans le nouveau point
 *                                                               
 * Sortie:  pointeur sur le nouveau point alloue
 *              (ou NULL si il n'y a pas assez de memoire)
 *
 * On essaie d'allouer un point d'arbre, si la memoire est suffisante
 * on initialise son premier champs avec le caractere donne et on met
 * les champs de lien vertical et horizontal a NULL
 *---------------------------------------------------------------
 */
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
}/*-------------------------------------------------------------------------
 * adjonctionCellule   Ajoute une cellule a la liste de message            
 *                                                                         
 * Entrees: prec, adresse du champs "suivant" de la cellule precedente     
 *          element, adresse de la cellule qu'il faut ajouter a la liste   
 *                                                                         
 *   Edite les liens du precedent et de l'element pour l'ajouter dans la   
 *    liste chainee                                                        
 *-------------------------------------------------------------------------
 */

/*---------------------------------------------------------------
 * adj_cell      ajoute un nouveau point avec un precedent
 *                                                               
 * Entree: prec, adresse du champs lien vertical ou lien horizontal
 *         nouv, adress
 *
 * On essaie d'allouer un point d'arbre, si la memoire est suffisante
 * on initialise son premier champs avec le caractere donne et on met
 * les champs de lien vertical et horizontal a NULL
 *---------------------------------------------------------------
 */
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
    noeud_t**   prec = NULL;

    while(i < tailleMot && rech_prec(r, mot[i], &prec))
    {
        *derCell = *prec;
        r = &((*prec)->lv);
        i++;
    }

    return i;
}

void ajouter_mot(noeud_t** racine, char* mot, int tailleMot)
{
    int         i       = 0;
    noeud_t**   prec    = racine;
    noeud_t*    nouv    = NULL;
    noeud_t*    derCell = NULL;

    if(tailleMot > 0)
    {
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