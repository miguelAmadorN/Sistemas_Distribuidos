PROYECTO=Cliente
CFLAGS=-Wall -lm 
LFLAGS=-std=c++11 -lpthread
CC=g++

all: $(PROYECTO)

%.o: %.cpp
	$(CC) -c $< $(CFLAGS) 

$(PROYECTO) : $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	$(CC) $^ -o $@ $(LFLAGS) 

.PHONY: clean

clean:
	rm -f *.o $(PROYECTO)
	


