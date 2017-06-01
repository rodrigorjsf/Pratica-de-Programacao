
#ifndef BUTTON_H_
#define BUTTON_H_

#include <allegro.h>
#include <stdlib.h>

typedef struct button
{
  BITMAP* img;
  BITMAP* h_img;
  SAMPLE* h_click;
  int pos_x;
  int pos_y;
  int highlightON;
  int bip;
}Button;


Button* create_button(BITMAP* image, BITMAP* h_image, SAMPLE* h_effect, int x, int y);
void button_input(Button* b);
void button_draw(Button* b, BITMAP* buffer);
void destroy_button(Button* b);


#endif /* BUTTON_H_ */
