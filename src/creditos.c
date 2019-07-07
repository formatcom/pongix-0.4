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

#include "creditos.h"
#include "mundo.h"

Creditos * creditos_iniciar (struct mundo * mundo)
{
	Creditos * data;

	data = (Creditos *) malloc (sizeof (Creditos));

	if (data == NULL)
	{
		printf ("No se puede crear el módulo Juego\n");
		return NULL;
	}

	data->mundo = mundo;

	return data;
}


void creditos_actualizar (Creditos * data, int key_escape)
{
	if (key_escape)
		mundo_cambiar_estado (data->mundo, MENU);
}

void creditos_imprimir (Creditos * data)
{
	fuente_printf (data->mundo->fuente, 10, 50, \
			" * Hugo Ruscitti\n"
			" * Lucas Liendo\n"\
			" * Ricardo Javier Tellechea Suárez\n"\
			" * Vinicio Valbuena ps2 port\n"\
			"\n"\
			" Este programa se distribuye bajo la \n"\
			" licencia GPL; visite nuestro sitio web: \n"\
			"\n"\
			"     ** www.losersjuegos.com.ar **\n"\
			"\n"\
			" para obtener mas detalles.\n");
}

void creditos_terminar (Creditos * data)
{
	free (data);
}
