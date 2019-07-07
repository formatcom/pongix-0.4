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

#ifndef _UTIL_
#define _UTIL_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "config.h"

enum estados_red {ERROR, ESPERA_TECLADO, ESPERA_CONEXION};

SDL_Surface * iniciar_sdl (void);
int procesar_eventos (void);
SDL_Surface * cargar_imagen (const char * ruta);
void limpiar (SDL_Surface * screen, SDL_Rect * rect);
int sincronizar_velocidad (void);
int util_leer_ip (char * buffer, int * n, int maxn, Uint8 * teclas);

#endif
