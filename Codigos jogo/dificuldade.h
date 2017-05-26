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

typedef struct tile{
	BITMAP* img;
	int num;
	struct tile * prox;
}Tile;

void fecha_dificuldade();
int tela_dificuldade(int op);
void dificuldade_facil(int op);
void dificuldade_medio(int op);
void dificuldade_dificil(int op);
int validar_vetor(int checar[], int aux);
Tile* create_Tile(BITMAP* image, int count, Tile * tile, int x, int y);
void destroy_Tile(Tile* t);

#endif /* DIFICULDADE_H_ */
