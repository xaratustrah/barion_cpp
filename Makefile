# barion
# Makefile

# default installation path
ifndef PREFIX
PREFIX = /opt/local/
endif
ifndef SYSTEMDIR
SYSTEMDIR=/usr/local/bin
endif
DBURL= http://amdc.impcas.ac.cn/evaluation/data2012/data/mass.mas12
CXX = g++
LD = g++
CINT = rootcint
XXD = xxd -i
CP = cp -rf
INSTALL= install

# mac vs linux
OS_NAME:=$(shell uname -s | tr A-Z a-z)
ifeq ($(OS_NAME),darwin)
STDINCDIR := -I/opt/local/include
STDLIBDIR := -L/opt/local/lib
EXTRAFLAG := -Qunused-arguments
SED := sed -i ""
else
STDINCDIR := 
STDLIBDIR := 
EXTRAFLAG :=
SED := sed -i
endif

LDFLAGS := $(shell root-config --libs --glibs) -lSpectrum
CPPFLAGS := $(shell root-config --cflags)
CPPFLAGS += -g -Wall $(EXTRAFLAG)
INCDIR=./inc/
SRCDIR=./src/

TARGET = barion
SRC = $(SRCDIR)Frame.cxx $(SRCDIR)Application.cxx $(SRCDIR)Particle.cxx $(SRCDIR)Ring.cxx Frame_Dict.cxx 
OBJ = $(SRC:.cxx=.o) 

all : readme $(TARGET)
arch : clean dmg tgz

$(TARGET) : dict readme $(OBJ) 
	$(LD) $(CPPFLAGS) $(LDFLAGS) -I$(INCDIR) -o $(TARGET) $(OBJ)

%.o : %.cxx
	$(CXX) $(CPPFLAGS) -I$(INCDIR) -c $< -o $@

dict:
	$(CINT) -f Frame_Dict.cxx -c $(INCDIR)Frame.h $(INCDIR)Frame_LinkDef.h
	$(CXX) $(CPPFLAGS) -c Frame_Dict.cxx

readme:
	$(XXD) README.md > inc/Readme.h
	$(SED) 's/unsigned/const/g' inc/Readme.h

db:
	curl $(DBURL) > mass
	tools/ame_data_extractor.rb mass > mass.mod
	./$(TARGET) -c mass.mod
	mv -f database.root rsrc/
	rm -r mass mass.mod
app:
	$(CP) root_runtime $(TARGET).app/Contents/Resources/
	$(CP) $(TARGET) $(TARGET).app/Contents/Resources/
	$(CP) rsrc/icon.icns $(TARGET).app/Contents/Resources/AutomatorApplet.icns
	$(CP) rsrc $(TARGET).app/Contents/Resources/

# may need sudo
install:
	$(INSTALL) -d $(PREFIX)/barion
	$(INSTALL) barion $(PREFIX)/barion/
	$(CP) rsrc $(PREFIX)/barion/

symlink:
	ln -s $(PREFIX)/barion/barion $(SYSTEMDIR)

dmg:
	hdiutil create $(TARGET).dmg -volname "$(TARGET)" -fs HFS+ -srcfolder $(TARGET).app

tgz:
	tar czvf $(TARGET).tar.gz src/*.cxx inc/*.h rsrc tools Makefile Readme.md

.PHONY : clean
clean :
	rm -rf $(SRCDIR)*.o $(TARGET) *_Dict.* $(TARGET).dSYM
