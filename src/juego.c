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

#include "juego.h"
#include "mundo.h"

Juego * juego_iniciar (struct mundo * mundo)
{
	Juego * data;

	data = (Juego *) malloc (sizeof (Juego));

	if (data == NULL)
	{
		printf ("No se puede crear el módulo Juego\n");
		return NULL;
	}

	data->mundo = mundo;

	data->pelota = pelota_iniciar (data);

	if (data->pelota == NULL)
		return NULL;

	data->paleta1 = paleta_iniciar (1, data);

	if (data->paleta1 == NULL)
		return NULL;

	data->paleta2 = paleta_iniciar (2, data);

	if (data->paleta2 == NULL)
		return NULL;

	data->marcador = marcador_iniciar ();

	if (data->marcador == NULL)
		return NULL;

	juego_reiniciar (data, NORED);

	return data;
}

void juego_reiniciar (Juego * data, enum tipo_juego tipo)
{
	data->tipo = tipo;

	pelota_reiniciar (data->pelota);
	paleta_reiniciar (data->paleta1);
	paleta_reiniciar (data->paleta2);
	marcador_reiniciar (data->marcador);
}

void juego_actualizar (Juego * data, int key_escape)
{

	if (key_escape)
	{
#ifdef __linux__
		switch (data->tipo)
		{
			case JUEGO_CLIENTE:
				cliente_cerrar (data->mundo->cliente);
				break;

			case JUEGO_SERVIDOR:
				servidor_cerrar (data->mundo->servidor);
				break;

			default:
				break;
		}
#endif

		mundo_cambiar_estado (data->mundo, MENU);
		return ;
	}

#ifdef __linux__
	switch (data->tipo)
	{
		case JUEGO_CLIENTE:
			paleta_recibir_pos (data->paleta1, \
					data->mundo->cliente->socket);

			paleta_actualizar (data->paleta2);
			paleta_enviar_pos (data->paleta2, \
					data->mundo->cliente->socket);

			pelota_actualizar (data->pelota, data->paleta1, \
					data->paleta2, data->marcador);
			break;

		case JUEGO_SERVIDOR:
			paleta_actualizar (data->paleta1);
			paleta_enviar_pos (data->paleta1, \
					data->mundo->servidor->cliente);

			paleta_recibir_pos (data->paleta2, \
					data->mundo->servidor->cliente);

			pelota_actualizar (data->pelota, data->paleta1, \
					data->paleta2, data->marcador);
			break;
		case NORED:
			paleta_actualizar (data->paleta1);
			paleta_actualizar (data->paleta2);

			pelota_actualizar (data->pelota, data->paleta1, \
					data->paleta2, data->marcador);
			break;
	}
#else
			paleta_actualizar (data->paleta1);
			paleta_actualizar (data->paleta2);

			pelota_actualizar (data->pelota, data->paleta1, \
					data->paleta2, data->marcador);
#endif
}

void juego_imprimir (Juego * data)
{
	pelota_imprimir (data->pelota, data->mundo);
	paleta_imprimir (data->paleta1, data->mundo);
	paleta_imprimir (data->paleta2, data->mundo);

	marcador_imprimir (data->marcador, data->mundo);
}

void juego_terminar (Juego * data)
{
	paleta_terminar (data->paleta1);
	paleta_terminar (data->paleta2);
	pelota_terminar (data->pelota);
	free (data);
}
