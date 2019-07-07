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

#ifndef _pelota_
#define _pelota_

#include "paleta.h"
#include "util.h"
#include "marcador.h"

#define LIMITE_IZQUIERDO -40
#define LIMITE_DERECHO 680

enum estado {INICIANDO, NORMAL};

typedef struct
{
	float x;
	float y;
	float dx;
	float dy;
	SDL_Surface * ima;
	enum estado estado;
	int direccion_inicial;
	struct juego * juego;
} Pelota;

#include "juego.h"

Pelota * pelota_iniciar (struct juego * juego);

void pelota_reiniciar (Pelota * data);
void pelota_terminar (Pelota * data);
void pelota_actualizar (Pelota * data, Paleta * paleta1, Paleta * paleta2, \
		Marcador * marcador);
void pelota_estado_normal (Pelota * data, Paleta * paleta1, Paleta * paleta2, \
		Marcador * marcador);
void pelota_estado_iniciando (Pelota * data);
void pelota_imprimir ( Pelota * data, struct mundo * mundo);

#endif
