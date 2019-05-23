#ifndef _DICTIONNAIRE_H_
#define _DICTIONNAIRE_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define HASH_MAX 29

struct cell
{
    char* mot;
    char* trad;
    struct cell* suivant;
};
typedef struct cell cell_t;

unsigned int    hash_string     (const char *str);
int             creer_cell      (cell_t** nouv, char* mot, char* trad);
void            adj_cell        (cell_t* nouv, cell_t** prec);
void            liberer_cell    (cell_t** prec);
int             rech_cell       (cell_t* liste, char* mot, cell_t** trouve);
cell_t**        init_table      ();
void            ajouter_table   (cell_t** MAJ, char* mot, char* trad);
void            debug_table     (cell_t** MAJ);
void            liberer_table   (cell_t** MAJ);

#endif // !_DICTIONNAIRE_H_