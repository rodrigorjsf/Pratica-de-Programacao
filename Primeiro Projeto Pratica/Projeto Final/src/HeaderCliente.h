#ifndef HEADERCLIENTE_H_
#define HEADERCLIENTE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include "Types.h"

void gerarMaiusculo (char nome[], TCliente * c);
int ValidaNome (char nome[]);
int ValidaTelefone (char telefone[]);
int ValidaEmail (char email[]);
int RecebeCPF(char cpf[]);
void CadastrarNome (TCliente * c);
void CadastrarTelefone (TCliente * c);
void CadastrarEmail (TCliente * c);
void CadastrarCliente (FILE * arq, char cpf []);
void AlterarCliente (FILE * arq, char cpf []);
void ExibirCliente (FILE * arq, char cpf []);
void RemoverCliente (FILE * arqPass, FILE * arqVoo,FILE * arq, char cpf []);
void MenuCliente (FILE * arqPassagem, FILE * arqVoo,FILE * arqCliente, char op);




#endif /* HEADERCLIENTE_H_ */
