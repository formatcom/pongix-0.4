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

#include <stdarg.h>
#include "fuente.h"

/* componentes del color utilizado como separador de letras */
#define KEY_R 255
#define KEY_G 0
#define KEY_B 255


Fuente * fuente_iniciar (const char * ruta, struct mundo * mundo)
{
	Fuente * aux;

	aux = (Fuente *) malloc (sizeof (Fuente));
	
	aux->ima = cargar_imagen (ruta);

	if (aux->ima == NULL)
	{
		printf ("error: %s\n", SDL_GetError ());
		return NULL;
	}

	aux->letras = 0;

	fuente_cargar_identificar_recs (aux);
	
	aux->mundo = mundo;
	return aux;
}

void fuente_guardar_rect (Fuente * data, int indice, SDL_Rect rect)
{
	data->rects [indice] = rect;
}

int fuente_es_pixel_opaco (SDL_Surface * ima, int fila, int col)
{
	int bpp = ima->format->BytesPerPixel;
	Uint8 * p = ima->pixels + col * bpp + fila * ima->pitch;
	Uint32 color;
	Uint8 r, g, b;

	switch (bpp)
	{
		case 1:
			color = * p;
			break;

		case 2:
			color = * (Uint16 *) p;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				color = p[0] << 16 | p[1] << 8 | p[2];
			else
				color = p[0] | p[1] << 8 | p[2] << 16;
			break;

		case 4:
			color = * (Uint32 *) p;
			break;

		default:
			printf ("Error por bpp = %d\n", bpp);
			break;
	}

	SDL_GetRGB (color, ima->format, &r, &g, &b);

	if (r == KEY_R && g == KEY_G && b == KEY_B)
		return 0;
	
	return 1;
}


int fuente_es_columna_vacia (SDL_Surface * ima, int col)
{
	int fila;

	for (fila = 0; fila < ima->h; fila ++)
	{
		if (fuente_es_pixel_opaco (ima, fila, col))
			return 0;
	}

	return 1;
}


void fuente_cargar_identificar_recs (Fuente * data)
{
	int i;
	int hay_letra = 0;
	int indice = 0;
	int i_ant;

	for (i = 0; i < data->ima->w; i++)
	{
		if (fuente_es_columna_vacia (data->ima, i))
		{
			if (hay_letra)
			{
				SDL_Rect rect = {i_ant, 0, i - i_ant, data->ima->h};

				hay_letra = 0;

				fuente_guardar_rect (data, indice, rect);
				indice ++;
			}
		}
		else
		{
			if (!hay_letra)
			{
				hay_letra = 1;
				i_ant = i;
			}
		}
	}

	printf ("Fuente: se encontraron %d letras\n", indice);
	data->letras = indice;
}


int fuente_imprimir_letra (Fuente * data, char letra, int x, int y)
{
	int i;
	SDL_Rect dst = {x, y, 0, 0};
	char letras [] = "abcdefghijklmnopqrstuvwxyz" \
			  "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
			  "1234567890" \
			  "ñÑáéíóúÁÉÍÓÚäëïöü" \
			  "!¡?¿@#$%&'+-=><*/,.:;-_()[]{}|^`~\\";

	
	if (letra == ' ')
		return data->rects [0].w;

	
	for (i = 0; letras [i] != '\0'; i ++)
	{
		if (letras [i] == letra)
		{
			SDL_BlitSurface (data->ima, data->rects + i, \
					data->mundo->screen, &dst);
			
			dirty_agregar (data->mundo->dirty, dst);
			
			return data->rects [i].w + 2;
		}
	}

	printf ("error: no encuentro '%c' en el alfabeto\n", letra);

	return 0;
}


void fuente_printf (Fuente * data, int x, int y, const char * format, ...)
{
	char buffer [1024];
	va_list va;
	int i;
	int x_inicial = x;

	if (! format)
		return;
	
	va_start (va, format);
	vsprintf (buffer, format, va);

	for (i = 0; buffer [i] != '\0'; i ++)
	{
		if (buffer [i] == '\n')
		{
			y += data->ima->h;
			x = x_inicial;
		}
		else
		{
			x += fuente_imprimir_letra (data, buffer [i], x, y);
		}
	}
	
	va_end (va);
}


void fuente_terminar (Fuente * fuente)
{
	free (fuente);
}



