#include "dictionnaire.h"

void    charger_fichier (table_t* table, char* nomFichier);
void    traduction      (table_t* dictionnaire, char* texte, char* traduction);
float   longueur_moyenne(table_t* table);

int main()
{
    table_t* dicoEN_FR   = init_table();
    table_t* dicoVide    = init_table();
    table_t* dicoCorr    = init_table();
    table_t* dicoRep     = init_table();
    table_t* dicoNExist  = init_table();

    char chaineVide[]   = "";
    char texte[]        = "where is bryan? Bryan is behind his computer.\nhe move his mouse and type his name on the screen with his keyboard";
    char trad[255];


    /*#####################################*/
    /*### TESTS CHARGEMENTS DE FICHIERS ###*/
    /*#####################################*/
    charger_fichier(dicoEN_FR, "anglais-français.txt");
    printf("\n=== Table dicoEN_FR ===\n");
    debug_table(dicoEN_FR);

    charger_fichier(dicoVide, "vide.txt");
    printf("\n=== Table dicoVide ===\n");
    debug_table(dicoVide);

    /* Fichier corrompu -> segfault
    charger_fichier(dicoCorr, "dicoCorr.txt");
    printf("\n=== Table dicoCorr ===\n");
    debug_table(dicoCorr);
    */

    charger_fichier(dicoRep, "dicoRep.txt");
    printf("\n=== Table dicoRep ===\n");
    debug_table(dicoRep);

    charger_fichier(dicoNExist, "dicoNExist.txt");
    printf("\n=== Table dicoNExist ===\n");
    debug_table(dicoNExist);


    /*#########################*/
    /*### TESTS TRADUCTIONS ###*/
    /*#########################*/
    printf("\n=== Traduction phrase ===\n");
    traduction(dicoEN_FR, texte, trad);
    printf("texte: %s\n", texte);
    printf("trad: %s\n", trad);

    printf("\n=== Traduction chaineVide ===\n");
    traduction(dicoEN_FR, chaineVide, trad);
    printf("texte: %s\n", chaineVide);
    printf("trad: %s\n\n", trad);

    printf("\n=== Traduction dicoVide ===\n");
    traduction(dicoVide, texte, trad);
    printf("texte: %s\n", texte);
    printf("trad: %s\n", trad);


    /*##########################*/
    /*### LONGUEURS MOYENNES ###*/
    /*##########################*/
    printf("\n=== Longueurs moyennes des sous-tables de chaque dictionnaire ===\n");
    printf("Longueur moyenne dicoEN_FR: %f\n", longueur_moyenne(dicoEN_FR));
    printf("Longueur moyenne dicoVide: %f\n", longueur_moyenne(dicoVide));
    printf("Longueur moyenne dicoRep: %f\n", longueur_moyenne(dicoRep));
    printf("Longueur moyenne dicoNExist: %f\n", longueur_moyenne(dicoNExist));

    liberer_table(dicoEN_FR);
    liberer_table(dicoVide);
    liberer_table(dicoCorr);
    liberer_table(dicoRep);
    liberer_table(dicoNExist);

    return 0;
}

/*-------------------------------------------------------------------------------
 * charger_fichier      Recupere le contenu d'un fichier pour creer un dictionnaire
 *                          sous la forme d'une table
 *                                                               
 * Entree: table, table majeure representant un dictionnaire dans lequel on insere
 *                  les mots et les traductions du fichier
 *         nomFichier, nom du fichier
 *
 * On recupere le contenu du fichier ligne par ligne. Pour chacune d'elle, on utilise
 * la fonction "strtok" afin de separer le mot et sa traduction dans deux chaines de
 * caracteres differentes. On utilise alors la fonction "ajouter_table" afin de les
 * inserer dans la table-dictionnaire
 * 
 * Lexique: fichier, pointeur de fichier ouvert en lecture
 *          buffer, chaine de caracteres contenant la ligne actuelle
 *          cle, chaine de caractere contenant le mot (pointeur dans buffer)
 *          valeur, chaine de caractere contenant la traduction (pointeur dans buffer)
 *-------------------------------------------------------------------------------
 */
void charger_fichier(table_t* table, char* nomFichier)
{
    FILE*   fichier = fopen(nomFichier, "r");
    char    buffer[255];
    char*   cle;
    char*   valeur;

    if(fichier != NULL)
    {
        while(fgets(buffer, 255, fichier))
        {
            cle = strtok(buffer, ";");
            valeur = strtok(NULL, "\r\n");

            ajouter_table(table, cle, valeur);
        }
        fclose(fichier);
    }
}

/*-------------------------------------------------------------------------------
 * traduction      Traduit a l'aide d'un dictionnaire une phrase donnee
 *                                                               
 * Entree: dictionnaire, table contenant des mots et leur traduction
 *         texte, texte a traduire
 *                                                               
 * Sortie: traduction, le texte traduit
 *
 * On parcours chaque lettre du texte. Tant que ce n'est pas un caractere indiquant
 * la fin d'un mot (point, espace, ...) on ajoute la lettre dans une chaine de caractere.
 * Une fois un mot entier dans la chaine, on cherche une traduction dans le dictionnaire:
 * Si il y en a une, on l'ajoute dans la chaine de caractere "traduction" sinon on n'y
 * ajoute le mot. On ajoute aussi le caractere separateur et on avance dans le texte.
 * 
 * Lexique: mot, chaine de caractere contenant tour a tour les mots du texte
 *          trouve, pointeur sur la cellule du mot trouve dans le dictionnaire
 *                      (ou NULL si il n'y est pas)
 *          lettre, lettre du texte lue
 *          offset, decalage d'indice pour lire le texte
 *          index, indice pour ajouter les lettres dans "traduction"
 *          i, j, indices de parcours de chaines de caracteres
 *-------------------------------------------------------------------------------
 */
void traduction(table_t* dictionnaire, char* texte, char* traduction)
{
    char    mot[255];
    cell_t* trouve  = NULL;
    int     i, j;
    int     offset  = 0;
    char    lettre  = ' ';
    int     index   = 0;

    while(lettre != '\0')
    {
        i = 0;
        lettre = texte[offset + i];
        while(lettre != ' ' && lettre != ',' && lettre != ';' && lettre != '.' && lettre != '!' && lettre != '?' && lettre != '\n' && lettre != '\0' && lettre != '\r')
        {
            mot[i] = lettre;
            i++;
            lettre = texte[offset + i];
        }
        mot[i] = '\0';
        if(recherche_table(dictionnaire, mot, &trouve))
        {
            j = 0;
            while(trouve->trad[j] != '\0')
                traduction[index++] = trouve->trad[j++];
        }
        else
        {
            j = 0;
            while(mot[j] != '\0')
                traduction[index++] = mot[j++];
        }
        traduction[index] = lettre;
        index++;
        offset = offset + i + 1;
    }
}

float longueur_moyenne(table_t* table)
{
    float moy = 0.f;
    int i;

    for(i = 0; i < HASH_MAX; i++)
        moy += table[i].compteur;
    
    moy /= HASH_MAX;

    return moy;
}