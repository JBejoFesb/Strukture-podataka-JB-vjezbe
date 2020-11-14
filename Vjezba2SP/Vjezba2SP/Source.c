#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME (256)

struct _person;

typedef struct _person *Position;

typedef struct _person 
{

	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int birthYear;
	Position next;

}Person;

Position createStudent(char *firstName, char *lastName, int birthYear);

int insertAfter(Position where, Position what);

int insertLast(Position head, Position what);

int findStudent(Position head, char *lastName);

int printList(Position head);

int deleteStudent(Position head, char *lastName);

int main() 
{
	Person head;
	head.next = NULL;
	Position p = NULL;
	char firstname[MAX_NAME];
	char lastname[MAX_NAME];
	int birthyear;
	int odabir=1;
	puts("Dobrodosli u program za unos i upravljanje liste studenata. [Strukture podataka zadatak 2 - Jakov Bejo]\n");
	while (odabir!=0)
	{
		printf("\nPritisnite bilo koju tipku za meni odabira");
		system("pause > nul");
		system("cls");
		printList(&head);
		puts("Odaberite zeljenu funkciju programa unosom pripadajuceg broja:\n");
		puts("Unos studenta na pocetak liste (1)");
		puts("Unos studenta na kraj liste (2)");
		puts("Pretrazivanje po prezimenu (3)");
		puts("Brisanje elementa iz liste (4)");
		puts("Izlaz iz programa (0)\n");
		printf("Vas odabir: ");
		scanf("%d", &odabir);
		switch (odabir)
		{
		case 1:
			printf("Unesi ime i prezime studenta: ");	scanf(" %s %s", firstname,lastname);
			printf("Unesi godinu rodenja studenta: ");	scanf(" %d", &birthyear);
			p = createStudent(firstname, lastname, birthyear);
			insertAfter(&head, p);
			printf("\nStudent uspjesno dodan na pocetak liste\n");
			break;
		case 2:
			printf("Unesi ime i prezime studenta: ");	scanf(" %s %s", firstname, lastname);
			printf("Unesi godinu rodenja studenta: ");	scanf(" %d", &birthyear);
			p = createStudent(firstname, lastname, birthyear);
			insertLast(&head, p);
			printf("\nStudent uspjesno dodan na kraj liste\n");
			break;
		case 3:
			printf("Unesite prezime studenta kojeg zelite traziti: ");
			scanf(" %s", lastname);
			findStudent(&head, lastname);
			break;
		case 4:
			printf("Unesite prezime studenta kojeg zelite izbrisati: ");
			scanf(" %s", lastname);
			deleteStudent(&head, lastname);
			break;
		case 0:
			break;
		}
	}
	return 0;
}

Position createStudent(char *firstName, char *lastName, int birthYear) {
	Position p = NULL;
	p = (Position)malloc(sizeof(Person));
	if (NULL == p)
	{
		perror("Nesto poslo krivo sa memorijom\r\n");
		return NULL;
	}
	strcpy(p->firstName, firstName);
	strcpy(p->lastName, lastName);
	p->birthYear = birthYear;
	
	return p;
}
int insertAfter(Position where, Position what)
{
	what->next = where->next;
	where->next = what;
	return 0;
}
int insertLast(Position head, Position what)
{
	Position p = NULL;
	for (p = head; p->next != NULL; p = p->next) {};
	insertAfter(p, what);
	return 0;
}
int findStudent(Position head, char *lastName)
{
	Position p = NULL;
	int result = 0;
	for (p = head->next; p != NULL; p = p->next)
	{
		result = strcmp(p->lastName, lastName);
	if (result == 0)
		break;
	}
	if (NULL == p)
		printf("\nSpecificni student nije zapisan u listi\n");
	else
		printf("\nStudent: \n%s %s %d\n", p->firstName, p->lastName, p->birthYear);
	return 0;
}
int deleteStudent(Position head, char *lastName)
{
	Position p = NULL;
	Position q = NULL;
	int result = 0;
	int delResult = 0;
	for (p = head; p->next != NULL; p = p->next)
	{
		result = strcmp(p->next->lastName, lastName);
		if (result == 0)
		{
			q = p->next;
			p->next = p->next->next;
			free(q);
			delResult = 1;
			break;
		}
	}
	if (delResult == 0)
		printf("\nSpecificni student nije zapisan u listi\n");
	else
		printf("\nStudent izbrisan\n");
	return 0;
}
int printList(Position head)
{
	Position p = NULL;
	puts("Trenutni izgled liste je:");
	for (p = head->next; p != NULL; p = p->next)
	{
		printf("%s %s %d\r\n", p->firstName, p->lastName, p->birthYear);
	}
	printf("\n");
	return 0;
}