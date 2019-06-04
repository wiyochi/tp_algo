#include "dictionnaire.h"

/*-------------------------------------------------------------------------------
 * hash_string      Fonction de Hachage de D.J. Bernstein
 *-------------------------------------------------------------------------------
 */
unsigned int hash_string(const char *str)
{ 
    unsigned int hash = 5381;
    const char *s;

    for (s = str; *s; s++)
 	    hash = ((hash << 5) + hash) + tolower(*s);
         
    return (hash & 0x7FFFFFFF)%HASH_MAX;
}

/*-------------------------------------------------------------------------------
 * creer_cell      Creer une cellule contenant un mot et sa traduction
 *                                                               
 * Entree: mot, chaine de caractere du mot a mettre dans la cellule
 *         trad, chaine de caractere de la traduction a mettre dans la cellule
 *                                                               
 * Sortie: nouv, pointeur sur la nouvelle cellule creee
 *         un booleen, VRAI -> la cellule a bien ete creee
 *                     FAUX -> il y a eu un probleme d'allocation, la cellule n'a pas
 *                              pu etre creee
 *
 * On alloue une cellule, si l'allocation s'est bien passee on copie le contenu de
 * "mot" pour le mettre dans le champs "mot" de la cellule (l'allocation se fait avec
 * strdup). Si l'allocation s'est faite, on fait la meme chose pour "trad". Si une
 * allocation n'a pas pu avoir lieu, on libere la memoire precedemment allouee et
 * on renvoie FAUX.
 * 
 * Lexique: ok, booleen VRAI -> la cellule a bien ete creee
 *                      FAUX -> il y a eu un probleme d'allocation, la cellule n'a pas
 *                               pu etre creee
 *-------------------------------------------------------------------------------
 */
int creer_cell(cell_t** nouv, char* mot, char* trad)
{
    int ok = 0;
    *nouv = (cell_t*)malloc(sizeof(cell_t));
    if(*nouv != NULL)
    {
        (*nouv)->mot = strdup(mot);
        if((*nouv)->mot != NULL)
        {
            (*nouv)->trad = strdup(trad);
            if((*nouv)->trad != NULL)
            {
                (*nouv)->suivant = NULL;
                ok = 1;
            }
            else
            {
                free((*nouv)->mot);
                free(*nouv);
            }
        }
        else
        {
            free(*nouv);
        }
    }
    return ok;
}

/*-------------------------------------------------------------------------------
 * adj_cell      Ajoute une nouvelle cellule avec un precedent
 *                                                               
 * Entree: prec, adresse du champs "suivant" d'une cellule
 *                  (ou du champs "premier" d'une case de table)
 *         nouv, adresse de la nouvelle cellule a ajouter
 *
 * Edite les liens du precedent et de la nouvelle cellule pour l'ajouter
 * dans la sous-table
 *-------------------------------------------------------------------------------
 */
void adj_cell(cell_t* nouv, cell_t** prec)
{
    nouv->suivant = (*prec);
    (*prec) = nouv;
}

/*-------------------------------------------------------------------------------
 * liberer_cell      Libere la memoire occupee par une cellule
 *                                                               
 * Entree: prec, adresse du champs "suivant" d'une cellule
 *                  (ou du champs "premier" d'une case de table)
 *
 * Edite les liens de la sous-table pour enlever la cellule de celle-ci puis
 * libere la memoire du mot, la memoire de la traduction et enfin la memoire
 * de la cellule
 * 
 * Lexique: suppr, pointeur sur la cellule a supprimer
 *-------------------------------------------------------------------------------
 */
void liberer_cell(cell_t** prec)
{
    cell_t* suppr = (*prec);
    (*prec) = suppr->suivant;
    free(suppr->mot);
    free(suppr->trad);
    free(suppr);
}

/*-------------------------------------------------------------------------------
 * rech_cell      Recherche une cellule dans une sous-table avec un mot
 *                                                               
 * Entree: liste, pointeur de la sous-table dans laquelle on recherche le mot
 *         mot, chaine de caractere du mot a trouve
 *                                                               
 * Sortie: trouve, pointeur sur la cellule trouvee
 *         un booleen, VRAI -> le mot a bien ete trouve dans la sous-table
 *                     FAUX -> le mot n'a pas ete trouve
 *
 * On parcours la sous-table. On s'arrete soit quand on est a la fin, soit quand
 * on a trouve le mot recherche.
 * 
 * Lexique: cour, pointeur de la cellule actuelle dans le parcours
 *-------------------------------------------------------------------------------
 */
int rech_cell(cell_t* liste, char* mot, cell_t** trouve)
{
    cell_t* cour = liste;

    while(cour != NULL && strcmp(mot, cour->mot) != 0)
        cour = cour->suivant;

    *trouve = cour;
    return (cour != NULL);
}


/*-------------------------------------------------------------------------------
 * init_table      Cree et initialise une table majeure
 *                                                               
 * Sortie: une table majeur -> un tableau de structure chacune ayant un compteur
 *          de cellule et un pointeur sur la sous-table
 *
 * On alloue un tableau de structure. Si il a bien ete cree, on initialise chaque
 * structure avec un compteur a 0 et un pointeur de sous-table NULL
 *-------------------------------------------------------------------------------
 */
