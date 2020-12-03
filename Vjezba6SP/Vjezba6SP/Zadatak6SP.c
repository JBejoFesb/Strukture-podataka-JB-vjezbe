#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h> 

struct brojevi;
typedef struct brojevi *Position;
typedef struct brojevi
{
	int Vrijednost;
	Position next;
}Broj;

Position stvoriBroj();

int unosIzaElementa(Position, Position);

int pushStog(Position);

Position pushRed(Position);

int pop(Position);
																					
int ispis(Position,Position);															

int main()
{
	Position Stog=NULL;
	Position Red=NULL;
	Position Last = NULL;
	Stog = malloc(sizeof(Broj));
	Red = malloc(sizeof(Broj));
	Stog->next = NULL;
	Red->next = NULL;
	Last = Red;
	puts("Dobrodosli u program za simulaciju stoga i reda. [Strukture podataka zadatak 6 - Jakov Bejo]\n\n");
	printf("\nPritisnite bilo koju tipku za meni odabira");
	system("pause > nul");
	int odabir = -1;
	while (odabir != 0)
	{
		system("cls");
		puts("\tStog\t\t\tRed\n");
		puts("\t[  ]\t\t\t[  ]");
		ispis(Stog, Red);
		puts("\nOdaberite zeljenu funkciju programa unosom pripadajuceg broja:\n");
		puts("\tStog push(1)\t\tRed push(3)");
		puts("\tStog pop(2)\t\tRed pop(4)\n");
		puts("\tIzlaz iz programa (0)\n");
		printf("Vas odabir: ");
		scanf("%d", &odabir);
		switch (odabir)
		{
		case 1:
			pushStog(Stog);
			break;
		case 2:
			if (Stog->next != NULL)
				pop(Stog);
			break;
		case 3:
			Last=pushRed(Red,Last);
			break;
		case 4:
			if (Red->next != NULL)
			{
				pop(Red);
				if (Red->next == NULL)
					Last = Red;
			}
			break;
		case 0:
			break;
		}
	}
	return 0;
}

Position stvoriBroj()
{
	Position clan = NULL;
	clan = malloc(sizeof(Broj));
	if (NULL == clan)
	{
		perror("Nesto je poslo krivo sa alokacijom memorije\n");
		return NULL;
	}
	clan->Vrijednost = (rand() % (99 - 10 + 1)) + 10;
	return clan;
}

int pushStog(Position head)
{
	Position element = stvoriBroj();
	element->next = head->next;
	head->next = element;
	return 0;
}

Position pushRed(Position head, Position last)
{
	Position element = stvoriBroj();
	element->next = last->next;
	last->next = element;
	last = element;
	return last;
}
int pop(Position head)
{
	Position temp;
	temp = head->next;
	head->next = head->next->next;
	free(temp);
	return 0;
}

int ispis(Position stog,Position red)
{
	Position citacS=stog->next;
	Position citacR=red->next;
	while (citacS != NULL && citacR != NULL)
	{
		printf("\t[%d]\t\t\t[%d]\n", citacS->Vrijednost, citacR->Vrijednost);
		citacS = citacS->next;
		citacR = citacR->next;
	}
	while (citacS != NULL)
	{
		printf("\t[%d]\n", citacS->Vrijednost);
		citacS = citacS->next;
	}
	while (citacR != NULL)
	{
		printf("\t    \t\t\t[%d]\n", citacR->Vrijednost);
		citacR = citacR->next;
	}
	return 0;
}