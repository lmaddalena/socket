CC = gcc

CFLAGS = -std=c99 -g
LDFLAGS =  
ODIR = bin
PROG = a.out

all: main.o 
	$(CC) $(LDFLAGS) $(ODIR)/*.o -o $(ODIR)/$(PROG)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $(ODIR)/main.o

clean:
	rm -f $(ODIR)/$(PROG) $(ODIR)/*.o
