#include <allegro.h>
#include "setup.h"
#include "button.h"
#include "segunda.h"

volatile int sair_programa;

void fecha_programa()
{
	sair_programa = TRUE;
}
END_OF_FUNCTION(fecha_programa)



int main()
{
	setup();

   sair_programa = FALSE;
   LOCK_VARIABLE(sair_programa);
   LOCK_FUNCTION(fecha_programa);
   set_close_button_callback(fecha_programa);


   ///SONS
     SAMPLE* click = load_sample("sons/Click.wav");

   //BITMAPS

   BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);
   BITMAP * cursor = load_bitmap("Cursor/cursorp.bmp", NULL);
   BITMAP * cursorPress = load_bitmap("Cursor/botaop2.bmp", NULL);
   BITMAP * fundo = load_bitmap("Imagens/fundo.bmp", NULL);
   BITMAP * logo = load_bitmap("Imagens/RACHACUCA.bmp", NULL);
   BITMAP * BotaoJogar = load_bitmap("Imagens/BotaoJogar.bmp", NULL);
   BITMAP * BotaoJogarAtivo = load_bitmap("Imagens/BotaoJogarAtivo.bmp", NULL);
   BITMAP * BotaoSair = load_bitmap("Imagens/BotaoSair.bmp", NULL);
   BITMAP * BotaoSairAtivo = load_bitmap("Imagens/BotaoSairAtivo.bmp", NULL);

   //BOTOES

   Button* jogar = create_button(BotaoJogar, BotaoJogarAtivo, click, 200, 300);
   Button* sair = create_button(BotaoSair, BotaoSairAtivo, click, 450, 300);


   if(!cursor)
   {
 	    allegro_message("Error loading cursor.bmp");
     return 1;
    }

   //LOOP
   while(!sair_programa)
   {
	   //INPUT
	   if(key[KEY_ESC])
			   sair_programa = TRUE;


	   button_input(jogar);
	   button_input(sair);
	   //UPDATE


	   //DESENHO
	   draw_sprite(buffer, fundo, 0, 0);
	   draw_sprite(buffer, logo, 175, 50);
	   button_draw(jogar, buffer);
	   button_draw(sair, buffer);

	   if (mouse_x > 200 && mouse_x < 350 && mouse_y > 300 && mouse_y < 355)
	   {
		   if(mouse_b == 1){
			   if(segunda_tela() == 1)
				   sair_programa = TRUE;
			   else
				   key[KEY_ESC] = FALSE;
		   }
	   }

	   if (mouse_x > 450 && mouse_x < 600 && mouse_y > 300 && mouse_y < 355)
	   {
		   if(mouse_b == 1)
		   {
			   textout_ex(buffer, font, "TESTE", 100, 100, makecol(0, 0, 255), -1);
			   sair_programa = TRUE;
		   }
	   }
	   if(mouse_b == 1)
	   {
		   draw_sprite(buffer, cursorPress, mouse_x-11, mouse_y);
	   }
	   else
	   {
		   draw_sprite(buffer, cursor, mouse_x-11, mouse_y);
	   }
	   draw_sprite(screen, buffer, 0, 0);
	   clear(buffer);


   }

   //FINALIZACOES
   destroy_bitmap(cursor);
   destroy_bitmap(cursorPress);
   destroy_bitmap(logo);
   destroy_bitmap(BotaoJogar);
   destroy_bitmap(BotaoJogarAtivo);
   destroy_bitmap(BotaoSairAtivo);
   destroy_bitmap(BotaoSair);
   destroy_bitmap(buffer);
   destroy_bitmap(fundo);
   destroy_sample(click);
   destroy_button(jogar);
   destroy_button(sair);


   return 0;
}
END_OF_MAIN()
