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

#include "cliente.h"
#include "mundo.h"

Cliente * cliente_iniciar (struct mundo * mundo)
{
	Cliente * data;

	data = (Cliente *) malloc (sizeof (Cliente));

	if (data == NULL)
	{
		printf ("No se puede crear el módulo Juego\n");
		return NULL;
	}

	data->mundo = mundo;
	data->socket = NULL;

	strcpy (data->ip, "_");
	data->nip = 0;

	return data;
}


void cliente_conectar (Cliente * data)
{
	IPaddress addr;
	data->ip [data->nip] = '\0';

	if (SDLNet_ResolveHost (&addr, data->ip, 5000) == -1)
	{
		data->estado = ERROR;
		strcpy (data->mensaje, "No se puede resolver la dirección\n"
				"IP, pulse ESC para continuar.");
		return;
	}

	data->socket = SDLNet_TCP_Open (&addr);

	if (data->socket)
	{
		mundo_cambiar_estado (data->mundo, JUEGORED_CLIENTE);
	}
	else
	{
		data->estado = ERROR;
		strcpy (data->mensaje, "No se puede abrir un socket para\n"
				"establecer una comunicación de red.");
	}
}

void cliente_actualizar (Cliente * data, Uint8 * teclas)
{
	if (teclas [SDLK_ESCAPE])
	{
		mundo_cambiar_estado (data->mundo, MENU);
		return;
	}

	switch (data->estado)
	{
		case ESPERA_TECLADO:
			
			/* ingresa ip, no se permiten caracteres */
			
			util_leer_ip (data->ip, &data->nip, 16, teclas);
			
			if (teclas [SDLK_RETURN] && data->nip > 4)
				cliente_conectar (data);
		
			break;
		
		default:
			break;
	}
}

void cliente_imprimir (Cliente * data)
{
	fuente_printf (data->mundo->fuente, 10, 80, data->mensaje);
	fuente_printf (data->mundo->fuente, 200, 200, data->ip);
}

void cliente_terminar (Cliente * data)
{
	if (data->socket)
		SDLNet_TCP_Close (data->socket);

	free (data);
}


void cliente_reiniciar (Cliente * data)
{
	strcpy (data->ip, "_");
	data->nip = 0;

	strcpy (data->mensaje, "Ingrese la IP del equipo remoto\n"
			"(si verifica el programa en forma local\n"
			"utilice la IP 127.0.0.1)");
		
	data->estado = ESPERA_TECLADO;
}


void cliente_cerrar (Cliente * data)
{
	printf ("intendo cerrar el cliente\n"); 

	if (data->socket)
	{
		SDLNet_TCP_Close (data->socket);
		data->socket = NULL;
	}

	printf ("Cerrando el cliente\n");
}
