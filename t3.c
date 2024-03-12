// Tic-tac-toe (T3) Network Game
// Jason Losh

//-----------------------------------------------------------------------------
// Compile notes for C99 code
//-----------------------------------------------------------------------------

// gcc -o t3 t3.c udp.c

//-----------------------------------------------------------------------------
// Device includes, defines, and assembler directives
//-----------------------------------------------------------------------------

#include <stdlib.h>          // EXIT_ codes
#include <stdbool.h>         // bool
#include <stdio.h>           // printf, scanf
#include <string.h>          // strlen, strcmp

#include "udp.h"

#define CLIENT_PORT 4096
#define SERVER_PORT 4097

void clearBoard(char board[3][3])
{
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = '.';
}

// TODO: Add code to display the game board
void showBoard(char board[3][3])
{
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            printf("%c\t", board[r][c]); 
        }
        printf("\n");
    }
}

// TODO: Add code to determine if a winner (xo) has occurred
bool isWinner(char board[3][3], char xo)
{
    bool win;
    if(((board[0][0] == xo) && (board[0][1] == xo) && (board[0][2] == xo)) ||
       ((board[1][0] == xo) && (board[1][1] == xo) && (board[1][2] == xo)) ||
       ((board[2][0] == xo) && (board[2][1] == xo) && (board[2][2] == xo)) ||
       ((board[0][0] == xo) && (board[1][0] == xo) && (board[2][0] == xo)) ||
       ((board[0][1] == xo) && (board[1][1] == xo) && (board[2][1] == xo)) ||
       ((board[0][2] == xo) && (board[1][2] == xo) && (board[2][2] == xo)) ||
       ((board[0][0] == xo) && (board[1][1] == xo) && (board[2][2] == xo)) ||
       ((board[0][2] == xo) && (board[1][1] == xo) && (board[2][0] == xo))){
           
           win = true;
    }
    else{
        win = false;
    }
    return win;
}

// TODO: Add code to test if an x or o (xo) is a valid move
//       and then record in the game board
bool addMove(char board[3][3], char move[], char xo)
{
    bool ok = strlen(move) == 2;
    // ...
    int r = 0;
    int c = 0;
    if(ok == true){
        if(((move[0] == 'A') || (move[0] == 'B') || (move[0] == 'C')) && ((move[1] == '1') || (move[1] == '2') || (move[1] == '3'))){
            switch(move[0]){
                case 'A':
                    r = 0;
                    break;
                case 'B':
                    r = 1;
                    break;
                case 'C':
                    r = 2;
                    break;
            }
            switch(move[1]){
                case '1':
                    c = 0;
                    break;
                case '2':
                    c = 1;
                    break;
                case '3':
                    c = 2;
                    break;
            }
            if(board[r][c] == '.'){
                board[r][c] = xo;
            }
            else{
                ok = false;
            }
        }
        else{
            ok = false;
        }
    }
            
                    
    return ok;
}

//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    char *remoteIp;
    char *role;
    char str[100], str2[100];
    char board[3][3];
    bool validMove;
    bool winner = false;
    int moveCount = 0;
    bool listener;

    bool myTurn;
    char myLetter, opponentLetter;
    int remotePort;

    // TODO: Verify arguments are valie
     bool goodArguments;
    // ...
    if(argc == 3){
        if((strcmp((argv[2]), "accept") == 0) || (strcmp((argv[2]), "invite") == 0)){
            goodArguments = true;
            remoteIp = argv[1];
            if(strcmp((argv[2]), "accept") == 0){
                role = "server";
            }
            else if(strcmp((argv[2]), "invite") == 0){
                role = "client";
            }
        }
    }
    if (!goodArguments)
    {
        printf("usage: t3 IPV4_ADDRESS ROLE\n");
        printf("  where:\n");
        printf("  IPV4_ADDRESS is address of the remote machine\n");
        printf("  ROLE is either invite or accept\n");
        exit(EXIT_FAILURE);
    }

    // TODO: Determine if client or server
    // A server will wait to accept an invitation to play
    // A client will send an invitation to play
    // bool client = _____;
    bool client;
    int port = 0;
    if(strcmp(role, "server") == 0){
        client = false;                  //server
        port = SERVER_PORT;                //4097
    }
    else if(strcmp(role, "client") == 0){
        client = true;                      //client
        port = CLIENT_PORT;                   //4096
    }  
    
    // TODO: Open listener port number dependent on client/server role
    listener = openListenerPort(remoteIp, port);
    if(!listener){
        exit(EXIT_FAILURE);
    }
    
    
    // TODO: Determine remote port that you will send data to
    //       If you are server, send to client port, and vice versa
    int str_length = sizeof(str);
    bool send;
    if(client == false){
        printf("Waiting for an invitation\n");
        receiveData(str, str_length);
        if((strcmp(str, "invite")) == 0){
            printf("Invitation Received\n");
        }
        else{
            exit(EXIT_FAILURE);
        }
    }
    else if(client == true){
        strcpy(str, "invite");
        send = sendData(remoteIp, SERVER_PORT, str);
        if(send){
            printf("Sending an invite\n");
        }
        else{
            exit(EXIT_FAILURE);
        }
    }

    // Setup game
    clearBoard(board);

    // TODO: Determine whether it is your turn or not
    myTurn = false; 

    if(client == false){
        //server
        myTurn = true;
    }
    else if(client == true){
        //client
        myTurn = false;
    }
    // TODO: Determine your letter (x or o) and your opponent's letter
    
    if(client == false){
        myLetter = 'x';                      //server
        opponentLetter = 'o';                //client
    }
    else if(client == true){
        myLetter = 'o';                      //client
        opponentLetter = 'x';                //server
    }

    // TODO: Add code to send an invite or wait to accept an invite
    char input[3] = "";
    bool myTurnsend;
    // Start game loop, alternating turns
    while(!winner && moveCount != 9)
    {
        // get my move
        if (myTurn)
        {
            while(validMove == false){
                printf("Enter your move (%c): ", myLetter);
                scanf("%s", input); 
                validMove = addMove(board, input, myLetter);               
            }
            // TODO: add code your move here to get the move, validate move,
            //       show board, send move to remote port, and check for a winner
            showBoard(board);
            strcpy(str, input);
            if(client == false){
                myTurnsend = sendData(remoteIp, CLIENT_PORT, str);
            }
            else{
                myTurnsend = sendData(remoteIp, SERVER_PORT, str);
            }
            moveCount++;
            winner = isWinner(board, myLetter);
            if (winner){
                printf("You[%c]won\n", myLetter);
            }
        }
        // get opponent's move
        else
        {
            // TODO: add code to receive your opponent's move, validate move,
            //       show board, and check for a winner
            receiveData(str2, sizeof(str2));
            validMove = addMove(board, str2, opponentLetter);   
            if(validMove == false){
                printf("Invalid move\n");
            }
            else{
                moveCount++;
                printf("Your opponent (%c) moved to %s\n", opponentLetter, str2);
                showBoard(board);
                winner = isWinner(board, opponentLetter);
                if(winner){
                    printf("Your opponent (%c) won\n", opponentLetter);
                }
                
            }
            
        }

        // Increment move count, alternate turns
        //moveCount++;
        validMove = false;
        myTurn = !myTurn;
    }
    if (!winner){
        printf("The game was a draw\n");
    }

    // TO DO: Close listener port
    closeListenerPort;
    return EXIT_SUCCESS;
}
