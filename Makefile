# barion
# Makefile

# default installation path
ifndef PREFIX
PREFIX = /opt/local/
endif

CXX = g++
LD = g++
CINT = rootcint

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
CPPFLAGS += -g -Wall
INCDIR=./inc/
SRCDIR=./src/

TARGET = barion
SRC = $(SRCDIR)Frame.cxx $(SRCDIR)Application.cxx $(SRCDIR)Particle.cxx $(SRCDIR)Ring.cxx Frame_Dict.cxx 
OBJ = $(SRC:.cxx=.o) 

all : readme $(TARGET)
app: clean all osxapp
dist : clean all osxapp dmg tgz

$(TARGET) : dict readme $(OBJ) 
	$(LD) $(CPPFLAGS) $(LDFLAGS) -I$(INCDIR) -o $(TARGET) $(OBJ)

%.o : %.cxx
	$(CXX) $(CPPFLAGS) -I$(INCDIR) -c $< -o $@

dict:
	$(CINT) -f Frame_Dict.cxx -c $(INCDIR)Frame.h $(INCDIR)Frame_LinkDef.h
	$(CXX) $(CPPFLAGS) -c Frame_Dict.cxx

readme:
	xxd -i README.md > inc/Readme.h
	$(SED) 's/unsigned/const/g' inc/Readme.h

osxapp:
	cp -rf root_runtime $(TARGET).app/Contents/Resources/
	cp -f $(TARGET) $(TARGET).app/Contents/Resources/
	cp -f rsrc/icon.icns $(TARGET).app/Contents/Resources/AutomatorApplet.icns
	# cp -f rsrc/database.root $(TARGET).app/Contents/Resources/
	# cp -f rsrc/a?.png $(TARGET).app/Contents/Resources/root_runtime/icons/
	cp -rf rsrc $(TARGET).app/Contents/Resources/

# may need sudo
install:
	install -d $(PREFIX)/barion
	install barion $(PREFIX)/barion/
	cp -rf rsrc $(PREFIX)/barion/

dmg:
	hdiutil create $(TARGET).dmg -volname "$(TARGET)" -fs HFS+ -srcfolder $(TARGET).app

tgz:
	tar czvf $(TARGET).tar.gz src/*.cxx inc/*.h rsrc tools Makefile Readme.md

.PHONY : clean
clean :
	rm -rf $(SRCDIR)*.o $(TARGET) *_Dict.* $(TARGET).dSYM
