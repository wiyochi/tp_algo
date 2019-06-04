#include "dictionnaire.h"

void charger_fichier(table_t* table, char* nomFichier);
void traduction(table_t* dictionnaire, char* texte, char* traduction);

int main()
{
    table_t* dicoEN_FR = init_table();
    char texte[] = "hello Test de phrase! Est-ce que clement? il est, happy\n avec sylvanus; mathis boit la bottle";
    char trad[255];

    charger_fichier(dicoEN_FR, "anglais-français.txt");
    printf("\n=== Table ===\n");
    debug_table(dicoEN_FR);

    printf("\n=== Traduction ===\n");
    traduction(dicoEN_FR, texte, trad);
    printf("texte: %s\n", texte);
    printf("trad: %s\n", trad);

    liberer_table(dicoEN_FR);

    return 0;
}

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

            printf("Ajout a la table: %s;%s\n", cle, valeur);
            ajouter_table(table, cle, valeur);
        }
        fclose(fichier);
    }
}

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