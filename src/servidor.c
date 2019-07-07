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

#include "servidor.h"
#include "mundo.h"

Servidor * servidor_iniciar (struct mundo * mundo)
{
	Servidor * data;

	data = (Servidor *) malloc (sizeof (Servidor));

	if (data == NULL)
	{
		printf ("No se puede crear el módulo Juego\n");
		return NULL;
	}

	data->mundo = mundo;
	data->socket = NULL;
	data->cliente = NULL;
	
	return data;
}

void servidor_reiniciar (Servidor * data)
{
	IPaddress ip;

	if (SDLNet_ResolveHost (&ip, NULL, 5000))
	{
		strcpy (data->mensaje, "Falló la llamada a:"\
				"  SDLNet_ResolveHost (puerto 5000)");
		data->estado = ERROR;
		return;
	}

	data->socket = SDLNet_TCP_Open (&ip);

	if (data->socket)
	{
		strcpy (data->mensaje, "Esperando al programa cliente en el\n"\
				"puerto número 5000.");
		
		data->estado = ESPERA_CONEXION;
	}
	else
	{
		strcpy (data->mensaje, "No se puede atender el puerto 5000:\n");

		data->estado = ERROR;
	}
}

void servidor_salir (Servidor * data)
{
	SDLNet_TCP_Close (data->socket);
}

void servidor_actualizar (Servidor * data, Uint8 * teclas)
{
	if (teclas [SDLK_ESCAPE])
	{
		servidor_salir (data);
		mundo_cambiar_estado (data->mundo, MENU);
		return;
	}

	switch (data->estado)
	{
		case ESPERA_CONEXION:
			
			data->cliente = SDLNet_TCP_Accept (data->socket);

			if (data->cliente)
			{
				mundo_cambiar_estado (data->mundo, \
						JUEGORED_SERVIDOR);
			}
			
			break;

		default:
			/* espera que el usuario pulse ESC */
			break;
	}

}

void servidor_imprimir (Servidor * data)
{
	fuente_printf (data->mundo->fuente, 10, 80, data->mensaje);
}

void servidor_terminar (Servidor * data)
{
	/*
	if (data->socket)
		SDLNet_TCP_Close (data->socket);
	*/
/*
	if (data->cliente)
		SDLNet_TCP_Close (data->cliente);
*/	
	free (data);
}


void servidor_cerrar (Servidor * data)
{
	/*
	if (data->socket)
	{
		SDLNet_TCP_Close (data->socket);
		data->socket = NULL;
	}
	*/

	printf ("intento cerrar el servidor\n");

	if (data->cliente)
	{
		SDLNet_TCP_Close (data->cliente);
		data->socket = NULL;
	}

	printf ("servidor cerrado\n");
}
