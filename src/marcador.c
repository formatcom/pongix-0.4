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

#include "marcador.h"
#include "util.h"
#include "mundo.h"

Marcador * marcador_iniciar (void)
{
	Marcador * data;

	data = (Marcador *) malloc (sizeof (Marcador));

	if (data == NULL)
	{
		printf ("No se puede crear el módulo Marcador\n");
		return NULL;
	}

	return data;
}

void marcador_sumar (Marcador * data, int jugador)
{
	if (jugador == 1)
		data->puntos1 ++;
	else
		data->puntos2 ++;
}

void marcador_terminar (Marcador * data)
{
	free (data);
}

void marcador_imprimir (Marcador * data, struct mundo * mundo)
{
	fuente_printf (mundo->fuente, 10, 0, "%d", data->puntos1);
	fuente_printf (mundo->fuente, 600, 0, "%d", data->puntos2);
}

void marcador_reiniciar (Marcador * data)
{
	data->puntos1 = 0;
	data->puntos2 = 0;
}
