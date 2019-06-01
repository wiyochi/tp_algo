#include "arbre.h"

/*-------------------------------------------------------------------------------
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
 *-------------------------------------------------------------------------------
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
}

/*-------------------------------------------------------------------------------
 * adj_cell      ajoute un nouveau point avec un precedent
 *                                                               
 * Entree: prec, adresse du champs lien vertical ou lien horizontal
 *         nouv, adresse du nouveau point a ajouter
 *
 * Edite les liens du precedent et du nouveau point pour l'ajouter
 * dans l'arbre
 *-------------------------------------------------------------------------------
 */
void adj_cell(noeud_t** prec, noeud_t* nouv)
{
    nouv->lh = (*prec);
    *prec = nouv;
}

/*-------------------------------------------------------------------------------
 * rech_prec      Recherche le precedent d'un point dans une liste chainee
 *                  (lien horizontal d'un arbre)
 *                                                               
 * Entree: liste, adresse du pointeur de liste
 *         l, caractere recherche
 *                                                               
 * Sortie: prec, adresse du champs "lien horizontal" du point precedent au point recherche
 *         un booleen, VRAI -> le champs lh trouve pointe bien sur un point qui a le caractere donne
 *                     FAUX -> le champs lh trouve ne pointe pas sur un point qui a le caractere donne
 *                              mais sur l'endroit ou il devrait se trouve
 *
 * On fait pointer prec sur le pointeur de debut de liste et le cour sur le premier
 * element. Tant qu'on est pas a la fin de la liste et qu'on a pas trouve la position
 * voulue de la lettre recherchee, on avance dans la liste (via le lien vertical) en
 * deplacant les pointeurs prec et cour. Lorsqu'on trouve la position de la lettre, le
 * prec contient la bonne adresse et on renvoie le booleen en testant si la lettre de
 * l'element courant est la bonne ou non.
 * 
 * Lexique: cour, pointeur sur l'element courant dont on regarde la lettre
 *-------------------------------------------------------------------------------
 */
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

/*-------------------------------------------------------------------------------
 * recherche      Recherche un mot dans un arbre
 *                                                               
 * Entree: racine, adresse du pointeur de l'arbre
 *         mot, chaine de caractere contenant le mot qu'on recherche
 *         tailleMot, taille de "mot"
 *                                                               
 * Sortie: derCell, pointeur sur le dernier point existant du mot
 *         entier representant l'indice de la derniere lettre du mot trouvee dans l'arbre
 *
 * Pour chaque lettre du mot, on recherche le precedent de cette lettre dans la
 * sous-liste chainee du niveau de la lettre (la 1ere lettre est recherchee dans les
 * racines, la 2eme dans la sous-liste des fils du point contenant la 1ere lettre etc).
 * On s'arrete soit à la fin du mot soit lorsqu'il n'y a plus de lettre correspondante
 * dans l'arbre. On renvoie alors l'indice de la lettre dans le mot ou on s'est arrete
 * et un pointeur sur la derniere cellule de l'arbre contenant une lettre du mot.
 * 
 * Lexique: i, indice de la lettre du mot traitee
 *          r, pointeur sur la derniere lettre connue du mot dans l'arbre
 *          prec, pointeur sur le champs suivant du precedent a la lettre dans la sous-liste
 *-------------------------------------------------------------------------------
 */
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

/*-------------------------------------------------------------------------------
 * ajouter_mot      Ajoute un mot dans un arbre
 *                                                               
 * Entree: racine, adresse du pointeur de l'arbre
 *         mot, chaine de caractere contenant le mot qu'on recherche
 *         tailleMot, taille de "mot"
 *
 * On se sert de la fonction recherche pour trouver le mot dans l'arbre.
 * Soit il n'existe pas et on l'insere a la racine, soit le debut existe
 * et on insere le reste au bon endroit dans l'arbre, soit toutes les lettres
 * sont presentes et on s'assure juste de mettre la derniere lettre en majuscule.
 * 
 * Lexique: i, indice de la lettre du mot trouvee dans l'arbre
 *          prec, pointeur sur le champs suivant du precedent a la lettre
 *                  dans la sous-liste (lettre d'indice i dans le mot)
 *          nouv, pointeur sur les nouveau points crees pour etre inserer dans l'arbre
 *          derCell, pointeur sur le dernier point existant du mot dans l'arbre
 *-------------------------------------------------------------------------------
 */
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

/*-------------------------------------------------------------------------------
 * librer_arbre      supprime l'arbre et libere la memoire allouee
 *                                                               
 * Entree: racine, adresse du pointeur de l'arbre
 *
 * On fait un parcours d'arbre en profondeur classique grace a une pile
 * et on libere un point a chaque fois qu'on depile.
 * 
 * Lexique: cour, pointeur sur le point courant de l'arbre dans le parcours
 *          suppr, pointeur sur le point a supprime
 *          pile, pile utilisee pour parcourir l'arbre
 *-------------------------------------------------------------------------------
 */
