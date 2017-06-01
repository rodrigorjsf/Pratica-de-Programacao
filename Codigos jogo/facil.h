/*
 * facil.h
 *
 *  Created on: 30 de mai de 2017
 *      Author: Rodrigo
 */

#ifndef FACIL_H_
#define FACIL_H_
#include <time.h>
#include "tile.h"

void dificuldade_facil(int op);
void desenha_jogo(BITMAP * buffer, TILE * primeiro, TILE * invi, int tabuleiro[][3]);

#endif /* FACIL_H_ */
