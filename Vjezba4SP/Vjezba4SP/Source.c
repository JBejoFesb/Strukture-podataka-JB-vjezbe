#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() 
{
	int koeficijent[2];
	int exponent[2];
	FILE* dat;
	dat = fopen("polinomi.txt", "r");
	if (dat == NULL)
	{
		perror("Greska u citanju datoteke");
		return(-1);
	}

	
	int brZnakova = 0;
	int i = 0;
	while (i<2)
	{
		fscanf(dat + brZnakova, "%dX%d %n", &koeficijent[i], &exponent[i], &brZnakova);
		i++;
		printf("%dX%d", koeficijent[i], exponent[i]);
	}

	return 0;
}