#include "setup.h"
#include "button.h"
#include "dificuldade.h"
#include "tile.h"
#define SHORT 9
#define MEDIUM 15
#define LONG 24
#define SQUARE_W 160
#define SQUARE_H 160

FILE * criarArquivo() {
	FILE * arq;
	int aux = 0;
	arq = fopen("Arq/recorde.txt", "r+t");
	if (arq == NULL) {
		arq = fopen("Arq/recorde.txt", "w+t");
		fprintf(arq, "%d", aux);
	}
	return arq;
}

void menu_vitoria(int movimentos) {

	BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);

	int sair_menu_vitoria = FALSE;
	int recordeAux, recorde;
	FILE * rec = criarArquivo();
	fseek (rec, 0, 0);
	fscanf(rec, "%d", &recordeAux);

	recorde = movimentos;

	DATAFILE * data = NULL;
	packfile_password("trabalhopp");
	data = load_datafile("data/data.dat");
	packfile_password(NULL);
	DATAFILE * som = NULL;
	packfile_password("trabalhopp");
	som = load_datafile("data/sons.dat");
	packfile_password(NULL);
	if(!data || !som){
		allegro_message("Erro ao carregar datafile");
		sair_programa = TRUE;
	}

	Button* Bvoltar = create_button((BITMAP*) data[VOLTAR].dat, (BITMAP*) data[VOLTARATIVO].dat, (SAMPLE*) som[CLICK].dat,
			(SCREEN_W / 2) - 75, 500);

	draw_sprite(buffer, (BITMAP*) data[FUNDO].dat, 0, 0);
	draw_sprite(buffer, (BITMAP*) data[LOGO].dat, 175, 50);
	draw_sprite(screen, buffer, 0, 0);
	rest(1000);
	if (recordeAux == 0 || recorde < recordeAux) {
		fseek (rec, 0, 0);
		fprintf(rec, "%d", recorde);
		fclose (rec);

			play_sample((SAMPLE*) som[RECORD].dat, 200, 128, 1000, FALSE);

		draw_sprite(buffer, (BITMAP*) data[MEDALHA].dat, 600, (SCREEN_H / 2) - 125);
		rotate_sprite(buffer, (BITMAP*) data[NOVORECORDE].dat, 40, 220, ftofix(-25.0));
		draw_sprite(screen, buffer, 0, 0);
		rest(2000);
		textout_centre_ex(buffer, (FONT*) data[GAMEFONT].dat, "MOVIMENTOS:", SCREEN_W / 2, SCREEN_H / 2,makecol(0, 0, 255), -1);
		draw_sprite(screen, buffer, 0, 0);
		rest(2000);
		textprintf_centre_ex(buffer, (FONT*) data[GAMEFONT].dat, SCREEN_W / 2,(SCREEN_H / 2) + 50, makecol(0, 0, 255), -1, "%d", movimentos);
		draw_sprite(screen, buffer, 0, 0);
		rest(2000);
	}
	else {

			play_sample((SAMPLE*) som[VITORIA].dat, 200, 128, 1000, FALSE);

		draw_sprite(buffer, (BITMAP*) data[MEDALHA].dat, 600, (SCREEN_H / 2) - 125);
		draw_sprite(buffer, (BITMAP*) data[RECORDEATUAL].dat, (SCREEN_W / 2)-133, (SCREEN_H / 2)-100);
		textprintf_centre_ex(buffer, (FONT*) data[GAMEFONT].dat, SCREEN_W / 2,(SCREEN_H / 2)-60, makecol(0, 0, 255), -1, "%d Movimentos", recordeAux);
		textout_centre_ex(buffer, (FONT*) data[GAMEFONT].dat, "SEUS MOVIMENTOS:", SCREEN_W / 2, (SCREEN_H / 2)+20,makecol(0, 0, 255), -1);
		textprintf_centre_ex(buffer, (FONT*) data[GAMEFONT].dat, SCREEN_W / 2,(SCREEN_H / 2) + 50, makecol(0, 0, 255), -1, "%d", movimentos);
	}
	draw_sprite(screen, buffer, 0, 0);
	clear(buffer);

	while (!sair_programa && !sair_menu_vitoria) {
		while (ticks > 0 && !sair_programa && !sair_menu_vitoria) {

			button_input(Bvoltar);
			if(key[KEY_ESC])
				sair_menu_vitoria = TRUE;

			draw_sprite(buffer, (BITMAP*) data[FUNDO].dat, 0, 0);
			draw_sprite(buffer, (BITMAP*) data[LOGO].dat, 175, 50);

			button_draw(Bvoltar, buffer);
			if (recordeAux == 0 || recorde < recordeAux) {
				draw_sprite(buffer, (BITMAP*) data[MEDALHA].dat, 600, (SCREEN_H / 2) - 125);
				rotate_sprite(buffer, (BITMAP*) data[NOVORECORDE].dat, 40, 220, ftofix(-25.0));
				textout_centre_ex(buffer, (FONT*) data[GAMEFONT].dat, "MOVIMENTOS:", SCREEN_W / 2,SCREEN_H / 2, makecol(0, 0, 255), -1);
				textprintf_centre_ex(buffer, (FONT*) data[GAMEFONT].dat, SCREEN_W / 2,(SCREEN_H / 2) + 50, makecol(0, 0, 255), -1, "%d",movimentos);
			} else {
				draw_sprite(buffer, (BITMAP*) data[MEDALHA].dat, 600, (SCREEN_H / 2) - 125);
				draw_sprite(buffer, (BITMAP*) data[RECORDEATUAL].dat, (SCREEN_W / 2)-133, (SCREEN_H / 2)-100);
				textprintf_centre_ex(buffer, (FONT*) data[GAMEFONT].dat, SCREEN_W / 2,(SCREEN_H / 2)-60, makecol(0, 0, 255), -1, "%d", recordeAux);
				textout_centre_ex(buffer, (FONT*) data[GAMEFONT].dat, "SEUS MOVIMENTOS:", SCREEN_W / 2, (SCREEN_H / 2)+20,makecol(0, 0, 255), -1);
				textprintf_centre_ex(buffer, (FONT*) data[GAMEFONT].dat, SCREEN_W / 2,(SCREEN_H / 2) + 50, makecol(0, 0, 255), -1, "%d", movimentos);
			}
			if (mouse_x > 325 && mouse_x < 475 && mouse_y > 500 && mouse_y < 555) {
				if (mouse_b == 1) {
					mouse_b = 0;
					screen_state = MAINMENU;
					sair_menu_vitoria = TRUE;
				}
			}
			if (mouse_b == 1) {
				draw_sprite(buffer, (BITMAP*) data[CURSORATIVO].dat, mouse_x - 11, mouse_y);
			} else {
				draw_sprite(buffer, (BITMAP*) data[CURSOR].dat, mouse_x - 11, mouse_y);
			}
			draw_sprite(screen, buffer, 0, 0);
			clear(buffer);
			ticks--;
		}
	}
	destroy_bitmap(buffer);
	destroy_button(Bvoltar);
	if(!data){
		unload_datafile(data);
	}
	if(!som){
		unload_datafile(som);
	}


}

