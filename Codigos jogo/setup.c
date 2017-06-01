#include <allegro.h>
#include "setup.h"


void fecha_programa(){sair_programa = TRUE;}
END_OF_FUNCTION(fecha_programa)

void tick_counter()
{
	ticks++;
}
END_OF_FUNCTION(tick_counter)

void setup(){
	 allegro_init();
	   install_timer();
	   install_mouse();
	   install_keyboard();
	   install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	   set_color_depth(32);
	   if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0)!=0)
	   {
		   set_gfx_mode(GFX_TEXT,0,0,0,0);
		   allegro_message(allegro_error);
		   exit(1);
	   }
	   set_window_title("Quebra Cabeca");

	   sair_programa = FALSE;
	   LOCK_VARIABLE(sair_programa);
	   LOCK_FUNCTION(fecha_programa);
	   set_close_button_callback(fecha_programa);


	   ticks = 0;
	   LOCK_VARIABLE(ticks);
	   LOCK_FUNCTION(tick_counter);
	   install_int_ex(tick_counter, BPS_TO_TIMER(60));

	   screen_state = MAINMENU;
}
END_OF_FUNCTION(setup)

