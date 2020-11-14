#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct polinom;
typedef struct polinom *Position;
typedef struct polinom
{
	int Koeficijent;
	int Exponent;
	Position next;
}Polinom;

Position stvoriPolinom(int, int);

int brojPolinoma(char*);

int ucitavanjeDatoteke(Position, char*, int);

int sortiraniUnos(Position,Position);

int unosIzaElementa(Position,Position);

int zbrajanje(Position,Position,Position);

int mnozenje(Position, Position, Position);

int main()
{
	char datoteka[50];
	puts("Dobrodosli u program za zbrajanje i mnozenje polinoma. [Strukture podataka zadatak 3 - Jakov Bejo]\n\n");
	puts("Odaberite datoteku za unos polinoma, u projektu se po default-u nalazi polinomi.txt\n");
	scanf("%s", datoteka);

	int brojpolinoma = brojPolinoma(datoteka);				//deklaracija niza listi 
	Position nizHead;
	nizHead = malloc(sizeof(Polinom)*brojpolinoma);
	int n = 0;
	while (n < brojpolinoma)
	{
		(nizHead + n)->next = NULL;
		n++;
	}

	ucitavanjeDatoteke(nizHead, datoteka, brojpolinoma);  //ucitavanje preko fscanf-a sscanf-a i automatski poziv sortiranja pri unosu

	int odabir = -1;
	while (odabir != 0)
	{
		Position akumulator;									//deklaracija akumulatora koji sluzi kao rezultat ili privremeni registar za zbrajanje i mnozenje
		akumulator = malloc(sizeof(Polinom)*(brojpolinoma+1));
		int a = 0;
		while (a < brojpolinoma)
		{
			(akumulator + a)->next = NULL;
			a++;
		}

		int polinom1 = 0;
		int polinom2 = 0;
		int m = 2;

		printf("\nPritisnite bilo koju tipku za meni odabira");
		system("pause > nul");
		system("cls");
		puts("\nPolinomi dostupni iz datoteke:");
		puts("\n-----------------------------------------------------------------------");
		int r = 0;
		while (r < brojpolinoma)
		{
			printf("\n   Polinom %d:", r + 1);
			ispisListi(nizHead + r);
			printf("\n");
			r++;
		}
		puts("\n-----------------------------------------------------------------------");
		puts("\nOdaberite zeljenu funkciju programa unosom pripadajuceg broja:\n");
		puts("\tZbrajanje dva polinoma (1)");
		puts("\tZbrajanje svih polinoma (2)");
		puts("\tMnozenje dva polinoma (3)");
		puts("\tMnozenje svih polinoma (4)");
		puts("\tIzlaz iz programa (0)\n");
		printf("Vas odabir: ");
		scanf("%d", &odabir);
		if ((odabir < 0) || (odabir > 4))
			puts("\nKrivi odabir!");
		switch (odabir)
		{
		case 1:
			printf("\nOdaberite broj oznake prvog polinoma: ");
			while ((polinom1 < 1) || (polinom1 > brojpolinoma)) 
				scanf("%d", &polinom1);
			printf("\nOdaberite broj oznake drugog polinoma: ");
			while ((polinom2 < 1) ||(polinom2 > brojpolinoma)) 
				scanf("%d", &polinom2);

			zbrajanje(nizHead + (polinom1 - 1), nizHead + (polinom2 - 1), akumulator);

			printf("\nZbrojeni polinom iznosi:  ");
			ispisListi(akumulator);
			break;
		case 2:
			zbrajanje(nizHead, nizHead + 1, akumulator);
			for (int i = 2; i < brojpolinoma; i++)
				zbrajanje(nizHead+i, akumulator, akumulator);
			printf("\nZbrojeni polinom iznosi:  ");
			ispisListi(akumulator);
			break;
		case 3:
			printf("\nOdaberite broj oznake prvog polinoma: ");
			while ((polinom1 < 1) || (polinom1 > brojpolinoma)) 
				scanf("%d", &polinom1);
			printf("\nOdaberite broj oznake drugog polinoma: ");
			while ((polinom2 < 1) ||(polinom2 > brojpolinoma)) 
				scanf("%d", &polinom2);

			mnozenje(nizHead + (polinom1 - 1), nizHead + (polinom2 - 1), akumulator);

			printf("\nRezultat mnozenja polinoma iznosi:  ");
			ispisListi(akumulator);
			break;
		case 4:
			mnozenje(nizHead, nizHead + 1, akumulator);
			do
			{
				mnozenje(nizHead + m, akumulator+(m-2), akumulator + (m-1) );
				m++;
			} while (m < brojpolinoma);
			printf("\nRezultat mnozenja polinoma iznosi:  ");
			ispisListi(akumulator+(m-2));
			break;
		case 0:
			break;
		}
		printf("\n");
	}
	return 0;
}