void liberer_arbre(noeud_t** racine)
{
    noeud_t*    cour        = *racine;
    noeud_t*    suppr       = NULL;
    Pile_t*     pile        = NULL;

    if(!initPile(&pile, TAILLE_MAX))
        exit(EXIT_FAILURE);

    while ((!pileVide(pile)) ||  (cour != NULL))
    {
        if(!empiler(pile, cour))
            printf("ERREUR EMPILER\n");
        cour = cour->lv;

        while((cour == NULL) && (!pileVide(pile)))
        {
            if(!depiler(pile, &cour))
                printf("ERREUR DEPILER\n");
            suppr = cour;
            cour=cour->lh;
            free(suppr);
        }
    }
    libererPile(pile);
    *racine = NULL;
}

/*-------------------------------------------------------------------------------
 * affichage_arbre      Affiche le contenu de l'arbre
 *                                                               
 * Entree: a, pointeur de l'arbre
 *         prefixe, chaine de caractere a affichee avant chaque mot
 *
 * On fait un parcours d'arbre classique en profondeur grace a une pile
 * et on affiche le contenu de la pile a chaque fois qu'on empile un
 * point de l'arbre avec un caractere en majuscule.
 * 
 * Lexique: cour, pointeur sur le point de l'arbre courant
 *          car_sommet, pointeur sur le point de l'arbre sur le dessus de la pile
 *          pile, pile utilisee pour parcourir l'arbre et pour afficher les mots
 *          motAffiche, tableau de pointeur sur les noeuds formants un mot
 *          i, indice pour parcourir le tableau motAffiche
 *-------------------------------------------------------------------------------
 */
void affichage_arbre(noeud_t* a, char* prefixe)
{
    noeud_t*    cour        = a;
    noeud_t*    car_sommet  = NULL;
    Pile_t*     pile        = NULL;
    noeud_t**   motAffiche  = NULL; 
    int         i;

    if(!initPile(&pile, TAILLE_MAX))
        exit(EXIT_FAILURE);

    while ((!pileVide(pile)) ||  (cour != NULL))
    {
        if(!empiler(pile, cour))
            printf("ERREUR EMPILER\n");
        cour = cour->lv;

        if(!sommet(pile, &car_sommet))
            printf("ERREUR SOMMET\n");
        if ((car_sommet->lettre >= 'A') && (car_sommet->lettre <= 'Z'))
        {
            printf("%s", prefixe);
            motAffiche = affichagePile(pile);
            for(i = 0; i <= pile->rangSommet; i++)
                printf("%c", tolower(motAffiche[i]->lettre));
            printf("\n");
            free(motAffiche);
        }

        while((cour == NULL) && (!pileVide(pile)))
        {
            if(!depiler(pile, &cour))
                printf("ERREUR DEPILER\n");
            cour = cour->lh;
        }
    }
    libererPile(pile);
}

/*-------------------------------------------------------------------------------
 * affichage_motif      Affiche les mots d'un arbre commencant par un motif
 *                                                               
 * Entree: racine, pointeur de l'arbre
 *         motif, chaine de caractere representant le motif
 *         tailleMotif, taille de la chaine de caractere motif
 *
 * On fait une recherche dans l'arbre du motif. Ainsi si le motif est trouve
 * complet dans l'arbre, on affiche avec la fonction "affichage_arbre" les mots
 * en prenant comme racine le lien vertical du dernier point trouve avec la
 * recherche et comme prefixe a afficher avant le motif.
 * 
 * Lexique: racineMotif, pointeur sur le point de l'arbre contenant la derniere
 *                          lettre du motif
 *          ind, indice retourne par la recherche pour verifier si le motif est
 *                  est en entier dans l'arbre
 *-------------------------------------------------------------------------------
 */
void affichage_motif(noeud_t* racine, char* motif, int tailleMotif)
{
    noeud_t*    racineMotif = NULL;
    int         ind         = 0;

    if(tailleMotif > 0)
    {
        ind = recherche(&racine, motif, tailleMotif, &racineMotif);

        if(ind == tailleMotif)
        {
            if(racineMotif->lettre >= 'A' && racineMotif->lettre <= 'Z') // Si la derniere lettre du motif est une majuscule
                printf("%s\n", motif);                                   // on affiche le motif
            affichage_arbre(racineMotif->lv, motif);
        }
    }
}

/*-------------------------------------------------------------------------------
 * debug_arbre      Affiche le contenu d'un arbre
 *                                                               
 * Entree: racine, pointeur de l'arbre
 *
 * On fait un parcours d'arbre classique en profondeur grace a une pile
 * et on affiche la lettre courant avec des "-" avant pour indiquer son
 * niveau dans l'arbre.
 * 
 * Lexique: cour, pointeur sur le point de l'arbre courant
 *          pile, pile utilisee pour parcourir l'arbre et pour afficher les mots
 *          cmp, niveau dans l'arbre (incremente lorsqu'on empile et decrementer
 *                  lorsqu'on depile)
 *-------------------------------------------------------------------------------
 */
void debug_arbre(noeud_t* racine)
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
        printf("%c\n", cour->lettre);
        
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

    libererPile(pile);
}