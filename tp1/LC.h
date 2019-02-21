#ifndef _LC_H_
#define _LC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Message
{
    int                 dateDebut;
    int                 dateFin;
    char              * message;
    struct Message    * suivant;
};
typedef struct Message Message_t;

Message_t*  creerElement        (int, int, const char*);
Message_t** rechercherPrecedent (Message_t**, Message_t*);
void        ajouterElement      (Message_t**, Message_t*);
void        adjonctionCellule   (Message_t**, Message_t*);
void        suppressionCellule  (Message_t**);
void        libererListe        (Message_t**);
void        debugListe          (Message_t*);
void        debugElement        (Message_t*);


#endif // !_LC_H_