# Tic-Tac-Toe Network Game

## Introduction

Welcome to the Tic-Tac-Toe Network Game, a multiplayer implementation of the classic Tic-Tac-Toe game using a client-server architecture. This C program allows two players to connect over a network, take turns making moves, and determine the winner in a game of Tic-Tac-Toe.

## Features

- **Multiplayer:** Play Tic-Tac-Toe with a friend over a network.
- **Client-Server Architecture:** Utilize a client-server model for game communication.
- **Alternate Turns:** Players take turns making moves until there is a winner or a draw.
- **Winning Condition:** Determine the winner based on standard Tic-Tac-Toe rules.

## Getting Started

1. Clone the repository.
2. Compile the C program using a compatible compiler.
3. Run the server and client executables on the respective machines.
4. Follow the prompts to connect and play Tic-Tac-Toe.

```bash
gcc t3.c udp.c -o t3
./t3 <IP_ADDRESS> <ROLE>
```

## Game Mechanics

- **Game Board:** A 3x3 grid where players make their moves.
- **Turns:** Players take turns making moves, marking the board with 'x' or 'o.'
- **Winning:** The first player to get three of their marks in a row (horizontally, vertically, or diagonally) wins.
- **Draw:** If the board is filled with no winner, the game is a draw.

## Network Communication

- **Invite Mechanism:** The server waits for an invitation, while the client sends an invitation to the server.
- **Role Identification:** The program determines whether it is the client or server based on command-line arguments.
- **Turn Alternation:** Players alternate turns, and their moves are communicated over the network.
