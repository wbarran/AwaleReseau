# AwaleReseau
Multiplayer networked Awale game developed for the Programmation Réseau course

AwaleReseau is a client–server application that allows multiple users to connect to a central server, view online players, send and receive challenges, and play a complete Awale match over a TCP socket connection

The server handles:
- client connections and disconnections 
- a list of online users
- challenge sending/receiving
- creation and management of game sessions

Awale game rules and mechanics (board state, moves, captures, game-end conditions) are implemented in a dedicated module 

## Requirements

- GCC
- POSIX sockets (Linux or WSL environment)

### Build & Run


1. Compile:

make 

2. Start the Server:

./server_exec

3. Start Clients (each in a separate terminal):

./client_exec 127.0.0.1 <Username>

4. In the client, type:

/help


#### Awale Game Rules

1. Objective
Each player begins with 4 seeds in each of their 6 houses (48 total). The goal is to capture more seeds than the opponent.

- Capturing 25 seeds wins the game.

- If both players capture 24 seeds, the game is a draw.

2. Sowing
On your turn, choose one of your six houses:
- Pick up all seeds from that house.
- Sow them counter-clockwise, dropping one seed per house.
- Do not drop seeds into the house you started from or into scoring stores.
- The starting house ends empty; if sowing loops around, it is skipped.

3. Capturing
Captures happen only on the opponent’s side of the board:

- If the last seed you sow lands in an opponent’s house and makes its total exactly 2 or 3, those seeds are captured.

- If the houses immediately before it also end with 2 or 3, they are also captured, continuing backward until the chain breaks.

- Exception: If the move would capture all of the opponent’s seeds (leaving them unable to play), the capture is cancelled and seeds stay on the board.

4. Winning & End of Game
The game ends when:

- A player reaches 25 seeds (win), or

- Both players reach 24 seeds (draw), or

- Players agree the game is repeating endlessly, in which case each player keeps the seeds remaining on their side.