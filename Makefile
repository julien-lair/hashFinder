all: hashfinder

hashfinder: src/main.o
			gcc -o hashfinder src/main.o -lssl -lcrypto

hasfinder.o: src/main.c
			gcc -Wall -O2 -c src/main.c -o src/main.o

clean:
	rm -f hashfinder src/main.o