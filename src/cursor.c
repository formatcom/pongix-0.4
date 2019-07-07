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

#include "cursor.h"
#include "mundo.h"


Cursor * cursor_iniciar (void)
{
	Cursor * data;

	data = (Cursor *) malloc (sizeof (Cursor));

	if (data == NULL)
	{
		printf ("No se puede crear el módulo Cursor\n");
		return NULL;
	}

	data->ima = cargar_imagen ("pelota.bmp");

	cursor_reiniciar (data);
	
	if (data->ima == NULL)
		return NULL;
	
	return data;
}

void cursor_reiniciar (Cursor * data)
{
	data->x = 100;
	data->y = 115;
	data->y_final = data->y;
	data->opcion = 0;
}

void cursor_actualizar (Cursor * data, Uint8 * teclas)
{
	static SDLKey pulsada = 0;

	data->y_final = 115 + data->opcion * 50;

	if (teclas [SDLK_DOWN] && pulsada != SDLK_DOWN)
	{
		data->opcion ++;
		pulsada = SDLK_DOWN;
	}

	if (teclas [SDLK_UP] && pulsada != SDLK_UP)
	{
		data->opcion --;
		pulsada = SDLK_UP;
	}

	/* registra si se han soltado las teclas */
	if (pulsada != 0 && teclas [pulsada] == 0)
		pulsada = 0;
	
	if (data->opcion < 0)
		data->opcion = 5;
	
	if (data->opcion > 5)
		data->opcion = 0;

	/* movimiento suave del cursor */
	if (data->y != data->y_final)
		data->y += (data->y_final - data->y) / 5;
}

void cursor_imprimir (Cursor * data, struct mundo * mundo)
{
	SDL_Rect rect = {data->x - data->ima->w / 2, \
		data->y - data->ima->h / 2, 0, 0 };
	
	SDL_BlitSurface (data->ima, NULL, mundo->screen, &rect);
	dirty_agregar (mundo->dirty, rect);
}

void cursor_terminar (Cursor * data)
{
	SDL_FreeSurface (data->ima);
	free (data);
}
