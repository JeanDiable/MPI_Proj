cc = mpicc
object = hello.o pi.o
main: $(object)
	$(cc) -o $(object)

%.o: %.c
	$(cc) -c $<

clean:
	rm -f $(object)