#!gmake 

#-----------------------------------------
#Basic Stuff -----------------------------
CC          = g++ 
cc          = gcc

#-----------------------------------------
#Optimization ----------------------------
OPT   = -O3

#-----------------------------------------
# X       --------------------------------
X_INC  =   -I/usr/X11R6/include -I/sw/include -I/usr/sww/include -I/usr/sww/pkg/Mesa/include -I. 
X_LIB  =   -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib 

#-----------------------------------------

#-----------------------------------------
# GL      --------------------------------
GL_LIB  =   -lglut -lGLU -lGL -lX11

#-----------------------------------------

SOURCES=main.cpp patch.cpp parser.cpp window.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=run

#-----------------------------------------

LIBS = $(X_LIB) $(GL_LIB) 
INCS = $(X_INC) 

CCOPTS = $(OPT) $(INCS) -c
LDOPTS = $(OPT) $(INCS) $(LIBS)

#-----------------------------------------
#-----------------------------------------

default: $(EXECUTABLE)

clean:
	/bin/rm -f *.o $(EXECUTABLE)

#-----------------------------------------
#-----------------------------------------

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDOPTS) -o $(EXECUTABLE)

.cpp.o:
	$(CC) $< -c $(CCOPTS)


#export LD_LIBRARY_PATH="/usr/sww/pkg/Mesa/lib:/usr/lib:/usr/sww/lib"

