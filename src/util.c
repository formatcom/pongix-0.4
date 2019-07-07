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

#include <SDL/SDL.h>
#include <string.h>
#include "util.h"
#include "config.h"
#include "control.h"

#ifdef __linux__
#include <SDL/SDL_net.h>
#endif

SDL_Surface * iniciar_sdl (void)
{
	SDL_Surface * screen;

#ifdef _EE
	if ((SDL_Init (SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_JOYSTICK)) < 0)
#else
	if ((SDL_Init (SDL_INIT_VIDEO|SDL_INIT_TIMER)) < 0)
#endif
	{
		printf ("Error: %s\n", SDL_GetError ());
		return NULL;
	}

	if ((screen = SDL_SetVideoMode (640, 480, 16, SDL_SWSURFACE|SDL_DOUBLEBUF)) == NULL)
	{
		printf ("Error: %s\n", SDL_GetError ());
		return NULL;
	}

#ifdef __linux__
	if (SDLNet_Init() < 0)
	{
		printf ("Error en SDLNet_Init: %s\n", SDL_GetError());
		return NULL;
	}
#endif

	SDL_WM_SetCaption ("Pongix (" PACKAGE_STRING ")", NULL);

	SDL_ShowCursor (SDL_DISABLE);

	return screen;
}

int procesar_eventos (void)
{
	SDL_Event evento;

	while (SDL_PollEvent (& evento))
	{
		switch (evento.type)
		{
			case SDL_QUIT :
				return 1;
				break;
#ifndef _EE
			case SDL_KEYDOWN:
				control_actualizar(1, evento.key.keysym.sym);
				break;
			case SDL_KEYUP:
				control_actualizar(0, evento.key.keysym.sym);
				break;
#else
			case SDL_JOYHATMOTION:
				control_map(evento.jhat.which, evento.jhat.value);
				break;
#endif
			default:
				break;
		}
	}

	return 0;
}

#ifdef _EE
// fondo_juego.jpg  fuente.bmp  paleta.bmp  pelota.bmp
extern unsigned char fondo_juego_jpg[];
extern int           size_fondo_juego_jpg;
extern unsigned char fuente_bmp[];
extern int           size_fuente_bmp;
extern unsigned char paleta_bmp[];
extern int           size_paleta_bmp;
extern unsigned char pelota_bmp[];
extern int           size_pelota_bmp;
#endif

SDL_Surface * cargar_imagen (const char * ruta)
{
	SDL_Surface * tmp;
	SDL_Surface * ima;


#ifdef _EE
	void *_image = NULL;
	int _size = 0;
	if (strcmp(ruta, "fondo_juego.jpg") == 0) {
		_image = fondo_juego_jpg;
		_size = size_fondo_juego_jpg;
	}else if(strcmp(ruta, "fuente.bmp") == 0) {
		_image = fuente_bmp;
		_size = size_fuente_bmp;
	}else if(strcmp(ruta, "paleta.bmp") == 0) {
		_image = paleta_bmp;
		_size = size_paleta_bmp;
	}else if(strcmp(ruta, "pelota.bmp") == 0) {
		_image = pelota_bmp;
		_size = size_pelota_bmp;
	}else{
		return NULL;
	}
	tmp = IMG_Load_RW(SDL_RWFromMem(_image, _size), 1);
#else
	char ruta_completa [1024] = DATADIR;
	strcat (ruta_completa, ruta);
	tmp = IMG_Load (ruta_completa);
#endif

	if (! tmp)
	{
		printf ("error %s\n", SDL_GetError ());
		return NULL;
	}
#ifndef _EE
	else
	{
		printf ("cargando: %s\n", ruta_completa);
	}
#endif

	SDL_SetColorKey (tmp, SDL_SRCCOLORKEY, \
			SDL_MapRGB (tmp->format, 255, 0, 255));

	ima = SDL_DisplayFormat (tmp);

	if (!ima)
		return tmp;

	SDL_FreeSurface (tmp);
	return ima;
}

void limpiar (SDL_Surface * screen, SDL_Rect * rect)
{
	SDL_FillRect (screen, rect, 0);
}

int sincronizar_velocidad (void)
{
	static int t_anterior = -1;
	static int t_actual;
	static int repeticiones;
	static int delta;
#define FRECUENCIA 10 // 1000 (div) cuadros_por_segundo

	SDL_Delay (20);

	if (t_anterior == -1)
		t_anterior = SDL_GetTicks ();

	t_actual = SDL_GetTicks ();

	delta = t_actual - t_anterior;

	if (delta >= FRECUENCIA)
	{
		repeticiones = delta / FRECUENCIA;
		t_anterior += repeticiones * FRECUENCIA;
		return repeticiones;
	}
	else
	{
		SDL_Delay (FRECUENCIA - delta);
		t_anterior += FRECUENCIA;
		return 1;
	}
}


/* informa si se pulso una tecla (no admite repeticiones) */
int util_pulso_tecla (SDLKey tecla, Uint8 * teclas)
{
	static SDLKey anterior = SDLK_UNKNOWN;

	if (teclas [anterior] == 0)
		anterior = SDLK_UNKNOWN;

	if (teclas [tecla] && tecla != anterior)
	{
		anterior = tecla;
		return 1;
	}

	return 0;
}

int util_leer_ip (char * buffer, int * n, int maxn, Uint8 * teclas)
{
	int i;

	if (*n > 0)
	{
		if (util_pulso_tecla (SDLK_BACKSPACE, teclas))
		{
			(* n) --;
			buffer [*n] = '_';
			buffer [*n + 1] = '\0';
		}
	}

	if (*n < maxn)
	{
		if (util_pulso_tecla (SDLK_PERIOD, teclas))
		{
			buffer [*n] = '.';
			(*n) ++;
			buffer [*n] = '_';
			buffer [*n + 1] = '\0';
		}

		for (i = SDLK_0; i <= SDLK_9; i ++)
		{
			if (util_pulso_tecla (i, teclas))
			{
				buffer [* n] = '0' + i - SDLK_0;
				(*n) ++;
				buffer [*n] = '_';
				buffer [*n + 1] = '\0';
			}
		}
	}

	return 0;
}
