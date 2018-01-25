all: fileBase64

fileBase64: main.o base64.o
	gcc -g -Wall base64.o main.o -o fileBase64
	
main.o: main.c base64.h
	gcc -c -g -Wall main.c -o main.o
	
base64.o: base64.c base64.h
	gcc -c -g -Wall base64.c -o base64.o


clean:
	rm -f *.o
	rm -f fileBase64
