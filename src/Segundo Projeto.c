#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>



typedef struct cellT {
   char          ch;
   struct cellT *link;
} cellT;

typedef struct {
   cellT *start;
   cellT *cursor;
} bufferT;

FILE * criarArquivo (char nome[]) {
	FILE * arq;
	arq = fopen (nome, "r+b");
	if (arq == NULL) {
		arq = fopen (nome, "w+b");
	}
	return arq;
}

bufferT *NewBuffer( void) {
   bufferT *b;
   b = malloc( sizeof (bufferT));
   if (b == NULL)
	   exit( EXIT_FAILURE);
   b->start = b->cursor = malloc( sizeof (cellT)); // "dummy"
   return b;
}
void DeleteCharacter( bufferT *b) {
   cellT *cp;
   if (b->cursor->link != NULL) {
      cp = b->cursor->link;
      b->cursor->link = cp->link;
      free( cp);
   }
}
void InsertCharacter( bufferT *b, char ch) {
   cellT *cp;
   cp = malloc( sizeof (cellT));
   cp->ch = ch;
   cp->link = b->cursor->link;
   b->cursor->link = cp;
   b->cursor = cp;
}

void MoveCursorForward( bufferT *b) {
   if (b->cursor->link != NULL)
      b->cursor = b->cursor->link;
}

// Retrocede o cursor de uma posição.

void MoveCursorBackward( bufferT *b) {
   cellT *cp;
   if (b->cursor != b->start) {
      cp = b->start;
      while (cp->link != b->cursor)
         cp = cp->link;
      b->cursor = cp;
   }
}

void DisplayBuffer( bufferT *b) {
   cellT *cp;
   for (cp = b->start->link; cp != NULL; cp = cp->link)
      printf( " %c", cp->ch);
   printf( "\n");
   for (cp = b->start->link; cp != b->cursor; cp = cp->link)
      printf( "  ");
   printf( "^\n");
}

void FreeBuffer( bufferT *b) {
   cellT *cp, *next;
   cp = b->start;
   while (cp != NULL) {
      next = cp->link;
      free( cp);
      cp = next;
   }
   free( b);
}

int main(int argc, char *argv[ ] ) {
	FILE * arq = NULL;
	arq = criarArquivo (argv[1]);
	return 0;
}