int tela_dificuldade(int op) {

	int sair_dificuldade = FALSE;
	BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
	DATAFILE * data = NULL;
	packfile_password("trabalhopp");
	data = load_datafile("data/data.dat");
	packfile_password(NULL);
	DATAFILE * som = NULL;
	packfile_password("trabalhopp");
	som = load_datafile("data/sons.dat");
	packfile_password(NULL);
	//BOTOES
	if(!data || !som){
		allegro_message("Erro ao carregar datafile");
		sair_programa = TRUE;
	}


	Button* facil = create_button((BITMAP*) data[FACIL].dat, (BITMAP*) data[FACILATIVO].dat, (SAMPLE*) som[CLICK].dat, 125, 300);
	Button* medio = create_button((BITMAP*) data[MEDIO].dat, (BITMAP*) data[MEDIOATIVO].dat, (SAMPLE*) som[CLICK].dat, 325, 300);
	Button* dificil = create_button((BITMAP*) data[DIFICIL].dat, (BITMAP*) data[DIFICILATIVO].dat, (SAMPLE*) som[CLICK].dat, 525, 300);
	Button* Bvoltar = create_button((BITMAP*) data[VOLTAR].dat, (BITMAP*) data[VOLTARATIVO].dat, (SAMPLE*) som[CLICK].dat, 600, 500);

	while (!sair_programa && !sair_dificuldade) {
		//INPUT
		while (ticks > 0 && !sair_programa && !sair_dificuldade) {

			button_input(facil);
			button_input(medio);
			button_input(dificil);
			button_input(Bvoltar);
			//UPDATE

			//DESENHO
			set_trans_blender(255, 255, 255, 190);

			draw_sprite(buffer, (BITMAP*) data[FUNDO].dat, 0, 0);
			draw_sprite(buffer, (BITMAP*) data[LOGO].dat, 175, 50);
			button_draw(Bvoltar, buffer);
			button_draw(facil, buffer);
			button_draw(medio, buffer);
			button_draw(dificil, buffer);

			if (mouse_x > 125 && mouse_x < 275 && mouse_y > 300
					&& mouse_y < 355) {
				if (mouse_b == 1) {
					mouse_b = 0;
					screen_state = TELAFACIL;
					sair_dificuldade = TRUE;

				}
			}
			if (mouse_x > 325 && mouse_x < 475 && mouse_y > 300
					&& mouse_y < 355) {
				if (mouse_b == 1) {
					mouse_b = 0;

				}
			}
			if (mouse_x > 525 && mouse_x < 675 && mouse_y > 300
					&& mouse_y < 355) {
				if (mouse_b == 1) {
					mouse_b = 0;

				}
			}
			if (mouse_x > 600 && mouse_x < 750 && mouse_y > 500
					&& mouse_y < 555) {
				if (mouse_b == 1) {
					mouse_b = 0;
					screen_state = IMAGENS;
					sair_dificuldade = TRUE;

				}
			}
			if (mouse_b == 1) {
				draw_sprite(buffer, (BITMAP*) data[CURSORATIVO].dat, mouse_x - 11, mouse_y);
			} else {
				draw_sprite(buffer, (BITMAP*) data[CURSOR].dat, mouse_x - 11, mouse_y);
			}
			draw_sprite(screen, buffer, 0, 0);
			clear(buffer);

			ticks--;
		}
	}
	destroy_bitmap(buffer);
	destroy_button(Bvoltar);
	destroy_button(facil);
	destroy_button(medio);
	destroy_button(dificil);
	if(!data){
		unload_datafile(data);
	}
	if(!som){
		unload_datafile(som);
	}
	return op;

}

int validar_vetor(int checar[], int aux) {
	int i;

	if (checar == NULL)
		return FALSE;

	for (i = 0; i < SHORT; i++) {
		if (checar[i] == aux)
			return TRUE;
	}
	return FALSE;
}

int valida_tabuleiro(int tabuleiro[][3], int TabCerto[][3]) {

	int i = 0;
	int j = 0;
	int aux = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (tabuleiro[i][j] == TabCerto[i][j])
				aux++;
		}
	}
	if (aux == 9)
		return 1;

	return 0;
}

