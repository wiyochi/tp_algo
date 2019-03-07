/*procédure TRUC ( i , n, T ) :
	si  i = n   alors    pour j de 1 à n faire
				écrire T( j );
			 fait;
	sinon
	pour j  de i  à n faire
		temp := T( i ); T ( i ) := T ( j ); T ( j ) := temp;
		TRUC ( i + 1, n, T );
		temp := T( i ); T ( i ) := T ( j ); T ( j ) := temp;
	fait;
	fsi;
    */
#include <stdio.h>

void truc(int i, int n, int* T);

int main()
{
    int T[4] = { 1, 2, 3, 4 };

    truc(0, 4, T);
    return 0;
}

void truc(int i, int n, int* T)
{
    int j, tmp;

    if(i == n)
    {
        printf("[ ");
        for(j = 0; j < n; j++)
        {
            printf("%d ", T[j]);
        }
        printf("]\n");
    }
    else
    {
        for(j = i; j < n; j++)
        {
            tmp = T[i];
            T[i] = T[j];
            T[j] = tmp;
            truc(i + 1, n, T);
            tmp = T[i];
            T[i] = T[j];
            T[j] = tmp;
        }
    }
}