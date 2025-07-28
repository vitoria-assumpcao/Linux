all: peertalk

peertalk: peertalk.o ipc.o
	$(CC) -o peertalk peertalk.o ipc.o

peertalk.o: peertalk.c ipc.h
	$(CC) -c peertalk.c

ipc.o: ipc.c ipc.h
	$(CC) -c ipc.c

clean:
	rm -f *.o peertalk

