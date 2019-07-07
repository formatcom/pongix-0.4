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

#ifndef _juego_h
#define _juego_h

#include "util.h"
#include "pelota.h"
#include "paleta.h"
#include "marcador.h"

typedef struct juego
{
	struct mundo * mundo;
 	Pelota * pelota;
	Paleta * paleta1;
	Paleta * paleta2;
	Marcador * marcador;
	enum tipo_juego tipo;
} Juego;


Juego * juego_iniciar (struct mundo * mundo);
void juego_reiniciar (Juego * data, enum tipo_juego tipo);
void juego_actualizar (Juego * data, Uint8 * teclas);
void juego_imprimir (Juego * data);
void juego_terminar (Juego * data);

#endif
