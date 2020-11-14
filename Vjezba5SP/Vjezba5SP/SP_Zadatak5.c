#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct skupovi;
typedef struct skupovi *Position;
typedef struct skupovi
{
	int Vrijednost;
	Position next;
}Skup;

Position stvoriClanSkupa(int);

int brojSkupova(char*);

int ucitavanjeDatoteke(Position, char*);

int sortiraniUnos(Position, Position);

int unosIzaElementa(Position, Position);

int unija(Position, Position, Position);

int presjek(Position, Position, Position);

int main()
{
	char datoteka[50];
	int brojskupova=1;
	int unosOdabir=0;
	int upisivanje = 0;
	puts("Dobrodosli u program za izradu i obradu skupova brojeva. [Strukture podataka zadatak 5 - Jakov Bejo]\n\n");
	puts("Odaberite unos preko tipkovnice (1) ");
	puts("Odaberite unos preko datoteke (2)\n ");
	while (unosOdabir<1 || unosOdabir>2)
		scanf("%d", &unosOdabir);

	switch (unosOdabir)
	{
	case 1:
		while (brojskupova < 2)
		{
			printf("\nKoliko skupova brojeva zelite imati (minimalno dva):");
			scanf("%d", &brojskupova);
			upisivanje = 1;
		}
		break;
	case 2:
		puts("Odaberite datoteku za unos skupova, u projektu se po default-u nalazi skupovi.txt");
		scanf("%s", datoteka);
		brojskupova = brojSkupova(datoteka);
		break;
	}

	Position nizHead;
	nizHead = malloc(sizeof(Skup)*brojskupova);				//deklaracija niza listi 
	int n = 0;
	while (n < brojskupova)
	{
		(nizHead + n)->next = NULL;
		n++;
	}

	if (upisivanje == 1)
	{
		system("cls");
		int broj;
		int i = 0;
		puts("Unosite brojeve skupa sa razmakom: 4 5 6 Pritisnite enter za zavrsetak skupa.");
		while (i <brojskupova)
		{
			printf("Unos %d. skupa brojeva\n", i + 1);
			char c = ' ';
			while (c != '\n') 
			{
				scanf("%d%c", &broj, &c);
				sortiraniUnos(nizHead+i, stvoriClanSkupa(broj));
			}
			i++;
		}

	}
	else
		ucitavanjeDatoteke(nizHead, datoteka);		//ucitavanje preko fscanf-a sscanf-a i automatski poziv sortiranja pri unosu

	int odabir = -1;
	while (odabir != 0)
	{
		Position akumulator;									//deklaracija akumulatora koji sluzi kao rezultat ili privremeni registar za zbrajanje i mnozenje
		akumulator = malloc(sizeof(Skup)*(brojskupova + 1));
		int a = 0;
		while (a < brojskupova)
		{
			(akumulator + a)->next = NULL;
			a++;
		}

		int skup1 = 0;
		int skup2 = 0;
		int m = 2;

		printf("\nPritisnite bilo koju tipku za meni odabira");
		system("pause > nul");
		system("cls");
		puts("\nDostupni skupovi:");
		puts("\n-----------------------------------------------------------------------");
		int r = 0;
		while (r < brojskupova)
		{
			printf("\n   Skup %d:", r + 1);
			ispisListi(nizHead + r);
			printf("\n");
			r++;
		}
		puts("\n-----------------------------------------------------------------------");
		puts("\nOdaberite zeljenu funkciju programa unosom pripadajuceg broja:\n");
		puts("\tUnija dva skupa (1)");
		puts("\tUnija svih skupova (2)");
		puts("\tPresjek 2 skupa (3)");
		puts("\tPresjek svih skupova (4)");
		puts("\tIzlaz iz programa (0)\n");
		printf("Vas odabir: ");
		scanf("%d", &odabir);
		if ((odabir < 0) || (odabir > 4))
			puts("\nKrivi odabir!");
		switch (odabir)
		{
		case 1:
			printf("\nOdaberite broj oznake prvog skupa: ");
			while ((skup1 < 1) || (skup1 > brojskupova))
				scanf("%d", &skup1);
			printf("\nOdaberite broj oznake drugog skupa:");
			while ((skup2 < 1) || (skup2 > brojskupova))
				scanf("%d", &skup2);

			unija(nizHead + (skup1 - 1), nizHead + (skup2 - 1), akumulator);

			printf("\nUnija skupova iznosi:  ");
			ispisListi(akumulator);
			break;
		case 2:
			unija(nizHead, nizHead + 1, akumulator);
			for (int i = 2; i < brojskupova; i++)
				unija(nizHead + i, akumulator, akumulator);
			printf("\nUnija svih skupova iznosi:  ");
			ispisListi(akumulator);
			break;
		case 3:
			printf("\nOdaberite broj oznake prvog skupa: ");
			while ((skup1 < 1) || (skup1 > brojskupova))
				scanf("%d", &skup1);
			printf("\nOdaberite broj oznake drugog skupa:");
			while ((skup2 < 1) || (skup2 > brojskupova))
				scanf("%d", &skup2);

			presjek(nizHead + (skup1 - 1), nizHead + (skup2 - 1), akumulator);

			printf("\nPresjek skupova iznosi:  ");
			ispisListi(akumulator);
			break;
		case 4:
			presjek(nizHead, nizHead + 1, akumulator);
			for (int i = 2; i < brojskupova; i++)
				presjek(nizHead + i, akumulator, akumulator);
			printf("\nPresjek svih skupova iznosi:  ");
			ispisListi(akumulator);
			break;
			break;
		case 0:
			break;
		}
		printf("\n");
	}
	return 0;
}

