#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_DIR (256)

typedef struct tree* Position;
typedef struct tree {
	char Name[MAX_DIR];
	Position Sibling;
	Position Child;
}Tree;

typedef struct stack* PositionS;
typedef struct stack {
	Position Directory;
	PositionS Next;
}Stack;

int printDirPath(PositionS);

int sortedMakeDirectory(Position, char*);

int insertFirstChild(Position, Position);

int insertChildAfter(Position, Position);

Position changeDirectory(PositionS,Position, char*);

int printDirectory(Position);

int push(PositionS, PositionS);

Position pop(PositionS,Position);

Position createTreeNode(char*);

PositionS createStackNode(Position);

int deleteSibling(Position, char*);

int clearMemory(Position);

int main()
{
	Position Root = NULL;
	Root = malloc(sizeof(Tree));
	strcpy(Root->Name, " ");
	Root->Sibling = NULL;
	Root->Child = NULL;
	PositionS HeadS = NULL;
	HeadS = malloc(sizeof(Stack));
	HeadS->Directory = NULL;
	HeadS->Next = NULL;
	push(HeadS, createStackNode(Root));
	puts("CMD simulation (type help for available commands) [Strukture podataka zadatak 8 - Jakov Bejo]\n");
	while (1)
	{
		char Cmd[MAX_DIR];
		char Dir[MAX_DIR];
		printf("\nC:");
		printDirPath(HeadS);
		printf(">");
		scanf("%s", Cmd);

		if (!strcmp(Cmd, "md"))
		{
			scanf("%s", Dir);
			sortedMakeDirectory(Root, Dir);
		}

		else if (!strcmp(Cmd, "cd"))
		{
			scanf("%s", Dir);
			Root = changeDirectory(HeadS,Root, Dir);
		}

		else if (!strcmp(Cmd, "cd..")) 
			Root = pop(HeadS,Root);

		else if (!strcmp(Cmd, "dir"))
			printDirectory(Root);

		else if (!strcmp(Cmd, "rmdir"))
		{
			scanf("%s", Dir);
			deleteSibling(Root, Dir);
		}

		else if (!strcmp(Cmd, "help"))
		{
			puts("\n Available commands:");
			puts(" Make directory 'md Name'");
			puts(" Change directory 'cd Name'");
			puts(" Move up one directory 'cd..'");
			puts(" Display content of selected directory 'dir'");
			puts(" Delete specific directory 'rmdir Name'");
			puts(" Clear screen 'cls'");
			puts(" Exit the program 'exit'");
		}

		else if (!strcmp(Cmd, "cls"))
			system("cls");

		else if (!strcmp(Cmd, "exit"))
		{
			while(HeadS->Next->Next!=NULL)
				Root = pop(HeadS,Root);
			free(HeadS->Next);
			free(HeadS);
			clearMemory(Root);
			return 0;
		}

		else
			printf("'%s' is not recognized as correct command\n",Cmd);
	}
}

int printDirPath(PositionS StackNode)
{
	if (StackNode == NULL)
			return 0;
	printDirPath(StackNode->Next);
	if(StackNode->Directory!=NULL)
		if (strcmp(StackNode->Directory->Name, " ") != 0)
			printf("\\%s", StackNode->Directory->Name);
	return 0;
}

int sortedMakeDirectory(Position Root, char* name)
{
	if (Root->Child==NULL)
		insertFirstChild(Root, createTreeNode(name));

	else if(strcmp(Root->Child->Name, name) > 0)
		insertFirstChild(Root, createTreeNode(name));

	else if(strcmp(Root->Child->Name, name) == 0)
		puts("\nDirectory with the same name already exists, try something different.");

	else
	{
		Position previous = Root->Child;
		Position current = Root->Child->Sibling;
		while (current != NULL)
		{
			if (strcmp(current->Name, name) > 0)
				break;
			previous = previous->Sibling;
			current = current->Sibling;
		}
		insertChildAfter(previous, createTreeNode(name));
	}
	return 0;
}

int insertFirstChild(Position parent, Position child) 
{
	if (parent->Child != NULL)
		child->Sibling = parent->Child;
	parent->Child = child;
	return 0;
}

int insertChildAfter(Position head, Position element)
{
	element->Sibling = head->Sibling;
	head->Sibling = element;
	return 0;
}

Position changeDirectory(PositionS Stack,Position Root, char* Dir) 
{
	Position temp = Root->Child;
	while (temp!= NULL)
	{
		if (strcmp(temp->Name, Dir) == 0) 
		{
			push(Stack, createStackNode(temp));
			return temp;
		}
		temp = temp->Sibling;
	}
	puts("The system cannot find the directory specified");
	return Root;
}

int printDirectory(Position R)
{
	puts("\n    Directory contents:");
	Position reader = NULL;
	reader = R->Child;
	while (reader!= NULL)
	{
		printf("	-%s\n", reader->Name);
		reader = reader->Sibling;
	}
	return 0;
}

int push(PositionS head, PositionS element)
{
	element->Next = head->Next;
	head->Next = element;
	return 0;
}

Position pop(PositionS head,Position root)
{
	if (strcmp(head->Next->Directory->Name, " ") != 0)
	{
		PositionS temp = head->Next;
		Position dir = temp->Next->Directory;
		head->Next = temp->Next;
		free(temp);
		return dir;
	}
	else
		return root;
}

Position createTreeNode(char* directory)
{
	Position Node = NULL;
	Node = (Position)malloc(sizeof(Tree));
	if (NULL == Node)
	{
		perror("Memory allocation error\n");
		return NULL;
	}
	strcpy(Node->Name, directory);
	Node->Sibling = NULL;
	Node->Child = NULL;
	return Node;
}

PositionS createStackNode(Position Dir)
{
	PositionS Node = (PositionS)malloc(sizeof(Stack));
	if (NULL == Node)
	{
		perror("Memory allocation error\n");
		return NULL;
	}
	Node->Directory = Dir;
	return Node;
}

int deleteSibling(Position parent, char* name)
{
	if (parent->Child != NULL)
	{
		Position prev = parent->Child;
		Position temp = parent->Child;

		if (strcmp(temp->Name, name) == 0)
		{
			parent->Child = temp->Sibling;
			clearMemory(temp->Child);
			free(temp);
			return 0;
		}
		while (temp->Sibling != NULL)
		{
			temp = temp->Sibling;
			if (strcmp(temp->Name, name) == 0)
			{
				prev->Sibling = temp->Sibling;
				clearMemory(temp->Child);
				free(temp);
				return 0;
			}
			prev = prev->Sibling;
		}
	}
	puts("The system cannot find the directory specified");
	return 0;
}

int clearMemory(Position Node) {
	if (Node == NULL)
		return 0;
	clearMemory(Node->Sibling);
	clearMemory(Node->Child);
	free(Node);
	return 0;
}
