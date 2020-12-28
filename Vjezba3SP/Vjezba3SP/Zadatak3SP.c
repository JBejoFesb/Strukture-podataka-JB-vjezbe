#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX (256)

typedef struct student *Position;
typedef struct student {
	char firstName[MAX];
	char lastName[MAX];
	int birthYear;
	Position next;
	Position prev;
}Student;

Position createStudent(char*, char*, int);

Position searchStudent(Position, char*);

int readFromFile(Position, char*);

int writeIntoFile(Position, char*);

int sortedAddStudent(Position, Position);

int nameCompare(Position, Position);

int insertAfter(Position, Position);

int insertBefore(Position, Position);

int printList(Position);

int deleteStudent(Position);

int clearMemory(Position);

int main()
{
	Position List = NULL;
	List = (Position)malloc(sizeof(Student));
	List->next = NULL;
	List->prev = NULL;
	Position student = NULL;
	char readDat[MAX];
	char writeDat[MAX];
	char firstname[MAX];
	char lastname[MAX];
	int birthyear;
	int odabir = -1;
	while (1)
	{
		printf("\n Pritisnite bilo koju tipku za nastavak...");
		system("pause>nul");
		system("cls");
		puts("Program za unos i upravljanje liste studenata [Strukture podataka zadatak 3 - Jakov Bejo]\n");
		puts(" Odaberite zeljenu funkciju programa unosom pripadajuceg broja:\n");
		puts("  (1) Unos studenta preko tipkovnice");
		puts("  (2) Unos liste studenta preko datoteke");
		puts("  (3) Pretrazivanje studenata po prezimenu");
		puts("  (4) Brisanje studenta iz liste");
		puts("  (5) Ispis liste");
		puts("  (6) Ispis liste u datoteku");
		puts("  (0) Izlaz iz programa\n");
		printf(" Vas odabir: ");
		scanf("%d", &odabir);
		switch (odabir)
		{
		case 1:
			printf("\n Unesi ime, prezime i godinu rodenja studenta: ");
			scanf("%s %s %d", firstname, lastname, &birthyear);
			sortedAddStudent(List, createStudent(firstname, lastname, birthyear));
			break;

		case 2:
			printf("\n Odaberite datoteku iz koje ce se uzeti lista: ");
			scanf("%s", readDat);
			readFromFile(List, readDat);
			break;

		case 3:
			printf("\n Unesite prezime studenta kojeg zelite traziti: ");
			scanf(" %s", lastname);
			student = searchStudent(List, lastname);
			if (student != NULL)
				printf("\n Podaci trazenog studenta:  %s %s %d\n", student->firstName, student->lastName, student->birthYear);
			break;

		case 4:
			printf("\n Unesite prezime studenta kojeg zelite izbrisati: ");
			scanf("%s", lastname);
			deleteStudent(searchStudent(List, lastname));
			break;

		case 5:
			printList(List);
			break;

		case 6:
			puts("\n Odaberite datoteku u koje ce se upisati lista: ");
			scanf("%s", writeDat);
			writeIntoFile(List, writeDat);
			break;

		case 0:
			clearMemory(List);
			return 0;

		default:
			puts("\n Unesite ispravnu oznaku funkcije.");
			break;
		}
	}
}

Position createStudent(char* firstName, char* lastName, int birthYear)
{
	Position student = NULL;
	student = (Position)malloc(sizeof(Student));
	if (NULL == student)
	{
		perror("\n Nesto poslo po krivu sa memorijom\n");
		return NULL;
	}
	strcpy(student->firstName, firstName);
	strcpy(student->lastName, lastName);
	student->birthYear = birthYear;
	return student;
}

int insertAfter(Position current, Position element)
{
	element->next = current->next;
	element->prev = current;
	if (current->next != NULL)
		current->next->prev = element;
	current->next = element;
	return 0;
}

int insertBefore(Position current, Position element)
{
	element->next = current;
	element->prev = current->prev;
	if (current->prev != NULL)
		current->prev->next = element;
	current->prev = element;
	return 0;
}

int sortedAddStudent(Position head, Position element)
{
	Position temp = head;
	int result;
	while (temp->next != NULL)
	{
		temp = temp->next;
		result = nameCompare(temp, element);
		if (result == 1)
		{
			insertBefore(temp, element);
			puts("\n Student uspjesno dodan u listu.\n");
			return 0;
		}
		else if (result == 2)
		{
			puts("\n Student vec postoji.\n");
			return 0;
		}
	}
	insertAfter(temp, element);
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

Position searchStudent(Position head, char *lastName)
{
	Position temp = head->next;
	char tempFirstName[MAX];
	while (temp != NULL)
	{
		if (!strcmp(temp->lastName, lastName))
		{
			if (temp->next != NULL && !strcmp(temp->lastName, temp->next->lastName))
			{
				printf("\n Postoji vise studenata s tim prezimenom, upisite ime studenta: ");
				scanf("%s", tempFirstName);
				if (!strcmp(temp->firstName, tempFirstName))
					return temp;
				else
				{
					temp = temp->next;
					continue;
				}
			}
			else
				return temp;
		}
		temp = temp->next;
	}
	printf("\n Trazeni student ne postoji\n");
	return NULL;
}

int deleteStudent(Position temp)
{
	if (temp == NULL)
		return 0;
	temp->prev->next = temp->next;
	if (temp->next != NULL)
		temp->next->prev = temp->prev;
	free(temp);
	printf("\n Student uspjesno izbrisan.\n");
	return 0;
}

int printList(Position head)
{
	Position citac = NULL;
	citac = head->next;
	puts("\n Lista studenata:\n");
	while (citac != NULL)
	{
		printf("  %s %s %d\n", citac->firstName, citac->lastName, citac->birthYear);
		citac = citac->next;
	}
	printf("\n");
	return 0;
}

int clearMemory(Position currentNode)
{
	if (currentNode == NULL)
		return 0;
	clearMemory(currentNode->next);
	free(currentNode);
	return 0;
}

int readFromFile(Position head, char* readFileName)
{
	char fName[MAX];
	char lName[MAX];
	int bYear;

	FILE *dat;
	dat = fopen(readFileName, "r");
	if (dat == NULL)
	{
		perror("\n Greska u citanju datoteke.\n");
		return(-1);
	}

	while (fscanf(dat, "%s %s %d", fName, lName, &bYear) != EOF)
		sortedAddStudent(head, createStudent(fName, lName, bYear));

	printf("\n Lista studenata upisana iz datoteke.\n");
	fclose(dat);
	return 0;
}

int writeIntoFile(Position head, char* NovaDatoteka)
{
	Position writer = NULL;

	FILE *dat;
	dat = fopen(NovaDatoteka, "w");
	if (dat == NULL)
	{
		perror("\n Greska u citanju datoteke.\n");
		return(-1);
	}

	for (writer = head->next; writer != NULL; writer = writer->next)
		fprintf(dat, "%s %s %d\n", writer->firstName, writer->lastName, writer->birthYear);

	printf("\n Lista upisana u novu datoteku\n");
	fclose(dat);
	return 0;
}