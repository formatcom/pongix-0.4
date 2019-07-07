AC_INIT(pongix, 0.4)
AM_INIT_AUTOMAKE
AC_PREREQ([2.50])
AM_CONFIG_HEADER(config.h)

AC_PROG_CC

dnl Busca las bibliotecas SDL
AC_CHECK_LIB(SDL, SDL_Init, , \
	AC_MSG_ERROR([* Can't find SDL library: http://www.libsdl.org]))

AC_CHECK_LIB(SDL_image, IMG_Load, , \
	AC_MSG_ERROR([* Can't find SDL_image library: http://www.libsdl.org]))

AC_CHECK_LIB(SDL_net, SDLNet_Init, , \
	AC_MSG_ERROR([* Can't find SDLNet_Init library: http://www.libsdl.org]))


AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)

AC_OUTPUT([
Makefile
src/Makefile
data/Makefile
])
