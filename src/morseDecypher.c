#include "../headers/morse.h"

Arbre new_node()
{
	Noeud * node = malloc(sizeof(*node));
	if(!node)
	{
		fprintf(stderr, "Node creation failure\n");
		return NULL;
	}

	node->dot = NULL;
	node->dash = NULL;
	node->parent = NULL;
	node->character = '\0';

	return node;
}

Arbre add_char(Arbre * tree, char * morse, char c)
{
	if(!morse || !tree)
	{
		fprintf(stderr, "Unable to add a character.\n");
		return NULL;
	}

	if(!*tree)
	{
		*tree = new_node(*tree);
		if(!*tree)
		{
			fprintf(stderr, "Unable to create node\n");
			return NULL;
		}
	}

	if(!*morse)
	{
		(*tree)->character = c;
		return *tree;
	}

	if(*morse == DOT)
	{
		//Noeud * lchild;
		/*lchild =*/return add_char(&(*tree)->dot, ++morse, c);
		//lchild->parent = *tree;
		//return lchild;
	}
	if(*morse == DASH)
	{
		/*Noeud * rchild;*/
		/*rchild =*/return add_char(&(*tree)->dash, ++morse, c);
		//rchild->parent = *tree;
		//return rchild;
	}
	return NULL;
}

char seekChar(Arbre tree, char * morse)
{
	if(!tree)
		return '?';
	if(!*morse)
		return tree->character;
	if(*morse == DOT)
		return seekChar(tree->dot, ++morse);
	if(*morse == DASH)
		return seekChar(tree->dash, ++morse);
	return '?';
}

char * morseDecypher(Arbre tree, char * morse)
{
	char * current = morse;
	char * parsed = malloc(sizeof(char) * (strlen(morse)+1));

	if(!parsed)
	{
		fprintf(stderr, "Unable to alloc memory\n");
		return NULL;
	}

	char * current_parsed = parsed;
	int done = 0;
	while(!done)
	{
		while(*current && *current != SEP)
			++current;

		if(!*current)
			done = 1;

		else
			*current = '\0';

		*current_parsed = seekChar(tree, morse);
		++current_parsed;
		++current;
		morse = current;
	}
	*current_parsed = '\0';
	return parsed;
}

void inorder(Arbre tree)
{
	if(tree)
	{
		inorder(tree->dot);
		printf("Node: %c, ", tree->character);
		if(tree->parent == NULL)
			printf("Parent: NULL \n");
		else
			printf("Parent: %p \n", tree->parent);
		inorder(tree->dash);
	}
}

Arbre initForMorse()
{
	Arbre tree = NULL;
	add_char(&tree, ".-\0", 'A');
	add_char(&tree, "-...\0", 'B');
	add_char(&tree, "-.-.\0", 'C');
	add_char(&tree, "-..\0", 'D');
	add_char(&tree, ".\0", 'E');
	add_char(&tree, "..-.\0", 'F');
	add_char(&tree, "--.\0", 'G');
	add_char(&tree, "....\0", 'H');
	add_char(&tree, "..\0", 'I');
	add_char(&tree, ".---\0", 'J');
	add_char(&tree, "-.-\0", 'K');
	add_char(&tree, ".-..\0", 'L');
	add_char(&tree, "--\0", 'M');
	add_char(&tree, "-.\0", 'N');
	add_char(&tree, "---\0", 'O');
	add_char(&tree, ".--.\0", 'P');
	add_char(&tree, "--.-\0", 'Q');
	add_char(&tree, ".-.\0", 'R');
	add_char(&tree, "...\0", 'S');
	add_char(&tree, "-\0", 'T');
	add_char(&tree, "..-\0", 'U');
	add_char(&tree, "...-\0", 'V');
	add_char(&tree, ".--\0", 'W');
	add_char(&tree, "-..-\0", 'X');
	add_char(&tree, "-.--\0", 'Y');
	add_char(&tree, "--..\0", 'Z');
	add_char(&tree, ".----\0", '1');
	add_char(&tree, "..---\0", '2');
	add_char(&tree, "...--\0", '3');
	add_char(&tree, "....-\0", '4');
	add_char(&tree, ".....\0", '5');
	add_char(&tree, "-....\0", '6');
	add_char(&tree, "--...\0", '7');
	add_char(&tree, "---..\0", '8');
	add_char(&tree, "----.\0", '9');
	add_char(&tree, "-----\0", '0');
	add_char(&tree, ".-.-.-\0", '.');
	add_char(&tree, "--..--\0", ',');
	add_char(&tree, "..--..\0", '?');
	add_char(&tree, "-..-.\0", '/');
	add_char(&tree, ".----.\0", '\'');
	add_char(&tree, "-.-.--\0", '!');
	add_char(&tree, "-.-.-.\0", ';');
	add_char(&tree, "---...\0", ':');
	add_char(&tree, ".-.-.\0", '+');
	add_char(&tree, "-....-\0", '-');
	add_char(&tree, "-...-\0", '=');
	add_char(&tree, "-.--.\0", '(');
	add_char(&tree, "-.--.-\0", ')');
	add_char(&tree, "..--.-\0", '_');
	add_char(&tree, "...-..-\0", '$');
	add_char(&tree, ".-..-.\0", '"');
	add_char(&tree, ".--.-.\0", '@');
	add_char(&tree, ".-...\0", '&');
	add_char(&tree, "-...-\0", ' ');
	return tree;	
}

bool isDot(Arbre tree)
{
	return (tree->parent->dot == tree);
}

/*Arbre setParent(Arbre tree)
{
	Arbre temp = tree;
	while(temp)
	{
		Arbre parent = temp;
		temp->dot->parent = parent;
		if(temp->dot)
			temp = temp->dot;
		else if(temp->dash)
			temp = temp->dash;
		else
		{
			temp = temp->parent;
		}
	}
}*/

/*void bfs(Arbre tree, char queue[60], char c, int * front, int * before)
{
	c = tree->character;
	if((*front <= *before) && (tree->character == queue[*front]))
	{
		if(tree->dash)
			queue[++(*before)] = tree->dash->character;
		queue[++(*before)] = tree->dot->character;
		(*front)++;
	}
	if(tree->dash)
		bfs(tree->dash, queue, c, front, before);
	if(tree->dot)
		bfs(tree->dot, queue, c, front, before);
}*/

void morseTable()
{
	clrscr();
	//for(int i = 0; i < 27; i++)
	puts(".-\tA\t\t.----\t1");
	puts("-...\tB\t\t..---\t2");
	puts("-.-.\tC\t\t...--\t3");
	puts("-..\tD\t\t....-\t4");
	puts(".\tE\t\t.....\t5");
	puts("..-.\tF\t\t-....\t6");
	puts("--.\tG\t\t--...\t7");
	puts("....\tH\t\t---..\t8");
	puts("..\tI\t\t----.\t9");
	puts(".---\tJ\t\t-----\t0");
	puts("-.-");
}

void destroyTree(Arbre tree)
{
	if(tree)
	{
		destroyTree(tree->dot);
		destroyTree(tree->dash);
		free(tree);
	}
}