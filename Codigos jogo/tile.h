
#ifndef TILE_H_
#define TILE_H_
#include <allegro.h>

typedef struct tile{
	BITMAP* img;
	int num;
	int pos_x;
	int pos_y;
	struct tile * prox;
}TILE;


TILE* create_Tile(BITMAP* image, int tabuleiro[3][3], int count, TILE * tile, int pos_x, int pos_y);
void destroy_Tile(TILE* t);
void move_left(TILE * tile, int tabuleiro[][3], int i, int j);
void move_right(TILE * tile, int tabuleiro[][3], int i, int j);
void move_up(TILE * tile, int tabuleiro[][3], int i, int j);
void move_down(TILE * tile, int tabuleiro[][3], int i, int j);
TILE * busca_tile(TILE * PrimeiroTile, int tabuleiro[][3], int i, int j);


#endif /* TILE_H_ */
