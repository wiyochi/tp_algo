#include "LC.h"

/*---------------------------------------------------------------
 * creerElement         Creer une cellule "Message"              
 *                                                               
 * Entr�es: ddebut, dfin 2 entiers repr�sentant des dates        
 *          msg, une cha�ne de caract�res                        
 *                                                               
 * Sortie:  adresse d'une nouvelle cellule allou�e  
 *
 * On alloue un espace mémoire de la taille d'un élément et on
 *  initialise ses champs avec les données passées en argument   
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
 * rechercherPrecedent   Recherche le pr�cedent d'une cellule donn�e       
 *                                                                         
 * Entr�es: liste, adresse du pointeur de liste                            
 *          element, adresse de la cellule dont il faut le pr�cedent       
 *                                                                         
 * Sortie:  adresse de la case "suivant" de la cellule precedente          
 *                                                                         
 *  En l'occurence, le pr�cedent pointe sur le champs "suivant" de la cellule
 *   précédente à la cellule dont la date de d�but est �gale ou sup�rieur 
 *   a la date de d�but de l'�lement donn� 
 *
 * Lexique: cour, pointeur sur l'élément courant dont on teste la date de début
            prec, pointeur sur le champs suivant de l'élément précédent à cour
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
 * ajouterElement   Ajoute une cellule � la liste de message               
 *                                                                         
 * Entr�es: liste, adresse du pointeur de liste                            
 *          element, adresse de la cellule qu'il faut ajouter � la liste   
 *                                                                         
 *   Fonction l� uniquement pour "simplifier" dans le programme principal  
 *   Recherche le precedent avec recherchePrecedent et appelle             
 *    adjonctionCellule avec celui-ci                                      
 *-------------------------------------------------------------------------
 */
void ajouterElement(Message_t** liste, Message_t* element)
{
    Message_t** prec = rechercherPrecedent(liste, element);
    adjonctionCellule(prec, element);
}

/*-------------------------------------------------------------------------
 * adjonctionCellule   Ajoute une cellule � la liste de message            
 *                                                                         
 * Entr�es: prec, adresse du champs "suivant" de la cellule pr�cedente     
 *          element, adresse de la cellule qu'il faut ajouter � la liste   
 *                                                                         
 *   Edite les liens du pr�c�dent et de l'�l�ment pour l'ajouter dans la   
 *    liste cha�n�e                                                        
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
 * Entr�es: prec, adresse du champs "suivant" de la cellule pr�cedente     
 *                                                                         
 *   Edite les liens du pr�c�dent pour supprimer l'�l�ment de la liste     
 *    lib�re la m�moire du message de l'�l�ment supprim�                   
 *    lib�re la m�moire de l'�l�ment supprim� de la liste                  
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
 * Entr�es: liste, adresse du pointeur de liste                            
 *                                                                         
 *   Utilise suppressionCellule pour supprimer tous les �l�ments           
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
 * debugListe   Affiche tout les �l�ments d'une liste de message           
 *                                                                         
 * Entr�es: liste, pointeur de la liste                                    
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
 * debugElement   Affiche un �l�ment d'une liste de message                
 *                                                                         
 * Entr�es: element, pointeur sur un structure message                     
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
