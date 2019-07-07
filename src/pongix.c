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
#include "util.h"
#include "dirty.h"

int main (int argc, char * argv [])
{
	Mundo * mundo;
	int repeticiones;
	int i;
	
	mundo = mundo_iniciar ();

	if (mundo == NULL)
		return 1;

	while (! procesar_eventos () && ! mundo->salir)
	{
		repeticiones = sincronizar_velocidad ();

		for (i = 0; i < repeticiones; i ++)
			mundo_actualizar (mundo);
	
		mundo_imprimir (mundo);
	}
	
	mundo_terminar (mundo);
	return 0;
}
