CC=g++
ODIR=obj
SDIR=src
CFLAGS=-O3 -std=c++11

_SRC=editdistcom.cpp
_OBJ=editdistcom.o

SRC=$(patsubst %,$(SDIR)/%,$(_SRC))
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

exe/edtest:$(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)

run: exe/edtest
	./exe/edtest

$(ODIR)/%.o: $(SDIR)/%.cpp 
	$(CC) -o $@ -c $< $(CFLAGS)