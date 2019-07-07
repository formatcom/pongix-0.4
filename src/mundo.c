/* Pongix - clone of the "Pong" video game with net support
 * Copyright (C) 2005 - Hugo Ruscitti (see AUTHORS file)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include "mundo.h"
#include "control.h"
#include "juego.h"
#include "menu.h"

Mundo * mundo_iniciar (void)
{
	Mundo * data;

	data = (Mundo *) malloc (sizeof (Mundo));

	if (data == NULL)
	{
		printf ("error, no se puede crear la estructura Mundo\n");
		return NULL;
	}

	data->screen = iniciar_sdl ();

	if (data->screen == NULL)
		return NULL;

	data->fondo = cargar_imagen ("fondo_juego.jpg");

	if (data->fondo == NULL)
		return NULL;

	if (mundo_cargar_modulos (data))
		return NULL;

	SDL_BlitSurface (data->fondo, NULL, data->screen, NULL);
	dirty_agregar_pantalla_completa (data->dirty);
	mundo_cambiar_estado(data, MENU);

	data->salir = 0;

	return data;
}

int mundo_cargar_modulos (Mundo * data)
{

	control_iniciar();

	if ((data->creditos = creditos_iniciar (data)) == NULL)
		return 1;

	if ((data->menu = menu_iniciar (data)) == NULL)
		return 1;

	if ((data->juego = juego_iniciar (data)) == NULL)
		return 1;

	if ((data->dirty = dirty_iniciar ()) == NULL)
		return 1;

	if ((data->fuente = fuente_iniciar ("fuente.bmp", data)) == NULL)
		return 1;

#ifdef __linux__
	if ((data->cliente = cliente_iniciar (data)) == NULL)
		return 1;

	if ((data->servidor = servidor_iniciar (data)) == NULL)
		return 1;
#endif

	return 0;
}

void mundo_actualizar (Mundo * data)
{

#ifdef __linux__
	static Uint8 * teclas;
	teclas = SDL_GetKeyState (NULL);
#endif

	int move = 0;

	if (control_boton_pulsado(CONTROL_BUTTON_JOY0_UP)) {
		data->juego->paleta1->move = -1;
		move = data->juego->paleta1->move;
	}
	if (control_boton_pulsado(CONTROL_BUTTON_JOY0_DOWN)) {
		data->juego->paleta1->move = 1;
		move = data->juego->paleta1->move;
	}
	if (control_boton_pulsado(CONTROL_BUTTON_JOY1_UP)) {
		data->juego->paleta2->move = -1;
	}
	if (control_boton_pulsado(CONTROL_BUTTON_JOY1_DOWN)) {
		data->juego->paleta2->move = 1;
	}

	switch (data->estado)
	{
		case MENU:
			menu_actualizar (data->menu,
								move,
								control_boton_pulsado(CONTROL_BUTTON_JOY0_ENTER));
			break;

		case JUEGO:
		case JUEGORED_CLIENTE:
		case JUEGORED_SERVIDOR:
#ifdef _EE
			// desde el ps2 no se puede salir del juego ya que el boton es LEFT y
			// se podria presionar muy facilmente por error.
			juego_actualizar (data->juego, 0);
#else
			juego_actualizar (data->juego,
					control_boton_pulsado(CONTROL_BUTTON_JOY0_ESCAPE));
#endif
			break;

		case CREDITOS:
			creditos_actualizar (data->creditos,
					control_boton_pulsado(CONTROL_BUTTON_JOY0_ESCAPE));
			break;

#ifdef __linux__
		case SERVIDOR:
			servidor_actualizar (data->servidor, teclas);
			break;

		case CLIENTE:
			cliente_actualizar (data->cliente, teclas);
			break;
#endif
		default:
			printf ("en Mundo: el estado '%d' es incorrecto\n", \
					data->estado);
			break;
	}
}

void mundo_imprimir (Mundo * data)
{
	switch (data->estado)
	{
		case MENU:
			menu_imprimir (data->menu);
			break;

		case JUEGO:
		case JUEGORED_CLIENTE:
		case JUEGORED_SERVIDOR:
			juego_imprimir (data->juego);
			break;

		case CREDITOS:
			creditos_imprimir (data->creditos);
			break;

#ifdef __linux__
		case SERVIDOR:
			servidor_imprimir (data->servidor);
			break;

		case CLIENTE:
			cliente_imprimir (data->cliente);
			break;
#endif

		default:
			printf ("en Mundo: el estado '%d' es incorrecto\n", \
					data->estado);
			break;
	}

	dirty_actualizar (data->dirty, data->screen, data->fondo);
}

void mundo_cambiar_estado (Mundo * data, enum estados nuevo_estado)
{
	data->estado = nuevo_estado;

	switch (nuevo_estado)
	{
		case MENU:
			menu_reiniciar (data->menu);
			break;

		case JUEGORED_SERVIDOR:
			juego_reiniciar (data->juego, JUEGO_SERVIDOR);
			break;

		case JUEGORED_CLIENTE:
			juego_reiniciar (data->juego, JUEGO_CLIENTE);
			break;

		case JUEGO:
			juego_reiniciar (data->juego, NORED);
			break;

		case CREDITOS:
			break;

#ifdef __linux__
		case SERVIDOR:
			servidor_reiniciar (data->servidor);
			break;

		case CLIENTE:
			cliente_reiniciar (data->cliente);
			break;
#endif

		default:
			printf ("Escena inexistente, no se puede reiniciar\n");
			break;
	}
}

void mundo_pantalla_completa (Mundo * data)
{

#ifndef WIN32
	SDL_WM_ToggleFullScreen (data->screen);
#else
	int flags = data->screen->flags;
	int w = data->screen->w;
	int h = data->screen->h;
	int bpp = data->screen->format->BitsPerPixel;
	SDL_Surface * nueva;

	flags ^= SDL_FULLSCREEN;

	nueva = SDL_SetVideoMode (w, h, bpp, flags);

	if (nueva)
	{
		SDL_FreeSurface (data->screen);
		data->screen = nueva;

		dirty_agregar_pantalla_completa (data->dirty);
	}
	else
		printf ("No se puede cambiar el modo de video\n");

#endif

}

void mundo_terminar (Mundo * data)
{
	menu_terminar (data->menu);
	juego_terminar (data->juego);
	dirty_terminar (data->dirty);
	fuente_terminar (data->fuente);
#ifdef __linux__
	servidor_terminar (data->servidor);
	cliente_terminar (data->cliente);
#endif
	SDL_FreeSurface (data->fondo);

	free (data);

	control_terminar();
#ifdef __linux__
	SDLNet_Quit ();
#endif

#ifdef _EE
	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
#endif
	SDL_Quit ();

	printf ("¡ Gracias por jugar a %s !\n", PACKAGE_STRING);
}


void mundo_salir (Mundo * data)
{
	data->salir = 1;
}
