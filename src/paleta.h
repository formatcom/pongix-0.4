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

#ifndef _paleta_
#define _paleta_

#include "util.h"
#include "mundo.h"
#include "marcador.h"
#include "cliente.h"
#include "servidor.h"



typedef struct 
{
	int x;
	int y;
	SDL_Surface * ima;
	float dy;
	int jugador;
	struct juego * juego;	
	SDLKey up;
	SDLKey down;
} Paleta;


Paleta * paleta_iniciar (int jugador, struct juego * juego);
void paleta_reiniciar (Paleta * data);
void paleta_terminar (Paleta * data);
void paleta_actualizar (Paleta * data, Uint8 * teclas);
void paleta_manejar_con_teclado (Paleta * data, Uint8 * teclas);

#endif
