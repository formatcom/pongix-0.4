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

#include "paleta.h"
#include "mundo.h"
#include "juego.h"

Paleta * paleta_iniciar (int jugador, struct juego * juego)
{
	Paleta * paleta;
	paleta = (Paleta * )malloc (sizeof (Paleta));
	
	if ( paleta == NULL)
	{
		printf("Error : Paleta\n");
		return NULL;
	}

	if (jugador == 1 )
	{
		paleta->x = 20;
		paleta->up = SDLK_w;
		paleta->down = SDLK_s;
	}
	else
	{
		paleta->x = 620;
		paleta->up = SDLK_UP;
		paleta->down = SDLK_DOWN;
	}

	paleta->dy = 0;
	paleta->y = 260;
	paleta->juego = juego;

	paleta->ima = cargar_imagen ("paleta.bmp");

	if (paleta->ima == NULL ) 
	{
		printf("Error : %s\n", SDL_GetError());
		return NULL;
		
	}
	
	paleta->jugador = jugador;
	
	return paleta;
}


void paleta_reiniciar (Paleta * data)
{
	data->y = 260;
}


void paleta_imprimir (Paleta * data, struct mundo * mundo)
{
	SDL_Rect rect = { data->x - data->ima->w / 2, \
		data->y - data->ima->h / 2, 0, 0 };
	
	SDL_BlitSurface (data->ima, NULL, mundo->screen, &rect);
	dirty_agregar (mundo->dirty, rect);
}

void paleta_terminar (Paleta * data)
{
	SDL_FreeSurface (data->ima);
	free (data);
}


void paleta_manejar_con_teclado (Paleta * data, Uint8 * teclas)
{
}

int paleta_recibir_pos (Paleta * data, TCPsocket origen)
{
	char buffer [5];
	
	if (SDLNet_TCP_Recv (origen, buffer, 5) < 5)
	{
		printf ("Fall� al recibir pos\n");
//		SDLNet_TCP_Close (origen);
		mundo_cambiar_estado (data->juego->mundo, MENU);
		return;
	}

	data->y = atoi (buffer);
}

int paleta_enviar_pos (Paleta * data, TCPsocket destino)
{
	char buffer [5];
	
	sprintf (buffer, "%d", data->y);

	if (SDLNet_TCP_Send (destino, buffer, 5) < 5)
	{
		printf ("Fall� al enviar pos\n");
		SDLNet_TCP_Close (destino);
		mundo_cambiar_estado (data->juego->mundo, MENU);
		return;
	}
}

void paleta_actualizar (Paleta * data, Uint8 * teclas)
{
	if (teclas [data->up] && data->dy > -5)
		data->dy --;

	if (teclas [data->down] && data->dy < 5)
		data->dy ++;

	data->y += data->dy;

	if (!teclas [data->up] && !teclas [data->down])
	{
		if (data->dy > 0)
			data->dy -= 0.3;

		if (data->dy < 0)
			data->dy += 0.3;
	}

		
	if ((data->y + data->ima->h / 2 ) > 480)
	{
		data->y = 479 - data->ima->h / 2;
		data->dy *= -1;
	}

	if ((data->y - data->ima->h / 2 ) < 40)
	{
		data->y = data->ima->h / 2 + 40;
		data->dy *= -1;
	}



	
	/*
	switch (data->juego->tipo)
	{
		case NORED:
			paleta_manejar_con_teclado (data, teclas);
			break;
	
		case JUEGO_CLIENTE:

			if (data->jugador == 1)
			{
				paleta_recibir_pos (data, \
					data->juego->mundo->cliente->socket);
			}
			else
			{
				paleta_manejar_con_teclado (data, teclas);
				paleta_enviar_pos (data, \
					data->juego->mundo->cliente->socket);

			}
			
			break;

		case JUEGO_SERVIDOR:

			if (data->jugador == 1)
			{
				paleta_manejar_con_teclado (data, teclas);
				paleta_enviar_pos (data, \
					data->juego->mundo->servidor->cliente);
			}
			else
			{
				paleta_recibir_pos (data, \
					data->juego->mundo->servidor->cliente);
			}
			
			break;

	}
	*/
}
