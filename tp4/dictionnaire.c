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
    *nouv = (cell_t*)malloc(sizeof(cell_t));
    if(*nouv != NULL)
    {
        (*nouv)->
    }
}