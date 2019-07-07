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

#ifndef _cliente_h
#define _cliente_h

#include "util.h"
#include <SDL/SDL_net.h>


typedef struct
{
	struct mundo * mundo;
	TCPsocket socket;
	char mensaje [512];
	enum estados_red estado;
	char ip [17];
	int nip;
} Cliente;


Cliente * cliente_iniciar (struct mundo * mundo);
void cliente_conectar (Cliente * data);
void cliente_actualizar (Cliente * data, Uint8 * teclas);
void cliente_imprimir (Cliente * data);
void cliente_terminar (Cliente * data);
void cliente_cerrar (Cliente * data);
void cliente_reiniciar (Cliente * data);

#endif
