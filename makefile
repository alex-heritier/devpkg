CFLAGS=-g -Wall -c
LFLAGS=-g -Wall

devpkg: devpkg.o db.o
	cc $(LFLAGS) devpkg.o db.o -o devpkg
	
devpkg.o: devpkg.c db.h
	cc $(CFLAGS) devpkg.c
	
db.o: db.c db.h
	cc $(CFLAGS) db.c

clean:
	rm -f *.o
	rm -f devpkg
	rm -f *.tar
	rm -rf projects/*
	rm -rf *.dSYM

tar:
	mv db/database.txt temp.txt
	tar cvf devpkg.tar db.c db.h devpkg.c devpkg.h makefile README dbg.h db
	mv temp.txt db/database.txt
	
install:
	