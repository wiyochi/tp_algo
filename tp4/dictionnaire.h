#ifndef _DICTIONNAIRE_H_
#define _DICTIONNAIRE_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define HASH_MAX 29

struct cell
{
    char* mot;
    char* trad;
    struct cell* suivant;
};
typedef struct cell cell_t;

unsigned int    hash_string (const char *str);
int             creer_cell  (cell_t** nouv);
void            adj_cell    (cell_t* nouv, cell_t** prec);

#endif // !_DICTIONNAIRE_H_