#include <allegro.h>
#include "setup.h"



void setup_screen()
{
	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0)!=0)
	{
		set_gfx_mode(GFX_TEXT,0,0,0,0);
		allegro_message(allegro_error);
		exit(1);
	}
	set_window_title("Quebra Cabeca");
}
END_OF_FUNCTION(setup_screen)


void setup(){
	 allegro_init();
	   install_timer();
	   install_mouse();
	   install_keyboard();
	   install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	   set_color_depth(32);
	   setup_screen();
}
END_OF_FUNCTION(setup)