table_t* init_table()
{
    int i;
    table_t* MAJ = (table_t*)malloc(sizeof(table_t) * HASH_MAX);
    for(i = 0; i < HASH_MAX; i++)
    {
        MAJ[i].premier = NULL;
        MAJ[i].compteur = 0;
    }
    return MAJ;
}

/*-------------------------------------------------------------------------------
 * ajouter_table      Ajoute un mot avec sa traduction dans une table
 *                                                               
 * Entree: MAJ, table majeure dans laquelle on ajoute le mot
 *         mot, chaine de caractere du mot
 *         trad, chaine de caractere de la traduction
 *
 * Avec le hash du mot, on trouve la tete de sous-table dans la table majeure.
 * Si il y a une sous-table
 * |  On recherche le mot dans la sous-table
 * |  Si le mot existe deja
 * |  |  On remplace la traduction par celle passee en parametre
 * |  Sinon
 * |  |  On creer une nouvelle cellule avec le mot et la traductionet on l'insere
 * |  |  en tete de la sous-table. (Et on increment le compteur de la sous-table)
 * |  fsi
 * Sinon
 * |  On creer une nouvelle cellule avec le mot et la traductionet on l'insere
 * |  en tete de la sous-table. (Et on increment le compteur de la sous-table)
 * fsi
 * 
 * Lexique: hash, hash du mot qu'on veut ajouter dans la table
 *          trouve, pointeur sur la cellule contenant le mot (si elle existe)
 *          nouv, pointeur sur la cellule qu'on creee et qu'on ajoute (si besoin)
 *-------------------------------------------------------------------------------
 */
void ajouter_table(table_t* MAJ, char* mot, char* trad)
{
    int hash = hash_string(mot);
    cell_t* trouve = NULL;
    cell_t* nouv = NULL;

    if(MAJ[hash].premier != NULL)
    {
        if(rech_cell(MAJ[hash].premier, mot, &trouve))
        {
            if(trouve->trad != NULL)
                free(trouve->trad);
            trouve->trad = strdup(trad);
        }
        else
        {
            if(creer_cell(&nouv, mot, trad))
            {
                adj_cell(nouv, &(MAJ[hash].premier));
                MAJ[hash].compteur += 1;
            }
        }
    }
    else
    {
        if(creer_cell(&nouv, mot, trad))
        {
            adj_cell(nouv, &(MAJ[hash].premier));
            MAJ[hash].compteur += 1;
        }
    }
}

/*-------------------------------------------------------------------------------
 * recherche_table      Recherche un mot dans une table
 *                                                               
 * Entree: MAJ, table majeure dans laquelle on recherche le mot
 *         mot, chaine de caractere du mot
 *                                                               
 * Sortie: trouve, pointeur sur la cellule contenant le mot
 *         un booleen, VRAI -> le mot a bien ete trouve dans la table
 *                     FAUX -> le mot n'a pas ete trouve
 * 
 * On utilise la fonction rech_cell qui fait la meme chose mais dans une sous-table.
 * On lui passe juste en parametre la tete de sous-table correspondante au hash du mot
 *-------------------------------------------------------------------------------
 */
int recherche_table(table_t* MAJ, char* mot, cell_t** trouve)
{
    return rech_cell(MAJ[hash_string(mot)].premier, mot, trouve);
}

/*-------------------------------------------------------------------------------
 * debug_table      Affiche tous le contenu d'une table
 *                                                               
 * Entree: MAJ, table majeure
 * 
 * On parcours la table majeure, pour chaque sous-table on affiche son indice dans
 * la table majeure, on affiche le compteur et on affiche chaque mot et sa traduction
 * de la sous-table.
 * 
 * Lexique: cour, pointeur de la cellule actuelle dans le parcours de,sous-table
 *-------------------------------------------------------------------------------
 */
void debug_table(table_t* MAJ)
{
    int i;
    cell_t* cour = NULL;

    for(i = 0; i < HASH_MAX; i++)
    {
        printf("|%d|(%d)\n", i, MAJ[i].compteur);
        cour = MAJ[i].premier;
        while(cour != NULL)
        {
            printf(" \\-> %s;%s\n", cour->mot, cour->trad);
            cour = cour->suivant;
        }
    }
}

/*-------------------------------------------------------------------------------
 * liberer_table      Libere la memoire utilisee par une table
 *                                                               
 * Entree: MAJ, table majeure a liberer
 *
 * On parcours la table majeure, pour chaque sous-table on supprime l'element en tete
 * et on le libere jusqu'a ce que la sous-table soit vide. On met alors le compteur
 * de la sous-table a 0 et son pointeur de tete a NULL
 * 
 * Lexique: i, indice de parcours dans la table majeure
 *-------------------------------------------------------------------------------
 */
void liberer_table(table_t* MAJ)
{
    int i;

    for(i = 0; i < HASH_MAX; i++)
    {
        while(MAJ[i].premier != NULL)
            liberer_cell(&(MAJ[i].premier));
        MAJ[i].premier = NULL;
        MAJ[i].compteur = 0;
    }
    free(MAJ);
}