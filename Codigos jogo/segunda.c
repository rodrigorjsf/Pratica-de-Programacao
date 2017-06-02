#include "segunda.h"
#include "setup.h"
#include "button.h"
#include "dificuldade.h"

volatile int sair_segunda_tela;

void fecha_tudo()
{
	sair_segunda_tela = TRUE;
}
END_OF_FUNCTION(fecha_tudo)


int segunda_tela(){

	sair_segunda_tela = FALSE;
	LOCK_VARIABLE(sair_segunda_tela);
	LOCK_FUNCTION(fecha_tudo);
	set_close_button_callback(fecha_tudo);

	int r = 1;
	int op;
	SAMPLE* clickAux = load_sample("sons/Click.wav");
	BITMAP * bufferAux = create_bitmap(SCREEN_W, SCREEN_H);
	BITMAP * cursorAux = load_bitmap("Cursor/cursorp.bmp", NULL);
	BITMAP * cursorPressAux = load_bitmap("Cursor/botaop2.bmp", NULL);
	BITMAP * fundoAux = load_bitmap("Imagens/fundo.bmp", NULL);
	BITMAP * logoAux = load_bitmap("Imagens/RACHACUCA.bmp", NULL);
	BITMAP * mickey = load_bitmap("Mickey/mickey.bmp", NULL);
	BITMAP * donald = load_bitmap("Donald/donald.bmp", NULL);
	BITMAP * voltar = load_bitmap("Imagens/voltar.bmp", NULL);
	BITMAP * voltarPress = load_bitmap("Imagens/voltarAtivo.bmp", NULL);
	BITMAP * escolha = load_bitmap("Imagens/escolha.bmp", NULL);

	Button* Bvoltar = create_button(voltar, voltarPress, clickAux, 600, 500);

	while(!sair_segunda_tela)
	{
		//INPUT
		if(key[KEY_ESC]){
			sair_segunda_tela = TRUE;
			r = 0;
		}

		button_input(Bvoltar);
		//UPDATE

		//DESENHO
		set_trans_blender(255, 255, 255, 190);

		draw_sprite(bufferAux, fundoAux, 0, 0);
		draw_sprite(bufferAux, logoAux, 175, 50);
		draw_sprite(bufferAux, escolha, 200, 180);
		draw_sprite_ex(bufferAux, mickey, 110, 250,DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
		draw_sprite_ex(bufferAux, donald, 510, 250,DRAW_SPRITE_TRANS, DRAW_SPRITE_NO_FLIP);
		button_draw(Bvoltar, bufferAux);

		if (mouse_x > 110 && mouse_x < 290 && mouse_y > 250 && mouse_y < 430)
		{
			draw_sprite(bufferAux, mickey, 110, 250);
			if(mouse_b == 1){
				mouse_b = 0;				
				op = 0;
				if(tela_dificuldade(op) == 1)
					sair_segunda_tela = TRUE;
			}
		}

		if (mouse_x > 510 && mouse_x < 690 && mouse_y > 250 && mouse_y < 442)
		{
			draw_sprite(bufferAux, donald, 510, 250);
			if(mouse_b == 1){
				mouse_b = 0;				
				op = 1;
				if(tela_dificuldade(op) == 1)
					sair_segunda_tela = TRUE;
			}
		}
		if (mouse_x > 600 && mouse_x < 750 && mouse_y > 500 && mouse_y < 555)
		{
			if(mouse_b == 1){

				mouse_b = 0;
				sair_segunda_tela = TRUE;
				r = 0;
			}
		}
		if(mouse_b == 1)
		{
			draw_sprite(bufferAux, cursorPressAux, mouse_x-11, mouse_y);
		}
		else
		{
			draw_sprite(bufferAux, cursorAux, mouse_x-11, mouse_y);
		}
		draw_sprite(screen, bufferAux, 0, 0);
		clear(bufferAux);
	}

	//FINALIZACOES
	destroy_bitmap(cursorAux);
	destroy_bitmap(cursorPressAux);
	destroy_bitmap(logoAux);
	destroy_bitmap(mickey);
	destroy_bitmap(donald);
	destroy_bitmap(bufferAux);
	destroy_bitmap(fundoAux);
	destroy_bitmap(escolha);
	destroy_bitmap(voltar);
	destroy_bitmap(voltarPress);
	destroy_sample(clickAux);
	destroy_button(Bvoltar);

	return r;
}


