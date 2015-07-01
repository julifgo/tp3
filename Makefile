CC=g++
LDFLAGS=
CFLAGS=-g -std=c++11 -Werror
EXECUTABLE=main
SOURCES=aed2/ConjAcotado.cpp \
		nuestros/compu.cpp \
		nuestros/paquete.cpp \
		nuestros/dcnet.cpp \
		nuestros/red.cpp \
		main.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

#http://valgrind.org/docs/manual/quick-start.html
valgrind: $(EXECUTABLE)
	valgrind --leak-check=full -v ./$(EXECUTABLE)

clean:
	rm -rf *.o
	rm -rf nuestros/*.o
	rm -rf aed2/*.o

#TODO: Agregar rutinas tests uniterios y checkear si la rutina para valgrind es correcta