/*
 * dificuldade.h
 *
 *  Created on: 26 de mai de 2017
 *      Author: Rodrigo
 */

#ifndef DIFICULDADE_H_
#define DIFICULDADE_H_

#include <stdio.h>
#include <stdlib.h>


FILE * criarArquivo();
void menu_vitoria(int movimentos);
int tela_dificuldade(int op);
int validar_vetor(int checar[], int aux);
int valida_tabuleiro(int tabuleiro[3][3], int TabCerto[3][3]);

#endif /* DIFICULDADE_H_ */
