/* Basado en el programa "mini ejemplo : fuentes" de Hugo Ruscitti
 * Fecha actual: 17-11-05
 *
 * Pongix - clone of the "Pong" video game with net support
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

#ifndef _fuente_
#define _fuente_

#include "util.h"
#include "mundo.h"

typedef struct fuente
{
	SDL_Rect rects [1024];
	int letras;
	SDL_Surface * ima;
	struct mundo * mundo;
} Fuente;


Fuente * fuente_iniciar (const char * ruta, struct mundo * mundo);
void fuente_guardar_rect (Fuente * data, int indice, SDL_Rect rect);
int fuente_es_pixel_opaco (SDL_Surface * ima, int fila, int col);
int fuente_es_columna_vacia (SDL_Surface * ima, int col);
void fuente_cargar_identificar_recs (Fuente * data);
void fuente_terminar (Fuente * fuente);
void fuente_printf (Fuente * data, int x, int y, const char * format, ...);

#endif
