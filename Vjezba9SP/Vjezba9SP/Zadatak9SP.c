#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct tree *Position;
typedef struct tree {
	int number;
	Position left;
	Position right;
}Tree;

Position createTreeNode(int);

Position addTreeNode(Position, int);

Position searchTreeNode(Position, int);

Position searchMin(Position);

Position searchMax(Position);

Position deleteTreeNode(Position,int);

int printTreeInOrder(Position);

int printTreePreOrder(Position);

int printTreePostOrder(Position);

int cleanMemory(Position);

int main()
{
	Position Node = NULL;
	Position Root = NULL;
	int choice=-1, Number=-1;
	while (1)
	{
		puts("\n Pritisnite bilo koju tipku za nastavak...");
		system("pause>nul");
		system("cls");
		puts(" Binarno stablo za pretrazivanje [Strukture podataka zadatak 9 - Jakov Bejo]\n");
		puts(" Odaberite funkciju programa:\n");
		puts("  (1)Unosenje novog elementa u stablo");
		puts("  (2)Trazenje odredenog elementa u stablu");
		puts("  (3)Trazenje najmanjeg elementa u stablu");
		puts("  (4)Trazenje najveceg elementa u stablu");
		puts("  (5)Brisanje odredenog elementa iz stabla");
		puts("  (6)Ispis binarnog stabla InOrder");
		puts("  (6)Ispis binarnog stabla PreOrder");
		puts("  (7)Ispis binarnog stabla PostOrder");
		puts("  (0)Izlaz iz programa");
		printf("\n Vas odabir: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("\n Unesite broj kojeg zelite unijeti u binarno stablo: ");
			scanf("%d", &Number);
			if (NULL == Root)
			{
				Root = createTreeNode(Number);
				printf("\n Element uspjesno dodan u stablo.\n");
			}
			else
			{
				Node = addTreeNode(Root, Number);
				if(Node==NULL)
					printf("\n Broj vec postoji u stablu.\n");
				else
					printf("\n Element uspjesno dodan u stablo.\n");
			}
			break;

		case 2:
			printf("\n Unesite broj kojeg zelite traziti u binarnom stablu: ");
			scanf("%d", &Number);
			Node=searchTreeNode(Root, Number);
			if (NULL != Node) 
				printf("\n Element vrijednosti %d postoji u binarnom stablu.\n",Node->number);
			else
				printf("\n Trazeni element ne postoji u binarnom stablu.\n");
			break;

		case 3:
			Node = searchMin(Root);
			if (NULL != Node)
				printf("\n Vrijednost najmanjeg elementa je %d", Node->number);
			else
				printf("\n Stablo je prazno.\n");
			break;

		case 4:
			Node = searchMax(Root);
			if (NULL != Node)
				printf("\n Vrijednost najveceg elementa je %d", Node->number);
			else
				printf("\n Stablo je prazno.\n");
			break;

		case 5:
			printf("\n Unesite broj kojeg zelite izbrisati iz binarnog stabla: ");
			scanf("%d", &Number);
			deleteTreeNode(Root,Number);
			break;

		case 6:
			printf("\n Binarno stablo trenutno sadrzi (InOrder):\n\n");
			printTreeInOrder(Root);
			printf("\n");
			break;

		case 7:
			printf("\n Binarno stablo trenutno sadrzi: (PreOrder)\n\n");
			printTreePreOrder(Root);
			printf("\n");
			break;

		case 8:
			printf("\n Binarno stablo trenutno sadrzi: (PostOrder)\n\n");
			printTreePostOrder(Root);
			printf("\n");
			break;

		case 0:
			cleanMemory(Root);
			return 0;

		default:
			printf("\n Krivo unesen broj funkcije.\n");
			break;
		}
	}
}

Position createTreeNode(int Number)
{
	Position Node = NULL;
	Node = malloc(sizeof(Tree));
	if (NULL == Node)
	{
		perror("\n Nesto je poslo krivo sa alokacijom memorije\n");
		return NULL;
	}
	Node->number = Number;
	Node->left = NULL;
	Node->right = NULL;
	return Node;
}

Position addTreeNode(Position treeNode, int x)
{
	if (NULL == treeNode)
		treeNode = createTreeNode(x);
	else if (x < treeNode->number)
		treeNode->left = addTreeNode(treeNode->left, x);
	else if (x > treeNode->number)
		treeNode->right = addTreeNode(treeNode->right, x);
	else
		return NULL;
	return treeNode;
}

Position searchTreeNode(Position treeNode, int x)
{
	if (treeNode == NULL)
		return NULL;
	else if (x < treeNode->number)
		return searchTreeNode(treeNode->left, x);
	else if (x > treeNode->number)
		return searchTreeNode(treeNode->right, x);
	else return treeNode;
}

Position searchMin(Position treeNode)
{
	if (NULL == treeNode)
		return NULL;
	else if (NULL == treeNode->left)
		return treeNode;
	return searchMin(treeNode->left);
}

Position searchMax(Position treeNode)
{
	if (NULL == treeNode)
		return NULL;
	else if (NULL == treeNode->right)
		return treeNode;
	return searchMax(treeNode->right);
}

Position deleteTreeNode(Position treeNode, int x)
{
	if (NULL == treeNode)
		printf("\n Trazeni element ne postoji u binarnom stablu.\n");
	else if (x < treeNode->number)
		treeNode->left = deleteTreeNode(treeNode->left, x);
	else if (x > treeNode->number)
		treeNode->right = deleteTreeNode(treeNode->right, x);
	else if (treeNode->left != NULL && treeNode->right != NULL)
	{
		Position temp = searchMin(treeNode->right);
		treeNode->number = temp->number;
		treeNode->right = deleteTreeNode(treeNode->right, treeNode->number);
	}
	else
	{
		Position temp = treeNode;
		if (NULL == treeNode->left)
			treeNode = treeNode->right;
		else
			treeNode = treeNode->left;
		free(temp);
		printf("\n Element uspjesno izbrisan.\n");
	}
	return treeNode;
}

int printTreeInOrder(Position treeNode)
{
	if (treeNode == NULL)
		return 0;
	printTreeInOrder(treeNode->left);
	printf(" %d", treeNode->number);
	printTreeInOrder(treeNode->right);
	return 0;
}

int printTreePreOrder(Position treeNode)
{
	if (treeNode == NULL)
		return 0;
	printf(" %d", treeNode->number);
	printTreePreOrder(treeNode->left);
	printTreePreOrder(treeNode->right);
	return 0;
}

int printTreePostOrder(Position treeNode)
{
	if (treeNode == NULL)
		return 0;
	printTreePostOrder(treeNode->left);
	printTreePostOrder(treeNode->right);
	printf(" %d", treeNode->number);
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