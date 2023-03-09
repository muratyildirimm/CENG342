CC=gcc
CFLAGS=-I.
DEPS = hellomake.h
OBJ = 20050151005.o hellofunction.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

