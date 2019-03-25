#include "file.h"

/*---------------------------------------------------------------
 * initFile      Creer et initialise une file
 *                                                               
 * Entrees: file, adresse de pointeur de la tête de la file
 *          taille, entier représentant la taille de la file
 *                                                               
 * Sortie:  booleen d'erreur
 *   0 -> il y a eu une erreur d'allocation, le contenu pointé par file est NULL
 *   1 -> la file à bien été initialisée
 *
 * On alloue une tête de file:
 *      - tailleMax: taille maximum de la file
 *      - compteur: nombre d'éléments dans la file
 *      - rangPremier: rang de l'élément de tête dans le tableau de la file
 *      - rangDernier: range de l'élément de queue dans le tableau de la file
 *      - tab: tableau de la file
 *---------------------------------------------------------------
 */
int initFile(File_t** file, int taille)
{
    if((*file = (File_t*)malloc(sizeof(File_t))) != NULL)
    {
        if(((*file)->tab = (T*)malloc(sizeof(T) * taille)) != NULL)
        {
            (*file)->tailleMax = taille;
            (*file)->compteur = 0;
            (*file)->rangPremier = 0;
            (*file)->rangDernier = taille - 1;
        }
        else
        {
            free(*file);
            *file = NULL;
        }
    }
    return (*file != NULL);
}

/*---------------------------------------------------------------
 * fileVide      Teste si la file est vide
 *                                                               
 * Entrees: file, pointeur de la tête de la file
 *                                                               
 * Sortie:  booleen
 *      0 -> la file n'est pas vide
 *      1 -> la file est vide
 *
 * La fonction teste si la file est vide en regardant si 
 *  son nombre d'éléments est égal à 0
 *---------------------------------------------------------------
 */
int fileVide(File_t* file)
{
    return (file->compteur == 0);
}

/*---------------------------------------------------------------
 * filePleine      Teste si la file est pleine
 *                                                               
 * Entrees: file, pointeur de la tête de la file
 *                                                               
 * Sortie:  booleen
 *      0 -> la file n'est pas pleine
 *      1 -> la file est pleine
 *
 * La fonction teste si la file est pleine en regardant si 
 *  son nombre d'éléments est égal au nombre maximum d'éléments
 *---------------------------------------------------------------
 */
int filePleine(File_t* file)
{
    return (file->compteur == file->tailleMax);
}

/*---------------------------------------------------------------
 * enfiler      Ajoute un élément dans la file
 *                                                               
 * Entrees: file, pointeur de la tête de la file
 *          element, l'élément à ajouter dans la file
 *                                                               
 * Sortie:  booleen d'erreur
 *   0 -> la file est pleine, on ne peut pas ajouter d'élément
 *   1 -> l'élément à bien été ajouté
 *
 * On regarde d'abord si la file est pleine. Si elle ne l'est pas,
 * on ajoute 1 au compteur d'éléments, on décale le rang de queue
 * de file de 1 (modulo la taille de la file) et on met dans le 
 * tableau à cet endroit le nouvel élément.
 * 
 * Lexique: ok, booleen représentant si la file est pleine ou non
 *---------------------------------------------------------------
 */
int enfiler(File_t* file, T element)
{
    int ok = !filePleine(file);
    if(ok)
    {
        file->compteur += 1;
        file->rangDernier = (file->rangDernier + 1) % file->tailleMax;
        (file->tab)[file->rangDernier] = element;
    }
    return ok;
}

/*---------------------------------------------------------------
 * defiler      Retire un élément de la file
 *                                                               
 * Entrees: file, pointeur de la tête de la file
 *                                                               
 * Sortie:  element, adresse de l'élément à renvoyer
 *          booleen d'erreur
 *              0 -> la file est vide, on ne peut pas retirer d'élément
 *              1 -> l'élément à bien été retiré et renvoyé
 *
 * On regarde d'abord si la file est vide. Si elle ne l'est pas,
 * on enleve 1 au compteur d'éléments, on copie l'élément au rangDernier
 * du tableau dans la case mémoire pointée par "element" et on décale
 * le rang de tête de file de 1 (modulo la taille de la file).
 * 
 * Lexique: ok, booleen représentant si la file est vide ou non
 *---------------------------------------------------------------
 */
int defiler(File_t* file, T* element)
{
    int ok = !fileVide(file);
    if(ok)
    {
        file->compteur -= 1;
        *element = (file->tab)[file->rangPremier];
        file->rangPremier = (file->rangPremier + 1) % file->tailleMax;
    }
    return ok;
}

/*---------------------------------------------------------------
 * libererFile      Libere la mémoire occupé par une file
 *                                                               
 * Entrees: file, pointeur de la tête de la file
 *
 * Si la file existe, on libère le tableau de la file puis on
 * libère la tête.
 *---------------------------------------------------------------
 */
void libererFile(File_t* file)
{
    if(file != NULL)
    {
        free(file->tab);
        free(file);
    }
}

/*---------------------------------------------------------------
 * debugFile      Affiche les champs de la tête et les éléments de la file
 *                                                               
 * Entrees: file, pointeur de la tête de la file
 *
 * Affiche:
 *      - La taille maximum de la file
 *      - Le nombre déléments dans la file
 *      - Le rang du premier élément de la file
 *      - Le rang du dernier élément de la file
 *      - Tous les éléments de la file (du rangPremier au rangDernier)
 *---------------------------------------------------------------
 */
void debugFile(File_t* file)
{
    int i;

    printf("File:\n");
    printf("\tTaille max: %d\n", file->tailleMax);
    printf("\tCompteur: %d\n", file->compteur);
    printf("\tRang premier: %d\n", file->rangPremier);
    printf("\tRang dernier: %d\n", file->rangDernier);
    for(i = file->rangPremier; i != file->rangDernier; i = (i+1)%file->tailleMax)
    {
        printf("\t"FORMAT, (file->tab)[i]);
    }
    printf("\t"FORMAT, (file->tab)[i]);
}