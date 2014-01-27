CFLAGS=-g -Wall

devpkg: db.o

clean:
	rm -f *.o
	rm -f devpkg
	rm -rf *.dSYM