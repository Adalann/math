CC        = g++
HDR_PATHS = -I/usr/X11R6/include
LIBS      = -lglut -lGLU -lGL -lm -L/usr/X11/lib -lXext #-lXmu -lXi -lX11 -g-std=c++98
CFLAGS    = $(HDR_PATHS) -Wno-deprecated -std=c++11
OBJECTS   = OpenGL.o Point.o PointMassique.o Segment.o FractionRationnelle.o Polynome.o Dessin.o Casteljau.o Bernstein.o

ifeq ($(UNAME_S),Linux)
    LIB_PATHS= -L/usr/X11R6/lib -L/usr/lib
endif
ifeq ($(UNAME_S),Darwin)
    LIB_PATHS= -framework GLUT -framework OpenGL -framework Cocoa
endif

all : OpenGL
	mv *.o obj/

OpenGL:  $(OBJECTS)
	$(CC) $(OBJECTS) -o OpenGL $(LIB_PATHS) $(LIBS)

.cc.o:
	$(CC) -c -O3 $(CFLAGS) $<

exe: OpenGL
	mv *.o obj/
	./OpenGL

indenter :
	for i in *.h *.cpp do sed -i~ -f sed.sed  $i done
	indent  *.h *.cpp

clean :
	rm -fr *.o
	rm -fr obj/*.o
	touch *.cc #*.h

delete :
	rm -f *.h~
	rm -f *.cc~
