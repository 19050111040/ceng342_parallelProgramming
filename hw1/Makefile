CC=gcc
CFLAGS=-I.
DEPS = hellomake.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: 19050111040.o hellofunc.o 
	$(CC) -o hellomake 19050111040.o hellofunc.o 

