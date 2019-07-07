bin_PROGRAMS = pongix

pongixdir = $(datadir)/pongix/

pongix_LDADD = $(DEPS_LIBS)
INCLUDES = $(DEPS_CFLAGS) -DDATADIR=\""$(pongixdir)"\"

pongix_SOURCES = pongix.c util.c pelota.c dirty.c paleta.c mundo.c menu.c \
        juego.c fuente.c cursor.c marcador.c creditos.c cliente.c servidor.c

EXTRA_DIST= cursor.h dirty.h fuente.h juego.h menu.h mundo.h paleta.h \
	pelota.h util.h Makefile.win marcador.h creditos.h cliente.h \
	servidor.h
