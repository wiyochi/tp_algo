#include "dictionnaire.h"

unsigned int hash_string(const char *str)
{ 
    unsigned int hash = 5381;                /*  fonction de hachage de D.J. Bernstein*/
    const char *s;

    for (s = str; *s; s++)
 	    hash = ((hash << 5) + hash) + tolower(*s);
         
    return (hash & 0x7FFFFFFF)%HASH_MAX;
}

int creer_cell(cell_t** nouv, char* mot, char* trad)
{
    int ok = 0;
    *nouv = (cell_t*)malloc(sizeof(cell_t));
    if(*nouv != NULL)
    {
        (*nouv)->mot = (char*)malloc(sizeof(char) * (strlen(mot) + 1));
        if((*nouv)->mot != NULL)
        {
            strcpy((*nouv)->mot, mot);

            (*nouv)->trad = (char*)malloc(sizeof(char) * (strlen(trad) + 1));
            if((*nouv)->trad != NULL)
            {
                strcpy((*nouv)->trad, trad);
                ok = 1;
            }
        }
        (*nouv)->suivant = NULL;
    }
    return ok;
}

void adj_cell(cell_t* nouv, cell_t** prec)
{
    nouv->suivant = (*prec);
    (*prec) = nouv;
}

void liberer_cell(cell_t** prec)
{
    cell_t* suppr = (*prec);
    (*prec) = suppr->suivant;
    free(suppr->mot);
    printf("trad: %s\n", suppr->trad);
    free(suppr->trad);
    free(suppr);
}

int rech_cell(cell_t* liste, char* mot, cell_t** trouve)
{
    cell_t* cour = liste;

    while(cour != NULL && strcmp(mot, cour->mot) != 0)
        cour = cour->suivant;

    *trouve = cour;
    return (cour != NULL);
}

cell_t** init_table()
{
    int i;
    cell_t** MAJ = (cell_t**)malloc(sizeof(cell_t*) * HASH_MAX);
    for(i = 0; i < HASH_MAX; i++)
        MAJ[i] = NULL;
    return MAJ;
}

void ajouter_table(cell_t** MAJ, char* mot, char* trad)
{
    int hash = hash_string(mot);
    cell_t* trouve = NULL;
    cell_t* nouv = NULL;

    if(MAJ[hash] != NULL)
    {
        if(rech_cell(MAJ[hash], mot, &trouve))
        {
            trouve->trad = trad;
        }
        else
        {
            if(creer_cell(&nouv, mot, trad))
            {
                adj_cell(nouv, &(MAJ[hash]));
            }
        }
    }
    else
    {
        if(creer_cell(&nouv, mot, trad))
        {
            adj_cell(nouv, &(MAJ[hash]));
        }
    }
}

void debug_table(cell_t** MAJ)
{
    int i;
    cell_t* cour = NULL;

    for(i = 0; i < HASH_MAX; i++)
    {
        printf("|%d|", i);
        cour = MAJ[i];
        while(cour != NULL)
        {
            printf("  %s;%s |", cour->mot, cour->trad);
            cour = cour->suivant;
        }
        printf("\n");
    }
}

void liberer_table(cell_t** MAJ)
{
    int i;

    for(i = 0; i < HASH_MAX; i++)
    {
        while(MAJ[i] != NULL)
            liberer_cell(&(MAJ[i]));
        MAJ[i] = NULL;
    }
    free(MAJ);
}