IDIR=include
CC=gcc
CFLAGS=-c -g -Wall -pedantic -std=c99
INC=-I$(IDIR)
ODIR=obj
OBJ=$(ODIR)/main.o $(ODIR)/readData.o $(ODIR)/suffixTree.o $(ODIR)/musicFunctions.o $(ODIR)/alignment.o
TARGET=main
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -lm -o $(TARGET) $(OBJ) $(INC)

$(ODIR)/main.o: main.c
	$(CC) $(CFLAGS) main.c $(INC) -o $(ODIR)/main.o

$(ODIR)/readData.o: readData.c
	$(CC) $(CFLAGS) readData.c $(INC) -o $(ODIR)/readData.o

$(ODIR)/suffixTree.o: suffixTree.c
	$(CC) $(CFLAGS) suffixTree.c $(INC) -o $(ODIR)/suffixTree.o

$(ODIR)/musicFunctions.o: musicFunctions.c
	$(CC) $(CFLAGS) musicFunctions.c $(INC) -o $(ODIR)/musicFunctions.o

$(ODIR)/alignment.o: alignment.c
	$(CC) $(CFLAGS) alignment.c $(INC) -o $(ODIR)/alignment.o

clean:
	rm $(ODIR)/*.o $(TARGETS)
