#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX (256)
#define TABLE (11)

typedef struct student *Position;
typedef struct student {
	char firstName[MAX];
	char lastName[MAX];
	int id;
	Position next;
}Student;

Position createStudentNode(char*, char*, int);

int initHashTable(Position);

int index(char*);

int sortedAddStudent(Position, Position);

int nameCompare(Position, Position);

int idCheck(Position, int);

int insertAfter(Position, Position);

int printHashTable(Position);

int idFind(Position, char*, char*);

int stdInput(Position);

int readFromFile(Position*, char*);

int main()
{
	Position HashTable[TABLE];
	initHashTable(HashTable);
	char filename[MAX] = "students.txt";
	char firstname[MAX];
	char lastname[MAX];
	int odabir = -1;
	int key;
	while (1)
	{
		puts("Hash tablica studenata [Strukture podataka zadatak 3 - Jakov Bejo]\n");
		printHashTable(HashTable);
		puts("\n Odaberite zeljenu funkciju programa unosom pripadajuceg broja:\n");
		puts("  (1) Unos studenta preko tipkovnice");
		puts("  (2) Unos studenata iz datoteke");
		puts("  (3) Trazenje maticnog broja");
		puts("  (0) Izlaz iz programa\n");
		printf(" Vas odabir: ");
		scanf("%d", &odabir);
		switch (odabir)
		{
		case 1:
			stdInput(HashTable);
			break;

		case 2:
			readFromFile(HashTable, filename);
			break;

		case 3:
			printf("\n Unesite ime i prezime studenta za kojeg zelite znati maticni broj: ");
			scanf("%s %s", firstname, lastname);
			key = index(lastname);
			idFind(HashTable[key], firstname, lastname);
			break;

		case 0:
			return 0;

		default:
			puts("\n Unesite ispravnu oznaku funkcije.");
			break;
		}
		printf("\n Pritisnite bilo koju tipku za nastavak...");
		system("pause>nul");
		system("cls");
	}
}

int initHashTable(Position HashTable[])
{
	for (int i = 0; i < TABLE; i++)
	{
		HashTable[i] = NULL;
		HashTable[i] = malloc(sizeof(Student));
		HashTable[i]->next = NULL;
	}
	return 0;
}

int index(char* lastname)
{
	int key = 0;
	int i = 0;
	while (i < 5 && lastname[i] != 0)
	{
		key += lastname[i];
		i++;
	}
	return (key % TABLE);
}

Position createStudentNode(char* fn, char* ln, int id)
{
	Position Node = NULL;
	Node = malloc(sizeof(Student));
	if (NULL == Node)
	{
		perror("\n Nesto poslo po krivu sa memorijom\n");
		return NULL;
	}
	strcpy(Node->firstName, fn);
	strcpy(Node->lastName, ln);
	Node->id = id;
	return Node;
}

int sortedAddStudent(Position head, Position element)
{
	Position prev = head;
	Position temp = head->next;
	int result;
	if (idCheck(head, element->id))
		return 0;
	while (temp != NULL)
	{
		result = nameCompare(temp, element);
		if (result == 0)
		{
			insertAfter(temp, element);
			puts("\n Student uspjesno dodan u listu.\n");
			return 0;
		}
		else if (result == 2)
		{
			puts("\n Student vec postoji.\n");
			return 0;
		}
		temp = temp->next;
	}
	insertAfter(prev, element);
	puts("\n Student uspjesno dodan u listu.\n");
	return 0;
}

int nameCompare(Position Temp, Position Element)
{
	if (strcmp(Temp->lastName, Element->lastName) > 0)
		return 1;
	else if (strcmp(Temp->lastName, Element->lastName) < 0)
		return 0;
	else
	{
		if (strcmp(Temp->firstName, Element->firstName) > 0)
			return 1;
		else if (strcmp(Temp->firstName, Element->firstName) < 0)
			return 0;
		else
			return 2;
	}
}

int idCheck(Position head, int id)
{
	Position temp = head->next;
	while (temp != NULL)
	{
		if (temp->id == id)
		{
			printf("\n Maticni broj vec postoji, pokusajte ponovno.\n");
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

int insertAfter(Position current, Position element)
{
	element->next = current->next;
	current->next = element;
	return 0;
}

int printHashTable(Position HashTable[])
{
	Position temp = NULL;
	printf("\n\tHASH KEY:\t  DATA:\n\n");
	for (int i = 0; i < TABLE; i++)
	{
		printf("\t   %d\t    -->\t", i);
		if (HashTable[i]->next == NULL)
			printf("--empty--\n");
		else
		{
			temp = HashTable[i]->next;
			while (temp != NULL)
			{
				printf(" %s %s,", temp->firstName, temp->lastName);
				temp = temp->next;
			}
			printf("\n");
		}
	}
	return 0;
}

int idFind(Position head, char* fn, char* ln)
{
	Position temp = head->next;
	while (temp != NULL)
	{
		if (!strcmp(temp->lastName, ln))
			if (!strcmp(temp->firstName, fn))
			{
				printf("\n Maticni broj trazenog studenta je: %d\n", temp->id);
				return 0;
			}
	}
	printf("\n Trazeni student ne postoji u hash-tablici.\n");
	return 0;
}

int stdInput(Position HashTable[])
{
	char firstname[MAX];
	char lastname[MAX];
	int id;
	int key;

	printf("\n Unesi ime, prezime i maticni broj studenta: ");
	scanf("%s %s %d", firstname, lastname, &id);
	key = index(lastname);
	sortedAddStudent(HashTable[key], createStudentNode(firstname, lastname, id));
	return 0;
}

int readFromFile(Position* HashTable, char* readFileName)
{
	char fName[MAX];
	char lName[MAX];
	int id;
	int key;
	FILE *dat;
	dat = fopen(readFileName, "r");
	if (dat == NULL)
	{
		perror("\n Greska u citanju datoteke.\n");
		return(-1);
	}

	while (fscanf(dat, "%s %s %d", fName, lName, &id) != EOF)
	{
		key = index(lName);
		sortedAddStudent(HashTable[key], createStudentNode(fName, lName, id));
	}

	printf("\n Lista studenata upisana iz datoteke.\n");
	fclose(dat);
	return 0;
}