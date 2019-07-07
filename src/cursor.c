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
#ifdef __linux__
	data->y = 115;
#else
	data->y = 215;
#endif
	data->y_final = data->y;
	data->opcion = 0;
}

// move -1 UP | 1 DOWN
void cursor_actualizar (Cursor * data, int move)
{

	int limit_opcion = 5;

#ifdef __linux__
	data->y_final = 115 + data->opcion * 50;
#else
	data->y_final = 215 + data->opcion * 50;
#endif

#ifdef _EE
	limit_opcion = 1;
#endif

#ifdef WIN32
	limit_opcion = 3;
#endif

	if (move > 0 && data->block_move != move)
	{
		data->opcion ++;
	}

	if (move < 0 && data->block_move != move)
	{
		data->opcion --;
	}
	data->block_move = move;

	if (data->opcion < 0)
		data->opcion = limit_opcion;

	if (data->opcion > limit_opcion)
		data->opcion = 0;

	/* movimiento suave del cursor */
	if (data->y != data->y_final)
		data->y += (data->y_final - data->y) / limit_opcion;
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
