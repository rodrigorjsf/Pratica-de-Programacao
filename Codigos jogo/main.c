#include <allegro.h>
#include "setup.h"
#include "button.h"
#include "imagens.h"
#include "dificuldade.h"
#include "facil.h"


void mainmenu(){

	int sair_mainmenu = FALSE;

   BITMAP * buffer = create_bitmap(SCREEN_W, SCREEN_H);

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
   Button* jogar = create_button((BITMAP*) data[JOGAR].dat, (BITMAP*) data[JOGARATIVO].dat, (SAMPLE*) som[CLICK].dat, 200, 300);
   Button* sair = create_button((BITMAP*) data[SAIR].dat, (BITMAP*) data[SAIRATIVO].dat, (SAMPLE*) som[CLICK].dat, 450, 300);

   while(!sair_programa && !sair_mainmenu)
   {
	   while(ticks > 0 && !sair_programa && !sair_mainmenu){
	   if(key[KEY_ESC])
		   sair_mainmenu = TRUE;


	   button_input(jogar);
	   button_input(sair);

	   draw_sprite(buffer, (BITMAP*) data[FUNDO].dat, 0, 0);
	   draw_sprite(buffer, (BITMAP*) data[LOGO].dat, 175, 50);
	   button_draw(jogar, buffer);
	   button_draw(sair, buffer);

	   if (mouse_x > 200 && mouse_x < 350 && mouse_y > 300 && mouse_y < 355)
	   {
		   if(mouse_b == 1){
			   mouse_b = 0;
			   screen_state = IMAGENS;
			   sair_mainmenu = TRUE;
		   }
	   }

	   if (mouse_x > 450 && mouse_x < 600 && mouse_y > 300 && mouse_y < 355)
	   {
		   if(mouse_b == 1)
		   {
			   mouse_b = 0;
			   sair_mainmenu = TRUE;
			   sair_programa = TRUE;
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
   destroy_button(jogar);
   destroy_button(sair);
   if(!data){
	   unload_datafile(data);
   }
   if(!som){
   	   unload_datafile(som);
      }

}

int main()
{
	setup();
	int op;
	while(!sair_programa)
	{
		if(screen_state == MAINMENU)
			mainmenu();
		else if (screen_state == IMAGENS)
			op = segunda_tela();
		else if (screen_state == DIFICULDADES)
			op = tela_dificuldade(op);
		else if (screen_state == TELAFACIL)
			dificuldade_facil(op);
	}
	return 0;
}
END_OF_MAIN();


