cc = mpicc
prime: prime.c
	$(cc) -o prime.s -S prime.c
	$(cc) -o prime.o -c prime.s
	$(cc) -o prime prime.o

clean:
	rm -f prime.s prime.o prime