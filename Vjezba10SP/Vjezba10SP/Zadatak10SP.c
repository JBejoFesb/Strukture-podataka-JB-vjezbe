#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX (256)

typedef struct tree *Position;
typedef struct tree {
	char element[MAX];
	Position left;
	Position right;
}Tree;

typedef struct stack* PositionS;
typedef struct stack {
	Position root;
	PositionS next;
}Stack;

int standardInput(PositionS);

int readFromFile(PositionS, char*);

int postfix(PositionS, char*);

int push(PositionS, PositionS);

Position pop(PositionS);

PositionS createOperandNode(char*);

Position createOperatorNode(Position,char*);

int stackCheck(PositionS);

int printTree(Position);

int printTreeToFile(Position);

int writeToFile(Position, char*);

int main()
{
	char ReadFile[MAX] = "postfix.txt";
	char WriteFile[MAX];
	int choice = -1;
	while (1)
	{
		PositionS Stack = NULL;
		Stack = (PositionS)malloc(sizeof(Stack));
		Stack->next = NULL;
		system("cls");
		puts(" Binarno stablo proracuna - Postfix->Infix [Strukture podataka zadatak 10 - Jakov Bejo]\n");
		puts("  (1)Unos preko tipkovnice");
		puts("  (2)Unos iz datoteke postfix.txt");
		puts("  (0)Izlaz iz programa");
		printf("\n  Odabir: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			standardInput(Stack);
			printf("\n  Izgled infix izraza je:\n\n  ");
			printTree(Stack->next->root);
			printf("\n\n  Upisite ime datoteke u koju zelite ispisati infix izraz: ");
			scanf("%s", WriteFile);
			writeToFile(Stack->next->root, WriteFile);
			printf("\n  Infix izraz uspjesno upisan u datoteku.\n");
			break;
		case 2:
			readFromFile(Stack, ReadFile);
			printf("\n  Izgled infix izraza je:\n\n  ");
			printTree(Stack->next->root);
			printf("\n\n  Upisite ime datoteke u koju zelite ispisati infix izraz: ");
			scanf("%s", WriteFile);
			writeToFile(Stack->next->root, WriteFile);
			printf("\n  Infix izraz uspjesno upisan u datoteku.\n");
			break;
		case 0:
			cleanMemory(Stack->next->root);
			free(Stack->next);
			free(Stack);
			return 0;
		default:
			printf("\n  Krivo unesen broj funkcije.\n");
			break;
		}
		puts("\n\n  Pritisnite bilo koju tipku za nastavak");
		system("pause>nul");
	}
	return 0;
}

int standardInput(PositionS stog)
{
	char* registar;
	registar = malloc(256 * sizeof(char));
	printf("\n  Unesite postfix izraz: ");
	getchar();
	gets(registar, 256);
	postfix(stog, registar);
	return 0;
}

int readFromFile(PositionS Stack, char* file)
{
	char* registry;
	registry = malloc(256 * sizeof(char));
	FILE* readFile;
	readFile = fopen(file, "r");
	if (NULL == readFile)
	{
		perror("Greska u citanju datoteke");
		return (-1);
	}
	fscanf(readFile, "%[^\n]%*c", registry);
	fclose(readFile);
	postfix(Stack, registry);
	return 0;
}

int postfix(PositionS Stack, char* Postfix)
{
	int procitani;
	int brojZnakova = strlen(Postfix);
	int prekid = 0;
	do
	{
		char string[MAX];
		sscanf(Postfix, "%s %n", string, &procitani);
		
		if (!strcmp(string, "+"))
		{
			if (stackCheck(Stack)) return 0;
			push(Stack, createOperatorNode(Stack,"+"));
		}

		else if (!strcmp(string, "-"))
		{
			if (stackCheck(Stack)) return 0;
			push(Stack, createOperatorNode(Stack, "-"));
		}

		else if (!strcmp(string, "*"))
		{
			if (stackCheck(Stack)) return 0;
			push(Stack, createOperatorNode(Stack, "*"));
		}
		
		else if (!strcmp(string, "/"))
		{
			if (stackCheck(Stack)) return 0;
			push(Stack, createOperatorNode(Stack, "/"));
		}

		else if (!strcmp(string, "%"))
		{
			if (stackCheck(Stack)) return 0;
			push(Stack, createOperatorNode(Stack, "%"));
		}
		
		else push(Stack, createOperandNode(string));

		Postfix += procitani;
		prekid += procitani;
	} while (prekid < brojZnakova);
	return 0;
}

