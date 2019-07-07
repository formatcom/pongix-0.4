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

#ifndef MARCADOR_H
#define MARCADOR_H

typedef struct
{
	int puntos1;
	int puntos2;
} Marcador;


#include "mundo.h"

Marcador * marcador_iniciar (void);
void marcador_sumar (Marcador * data, int jugador);
void marcador_terminar (Marcador * data);
void marcador_imprimir (Marcador * data, struct mundo * mundo);
void marcador_reiniciar (Marcador * data);

#endif