int brojSkupova(char* Datoteka)
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

Position stvoriClanSkupa(int vrijednost)
{
	Position clan = NULL;
	clan = (Position)malloc(sizeof(Skup));
	if (NULL == clan)
	{
		perror("Nesto je poslo krivo sa alokacijom memorije\n");
		return NULL;
	}
	clan->Vrijednost = vrijednost;
	return clan;
}

int sortiraniUnos(Position head, Position P) {
	Position prevEle;
	Position Element;

	int odluka = 1; //default

	for (prevEle = head, Element = head->next; Element != NULL; prevEle = prevEle->next, Element = Element->next)
	{
		if (P->Vrijednost < Element->Vrijednost)
			break;		
	}
	unosIzaElementa(prevEle, P);

	return 0;
}

int unosIzaElementa(Position gdje, Position element)
{
	element->next = gdje->next;
	gdje->next = element;
	return 0;
}

int ucitavanjeDatoteke(Position niz, char* Datoteka)
{
	FILE* dat;
	dat = fopen(Datoteka, "r");
	if (dat == NULL)
	{
		perror("Greska u citanju datoteke");
		return(-1);
	}

	char *registar;
	registar = malloc(128 * sizeof(char));
	int znkBroj, znkUcitanih, prekid, broj;
	int red = 0;

	while ((fscanf(dat, "%[^\n]%*c", registar)) != EOF)
	{
		prekid = 0;
		znkBroj = strlen(registar);

		do
		{
			sscanf(registar, "%d %n", &broj,&znkUcitanih);
			stvoriClanSkupa(broj);
			sortiraniUnos(niz + red, stvoriClanSkupa(broj));
			registar += znkUcitanih;
			prekid += znkUcitanih;
		} while (prekid < znkBroj);

		red++;
	}
	fclose(dat);
	return 0;
}

int unija(Position head1, Position head2, Position akumulator)
{
	Position reg1;		//registri za setanje po listama
	Position reg2;
	int prekid = 1024;

	for (reg1 = head1->next, reg2 = head2->next; (reg1 != NULL) && (reg2 != NULL);)
	{

		if (reg1->Vrijednost == reg2->Vrijednost)
		{
			if (prekid != reg1->Vrijednost)
			{
				unosIzaElementa(akumulator, stvoriClanSkupa(reg1->Vrijednost));
				akumulator = akumulator->next;
				akumulator->next = NULL;
				prekid = reg1->Vrijednost;
			}
			reg1 = reg1->next;
			reg2 = reg2->next;
		}
		else if (reg1->Vrijednost < reg2->Vrijednost)
		{
			if (prekid != reg1->Vrijednost)
			{
				unosIzaElementa(akumulator, stvoriClanSkupa(reg1->Vrijednost));
				akumulator = akumulator->next;
				akumulator->next = NULL;
				prekid = reg1->Vrijednost;
			}
			reg1 = reg1->next;
		}
		else
		{
			if (prekid != reg2->Vrijednost)
			{
				unosIzaElementa(akumulator, stvoriClanSkupa(reg2->Vrijednost));
				akumulator = akumulator->next;
				akumulator->next = NULL;
				prekid = reg2->Vrijednost;
			}
			reg2 = reg2->next;
		}
	}
	while (reg1 != NULL)
	{
		unosIzaElementa(akumulator, stvoriClanSkupa(reg1->Vrijednost));
		akumulator = akumulator->next;
		akumulator->next = NULL;
		reg1 = reg1->next;
	}
	while (reg2 != NULL)
	{
		unosIzaElementa(akumulator, stvoriClanSkupa(reg2->Vrijednost));
		akumulator = akumulator->next;
		akumulator->next = NULL;
		reg2 = reg2->next;
	}
	return 0;
}

int presjek(Position head1, Position head2, Position akumulator)
{
	Position reg1;		//registri za setanje po listama
	Position reg2;
	int prekid = 1024;

	for (reg1 = head1->next, reg2 = head2->next; (reg1 != NULL) && (reg2 != NULL);)
	{
		if (reg1->Vrijednost == reg2->Vrijednost)
		{
			unosIzaElementa(akumulator, stvoriClanSkupa(reg1->Vrijednost));
			akumulator = akumulator->next;
			akumulator->next = NULL;
			reg1 = reg1->next;
			reg2 = reg2->next;
		}
		else if (reg1->Vrijednost < reg2->Vrijednost)
			reg1 = reg1->next;
		else
			reg2 = reg2->next;
	}
	return 0;
}

int ispisListi(Position head)
{
	Position citac = NULL;
	citac = head->next;
	printf("\t");
	while (citac != NULL)
	{
		printf("%d ", citac->Vrijednost);
		citac = citac->next;
	}
	return 0;
}