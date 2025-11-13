CC = gcc
CFLAGS = -pthread

# Fichiers sources
CLIENT_SRC = Client/client2.c
SERVER_SRC = Server/server2.c Server/ServerChallenge.c Server/ServerGame.c Awale.c

# Executables
CLIENT_EXEC = client_exec
SERVER_EXEC = server_exec

all: $(CLIENT_EXEC) $(SERVER_EXEC)

# Compilation client
$(CLIENT_EXEC): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation serveur
$(SERVER_EXEC): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(CLIENT_EXEC) $(SERVER_EXEC)
