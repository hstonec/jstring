CC=cc

test: main.c jstring.o
	$(CC) -Wall -o test main.c jstring.o

jstring.o: jstring.c jstring.h
	$(CC) -Wall -c jstring.c
	
.PHONY: clean
clean:
	-rm test jstring.o