int brojPolinoma(char* Datoteka)
{
	FILE* dat;
	dat = fopen(Datoteka, "r");
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

Position stvoriPolinom(int koeficijent, int exponent)
{
	Position polinom = NULL;
	polinom = (Position)malloc(sizeof(Polinom));
	if (NULL == polinom)
	{
		perror("Nesto je poslo krivo sa alokacijom memorije\n");
		return NULL;
	}
	polinom->Koeficijent = koeficijent;
	polinom->Exponent = exponent;
	return polinom;
}

int sortiraniUnos(Position head, Position P) {
	Position prevEle;
	Position Element;

	int odluka=2; //default
	
	for(prevEle=head, Element=head->next; Element!=NULL; prevEle = prevEle->next, Element = Element->next)
	{

		if (P->Exponent == Element->Exponent)
		{
			if ((P->Koeficijent + Element->Koeficijent) != 0)
			{
				odluka = 1;
				break;
			}
			else
			{
				odluka = 0;
				break;
			}	
		}
		else if(P->Exponent < Element->Exponent)
		{
			odluka = 2;
			break;
		}
	}
	switch (odluka)
	{
	case 0:
		prevEle->next = Element->next;
		free(Element);
		break;
	case 1:
		(Element->Koeficijent) += (P->Koeficijent);
		break;
	case 2:
		unosIzaElementa(prevEle, P);
		break;
	}

	return 0;
}

int unosIzaElementa(Position gdje, Position element)
{
	element->next = gdje->next;
	gdje->next = element;
	return 0;
}

int ucitavanjeDatoteke(Position niz, char* Datoteka, int br)
{
	FILE* dat;
	dat = fopen(Datoteka, "r");
	if (dat == NULL)
	{
		perror("Greska u citanju datoteke");
		return(-1);
	}

	Position p = NULL;
	char *registar;
	registar = malloc(128 * sizeof(char));
	int znkBroj, znkUcitanih, prekid, koe, exp;
	int red = 0;

	while ((fscanf(dat, "%[^\n]%*c", registar)) != EOF)
	{
		prekid = 0;
		znkBroj = strlen(registar);

		do
		{
			sscanf(registar, "%dX%d %n", &koe, &exp, &znkUcitanih);

			if (koe != 0)
			{
				p = stvoriPolinom(koe, exp);
				sortiraniUnos(niz + red, p);
			}

			registar += znkUcitanih;
			prekid += znkUcitanih;
		} while (prekid < znkBroj);

		red++;
	}
	fclose(dat);
	return 0;
}

int ispisListi(Position head)
{
	Position citac=NULL;
	citac = head->next;
	while (citac != NULL)
	{
		printf("  %dX^%d", citac->Koeficijent, citac->Exponent);
		citac = citac->next;
	}
	return 0;
}

int zbrajanje(Position head1, Position head2,Position akumulator) 
{
	Position temp=NULL;
	temp = malloc(sizeof(Polinom));
	temp->next = NULL;

	Position reg1;		//registri za setanje po listama
	Position reg2;
	
	int prekid=1024;

	for (reg1 = head1->next, reg2 = head2->next; (reg1 != NULL) && (reg2 != NULL);)
	{

		if (reg1->Exponent == reg2->Exponent)
		{
			if ((reg1->Koeficijent + reg2->Koeficijent) != 0)
			{
				temp = stvoriPolinom((reg1->Koeficijent + reg2->Koeficijent), reg1->Exponent);
				unosIzaElementa(akumulator, temp);
				akumulator = akumulator->next;
				akumulator->next = NULL;
			}
			reg1 = reg1->next;
			reg2 = reg2->next;
		}
		else if (reg1->Exponent < reg2->Exponent)
		{
			if (prekid != reg1->Exponent)
			{
				temp = stvoriPolinom(reg1->Koeficijent, reg1->Exponent);
				unosIzaElementa(akumulator, temp);
				akumulator = akumulator->next;
				akumulator->next = NULL;
				prekid = reg1->Exponent;
			}
			reg1 = reg1->next;
		}
		else if (reg1->Exponent > reg2->Exponent)
		{
			if (prekid != reg2->Exponent)
			{
				temp = stvoriPolinom(reg2->Koeficijent, reg2->Exponent);
				unosIzaElementa(akumulator, temp);
				akumulator = akumulator->next;
				akumulator->next = NULL;
				prekid = reg2->Exponent;
			}
			reg2 = reg2->next;
		}
	}
	while(reg1 != NULL)
	{
		temp = stvoriPolinom(reg1->Koeficijent, reg1->Exponent);
		unosIzaElementa(akumulator, temp);
		akumulator = akumulator->next;
		akumulator->next = NULL;
		reg1 = reg1->next;
	}
	while (reg2 != NULL)
	{
		temp = stvoriPolinom(reg2->Koeficijent, reg2->Exponent);
		unosIzaElementa(akumulator, temp);
		akumulator = akumulator->next;
		akumulator->next = NULL;
		reg2 = reg2->next;
	}
	return 0;
}

int mnozenje(Position head1, Position head2, Position akumulator)
{
	Position temp = NULL;
	temp = malloc(sizeof(Polinom));
	temp->next = NULL;

	Position reg1;		//registri za setanje po listama
	Position reg2;

	for(reg1=head1->next;reg1!=NULL; reg1 = reg1->next)
		for (reg2 = head2->next; reg2 != NULL; reg2 = reg2->next)
		{
			temp= stvoriPolinom((reg1->Koeficijent*reg2->Koeficijent), (reg1->Exponent+reg2->Exponent));
			sortiraniUnos(akumulator, temp);
		}
	return 0;
}