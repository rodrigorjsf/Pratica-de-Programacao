#ifndef HEADERVOO_H_
#define HEADERVOO_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define ANO 2017

void gerarCodigo (TVoo * v);
int RecebeCOD(char cod[]);
void CadastrarVoo (FILE * arq);
void ProcurarVoo (FILE * arq, int origem, int destino, Data d);
int RecebeCodVoo(char cod[]);
void AlterarValorPassagem (FILE * arq, char cod[]);
void CancelarVoo (FILE * arq, char cod[]);
void menuProcurarVoo (FILE *arqPass, FILE *arqCliente,FILE * arqVoo ,char op);
void MenuVOO (FILE *arqPass, FILE *arqCliente,FILE * arqVoo ,char op);

#endif /* HEADERVOO_H_ */
