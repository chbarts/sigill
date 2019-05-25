sigill: sigill.c
	gcc -D_GNU_SOURCE sigill.c -o sigill

clean:
	rm sigill
