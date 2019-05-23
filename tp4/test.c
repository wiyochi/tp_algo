#include "dictionnaire.h"

int main()
{
    cell_t** MAJ = init_table();

    ajouter_table(MAJ, "hello", "bonjour");
    ajouter_table(MAJ, "hello", "bonjour2");
    ajouter_table(MAJ, "hello2", "bonjour3");
    ajouter_table(MAJ, "thing", "chose");
    ajouter_table(MAJ, "computer", "ordi");
    ajouter_table(MAJ, "foo", "toto");
    ajouter_table(MAJ, "bar", "titi");
    ajouter_table(MAJ, "test", "test");
    ajouter_table(MAJ, "find", "trouve");
    ajouter_table(MAJ, "other", "autre");
    ajouter_table(MAJ, "bye", "au revoir");
    ajouter_table(MAJ, "bliblablou", "bliblablou");
    ajouter_table(MAJ, "azerty", "123");
    ajouter_table(MAJ, "list", "liste");
    ajouter_table(MAJ, "29", "42");
    ajouter_table(MAJ, "bastien", "bastoune");
    ajouter_table(MAJ, "felix", "le chat");
    ajouter_table(MAJ, "mathieu", "mattthieux");

    debug_table(MAJ);

    liberer_table(MAJ);

    return 0;
}