int push(PositionS head, PositionS element)
{
	element->next = head->next;
	head->next = element;
	return 0;
}
Position pop(PositionS head)
{
	PositionS temp = head->next;
	head->next = temp->next;
	Position Root = temp->root;
	free(temp);
	return Root;
}

PositionS createOperandNode(char* Element)
{
	Position treeNode = NULL;
	PositionS stackNode = NULL;
	treeNode = malloc(sizeof(Tree));
	stackNode = malloc(sizeof(Stack));

	if (NULL == treeNode)
	{
		perror("Nesto je poslo krivo sa alokacijom memorije\n");
		return NULL;
	}

	if (NULL == stackNode)
	{
		perror("Nesto je poslo krivo sa alokacijom memorije\n");
		return NULL;
	}

	strcpy(treeNode->element, Element);
	treeNode->right = NULL;
	treeNode->left = NULL;

	stackNode->root = treeNode;
	stackNode->next = NULL;
	return stackNode;
}

Position createOperatorNode(Position stack,char* Element)
{
	Position treeNode = NULL;
	PositionS stackNode = NULL;
	treeNode = malloc(sizeof(Tree));
	stackNode = malloc(sizeof(Stack));

	if (NULL == treeNode)
	{
		perror("Nesto je poslo krivo sa alokacijom memorije\n");
		return NULL;
	}

	if (NULL == stackNode)
	{
		perror("Nesto je poslo krivo sa alokacijom memorije\n");
		return NULL;
	}

	strcpy(treeNode->element, Element);
	treeNode->right = pop(stack);
	treeNode->left = pop(stack);

	stackNode->root = treeNode;
	stackNode->next = NULL;
	return stackNode;
}

int stackCheck(PositionS check)
{
	if (check->next == NULL || check->next->next == NULL)
	{
		printf("\n Postfix izraz je neispravan i rezultat nece biti ispravan!");
		return 1;
	}
	return 0;
}

int printTree(Position treeNode)
{
	if (treeNode == NULL)
		return 0;
	if (treeNode->left != NULL && treeNode->right != NULL)
		printf("(");
	printTree(treeNode->left);
	printf("%s", treeNode->element);
	printTree(treeNode->right);
	if (treeNode->left != NULL && treeNode->right != NULL)
		printf(")");
	return 0;
}

int printTreeToFile(Position treeNode,FILE* wf)
{
	if (treeNode == NULL)
		return 0;
	if (treeNode->left != NULL && treeNode->right != NULL)
		fprintf(wf,"(");
	printTreeToFile(treeNode->left,wf);
	fprintf(wf,"%s", treeNode->element);
	printTreeToFile(treeNode->right, wf);
	if (treeNode->left != NULL && treeNode->right != NULL)
		fprintf(wf,")");
	return 0;
}

int writeToFile(Position treeRoot, char* datoteka)
{
	FILE* writeFile;
	writeFile = fopen(datoteka, "w");
	if (NULL == writeFile)
	{
		perror("Greska u citanju datoteke");
		return (-1);
	}
	printTreeToFile(treeRoot, writeFile);
	fclose(writeFile);
	return 0;
}

int cleanMemory(Position treeNode)
{
	if (NULL != treeNode)
	{
		cleanMemory(treeNode->left);
		cleanMemory(treeNode->right);
		free(treeNode);
	}
	return 0;
}