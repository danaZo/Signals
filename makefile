sig: sig.o
	gcc sig.c -o sig

clean:
	rm -rf *.o sig