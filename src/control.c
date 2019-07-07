#include "config.h"
#include "control.h"

#ifdef _EE
SDL_Joystick *_joy0 = NULL;
SDL_Joystick *_joy1 = NULL;

Uint8 _joy0_lastkey;
Uint8 _joy1_lastkey;
#endif


void control_iniciar()
{

#ifdef _EE
	_joy0 = SDL_JoystickOpen(0);
	_joy1 = SDL_JoystickOpen(1);
#endif

}

// Como el codigo esta en espa;ol y en ingles, no supe que regla de dise;o seguir
// intento ser lo mas parecido a la estructura del codigo original posible.
int control_boton_pulsado(Uint8 key)
{
	return ((CONTROL_BUTTON_STATE & key) == key);
}

#ifdef _EE
void control_map(Uint8 joy, Uint8 button)
{
	if (joy == 0) {
		switch(button) {
			case SDL_HAT_CENTERED:
				control_actualizar(0, _joy0_lastkey);
				break;
			case SDL_HAT_UP:
				control_actualizar(1, JOY0_UP);
				_joy0_lastkey = JOY0_UP;
				break;
			case SDL_HAT_RIGHT:
				control_actualizar(1, JOY0_ENTER);
				_joy0_lastkey = JOY0_ENTER;
				break;
			case SDL_HAT_DOWN:
				control_actualizar(1, JOY0_DOWN);
				_joy0_lastkey = JOY0_DOWN;
				break;
			case SDL_HAT_LEFT:
				control_actualizar(1, JOY0_ESCAPE);
				_joy0_lastkey = JOY0_ESCAPE;
				break;
		}
	}else{
		switch(button) {
			case SDL_HAT_CENTERED:
				control_actualizar(0, _joy1_lastkey);
				break;
			case SDL_HAT_UP:
				control_actualizar(1, JOY1_UP);
				_joy1_lastkey = JOY1_UP;
				break;
			case SDL_HAT_DOWN:
				control_actualizar(1, JOY1_DOWN);
				_joy1_lastkey = JOY1_DOWN;
				break;
			}
	}
}
#endif

void control_actualizar(int is_down, Uint8 key)
{
	if (is_down) {

		if (key == JOY0_ENTER){
			CONTROL_BUTTON_STATE |= CONTROL_BUTTON_JOY0_ENTER;
		}
		if (key == JOY0_ESCAPE){
			CONTROL_BUTTON_STATE |= CONTROL_BUTTON_JOY0_ESCAPE;
		}
		if (key == JOY0_UP) {
			CONTROL_BUTTON_STATE |= CONTROL_BUTTON_JOY0_UP;
		}
		if (key == JOY0_DOWN) {
			CONTROL_BUTTON_STATE |= CONTROL_BUTTON_JOY0_DOWN;
		}
		if (key == JOY1_UP) {
			CONTROL_BUTTON_STATE |= CONTROL_BUTTON_JOY1_UP;
		}
		if (key == JOY1_DOWN) {
			CONTROL_BUTTON_STATE |= CONTROL_BUTTON_JOY1_DOWN;
		}
	}else{
		if (key == JOY0_ENTER){
			CONTROL_BUTTON_STATE ^= CONTROL_BUTTON_JOY0_ENTER;
		}
		if (key == JOY0_ESCAPE){
			CONTROL_BUTTON_STATE ^= CONTROL_BUTTON_JOY0_ESCAPE;
		}
		if (key == JOY0_UP) {
			CONTROL_BUTTON_STATE ^= CONTROL_BUTTON_JOY0_UP;
		}
		if (key == JOY0_DOWN) {
			CONTROL_BUTTON_STATE ^= CONTROL_BUTTON_JOY0_DOWN;
		}
		if (key == JOY1_UP) {
			CONTROL_BUTTON_STATE ^= CONTROL_BUTTON_JOY1_UP;
		}
		if (key == JOY1_DOWN) {
			CONTROL_BUTTON_STATE ^= CONTROL_BUTTON_JOY1_DOWN;
		}
	}
}

void control_terminar()
{

#ifdef _EE
	SDL_JoystickClose(_joy0);
	SDL_JoystickClose(_joy1);
#endif

}
