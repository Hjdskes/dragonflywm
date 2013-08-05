# See LICENSE file for copyright and license details.

VERSION = 0.1
CC = cc
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# Xinerama - comment if you don't want it
#XINERAMALIBS = -L${X11LIB} -lXinerama
#XINERAMAFLAGS = -DXINERAMA

# Flags
CFLAGS = -std=c99 -pedantic -Wall -Os -I. -I/usr/include -I/usr/X11R6/include -DVERSION=\"${VERSION}\" ${XINERAMAFLAGS}
LDFLAGS = -s -L/usr/lib -lc -L/usr/X11R6/lib -lX11 ${XINERAMALIBS}

# Debug flags
#CFLAGS = -g -std=c99 -pedantic -Wall -O0 -I/usr/include -I/usr/X11R6/include -DVERSION=\"${VERSION}\" ${XINERAMAFLAGS}
#LDFLAGS = -g -L/usr/lib -lc -L/usr/X11R6/lib -lX11 ${XINERAMALIBS}

SRC = dragonfly.c
OBJ = ${SRC:.c=.o}

all: options dragonfly

options:
	@echo dragonfly build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h

config.h:
	@echo creating $@ from config.def.h
	@cp config.def.h $@

dragonfly: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f dragonfly ${OBJ} dragonfly-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p dragonfly-${VERSION}
	@cp -R LICENSE Makefile README config.def.h config.mk \
		dragonfly.1 ${SRC} dragonfly-${VERSION}
	@tar -cf dragonfly-${VERSION}.tar dragonfly-${VERSION}
	@gzip dragonfly-${VERSION}.tar
	@rm -rf dragonfly-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f dragonfly ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/dragonfly
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < dragonfly.1 > ${DESTDIR}${MANPREFIX}/man1/dragonfly.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/dragonfly.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/dragonfly
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/dragonfly.1

.PHONY: all options clean dist install uninstall
