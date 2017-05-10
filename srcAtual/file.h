#include <stdio.h>

#include "rotinas.h"
#define SUCESSO 1
#define FAILURE 0

FILE * Criar(char nome[]);
FILE * Abrir(char nome[]);
void Fechar(FILE *arq);
void Remover(char nome[]);
int Salvar(Linha ** Texto, char fileDir[200]);
