#include "tile.h"

TILE* create_Tile(BITMAP* image, int tabuleiro[][3], int count, TILE * tile, int pos_x, int pos_y)
{
	TILE* t = (TILE*) malloc(sizeof(TILE));

	int i = 0;
	int j = 0;
	int pos_x_atual;
	int pos_y_atual;

   t->img = image;
   t->num = count;
   t->prox = NULL;
   if(tile != NULL)
	   tile->prox = t;

   for ( i=0; i<3; i++ )
   {
	   for (j=0; j<3; j++ )
	   {
		   pos_x_atual = j*161;
		   pos_y_atual = i*161;
			   if (tabuleiro[i][j] == t->num)
			   {
				   t->pos_x = pos_x + pos_x_atual;
				   t->pos_y = pos_y + pos_y_atual;
				   break;
			   }
	   }
   }

   return t;
}

void destroy_Tile(TILE* t)
{
	if (t != NULL){
		destroy_Tile(t->prox);
		free(t);
	}
}


void move_left(TILE * tile, int tabuleiro[][3], int i, int j){

	int aux;
	j = j - 1;
	TILE * tileEsq;
	tileEsq = busca_tile(tile, tabuleiro, i, j);
	tileEsq->pos_x = tileEsq->pos_x + 161;
	tile->pos_x = tile->pos_x - 161;
	aux = tabuleiro[i][j+1];
	tabuleiro[i][j+1] = tabuleiro[i][j];
	tabuleiro[i][j] = aux;

}
void move_right(TILE * tile, int tabuleiro[][3], int i, int j){
	int aux;
	j = j + 1;
	TILE * tileDir;
	tileDir = busca_tile(tile, tabuleiro, i, j);
	tileDir->pos_x = tileDir->pos_x - 161;
	tile->pos_x = tile->pos_x + 161;
	aux = tabuleiro[i][j-1];
	tabuleiro[i][j-1] = tabuleiro[i][j];
	tabuleiro[i][j] = aux;

}
void move_up(TILE * tile, int tabuleiro[][3], int i, int j){
	int aux;
	i = i - 1;
	TILE * tileUp;
	tileUp = busca_tile(tile, tabuleiro, i, j);
	tileUp->pos_y = tileUp->pos_y + 161;
	tile->pos_y = tile->pos_y - 161;
	aux = tabuleiro[i+1][j];
	tabuleiro[i+1][j] = tabuleiro[i][j];
	tabuleiro[i][j] = aux;

}
void move_down(TILE * tile, int tabuleiro[][3], int i, int j){
	int aux;
	i = i + 1;
	TILE * tileDown;
	tileDown = busca_tile(tile, tabuleiro, i, j);
	tileDown->pos_y = tileDown->pos_y - 161;
	tile->pos_y = tile->pos_y + 161;
	aux = tabuleiro[i-1][j];
	tabuleiro[i-1][j] = tabuleiro[i][j];
	tabuleiro[i][j] = aux;

}

TILE * busca_tile(TILE * PrimeiroTile, int tabuleiro[][3], int i, int j){
	do{
		if (tabuleiro[i][j] == PrimeiroTile->num){
			return PrimeiroTile;
		}
		else
			PrimeiroTile = PrimeiroTile->prox;
	}while(PrimeiroTile != NULL);
	return NULL;
}

