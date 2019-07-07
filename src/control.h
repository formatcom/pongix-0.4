#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <SDL/SDL.h>

#define CONTROL_BUTTON_JOY0_ENTER  1 // 000001
#define CONTROL_BUTTON_JOY0_ESCAPE 2 // 000010
#define CONTROL_BUTTON_JOY0_UP     4 // 000100
#define CONTROL_BUTTON_JOY0_DOWN   8 // 001000
#define CONTROL_BUTTON_JOY1_UP    16 // 010000
#define CONTROL_BUTTON_JOY1_DOWN  32 // 100000

Uint8 CONTROL_BUTTON_STATE;

void control_iniciar();
void control_terminar();
int control_boton_pulsado(Uint8 key);
void control_actualizar(int is_down, Uint8 key);

#ifdef _EE
void control_map(Uint8 joy, Uint8 button);
#endif

#endif
