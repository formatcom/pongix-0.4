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

	if ((data->cliente = cliente_iniciar (data)) == NULL)
		return 1;
	
	if ((data->servidor = servidor_iniciar (data)) == NULL)
		return 1;

	return 0;
}

void mundo_actualizar (Mundo * data)
{
	static Uint8 * teclas;

	teclas = SDL_GetKeyState (NULL);

	switch (data->estado)
	{
		case MENU:
			menu_actualizar (data->menu, teclas);
			break;

		case JUEGO:
		case JUEGORED_CLIENTE:
		case JUEGORED_SERVIDOR:
			juego_actualizar (data->juego, teclas);
			break;
			
		case CREDITOS:
			creditos_actualizar (data->creditos, teclas);
			break;

		case SERVIDOR:
			servidor_actualizar (data->servidor, teclas);
			break;

		case CLIENTE:
			cliente_actualizar (data->cliente, teclas);
			break;
			
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

		case SERVIDOR:
			servidor_imprimir (data->servidor);
			break;

		case CLIENTE:
			cliente_imprimir (data->cliente);
			break;

			
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

		case SERVIDOR:
			servidor_reiniciar (data->servidor);
			break;

		case CLIENTE:
			cliente_reiniciar (data->cliente);
			break;
			
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
	servidor_terminar (data->servidor);
	cliente_terminar (data->cliente);
	SDL_FreeSurface (data->fondo);

	free (data);
	SDLNet_Quit ();
	SDL_Quit ();
	
	printf ("¡ Gracias por jugar a %s !\n", PACKAGE_STRING);
}


void mundo_salir (Mundo * data)
{
	data->salir = 1;
}
