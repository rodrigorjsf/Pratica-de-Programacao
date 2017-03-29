#ifndef BUSCAS_H_
#define BUSCAS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include "Types.h"

int BuscarPassagemCPF (FILE * arq, char cpf [], int pos);
int BuscarPassagemCodReserva (FILE * arq, char cod []);
int BuscarPassagemCodVoo (FILE * arq, char cod [], int pos);
int procurarVooPassagem(FILE *arqVoo, int origem, int destino, Data d, char cod[]);
int BuscarCliente (FILE * arq, char cpf []);
int BuscarVoo(FILE * arq, char cod[]);
int BuscarVooPorData(FILE * arq, Data d);
int BuscarTodosVoos (FILE * arq, int origem, int destino, Data d , int pos);



#endif /* BUSCAS_H_ */
