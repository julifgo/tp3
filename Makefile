CC=g++
LDFLAGS=
CFLAGS=-g -std=c++11 -Wall
EXECUTABLE=main
SOURCES=aed2/ConjAcotado.cpp \
		nuestros/compu.cpp \
		nuestros/paquete.cpp \
		nuestros/dcnet.cpp \
		nuestros/red.cpp \
		main.cpp
OBJECTS=$(SOURCES:.cpp=.o)

#TODO. REVISAR ESTE TEST2
EXECUTABLETEST=test2 
SOURCESTEST=aed2/ConjAcotado.cpp \
		nuestros/compu.cpp \
		nuestros/paquete.cpp \
		nuestros/dcnet.cpp \
		nuestros/red.cpp \
		test/Driver.cpp \
		test/ArbolSintactico.cpp \
		test/test.cpp
OBJECTSTEST=$(SOURCESTEST:.cpp=.o)

test: $(SOURCESTEST) $(EXECUTABLETEST)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLETEST): $(OBJECTSTEST) $(CC) $(LDFLAGS) $(OBJECTSTEST) -o $@
    
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
	rm -rf test/*.o
reset:
	reset
	rm -rf *.o
	rm -rf nuestros/*.o
	rm -rf aed2/*.o
	rm -rf test/*.o
	make all

resetTest:
	reset
	rm -rf *.o
	rm -rf nuestros/*.o
	rm -rf aed2/*.o
	rm -rf test/*.o
	make test

#TODO: Agregar rutinas tests uniterios y checkear si la rutina para valgrind es correcta
