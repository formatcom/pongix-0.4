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

#include "menu.h"
#include "mundo.h"

Menu * menu_iniciar (struct mundo * mundo)
{
	Menu * data;

	data = (Menu *) malloc (sizeof (Menu));

	if (data == NULL)
	{
		printf ("No se puede crear el módulo Menu\n");
		return NULL;
	}

	data->cursor = cursor_iniciar ();

	if (data->cursor == NULL)
		return NULL;

	data->mundo = mundo;

	return data;
}

void menu_actualizar (Menu * data, int move, int enter)
{
	cursor_actualizar (data->cursor, move);

	if (enter)
	{
#ifndef __linux__
		int opcion;
		if (data->cursor->opcion > 0) opcion = data->cursor->opcion + 2;
		switch (opcion)
#else
		switch (data->cursor->opcion)
#endif
		{
			case 0:
				mundo_cambiar_estado (data->mundo, JUEGO);
				break;

			case 1:
				mundo_cambiar_estado (data->mundo, SERVIDOR);
				break;

			case 2:
				mundo_cambiar_estado (data->mundo, CLIENTE);
				break;

			case 3:
				mundo_cambiar_estado (data->mundo, CREDITOS);
				break;

			case 4:
				mundo_pantalla_completa (data->mundo);
				break;

			case 5:
				mundo_salir (data->mundo);
				break;

			default:
				printf ("La opción %d no está disponible\n", \
						data->cursor->opcion);
				break;
		}
	}
}

void menu_imprimir (Menu * data)
{
#ifdef __linux__
	int y = 100;
#else
	int y = 200;
#endif
	fuente_printf (data->mundo->fuente, 150, y, "Iniciar partida local");
	y+=50;
#ifdef __linux__
	fuente_printf (data->mundo->fuente, 150, y, "Iniciar servidor (red)");
	y+=50;
	fuente_printf (data->mundo->fuente, 150, y, "Iniciar cliente (red)");
	y+=50;
#endif
	fuente_printf (data->mundo->fuente, 150, y, "Creditos");
	y+=50;
#ifndef _EE
	fuente_printf (data->mundo->fuente, 150, y, "Pantalla Completa");
	y+=50;
	fuente_printf (data->mundo->fuente, 150, y, "Salir");
#endif

	cursor_imprimir (data->cursor, data->mundo);
}

void menu_reiniciar (Menu * data)
{
}

void menu_terminar (Menu * data)
{
	cursor_terminar (data->cursor);
	free (data);
}
