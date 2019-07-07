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

#include "mundo.h"
#include "pelota.h"


int dist (int a, int b)
{
	return sqrt (a*a + b*b);
}

Pelota * pelota_iniciar (struct juego * juego)
{
	Pelota * pelota;
	pelota = (Pelota * )malloc (sizeof (Pelota));

	if ( pelota == NULL)
	{
		printf("Error: no se puede crear el módulo Pelota\n");
		return NULL;
	}

	pelota_reiniciar (pelota);
	pelota->direccion_inicial = 1;
	pelota->juego = juego;

	pelota->ima = cargar_imagen ("pelota.bmp");

	if (pelota->ima == NULL )
	{
		printf("Error : %s\n", SDL_GetError());
		return NULL;

	}

	return pelota;
}

void pelota_imprimir ( Pelota * data, struct mundo * mundo)
{
	SDL_Rect rect = { data->x - data->ima->w / 2, \
		data->y - data->ima->h / 2, 0, 0 };

	SDL_BlitSurface ( data->ima, NULL, mundo->screen, &rect);
	dirty_agregar (mundo->dirty, rect);
}

void pelota_terminar (Pelota * data)
{
	SDL_FreeSurface (data->ima);
	free (data);
}

void pelota_reiniciar (Pelota * data)
{
	data->dy = 300;
	data->x = 320;
	data->y = 260;
	data->estado = INICIANDO;
}

void pelota_actualizar (Pelota * data, Paleta * paleta1, Paleta * paleta2, \
		Marcador * marcador)
{
	switch (data->estado)
	{
		case INICIANDO:
			pelota_estado_iniciando (data);
			break;

		case NORMAL:
			pelota_estado_normal (data, \
					data->juego->paleta1, \
					data->juego->paleta2, \
					data->juego->marcador);
			break;
	}
}

void pelota_estado_iniciando (Pelota * data)
{
	static float t = 0;

	data->y = 260 + sin (t += 0.1) * data->dy;
	data->x = 320 + cos (t) * 20;

	data->dy --;

	if (data->dy < 0)
	{
		data->dy = 0.01;
		data->dx = data->direccion_inicial * 3;
		data->estado = NORMAL;
	}
}

void pelota_estado_normal (Pelota * data, Paleta * paleta1, Paleta * paleta2, \
		Marcador * marcador)
{
	int a;
	int b;
	int l;
	int distancia = 0;

	/* limites laterales */
	if (data->x > LIMITE_DERECHO)
	{
		marcador_sumar (marcador, 1);
		pelota_reiniciar (data);
		data->direccion_inicial = 1;
	}

	if (data->x < LIMITE_IZQUIERDO)
	{
		marcador_sumar (marcador, 2);
		pelota_reiniciar (data);
		data->direccion_inicial = -1;
	}

	if ((data->y + 10) > 480)
		data->dy *= -1;

	if ((data->y - 10) < 40)
		data->dy *= -1;



	data->x += data->dx;
	data->y += data->dy;

	#define cuadrado(X) (X*X)

	/* colisiones hacia la izquierda */
	if (data->dx < 0)
	{
		a = paleta1->y - (paleta1->ima->h / 2) + 10;
		b = paleta1->y + (paleta1->ima->h / 2) - 10;

		/* colision sobre los bordes planos de la paleta */
		if (data->y < a)
			distancia = dist ((data->y - a),(data->x - paleta1->x));

		if (data->y > b)
			distancia = dist ((data->y - b),(data->x - paleta1->x));

		/* colision en las esquinas redondas de la paleta */
		if ((data->y > a && data->y < b) || distancia < 20)
		{
			l = paleta1->x + 10;

			if (data->x - 10 < l && data->x > l - 10)
			{
				data->dx *= -1;
				data->dy = (data->y - paleta1->y) / (20 - data->dx * 2);
			}
		}
	}
	else
	{
		a = paleta2->y - (paleta2->ima->h / 2) + 10;
		b = paleta2->y + (paleta2->ima->h / 2) - 10;

		/* colision sobre los bordes planos de la paleta */
		if (data->y < a)
			distancia = dist ((data->y - a),(data->x - paleta2->x));

		if (data->y > b)
			distancia = dist ((data->y - b),(data->x - paleta2->x));

		if ((data->y > a && data->y < b) || distancia < 20 )
		{
			l = paleta2->x - 10;

			/* colision en las esquinas redondas de la paleta */
			if (data->x + 10 > l && data->x < l + 10)
			{
				data->dx *= -1;
				data->dy = (data->y - paleta2->y) / (20 - data->dx * 2);
			}
		}
	}
}
