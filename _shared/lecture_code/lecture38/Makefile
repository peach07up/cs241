OPTS=  -std=gnu99 -Wall -g 
all: recvfrom sendto

recvfrom: recvfrom.c
	gcc $(OPTS) recvfrom.c -o recvfrom

sendto: sendto.c
	gcc  $(OPTS)  sendto.c -o sendto

clean:
	rm -rf recvfrom sendto *.dSYM

pretty:
	astyle -n *.c
