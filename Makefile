#
# Makefile:
#	This file is part of stepmotor - RaspberryPi stepper motor 
#       control library using A4988 controller
#       Copyright (C) 2021  Boguslaw Kempny kempny@stanpol.com.pl
#
#################################################################################
#    stepmotor is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    stepmotor is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
#
#################################################################################

VERSION=$(shell cat VERSION)
DESTDIR?=/usr
PREFIX?=/local

LDCONFIG?=ldconfig

ifneq ($V,1)
Q ?= @
endif

DYNAMIC=libsteplib.so.$(VERSION)

DEBUG	= -O2
CC	= gcc
INCLUDE	= -I.
DEFS	= -D_GNU_SOURCE
CFLAGS	= $(DEBUG) $(DEFS) -Wformat=2 -Wall -Wextra -Winline $(INCLUDE) -pipe -fPIC

LIBS    = -lpthread 

###############################################################################

SRC	=	steplib.c delay.c					

HEADERS =	steplib.h

OBJ	=	$(SRC:.c=.o)

all:		$(DYNAMIC)


$(DYNAMIC):	$(OBJ)
	$Q echo "[Link (Dynamic)]"
	$Q $(CC) -shared -Wl,-soname,libsteplib.so$(WIRINGPI_SONAME_SUFFIX) -o libsteplib.so.$(VERSION) $(LIBS) $(OBJ)

.c.o:
	$Q echo [Compile] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@


.PHONY:	clean
clean:
	$Q echo "[Clean]"
	$Q rm -f $(OBJ)  *~ Makefile.bak libsteplib.*



.PHONY:	install
install:	$(DYNAMIC)
	$Q echo "[Install Headers]"
	$Q install -m 0755 -d						$(DESTDIR)$(PREFIX)/include
	$Q install -m 0644 $(HEADERS)					$(DESTDIR)$(PREFIX)/include
	$Q echo "[Install Dynamic Lib]"
	$Q install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	$Q install -m 0755 libsteplib.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/libsteplib.so.$(VERSION)
	$Q ln -sf $(DESTDIR)$(PREFIX)/lib/libsteplib.so.$(VERSION)	$(DESTDIR)/lib/libsteplib.so
	$Q $(LDCONFIG)


.PHONY:	uninstall
uninstall:
	$Q echo "[UnInstall]"
	$Q cd $(DESTDIR)$(PREFIX)/include/ && rm -f $(HEADERS)
	$Q cd $(DESTDIR)$(PREFIX)/lib/     && rm -f libsteplib.*
	$Q $(LDCONFIG)



# DO NOT DELETE
