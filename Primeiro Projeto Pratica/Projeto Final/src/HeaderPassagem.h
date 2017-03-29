#ifndef HEADERPASSAGEM_H_
#define HEADERPASSAGEM_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void gerarCodigoReserva (TPass * p);
void ConsultarPassagem (FILE * arqCliente, FILE * arqPass, FILE * arqVoo,char cpf []);
void ImagemVoo(char voo[6][6]);
void preencherMatriz(FILE *arqVoo, char matriz[6][6], int posi);
int confirmaCompra(FILE *arqVoo, int i, int j, int posi);
float valorPassagem(FILE *arqVoo, int posi);
void liberarPoltrona(char matriz[6][6], int i, int j);
void acharCodigoVoo(FILE *arqVoo, int posi, char * cod);
void venderPassagem(FILE *arqPass, FILE *arqCliente, FILE *arqVoo, int origem, int destino, Data d);
void cancelarPassagem(FILE *arqPass, FILE *arqVoo, char codReserva[]);
void consultarPassageirosVoo(FILE *arqPass, FILE *arqCliente, char codVoo[]);
void MenuPassagem (FILE * arqPassagem, FILE * arqVoo,FILE * arqCliente, char op);


#endif /* HEADERPASSAGEM_H_ */
