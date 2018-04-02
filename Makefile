#Ante Dominum by Traction
SHELL = /bin/sh
PLATFORM = $(shell uname)
ifeq ($(PLATFORM),Linux)
PLATFORM = LINUX
endif
ifeq ($(PLATFORM),Darwin)
PLATFORM = OS_X
endif
ifeq ($(PLATFORM),)
PLATFORM = WIN32
endif

FULLSCREEN = FALSE
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

#compiler we're using
CC = gcc
CXX = g++

OBJ = changer.o filter.o hermitecurve.o lista.o matrix.o path.o stuff.o texture.o win32.o complex.o floater.o liikkuva.o main.o molekyylidata.o primitives.o sync.o timer.o config.o font.o line.o matikka.o object3d.o sound.o tausta.o vector.o alku.o curves.o field.o newton.o rossler.o cell.o dla.o iterator.o platon.o runko.o converge.o fibotree.o lorentz.o pot2d.o

TARGET = antedominium-by-traction
LDFLAGS += -lm
CFLAGS += -DWINDOW_WIDTH=$(WINDOW_WIDTH) -DWINDOW_HEIGHT=$(WINDOW_HEIGHT) -Wall -O3 -flto -ffast-math -std=gnu90 -pipe
CXXFLAGS += -Wall -O3 -flto -ffast-math -fno-exceptions -fno-rtti -DWINDOW_WIDTH=$(WINDOW_WIDTH) -DWINDOW_HEIGHT=$(WINDOW_HEIGHT) -std=gnu++98 -fabi-version=2 -pipe
CCFLAGS =
RELEASES =
#variable de nettoyage
RM_F = rm -f

ifeq ($(FULLSCREEN),TRUE)
	CFLAGS += -DFULLSCREEN
endif

ifeq ($(PLATFORM), LINUX)
	LDFLAGS += -L/usr/lib/ -I./ $(shell pkgconf --libs glu sdl) -lfmodex
	CFLAGS += $(shell pkgconf --cflags glu sdl)
endif

#variables d'instalation
INSTALL = install
INSTALL_DIR     = $(INSTALL) -p -d -o root -g root  -m  755
INSTALL_PROGRAM = $(INSTALL) -p    -o root -g root  -m  755
INSTALL_DATA    = $(INSTALL) -p    -o root -g root  -m  644

prefix          = /usr
exec_prefix     = $(prefix)
bindir          = $(prefix)/bin
datarootdir     = $(prefix)/share
datadir         = $(prefix)/share/antedominium-by-traction

.PHONY: all all-before all-after clean clean-custom
all: all-before $(TARGET) all-after
#define some system utilities
CP = cp -R
MKDIR = mkdir

#parallel compilation if available
ifneq (,$(filter parallel=%,$(DEB_BUILD_OPTIONS)))
 NUMJOBS = $(patsubst parallel=%,%,$(filter parallel=%,$(DEB_BUILD_OPTIONS)))
 MAKEFLAGS += -j$(NUMJOBS)
endif

export

all: $(TARGET)

clean:
	 $(RM_F) $(OBJ)
	 $(RM_F) $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(EXTRACFLAGS) $(CFLAGS)) -c $<

%.o: %.cpp $(HEADERS)
	$(CXX) $(EXTRACFLAGS) $(CXXFLAGS) -c $<

%.o: ./Effects/%.cpp $(HEADERS)
	$(CXX) $(EXTRACFLAGS) $(CXXFLAGS) -c $<

$(TARGET): $(OBJ)
	$(CXX) -flto -o $@ $(OBJ) $(LDFLAGS)

install: $(TARGET)
	$(INSTALL_DIR) $(DESTDIR)$(bindir)
	-@$(RM_F) $(DESTDIR)$(bindir)/$(TARGET)
	$(INSTALL_PROGRAM) $(TARGET) $(DESTDIR)$(bindir)
	$(INSTALL_DIR) $(DESTDIR)$(datadir)
	$(INSTALL_DATA) music.xm $(DESTDIR)$(datadir)
