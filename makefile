ifeq ($(UNAME_S),Linux)
    LIB_PATHS= -L/usr/X11R6/lib -L/usr/lib
endif
ifeq ($(UNAME_S),Darwin)
    LIB_PATHS= -framework GLUT -framework OpenGL -framework Cocoa
endif

HDR_PATHS= -I/usr/X11R6/include
LIBS=-lglut -lGLU -lGL -lm -L/usr/X11/lib -lXext #-lXmu -lXi -lX11 -g-std=c++98

CFLAGS=$(HDR_PATHS) -Wno-deprecated
CC=g++
#CC=gcc

ok : OpenGL
	mv *.o obj/

.cc.o:
	$(CC) -c -O3 $(CFLAGS) $<

OBJECTS_main = OpenGL.o Point.o Segment.o FractionRationnelle.o


OpenGL:  $(OBJECTS_main)
	$(CC) $(OBJECTS_main) -o OpenGL $(LIB_PATHS) $(LIBS)
	
	
exe: OpenGL
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
