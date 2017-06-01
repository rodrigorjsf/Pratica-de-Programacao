
#ifndef SETUP_H_
#define SETUP_H_
#include <allegro.h>
#include "soundfile.h"
#include "datafile.h"
#include "mickeydata.h"
#include "donalddata.h"

volatile int sair_programa;
volatile int ticks;

enum {MAINMENU, IMAGENS, DIFICULDADES, TELAFACIL};
int screen_state;

void fecha_programa();
void tick_counter();
void setup();

#endif /* SETUP_H_ */
