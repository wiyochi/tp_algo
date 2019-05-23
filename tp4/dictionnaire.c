#include "dictionnaire.h"

unsigned int hash_string(const char *str)
{ 
    unsigned int hash = 5381;                /*  fonction de hachage de D.J. Bernstein*/
    const char *s;

    for (s = str; *s; s++)
 	    hash = ((hash << 5) + hash) + tolower(*s);
         
    return (hash & 0x7FFFFFFF)%HASH_MAX;
}