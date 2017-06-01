#include "setup.h"
#include "button.h"
#include "dificuldade.h"
#include "facil.h"
#define SHORT 9

void dificuldade_facil(int op) {

	int sair_facil = FALSE;
	BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
	TILE * tileAux = NULL;
	TILE * tilePrimeiro = NULL;
	int countTile = 1;
	int som = 1;
	int pos_x = 99;
	int pos_y = 49;
	int movimentos = 0;
	int tabuleiro[3][3];
	int TabCerto[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 0 } };
	int checar[SHORT];
	int i, j, k, aux;

	srand(time(NULL));
	do {
		k = 0;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				aux = rand() % SHORT;
				tabuleiro[i][j] = aux;

				do {
					if (validar_vetor(checar, aux) == TRUE) {
						aux = rand() % SHORT;
						tabuleiro[i][j] = aux;
					}
				} while (validar_vetor(checar, aux) == TRUE);
				checar[k] = tabuleiro[i][j];
				k++;

			}

		}
	} while (valida_tabuleiro(tabuleiro, TabCerto) == 1);


	DATAFILE * data = NULL;
	packfile_password("trabalhopp");
	data = load_datafile("data/data.dat");
	packfile_password(NULL);
	DATAFILE * sons = NULL;
	packfile_password("trabalhopp");
	sons = load_datafile("data/sons.dat");
	packfile_password(NULL);
	DATAFILE * mick = NULL;
	packfile_password("trabalhopp");
	mick = load_datafile("data/mickey.dat");
	packfile_password(NULL);
	DATAFILE * don = NULL;
	packfile_password("trabalhopp");
	don = load_datafile("data/donald.dat");
	packfile_password(NULL);
	if (!data || !som || !mick || !don) {
		allegro_message("Erro ao carregar datafile");
		op = 2;
		sair_programa = TRUE;
	}

	if (op == 0) {
		TILE* MTum = create_Tile((BITMAP*) mick[M_TRES_UM].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = MTum;
		tilePrimeiro = MTum;
		TILE* MTdois = create_Tile((BITMAP*) mick[M_TRES_DOIS].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = MTdois;
		TILE* MTtres = create_Tile((BITMAP*) mick[M_TRES_TRES].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = MTtres;
		TILE* MTquatro = create_Tile((BITMAP*) mick[M_TRES_QUATRO].dat,
				tabuleiro, countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = MTquatro;
		TILE* MTcinco = create_Tile((BITMAP*) mick[M_TRES_CINCO].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = MTcinco;
		TILE* MTseis = create_Tile((BITMAP*) mick[M_TRES_SEIS].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = MTseis;
		TILE* MTsete = create_Tile((BITMAP*) mick[M_TRES_SETE].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = MTsete;
		TILE* MToito = create_Tile((BITMAP*) mick[M_TRES_OITO].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = MToito;
	} else {
		TILE* DTum = create_Tile((BITMAP*) don[D_TRES_UM].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = DTum;
		tilePrimeiro = DTum;
		TILE* DTdois = create_Tile((BITMAP*) don[D_TRES_DOIS].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = DTdois;
		TILE* DTtres = create_Tile((BITMAP*) don[D_TRES_TRES].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = DTtres;
		TILE* DTquatro = create_Tile((BITMAP*) don[D_TRES_QUATRO].dat,
				tabuleiro, countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = DTquatro;
		TILE* DTcinco = create_Tile((BITMAP*) don[D_TRES_CINCO].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = DTcinco;
		TILE* DTseis = create_Tile((BITMAP*) don[D_TRES_SEIS].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = DTseis;
		TILE* DTsete = create_Tile((BITMAP*) don[D_TRES_SETE].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = DTsete;
		TILE* DToito = create_Tile((BITMAP*) don[D_TRES_OITO].dat, tabuleiro,
				countTile, tileAux, pos_x, pos_y);
		countTile++;
		tileAux = DToito;
	}
	countTile = 0;
	TILE * tileNull = create_Tile((BITMAP*) data[GHOST_TREE].dat, tabuleiro,
			countTile, tileAux, pos_x, pos_y);

	Button* sair = create_button((BITMAP*) data[SAIR].dat,
			(BITMAP*) data[SAIRATIVO].dat, (SAMPLE*) sons[CLICK].dat, 600, 500);
	draw_sprite(buffer, (BITMAP*) data[FUNDO].dat, 0, 0);
	draw_sprite(buffer, (BITMAP*) data[BACKGROUND].dat, 95, 45);
	if (op == 0)
		draw_sprite(buffer, (BITMAP*) mick[MICKEYMEDIOTRES].dat, 99, 49);
	else
		draw_sprite(buffer, (BITMAP*) don[DONALDMEDIOTRES].dat, 99, 49);
	draw_sprite(buffer, (BITMAP*) data[MUTE].dat, 20, 520);
	button_draw(sair, buffer);
	draw_sprite(screen, buffer, 0, 0);
	rest(3000);
	clear(buffer);
	play_midi((MIDI*) sons[MUSICA].dat, TRUE);
	while (!sair_programa && !sair_facil) {
		while (ticks > 0 && !sair_programa && !sair_facil) {

			button_input(sair);

			draw_sprite(buffer, (BITMAP*) data[FUNDO].dat, 0, 0);
			draw_sprite(buffer, (BITMAP*) data[BACKGROUND].dat, 95, 45);
			button_draw(sair, buffer);
			textprintf_ex(buffer, font, 600, 100, makecol(255, 255, 255), -1,
					"MOVIMENTOS: %d", movimentos);
			desenha_jogo(buffer, tilePrimeiro, tileNull, tabuleiro);

			if (valida_tabuleiro(tabuleiro, TabCerto) == 1) {
				stop_midi();
				menu_vitoria(movimentos);
				sair_facil = TRUE;
				break;
			} else {
				if (mouse_x > 100 && mouse_x < 260 && mouse_y > 50
						&& mouse_y < 210) {
					if (mouse_b == 1) {
						mouse_b = 0;
						i = 0;
						j = 0;
						tileAux = busca_tile(tilePrimeiro, tabuleiro, i, j);
						if (tabuleiro[0][1] == 0) {
							move_right(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[1][0] == 0) {
							move_down(tileAux, tabuleiro, i, j);
							movimentos++;
						}
					}
				}
				if (mouse_x > 260 && mouse_x < 420 && mouse_y > 50
						&& mouse_y < 210) {
					if (mouse_b == 1) {
						mouse_b = 0;
						i = 0;
						j = 1;
						tileAux = busca_tile(tilePrimeiro, tabuleiro, i, j);

						if (tabuleiro[0][0] == 0) {
							move_left(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[0][2] == 0) {
							move_right(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[1][1] == 0) {
							move_down(tileAux, tabuleiro, i, j);
							movimentos++;
						}
					}
				}
				if (mouse_x > 420 && mouse_x < 580 && mouse_y > 50
						&& mouse_y < 210) {
					if (mouse_b == 1) {
						mouse_b = 0;
						i = 0;
						j = 2;
						tileAux = busca_tile(tilePrimeiro, tabuleiro, i, j);
						if (tabuleiro[0][1] == 0) {
							move_left(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[1][2] == 0) {
							move_down(tileAux, tabuleiro, i, j);
							movimentos++;
						}
					}
				}
				if (mouse_x > 100 && mouse_x < 260 && mouse_y > 210
						&& mouse_y < 370) {
					if (mouse_b == 1) {
						mouse_b = 0;
						i = 1;
						j = 0;
						tileAux = busca_tile(tilePrimeiro, tabuleiro, i, j);
						if (tabuleiro[0][0] == 0) {
							move_up(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[1][1] == 0) {
							move_right(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[2][0] == 0) {
							move_down(tileAux, tabuleiro, i, j);
							movimentos++;
						}
					}
				}
				if (mouse_x > 260 && mouse_x < 420 && mouse_y > 210
						&& mouse_y < 370) {
					if (mouse_b == 1) {
						mouse_b = 0;
						i = 1;
						j = 1;
						tileAux = busca_tile(tilePrimeiro, tabuleiro, i, j);
						if (tabuleiro[0][1] == 0) {
							move_up(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[1][0] == 0) {
							move_left(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[1][2] == 0) {
							move_right(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[2][1] == 0) {
							move_down(tileAux, tabuleiro, i, j);
							movimentos++;
						}
					}
				}
				if (mouse_x > 420 && mouse_x < 580 && mouse_y > 210
						&& mouse_y < 370) {
					if (mouse_b == 1) {
						mouse_b = 0;
						i = 1;
						j = 2;
						tileAux = busca_tile(tilePrimeiro, tabuleiro, i, j);
						if (tabuleiro[0][2] == 0) {
							move_up(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[1][1] == 0) {
							move_left(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[2][2] == 0) {
							move_down(tileAux, tabuleiro, i, j);
							movimentos++;
						}
					}
				}
				if (mouse_x > 100 && mouse_x < 260 && mouse_y > 370
						&& mouse_y < 530) {
					if (mouse_b == 1) {
						mouse_b = 0;
						i = 2;
						j = 0;
						tileAux = busca_tile(tilePrimeiro, tabuleiro, i, j);
						if (tabuleiro[1][0] == 0) {
							move_up(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[2][1] == 0) {
							move_right(tileAux, tabuleiro, i, j);
							movimentos++;
						}
					}
				}
				if (mouse_x > 260 && mouse_x < 420 && mouse_y > 370
						&& mouse_y < 530) {
					if (mouse_b == 1) {
						mouse_b = 0;
						i = 2;
						j = 1;
						tileAux = busca_tile(tilePrimeiro, tabuleiro, i, j);
						if (tabuleiro[1][1] == 0) {
							move_up(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[2][0] == 0) {
							move_left(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[2][2] == 0) {
							move_right(tileAux, tabuleiro, i, j);
							movimentos++;
						}
					}
				}
				if (mouse_x > 420 && mouse_x < 580 && mouse_y > 370
						&& mouse_y < 530) {
					if (mouse_b == 1) {
						mouse_b = 0;
						i = 2;
						j = 2;
						tileAux = busca_tile(tilePrimeiro, tabuleiro, i, j);
						if (tabuleiro[1][2] == 0) {
							move_up(tileAux, tabuleiro, i, j);
							movimentos++;
						} else if (tabuleiro[2][1] == 0) {
							move_left(tileAux, tabuleiro, i, j);
							movimentos++;
						}
					}
				}
			}
			if (mouse_x > 20 && mouse_x < 75 && mouse_y > 520
					&& mouse_y < 566) {
				if (mouse_b == 1) {
					mouse_b = 0;
					if (som == 1) {
						som = 0;
						midi_pause();
					} else {
						som = 1;
						midi_resume();
					}
				}
			}
			if (som == 1) {
				draw_sprite(buffer, (BITMAP*) data[PLAY].dat, 20, 520);
			} else {
				draw_sprite(buffer, (BITMAP*) data[MUTE].dat, 20, 520);
			}
			if (mouse_x > 600 && mouse_x < 750 && mouse_y > 500
					&& mouse_y < 555) {
				if (mouse_b == 1) {
					mouse_b = 0;
					screen_state = MAINMENU;
					sair_facil = TRUE;
				}
			}
			if (mouse_b == 1) {
				draw_sprite(buffer, (BITMAP*) data[CURSORATIVO].dat,
						mouse_x - 11, mouse_y);
			} else {
				draw_sprite(buffer, (BITMAP*) data[CURSOR].dat, mouse_x - 11,
						mouse_y);
			}
			draw_sprite(screen, buffer, 0, 0);
			clear(buffer);
			ticks--;
		}
	}
	stop_midi();
	destroy_bitmap(buffer);
	destroy_button(sair);
	destroy_Tile(tilePrimeiro);
	destroy_Tile(tileNull);
	if (!data) {
		unload_datafile(data);
	}
	if (!sons) {
		unload_datafile(sons);
	}
	if (!mick) {
		unload_datafile(mick);
	}
	if (!don) {
		unload_datafile(don);
	}
}

void desenha_jogo(BITMAP * buffer, TILE * primeiro, TILE * invi,
		int tabuleiro[][3]) {

	TILE * tileAux2 = primeiro;
	int i, j;
	int aux = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			primeiro = tileAux2;
			do {
				if (tabuleiro[i][j] == invi->num) {
					draw_sprite(buffer, invi->img, invi->pos_x, invi->pos_y);
					aux = 1;
				}

				else if (tabuleiro[i][j] == primeiro->num) {
					draw_sprite(buffer, primeiro->img, primeiro->pos_x,
							primeiro->pos_y);
					aux = 1;
				} else
					primeiro = primeiro->prox;

			} while (aux != 1);
			aux = 0;
		}
	}
}

