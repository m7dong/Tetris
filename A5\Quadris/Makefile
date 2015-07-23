CXX = g++
XXFLAGS = -Wall -MMD 
EXEC = quadris -lX11 -L/usr/X11/lib
OBJECTS = quadris.o game.o board.o window.o block.o cell.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${XXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}