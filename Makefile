CC=gcc
CFLAGS=
LDFLAGS=-lstdc++
SOURCES=main.cpp calc.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=calculator

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(SOURCES) 
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $@
clean:
	rm -rf $(EXECUTABLE)