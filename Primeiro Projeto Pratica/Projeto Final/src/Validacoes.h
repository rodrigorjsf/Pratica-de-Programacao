#ifndef VALIDACOES_H_
#define VALIDACOES_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#define ANO 2017

FILE * criarArquivo (char nome[]);
void opcoesOrigem ();
void opcoesDestinos ();
int bissexto (int ano);
int ValidaCPF (char cpf[]);
int validaRemocao (FILE * arqPass, FILE * arqVoo,char cpf[]);
int validaDataCorreta(Data d);
int validaHoraCorreta (Horario horario);
int ValidaData(Data d);
int ValidaHora(Horario horario);
int ValidaCodVoo(char cod[]);
int validaCodReserva(char cod[]);
void atualizarVoos_e_Passagens (FILE *arqVoo, FILE *arqPassagem);


#endif /* VALIDACOES_H_ */
