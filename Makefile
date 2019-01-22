CC := gcc
CFLAGS := -g

twrandom: twrandom.o
	$(CC) $(CFLAGS) -o $@ $^


twrandom.o: twrandom.c

clean:
	rm twrandom.o twrandom
