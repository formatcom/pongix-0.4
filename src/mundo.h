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

#ifndef _mundo_h
#define _mundo_h

#include "util.h"
#include "dirty.h"
#include "fuente.h"
#include "creditos.h"

#include "cliente.h"
#include "servidor.h"

enum estados {MENU, JUEGO, CREDITOS, SERVIDOR, CLIENTE, JUEGORED_CLIENTE, \
	JUEGORED_SERVIDOR};

enum tipo_juego {NORED, JUEGO_CLIENTE, JUEGO_SERVIDOR};

typedef struct mundo
{
	SDL_Surface * screen;
	SDL_Surface * fondo;
	enum estados estado;
	int salir;
	Dirty * dirty;

	struct fuente * fuente;
	struct menu * menu;
	struct juego * juego;
	
	Cliente * cliente;
	Servidor * servidor;
	Creditos * creditos;

} Mundo;


Mundo * mundo_iniciar (void);
int mundo_cargar_modulos (Mundo * data);
void mundo_actualizar (Mundo * data);
void mundo_imprimir (Mundo * data);
void mundo_terminar (Mundo * data);
void mundo_pantalla_completa (Mundo * data);
void mundo_cambiar_estado (Mundo * data, enum estados nuevo_estado);
void mundo_salir (Mundo * data);

#endif
