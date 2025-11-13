all: client server

client:
	gcc -o client_exec Client/client2.c

server:
	gcc -o server_exec Server/server2.c Server/ServerChallenge.c Server/ServerGame.c Awale.c -lpthread

clean:
	rm -f client server
