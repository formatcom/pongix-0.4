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

#include "dirty.h"

Dirty * dirty_iniciar (void)
{
	Dirty * tmp;

	tmp = (Dirty *) malloc (sizeof (Dirty));

	if (! tmp)
	{
		printf ("error al iniciar Dirty Rects\n");
		return NULL;
	}

	tmp->limite_actuales = 0;

	return tmp;
}

void dirty_agregar_sin_duplicados (SDL_Rect * dst, int * ndst, SDL_Rect * src)
{
	int i;

	/* busca un duplicado */
	for (i = 0; i < * ndst; i ++)
	{
		if (dst [i].x == (* src).x \
				&& dst [i].y == (* src).y \
				&& dst [i].w == (* src).w \
				&& dst [i].h == (* src).h)
			return;
	}

	/* si no encuentra duplicados lo agrega */
	dst [* ndst] = * src;
	(* ndst) ++;
}

void dirty_agregar (Dirty * data, SDL_Rect rect)
{
	dirty_agregar_sin_duplicados (data->actuales, \
			&(data->limite_actuales), & rect);
}

void dirty_agregar_pantalla_completa (Dirty * data)
{
	data->actuales [0].x = 0;
	data->actuales [0].y = 0;
	data->actuales [0].w = 640;
	data->actuales [0].h = 480;

	data->limite_actuales = 1;
}

void dirty_terminar (Dirty * data)
{
	free (data);
}

#define iguales(A, B) A.x == B.x && A.y == B.y && A.w == B.w && A.h == B.h

void dirty_copiar (SDL_Rect * dst, SDL_Rect * src, int * lim_dst, int lim_src)
{
	int i;

	for (i = 0; i < lim_src; i ++)
		dirty_agregar_sin_duplicados (dst, lim_dst, src + i);
}

void dirty_restaurar (SDL_Surface * dst, SDL_Surface * src, SDL_Rect * rect, \
		int n)
{
	int i;

	for (i = 0; i < n; i ++)
		SDL_BlitSurface (src, rect + i, dst, rect + i);

}

void dirty_actualizar (Dirty * data, SDL_Surface * screen, SDL_Surface * fondo)
{
	static SDL_Rect todos [400];
	static int n = 0;

	dirty_copiar (todos, data->actuales, &n, data->limite_actuales);

	SDL_UpdateRects (screen, n, todos);
	SDL_Flip(screen);

	/* prepara el próximo cuadro */
	n = 0;
	dirty_restaurar (screen, fondo, data->actuales, data->limite_actuales);
	dirty_copiar (todos, data->actuales, &n, data->limite_actuales);
	data->limite_actuales = 0;
}
