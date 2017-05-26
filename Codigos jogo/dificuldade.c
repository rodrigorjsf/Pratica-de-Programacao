#include "setup.h"
#include "button.h"
#include "dificuldade.h"
#define SHORT 8
#define MEDIUM 15
#define LONG 24

volatile int sair_dificuldade;

void fecha_dificuldade()
{
	sair_dificuldade = TRUE;
}
END_OF_FUNCTION(fecha_dificuldade)

int tela_dificuldade(int op){


	sair_dificuldade = FALSE;
	LOCK_VARIABLE(sair_dificuldade);
	LOCK_FUNCTION(fecha_dificuldade);
	set_close_button_callback(fecha_dificuldade);

	int r = 1;

	SAMPLE* clickAux = load_sample("sons/Click.wav");

	BITMAP * bufferAux = create_bitmap(SCREEN_W, SCREEN_H);
	BITMAP * cursorAux = load_bitmap("Cursor/cursorp.bmp", NULL);
	BITMAP * cursorPressAux = load_bitmap("Cursor/botaop2.bmp", NULL);
	BITMAP * fundoAux = load_bitmap("Imagens/fundo.bmp", NULL);
	BITMAP * logoAux = load_bitmap("Imagens/RACHACUCA.bmp", NULL);
	BITMAP * voltar = load_bitmap("Imagens/voltar.bmp", NULL);
	BITMAP * voltarPress = load_bitmap("Imagens/voltarAtivo.bmp", NULL);
	BITMAP * bfacil = load_bitmap("Imagens/BotaoFacil.bmp", NULL);
	BITMAP * bfacilHL = load_bitmap("Imagens/BotaoFacilHL.bmp", NULL);
	BITMAP * bmedio = load_bitmap("Imagens/BotaoMedio.bmp", NULL);
	BITMAP * bmedioHL = load_bitmap("Imagens/BotaoMedioHL.bmp", NULL);
	BITMAP * bdificil = load_bitmap("Imagens/BotaoDificil.bmp", NULL);
	BITMAP * bdificilHL = load_bitmap("Imagens/BotaoDificilHL.bmp", NULL);

	Button* facil = create_button(bfacil, bfacilHL, clickAux, 125, 300);
	Button* medio = create_button(bmedio, bmedioHL, clickAux, 325, 300);
	Button* dificil = create_button(bdificil, bdificilHL, clickAux, 525, 300);
	Button* Bvoltar = create_button(voltar, voltarPress, clickAux, 600, 500);

	while(!sair_dificuldade){
		//INPUT

		button_input(facil);
		button_input(medio);
		button_input(dificil);
		button_input(Bvoltar);
		//UPDATE

		//DESENHO
		set_trans_blender(255, 255, 255, 190);

		draw_sprite(bufferAux, fundoAux, 0, 0);
		draw_sprite(bufferAux, logoAux, 175, 50);
		button_draw(Bvoltar, bufferAux);
		button_draw(facil, bufferAux);
		button_draw(medio, bufferAux);
		button_draw(dificil, bufferAux);

		if (mouse_x > 125 && mouse_x < 275 && mouse_y > 300 && mouse_y < 355)
		{
			if(mouse_b == 1){
				mouse_b = 0;
				textout_ex(bufferAux, font, "TESTE", 100, 100, makecol(0, 0, 255), -1);
				dificuldade_facil(op);

			}
		}
		if (mouse_x > 325 && mouse_x < 475 && mouse_y > 300 && mouse_y < 355)
		{
			if(mouse_b == 1){
				mouse_b = 0;
				textout_ex(bufferAux, font, "TESTE", 100, 100, makecol(0, 0, 255), -1);
			}
		}
		if (mouse_x > 525 && mouse_x < 675 && mouse_y > 300 && mouse_y < 355)
		{
			if(mouse_b == 1){
				mouse_b = 0;

			}
		}
		if (mouse_x > 600 && mouse_x < 750 && mouse_y > 500 && mouse_y < 555)
		{
			if(mouse_b == 1){
				mouse_b = 0;
				sair_dificuldade = TRUE;
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
	destroy_bitmap(bfacil);
	destroy_bitmap(bfacilHL);
	destroy_bitmap(bmedio);
	destroy_bitmap(bmedioHL);
	destroy_bitmap(bdificil);
	destroy_bitmap(bdificilHL);
	destroy_bitmap(bufferAux);
	destroy_bitmap(fundoAux);
	destroy_bitmap(voltar);
	destroy_bitmap(voltarPress);
	destroy_sample(clickAux);
	destroy_button(Bvoltar);
	destroy_button(facil);
	destroy_button(medio);
	destroy_button(dificil);

	return r;

}

void dificuldade_facil(int op){

    int tabuleiro[3][3];
    int checar[SHORT];
    int i, j, k, aux;
    Tile * tab[3][3];

    k = 0;
    for ( i=0; i<3; i++ )
      for (j=0; j<3; j++ )
      {
         tabuleiro[i][j] = rand()%SHORT;
         aux = tabuleiro[i][j];
         do{
        	 if (validar_vetor(checar, aux) == TRUE){
        		 tabuleiro[i][j] = rand()%SHORT;
        		 aux = tabuleiro[i][j];
        	 }
         }while (validar_vetor(checar, aux) == TRUE);
         checar[k] = tabuleiro[i][j];
         k++;
      }

	BITMAP * bufferAux = create_bitmap(SCREEN_W, SCREEN_H);
	BITMAP * cursorAux = load_bitmap("Cursor/cursorp.bmp", NULL);
	BITMAP * cursorPressAux = load_bitmap("Cursor/botaop2.bmp", NULL);
	BITMAP * fundoAux = load_bitmap("Imagens/fundo.bmp", NULL);
	BITMAP * logoAux = load_bitmap("Imagens/RACHACUCA.bmp", NULL);

	if(op == 0){


		BITMAP * voltarPress = load_bitmap("Imagens/voltarAtivo.bmp", NULL);
		BITMAP * bfacil = load_bitmap("Imagens/BotaoFacil.bmp", NULL);
		BITMAP * bfacilHL = load_bitmap("Imagens/BotaoFacilHL.bmp", NULL);
		BITMAP * bmedio = load_bitmap("Imagens/BotaoMedio.bmp", NULL);
		BITMAP * bmedioHL = load_bitmap("Imagens/BotaoMedioHL.bmp", NULL);
		BITMAP * bdificil = load_bitmap("Imagens/BotaoDificil.bmp", NULL);
		BITMAP * bdificilHL = load_bitmap("Imagens/BotaoDificilHL.bmp", NULL);
	}
	else{
		BITMAP * um = load_bitmap("Donald/3x3/1.bmp", NULL);
		BITMAP * dois = load_bitmap("Donald/3x3/2.bmp", NULL);
		BITMAP * tres = load_bitmap("Donald/3x3/3.bmp", NULL);
		BITMAP * quatro = load_bitmap("Donald/3x3/4.bmp", NULL);
		BITMAP * cinco = load_bitmap("Donald/3x3/5.bmp", NULL);
		BITMAP * seis = load_bitmap("Donald/3x3/6.bmp", NULL);
		BITMAP * sete = load_bitmap("Donald/3x3/7.bmp", NULL);
		BITMAP * oito = load_bitmap("Donald/3x3/8.bmp", NULL);
		BITMAP * voltar = load_bitmap("Imagens/voltar.bmp", NULL);
		BITMAP * voltarPress = load_bitmap("Imagens/voltarAtivo.bmp", NULL);
		BITMAP * bfacil = load_bitmap("Imagens/BotaoFacil.bmp", NULL);
		BITMAP * bfacilHL = load_bitmap("Imagens/BotaoFacilHL.bmp", NULL);
		BITMAP * bmedio = load_bitmap("Imagens/BotaoMedio.bmp", NULL);
		BITMAP * bmedioHL = load_bitmap("Imagens/BotaoMedioHL.bmp", NULL);
		BITMAP * bdificil = load_bitmap("Imagens/BotaoDificil.bmp", NULL);
		BITMAP * bdificilHL = load_bitmap("Imagens/BotaoDificilHL.bmp", NULL);
	}

}

void dificuldade_medio(int op){


}

void dificuldade_dificil(int op){


}

int validar_vetor(int checar[], int aux){
	int i;

	for ( i=0; i<SHORT; i++ ){
		if(checar[i] == aux)
			return TRUE;
	}
	return FALSE;
}
