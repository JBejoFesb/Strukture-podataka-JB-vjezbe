#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME (256)

struct student;

typedef struct student *Position;

typedef struct student
{
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int birthYear;
	Position next;

}Student;

Position stvoriStudent(char*,char*,int);

Position traziStudenta(Position,char*);

int ucitavanjeIzDatoteke(Position,char*);

int ucitavanjeUDatoteku(Position,char*);

int sortiraniUnos(Position, Position);

int unosIzaElementa(Position, Position);

int unosIspredElementa(Position, Position);

int ispisStudenata(Position);

int izbrisiStudenta(Position, char*);

int main()
{
	Student head;
	head.next = NULL;
	Position p = NULL;
	p = malloc(sizeof(Student));
	char datoteka[MAX_NAME];
	char novadatoteka[MAX_NAME];
	char firstname[MAX_NAME];
	char lastname[MAX_NAME];
	int birthyear;
	int odabir = 1;
	puts("Dobrodosli u program za unos i upravljanje liste studenata. [Strukture podataka zadatak 2 - Jakov Bejo]\n");
	while (odabir != 0)
	{
		printf("\nPritisnite bilo koju tipku za meni odabira");
		system("pause > nul");
		system("cls");
		ispisStudenata(&head);
		puts("Odaberite zeljenu funkciju programa unosom pripadajuceg broja:\n");
		puts("Unos sortirane liste studenta preko standard inputa-a (1)");
		puts("Unos sortirane liste studenta preko datoteke (2)");
		puts("Pretrazivanje po prezimenu (3)");
		puts("Brisanje elementa iz liste (4)");
		puts("Ispis liste u datoteku (5)");
		puts("Izlaz iz programa (0)\n");
		printf("Vas odabir: ");
		scanf("%d", &odabir);
		switch (odabir)
		{
		case 1:
			printf("Unesi ime i prezime studenta: ");	scanf(" %s %s", firstname, lastname);
			printf("Unesi godinu rodenja studenta: ");	scanf(" %d", &birthyear);
			p = stvoriStudent(firstname, lastname, birthyear);
			sortiraniUnos(&head, p);
			printf("\nStudent uspjesno dodan u listu\n");
			break;
		case 2:
			puts("Odaberite datoteku iz koje ce se uzeti lista:");
			scanf("%s", datoteka);
			ucitavanjeIzDatoteke(&head, datoteka);
			break;
		case 3:
			printf("Unesite prezime studenta kojeg zelite traziti: ");
			scanf(" %s", lastname);
			p=traziStudenta(&head, lastname);
			printf("\nStudent: \n%s %s %d\n", p->firstName, p->lastName, p->birthYear);
			break;
		case 4:
			printf("Unesite prezime studenta kojeg zelite izbrisati: ");
			scanf(" %s", lastname);
			izbrisiStudenta(&head, lastname);
			break;
		case 5:
			puts("Odaberite datoteku u koje ce se upisati lista:");
			scanf("%s", novadatoteka);
			ucitavanjeUDatoteku(&head, novadatoteka);
			break;
		case 0:
			break;
		}
	}
	return 0;
}

Position stvoriStudent(char* firstName, char* lastName, int birthYear)
{
	Position stud = NULL;
	stud = malloc(sizeof(Student));
	if (NULL == stud)
	{
		perror("Nesto poslo po krivu sa memorijom\n");
		return NULL;
	}
	strcpy(stud->firstName, firstName);
	strcpy(stud->lastName, lastName);
	stud->birthYear = birthYear;
	return stud;
}
int unosIzaElementa(Position prev, Position element)
{
	element->next = prev->next;
	prev->next = element;
	return 0;
}
int unosIspredElementa(Position head, Position element) {
	Position prevEle = NULL;
	Position trenutni = NULL;
	int prekid = 0;
	for (prevEle = head, trenutni = head->next; trenutni != NULL; prevEle = prevEle->next, trenutni = trenutni->next)
	{
		prekid = strcmp(trenutni->lastName, element->lastName);
		if (prekid == 0)
		{
			unosIzaElementa(prevEle, element);
			break;
		}
	}
	return 0;
}

int sortiraniUnos(Position head, Position element) {
	Position prevEle = NULL;
	Position trenutni = NULL;
	int prekid = 0;
	for (prevEle = head, trenutni = head->next; trenutni != NULL; prevEle = prevEle->next, trenutni = trenutni->next)
	{
		prekid = strcmp(trenutni->lastName,prevEle->lastName);
		if (prekid < 0)
		{
			unosIspredElementa(prevEle, element);
		}
		else if (prekid > 0)
		{
			unosIzaElementa(prevEle, element);
		}
	}
	return 0;
}
Position traziStudenta(Position head, char *lastName)
{
	Position tragac = NULL;
	int prekid = 0;
	for (tragac = head->next; tragac != NULL; tragac = tragac->next)
	{
		prekid= strcmp(tragac->lastName, lastName);
		if (prekid == 0)
			break;
	}
	if (NULL == tragac)
		printf("\nNeuspjesno trazenje studenta\n");
	return tragac;
}
int izbrisiStudenta(Position head, char *lastName)
{
	Position prevEle = NULL;
	Position Element = NULL;
	int prekid = 0;
	for (prevEle = head, Element = head->next; Element != NULL; prevEle = prevEle->next, Element = Element->next)
	{
		prekid=strcmp(Element->lastName, lastName);
		if (prekid == 0)
		{
			prevEle->next = Element->next;
			free(Element);
			break;
		}
	}
	if (prekid!= 0)
		printf("\nNmg nac studenta\n");
	else
		printf("\nStudent izbrisan\n");
	return 0;
}

int ispisStudenata(Position head)
{
	Position citac = NULL;
	citac = head->next;
	while (citac != NULL)
	{
		printf("%s %s %d\n", citac->firstName, citac->lastName, citac->birthYear);
		citac = citac->next;
	}
	printf("\n");
	return 0;
}

int ucitavanjeIzDatoteke(Position head, char* Datoteka)
{
	char registar[64];
	Position citac = NULL;
	FILE *dat;
	dat = fopen(Datoteka, "r");
	if (dat == NULL)
	{
		perror("Greska u citanju datoteke");
		return(-1);
	}

	for (citac = head->next; citac != NULL; citac = citac->next)
	{
		if ((fscanf(dat, "%[^\n]%*c", registar)) != EOF)
		{
			sscanf(registar, "%s %s %d", citac->firstName, citac->lastName, &citac->birthYear);
			sortiraniUnos(head, citac);
		}
	}
	printf("\nLista upisana iz datoteke\n");
	fclose(dat);
	return 0;
}

int ucitavanjeUDatoteku(Position head, char* NovaDatoteka)
{
	Position pisac = NULL;
	FILE *dat;
	dat = fopen(NovaDatoteka, "w");
	if (dat == NULL)
	{
		perror("Greska u citanju datoteke");
		return(-1);
	}

	for (pisac = head->next; pisac != NULL; pisac = pisac->next)
	{
		fprintf(dat, "%s %s %d\n", pisac->firstName, pisac->lastName, pisac->birthYear);
	}
	printf("\nLista upisana u novu datoteku\n");
	fclose(dat);
	return 0;
}