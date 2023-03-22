cc = mpicc
object = hello.o pi.o
main: $(object)
	$(cc) -o $(object)
	chmod +x $(object)

%.o: %.c
	$(cc) -c $<

clean:
	rm -f $(object)