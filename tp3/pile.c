#include "pile.h"

/*---------------------------------------------------------------
 * initPile      Creer et initialise une pile
 *                                                               
 * Entrees: pile, adresse de pointeur de la tête de la pile
 *          taille, entier représentant la taille de la pile
 *                                                               
 * Sortie:  booleen d'erreur
 *   0 -> il y a eu une erreur d'allocation, le contenu pointé par pile est NULL
 *   1 -> la pile à bien été initialisée
 *
 * On alloue une tête de pile:
 *      - tailleMax: taille maximum de la pile
 *      - rangSommet: rang de l'élément au sommet de la pile dans le tableau
 *      - tab: tableau de la pile
 *---------------------------------------------------------------
 */
int initPile(Pile_t** pile, int taille)
{
    if((*pile = (Pile_t*)malloc(sizeof(Pile_t))) != NULL)
    {
        if(((*pile)->tab = (T*)malloc(sizeof(T) * taille)) == NULL)
        {
            free(*pile);
            *pile = NULL;
        }
        else
        {
            (*pile)->tailleMax = taille;
            (*pile)->rangSommet = -1;
        }
    }
    return *pile != NULL;
}

/*---------------------------------------------------------------
 * pileVide      Teste si la pile est vide
 *                                                               
 * Entrees: pile, pointeur de la tête de la pile
 *                                                               
 * Sortie:  booleen
 *      0 -> la pile n'est pas vide
 *      1 -> la pile est vide
 *
 * La fonction teste si la pile est vide en regardant si le rang
 * du sommet de la pile est égal à -1.
 *---------------------------------------------------------------
 */
int pileVide(Pile_t* pile)
{
    return (pile->rangSommet == -1);
}

/*---------------------------------------------------------------
 * pilePleine      Teste si la pile est pleine
 *                                                               
 * Entrees: pile, pointeur de la tête de la pile
 *                                                               
 * Sortie:  booleen
 *      0 -> la pile n'est pas pleine
 *      1 -> la pile est pleine
 *
 * La fonction teste si la pile est pleine en regardant si le rang
 * du sommet de la pile est égal à la taille max de la pile (taille
 * du tableau).
 *---------------------------------------------------------------
 */
int pilePleine(Pile_t* pile)
{
    return (pile->rangSommet == (pile->tailleMax - 1));
}

/*---------------------------------------------------------------
 * empiler      Ajoute un élément dans la pile
 *                                                               
 * Entrees: pile, pointeur de la tête de la pile
 *          element, l'élément à ajouter dans la pile
 *                                                               
 * Sortie:  booleen d'erreur
 *   0 -> la pile est pleine, on ne peut pas ajouter d'élément
 *   1 -> l'élément à bien été ajouté
 *
 * On regarde d'abord si la pile est pleine. Si elle ne l'est pas,
 * on décale le rang du sommet de la pile de 1 et on met dans le 
 * tableau à cet endroit le nouvel élément.
 * 
 * Lexique: ok, booleen représentant si la pile est pleine ou non
 *---------------------------------------------------------------
 */
int empiler(Pile_t* pile, T element)
{
    int ok = !pilePleine(pile);
    if(ok)
    {
        pile->rangSommet += 1;
        (pile->tab)[pile->rangSommet] = element;
    }
    return ok;
}

/*---------------------------------------------------------------
 * depiler      Retire un élément de la pile
 *                                                               
 * Entrees: pile, pointeur de la tête de la pile
 *                                                               
 * Sortie:  element, adresse de l'élément à renvoyer
 *          booleen d'erreur
 *              0 -> la pile est vide, on ne peut pas retirer d'élément
 *              1 -> l'élément à bien été retiré et renvoyé
 *
 * On regarde d'abord si la pile est vide. Si elle ne l'est pas,
 * on copie l'élément au rangSommet du tableau dans la case mémoire
 * pointée par "element" et on enlève 1 au rangSommet.
 * 
 * Lexique: ok, booleen représentant si la pile est vide ou non
 *---------------------------------------------------------------
 */
int depiler(Pile_t* pile, T* element)
{
    int ok = !pileVide(pile);
    if(ok)
    {
        *element = (pile->tab)[pile->rangSommet];
        pile->rangSommet -= 1;
    }
    return ok;
}

/*---------------------------------------------------------------
 * sommet      Renvoie l'élément au sommet de la pile
 *                                                               
 * Entrees: pile, pointeur de la tête de la pile
 *                                                               
 * Sortie:  element, adresse de l'élément à renvoyer
 *          booleen d'erreur
 *              0 -> la pile est vide, on ne peut pas renvoyer d'élément
 *              1 -> l'élément à bien été renvoyé
 *
 * On regarde d'abord si la pile est vide. Si elle ne l'est pas,
 * on copie l'élément au rangSommet du tableau dans la case mémoire
 * pointée par "element".
 * 
 * Lexique: ok, booleen représentant si la pile est vide ou non
 *---------------------------------------------------------------
 */
int sommet(Pile_t* pile, T* element)
{
    int ok = !pileVide(pile);
    if(ok)
        *element = (pile->tab)[pile->rangSommet];
    return ok;
}

/*---------------------------------------------------------------
 * libererPile      Libere la mémoire occupé par une pile
 *                                                               
 * Entrees: pile, pointeur de la tête de la pile
 *
 * Si la pile existe, on libère le tableau de la pile puis on
 * libère la tête.
 *---------------------------------------------------------------
 */
void libererPile(Pile_t* pile)
{
    if(pile != NULL)
    {
        free(pile->tab);
        free(pile);
    }
}

T* affichagePile(Pile_t* pile)
{
    int j;
    T* mot = (T*)malloc((pile->rangSommet + 1) * sizeof(T));
    
    for (j = 0; j <= (pile->rangSommet); j++)
    {
        mot[j] = (pile->tab)[j];
    }
    return mot;
}

/*---------------------------------------------------------------
 * debugPile      Affiche les champs de la tête et les éléments de la pile
 *                                                               
 * Entrees: pile, pointeur de la tête de la pile
 *
 * Affiche:
 *      - La taille maximum de la pile
 *      - Le rang de l'élément au sommet de la pile
 *      - Tous les éléments de la pile
 *---------------------------------------------------------------
 */
void debugPile(Pile_t* pile)
{
    int i;

    printf("Pile:\n");
    printf("\tTaille max: %d\n", pile->tailleMax);
    printf("\tRang sommet: %d\n", pile->rangSommet);
    printf("\t[");
    for(i = 0; i <= pile->rangSommet; i++)
    {
        printf((i == pile->rangSommet ? FORMAT_PILE"" : FORMAT_PILE", "), (pile->tab)[i]);
    }
    printf("]\n");
}