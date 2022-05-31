$(CC) = gcc

run:
	$(CC) -o run *.c -lncurses

clean:
		rm -f *.o
		rm run