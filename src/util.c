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

#include "util.h"
#include <SDL/SDL.h>

SDL_Surface * iniciar_sdl (void)
{
	SDL_Surface * screen;
	
	if ((SDL_Init (SDL_INIT_VIDEO)) < 0)
	{
		printf ("Error: %s\n", SDL_GetError ());
		return NULL;
	}

	if ((screen = SDL_SetVideoMode (640, 480, 16, SDL_SWSURFACE)) == NULL)	
	{
		printf ("Error: %s\n", SDL_GetError ());
		return NULL;
	}

	if (SDLNet_Init() < 0)
	{
		printf ("Error en SDLNet_Init: %s\n", SDL_GetError());
		return NULL;
	}
	
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
				
			default: 
				break;
		}
	}

	return 0;
}

SDL_Surface * cargar_imagen (const char * ruta)
{
	SDL_Surface * tmp;
	SDL_Surface * ima;
	char ruta_completa [1024] = DATADIR;

	strcat (ruta_completa, ruta);

	tmp = IMG_Load (ruta_completa);

	if (! tmp)
	{
		printf ("error %s\n", SDL_GetError ());
		return NULL;
	}
	else
	{
		printf ("cargando: %s\n", ruta_completa);
	}

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
	static int i;
	static int delta;
#define FRECUENCIA 10 /* 1000 (div) cuadros_por_segundo */

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
