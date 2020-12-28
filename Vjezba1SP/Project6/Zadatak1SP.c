#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {

	char ime[20];
	char prezime[20];
	int bodovi;

}studenti;

int brojacRedova(char* imeDatoteke) {
	
	FILE* dat;
	dat = fopen(imeDatoteke, "r");
	if (dat == NULL)
	{
		perror("Greska u citanju datoteke");
		return(-1);
	}

	int brojac = 0;
	char x;
	while (!feof(dat))
	{
		x = fgetc(dat);
		if (x == '\n')
			brojac++;
	}
	
	fclose(dat);
	return brojac;

}
int upisPodataka(char*imeDatoteke, studenti* student) {
	
	FILE* dat;
	dat = fopen(imeDatoteke, "r");
	if (dat == NULL)
	{
		perror("Greska u citanju datoteke");
		return(-1);
	}
	
	int i;
	for(i=0;!feof(dat);i++)
	{
		fscanf(dat, " %s %s %d", student[i].ime, student[i].prezime, &(student[i].bodovi));
		
	}

	fclose(dat);
	return 0;
}
int ispisPodataka(studenti* student,int brojRedova) 
{
	puts("\n");
	int i;
	for(i=0;i<brojRedova;i++)
	{
		printf("Ime: %s\n", student[i].ime);
		printf("Prezime: %s\n", student[i].prezime);
		printf("Bodovi: %d\n", student[i].bodovi);
		printf("Relativni bodovi: %.2f%%\n", (float)(student[i].bodovi) / 100 * 100);
		puts("\n========================================\n");
	}
	return 0;

}

int main()
{

	studenti* student;

	char imeDatoteke[50];
	puts("Upisite ime datoteke:\n");
	scanf("%s", imeDatoteke);
	int brojRedova = brojacRedova(imeDatoteke);

	student = (studenti*)malloc(brojRedova * sizeof(studenti));

	upisPodataka(imeDatoteke, student);

	ispisPodataka(student, brojRedova);



	return 0;
}