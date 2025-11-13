all: client_exec server_exec

client_exec:
	gcc -o client_exec Client/client2.c

server_exec:
	gcc -o server_exec Server/server2.c Server/ServerChallenge.c Server/ServerGame.c Awale.c -lpthread

clean:
	rm -f client_exec server_exec
