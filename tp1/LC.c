#include "LC.h"

/*---------------------------------------------------------------
 * creerElement         Creer une cellule "Message"              
 *                                                               
 * Entrees: ddebut, dfin 2 entiers representant des dates        
 *          msg, une chaine de caracteres                        
 *                                                               
 * Sortie:  adresse d'une nouvelle cellule allouee  
 *
 * On alloue un espace mémoire de la taille d'un élément et on
 *  initialise ses champs avec les données passées en argument   
 * 
 * Lexique: element, pointeur sur le nouvel élément que l'on créer
 *                    et que l'on initialise
 *---------------------------------------------------------------
 */
Message_t* creerElement(int ddebut, int dfin, const char* msg)
{
    Message_t * element;

    element = (Message_t*)malloc(sizeof(Message_t));
    if(element != NULL)
    {
        element->dateDebut = ddebut;
        element->dateFin = dfin;
        element->message = (char*)malloc(sizeof(char) * (strlen(msg)+1));
        strcpy(element->message, msg);
        element->suivant = NULL;
    }
    return element;
}

/*-------------------------------------------------------------------------
 * rechercherPrecedent   Recherche le precedent d'une cellule donnee       
 *                                                                         
 * Entr�es: liste, adresse du pointeur de liste                            
 *          element, adresse de la cellule dont il faut le precedent       
 *                                                                         
 * Sortie:  adresse de la case "suivant" de la cellule precedente          
 *                                                                         
 *  En l'occurence, le precedent pointe sur le champs "suivant" de la cellule
 *   précédente à la cellule dont la date de debut est egale ou superieur 
 *   a la date de debut de l'element donne
 *
 * Lexique: cour, pointeur sur l'élément courant dont on teste la date de début
 *          prec, pointeur sur le champs suivant de l'élément précédent à cour
 *-------------------------------------------------------------------------
 */
Message_t** rechercherPrecedent(Message_t** liste, Message_t* element)
{
    Message_t* cour = *liste;
    Message_t** prec = liste;

    while(cour != NULL && cour->dateDebut < element->dateDebut)
    {
        prec = &(cour->suivant);
        cour = cour->suivant;
    }
    return prec;
}

/*-------------------------------------------------------------------------
 * ajouterElement   Ajoute une cellule a la liste de message               
 *                                                                         
 * Entrees: liste, adresse du pointeur de liste                            
 *          element, adresse de la cellule qu'il faut ajouter a la liste   
 *                                                                         
 *   Fonction la uniquement pour "simplifier" dans le programme principal  
 *   Recherche le precedent avec recherchePrecedent et appelle             
 *    adjonctionCellule avec celui-ci
 * 
 * Lexique: prec, pointeur sur le champs suivant de l'element precedent
 *                  a l'endroit ou devrait se situer "element"                                 
 *-------------------------------------------------------------------------
 */
void ajouterElement(Message_t** liste, Message_t* element)
{
    Message_t** prec = rechercherPrecedent(liste, element);
    adjonctionCellule(prec, element);
}

/*-------------------------------------------------------------------------
 * adjonctionCellule   Ajoute une cellule a la liste de message            
 *                                                                         
 * Entrees: prec, adresse du champs "suivant" de la cellule precedente     
 *          element, adresse de la cellule qu'il faut ajouter a la liste   
 *                                                                         
 *   Edite les liens du precedent et de l'element pour l'ajouter dans la   
 *    liste chainee                                                        
 *-------------------------------------------------------------------------
 */
void adjonctionCellule(Message_t** prec, Message_t* element)
{
    element->suivant = *prec;
    *prec = element;
}

/*-------------------------------------------------------------------------
 * suppressionCellule   Supprime une cellule de la liste                   
 *                                                                         
 * Entrees: prec, adresse du champs "suivant" de la cellule precedente     
 *                                                                         
 *   Edite les liens du precedent pour supprimer l'element de la liste     
 *    libere la memoire du message de l'element supprime                 
 *    libere la memoire de l'element supprime de la liste                  
 *
 * Lexique: el, pointeur sur l'élément à supprimer (permet de le libérer une
 *               fois la modification des liens faites)
 *-------------------------------------------------------------------------
 */
void suppressionCellule(Message_t** prec)
{
    Message_t* el = *prec;
    *prec = el->suivant;
    free(el->message);
    free(el);
}

/*-------------------------------------------------------------------------
 * libererListe   Supprime toutes les cellules de la liste                 
 *                                                                         
 * Entrees: liste, adresse du pointeur de liste                            
 *                                                                         
 *   Utilise suppressionCellule pour supprimer tous les elements           
 *    de la liste. On supprime l'élément en tête jusqu'à ce que la liste
 *    soit vide                                                          
 *-------------------------------------------------------------------------
 */
void libererListe(Message_t** liste)
{
    while(*liste != NULL)
    {
        suppressionCellule(liste);
    }
}

/*-------------------------------------------------------------------------
 * debugListe   Affiche tout les elements d'une liste de message           
 *                                                                         
 * Entrees: liste, pointeur de la liste                                    
 *                                                                         
 *   Affiche les éléments de la liste de manière complète                  
 *   (place dans la liste, adresse mémoire, contenu et adresse du suivant)
 *
 * Lexique: cour, pointeur sur l'élément à afficher
 *          cpt, compteur d'élément pour afficher la place des éléments
 *                dans la liste
 *-------------------------------------------------------------------------
 */
void debugListe(Message_t* liste)
{
    Message_t* cour = liste;
    int cpt = 1;

    while(cour != NULL)
    {
        printf("Message %d:\n", cpt);
        debugElement(cour);
        cour = cour->suivant;
        cpt++;
    }
}

/*-------------------------------------------------------------------------
 * debugElement   Affiche un element d'une liste de message                
 *                                                                         
 * Entrees: element, pointeur sur un structure message                     
 *                                                                         
 *   Affiche un éléments de la liste de manière complète                   
 *    (adresse mémoire, contenu et adresse du suivant)                     
 *-------------------------------------------------------------------------
 */
void debugElement(Message_t* element)
{
    printf("\tpt: %p\n", element);
    printf("\tDate debut: %d\n", element->dateDebut);
    printf("\tDate fin: %d\n", element->dateFin);
    printf("\tMessage: %s\n", element->message);
    printf("\tSuivant: %p\n", element->suivant);
}
