all: client server

client:
	gcc -o client Client/client2.c

server:
	gcc -o server Server/server2.c Server/ServerChallenge.c Server/ServerGame.c Awale.c -lpthread

clean:
	rm -f client server
