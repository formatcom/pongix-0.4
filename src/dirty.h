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

#ifndef _DIRTY_
#define _DIRTY_

#include "util.h"

typedef struct
{
	struct mundo * mundo;
	SDL_Rect actuales [200];
	int limite_actuales;
} Dirty;


Dirty * dirty_iniciar (void);
void dirty_agregar (Dirty * data, SDL_Rect rect);
void dirty_agregar_pantalla_completa (Dirty * data);
void dirty_terminar (Dirty * data);
void dirty_actualizar (Dirty * data, SDL_Surface * screen, SDL_Surface * fondo);
void dirty_copiar (SDL_Rect * dst, SDL_Rect * src, int * lim_dst, int lim_src);

#endif
