#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stog* Position;
typedef struct stog {
	int Broj;
	Position next;
}stog;

int standardUlaz(Position);
int datotekaUlaz(Position, char*);
int postfix(Position, char*);
int push(Position, Position);
int pop(Position);
Position stvoriNode(int);
int provjera(Position);

int main() 
{
	char Datoteka[12] = "postfix.txt";
	int odabir = -1;
	while (odabir != 0)
	{
		Position Stog = (Position)malloc(sizeof(stog));
		Stog->next = NULL;
		system("cls");
		puts("Program za izracun postfix izraza ( operacije + - * / % ) [Strukture podataka zadatak 7 - Jakov Bejo]\n\n");
		puts("Unos preko tipkovnice (1)");
		puts("Unos iz datoteke postfix.txt (2)");
		puts("Izlaz iz programa (0)");
		printf("\nOdabir: ");
		scanf("%d", &odabir);
		switch (odabir)
		{
		case 1:
			standardUlaz(Stog);
			break;
		case 2:
			datotekaUlaz(Stog, Datoteka);
			break;
		case 0:
			return 0;
		}
		puts("\n\nPritisnite bilo koju tipku za nastavak");
		system("pause>nul");
	}
	return 0;
}

int standardUlaz(Position stog)
{
	char* registar;
	registar = malloc(256 * sizeof(char));
	printf("\nUnesite postfix izraz: ");
	getchar();
	gets(registar, 256);
	postfix(stog, registar);
	return 0;
}

int datotekaUlaz(Position stog, char* datoteka) 
{
	char* registar;
	registar = malloc(256 * sizeof(char));
	FILE* dat;
	dat = fopen(datoteka, "r");
	if (NULL == dat)
	{
		perror("Greska u citanju datoteke");
		return (-1);
	}
	fscanf(dat,"%[^\n]%*c", registar);
	fclose(dat);
	postfix(stog, registar);
	return 0;
}

int postfix(Position Stog, char* Postfix)
{
	int a,b,scanf,procitani;
	int brojZnakova = strlen(Postfix);
	int prekid = 0;
	do
	{
		int broj;
		char znak = ' ';
		scanf=sscanf(Postfix, "%d %n", &broj, &procitani);
		if (scanf != 1)
		{
			sscanf(Postfix, "%c %n", &znak, &procitani);
			if (provjera(Stog))
				return 0;
		}
		else
			push(Stog, stvoriNode(broj));
		switch (znak)
		{
		case 37:
			a = pop(Stog);
			b = pop(Stog);
			push(Stog, stvoriNode(b%a));
			break;
		case 42:
			a = pop(Stog);
			b = pop(Stog);
			push(Stog, stvoriNode(b*a));
			break;
		case 43:
			a = pop(Stog);
			b = pop(Stog);
			push(Stog, stvoriNode(b + a));
			break;
		case 45:
			a = pop(Stog);
			b = pop(Stog);
			push(Stog, stvoriNode(b - a));
			break;
		case 47:
			a = pop(Stog);
			b = pop(Stog);
			push(Stog, stvoriNode(b / a));
			break;
		}
		Postfix += procitani;
		prekid += procitani;
	} while (prekid < brojZnakova);
	printf("\nRezultat postfix izraza je: %d", Stog->next->Broj);
	return 0;
}

int push(Position head, Position element)
{
	element->next = head->next;
	head->next = element;
	return 0;
}

int pop(Position head)
{
	Position temp = head->next;
	head->next = temp->next;
	int broj = temp->Broj;
	free(temp);
	return broj;
}

Position stvoriNode(int broj)
{
	Position Node = (Position)malloc(sizeof(stog));
	if (NULL == Node)
	{
		perror("Nesto je poslo krivo sa alokacijom memorije\n");
		return (-1);
	}
	Node->Broj = broj;
	return Node;
}

int provjera(Position ispis)
{
	if (ispis->next == NULL || ispis->next->next == NULL)
	{
		printf("\nPostfix izraz je neispravan i rezultat nece biti ispravan!");
		return 1;
	}
	return 0;
}