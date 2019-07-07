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

void menu_actualizar (Menu * data, Uint8 * teclas)
{
	cursor_actualizar (data->cursor, teclas);

	if (teclas [SDLK_RETURN])
	{
		switch (data->cursor->opcion)
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
	fuente_printf (data->mundo->fuente, 150, 100, "Iniciar partida local");
	fuente_printf (data->mundo->fuente, 150, 150, "Iniciar servidor (red)");
	fuente_printf (data->mundo->fuente, 150, 200, "Iniciar cliente (red)");
	fuente_printf (data->mundo->fuente, 150, 250, "Creditos");
	fuente_printf (data->mundo->fuente, 150, 300, "Pantalla Completa");
	fuente_printf (data->mundo->fuente, 150, 350, "Salir");

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
