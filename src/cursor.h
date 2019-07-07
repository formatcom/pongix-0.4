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

#ifndef _CURSOR_H
#define _CURSOR_H

#include "mundo.h"
#include "util.h"

typedef struct cursor
{
	int x;
	int y;
	int y_final;
	SDL_Surface * ima;
	int opcion;
	int block_move;
} Cursor;


Cursor * cursor_iniciar (void);

void cursor_imprimir (Cursor * data, struct mundo * mundo);
void cursor_reiniciar (Cursor * data);
void cursor_actualizar (Cursor * data, int move);
void cursor_terminar (Cursor * data);

#endif
