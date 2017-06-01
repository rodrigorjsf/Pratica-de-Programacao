#include "imagens.h"

#include "setup.h"
#include "button.h"
#include "dificuldade.h"

int segunda_tela(){

	int sair_segunda_tela = FALSE;
	int op;

	BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
	DATAFILE * data = NULL;
	packfile_password("trabalhopp");
	data = load_datafile("data/data.dat");
	packfile_password(NULL);
	DATAFILE * som = NULL;
	packfile_password("trabalhopp");
	som = load_datafile("data/sons.dat");
	packfile_password(NULL);
	DATAFILE * mick = NULL;
	packfile_password("trabalhopp");
	mick = load_datafile("data/mickey.dat");
	packfile_password(NULL);
	DATAFILE * don = NULL;
	packfile_password("trabalhopp");
	don = load_datafile("data/donald.dat");
	packfile_password(NULL);

		if(!data || !som || !mick || !don){
			allegro_message("Erro ao carregar datafile");
			sair_programa = TRUE;
		}

	Button* Bvoltar = create_button((BITMAP*) data[VOLTAR].dat, (BITMAP*) data[VOLTARATIVO].dat, (SAMPLE*) som[CLICK].dat, 600, 500);

	while(!sair_programa && !sair_segunda_tela)
	{
		while(ticks > 0 && !sair_programa && !sair_segunda_tela){
		if(key[KEY_ESC]){
			screen_state = MAINMENU;
			sair_segunda_tela = TRUE;
		}

		button_input(Bvoltar);

		set_trans_blender(255, 255, 255, 190);

		draw_sprite(buffer, (BITMAP*) data[FUNDO].dat, 0, 0);
		draw_sprite(buffer, (BITMAP*) data[LOGO].dat, 175, 50);
		draw_sprite(buffer, (BITMAP*) data[ESCOLHA].dat, 200, 180);
		draw_sprite_ex(buffer, (BITMAP*) mick[MICKEY].dat, 110, 250,DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
		draw_sprite_ex(buffer, (BITMAP*) don[DONALD].dat, 510, 250,DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
		button_draw(Bvoltar, buffer);

		if (mouse_x > 110 && mouse_x < 290 && mouse_y > 250 && mouse_y < 430)
		{
			draw_sprite(buffer, (BITMAP*) mick[MICKEY].dat, 110, 250);
			if(mouse_b == 1){
				mouse_b = 0;
				op = 0;
				screen_state = DIFICULDADES;
				sair_segunda_tela = TRUE;
			}
		}

		if (mouse_x > 510 && mouse_x < 690 && mouse_y > 250 && mouse_y < 442)
		{
			draw_sprite(buffer, (BITMAP*) don[DONALD].dat, 510, 250);
			if(mouse_b == 1){
				mouse_b = 0;
				op = 1;
				screen_state = DIFICULDADES;
				sair_segunda_tela = TRUE;
			}
		}
		if (mouse_x > 600 && mouse_x < 750 && mouse_y > 500 && mouse_y < 555)
		{
			if(mouse_b == 1){
				mouse_b = 0;
				screen_state = MAINMENU;
				sair_segunda_tela = TRUE;
			}
		}
		if(mouse_b == 1)
		{
			draw_sprite(buffer, (BITMAP*) data[CURSORATIVO].dat, mouse_x-11, mouse_y);
		}
		else
		{
			draw_sprite(buffer, (BITMAP*) data[CURSOR].dat, mouse_x-11, mouse_y);
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
	if(!mick)
	{
		unload_datafile(mick);
	}
	if(!don)
	{
		unload_datafile(don);
	}

	return op;
}


