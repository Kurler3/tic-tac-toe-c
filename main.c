//////////////////////////////////////////////////////////////
// LIBRARIES /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

#include<stdlib.h>
#include<stdio.h>

//////////////////////////////////////////////////////////////
// CONSTANTS /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

const int GAMEBOARD_SIZE = 3;
const int GAMEBOARD_ROW_SIZE = 3;
const char PLAYER_1_MARKER = 'X';
const char PLAYER_2_MARKER = 'O';

//////////////////////////////////////////////////////////////
// TYPE DEFINITIONS //////////////////////////////////////////
//////////////////////////////////////////////////////////////

typedef struct {
    char name[30];
    int id;
} Player;

typedef int GameBoard[3][3];

//////////////////////////////////////////////////////////////
// FUNCTION DEFINITIONS //////////////////////////////////////
//////////////////////////////////////////////////////////////

/// @brief Setups up the initial game
/// @param player1 
/// @param player2 
void initialSetup(Player* player1, Player* player2);

void displayGame(GameBoard gameboard);

int canStillPlay(GameBoard gameboard);

int checkIfWon(GameBoard gameboard, int playerId);

int* makePlay(GameBoard gameboard, int playerId);

//////////////////////////////////////////////////////////////
// MAIN FUNCTION /////////////////////////////////////////////
//////////////////////////////////////////////////////////////  

int main() {

    // Declare the players
    Player player1;
    Player player2;

    // Declare the current player.
    int currentPlayer = 1; 

    // Declare game board
    GameBoard gameboard = {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'}
    };

    // Initial setup
    initialSetup(&player1, &player2);

    int winner = 0;

    while(!winner) {

        // Display the game
        displayGame(gameboard);

        // Ask for current player to make a move
        int* chosenSlots = makePlay(gameboard, currentPlayer);

        // Change slot in gameboard
        gameboard[chosenSlots[0]][chosenSlots[1]] = currentPlayer == 1 ? PLAYER_1_MARKER : PLAYER_2_MARKER;

        // Check if won
        int hasOwn = checkIfWon(gameboard, currentPlayer);

        if(hasOwn) {
            winner = currentPlayer;
            break;
        }

        // Check if is a tie
        int isNotTie = canStillPlay(gameboard);

        if(!isNotTie) {
            winner = 3;
            break;
        }

        // Change the current player
        if(currentPlayer == 1) {
            currentPlayer = 2;
        } else {
            currentPlayer = 1;
        }
    }

    // Display the game
    displayGame(gameboard);

    if(winner == 3) {
        printf("It's a tie!\n");
    } else {
        printf("%s won!\n", winner == 1 ? player1.name : player2.name);
    }

    return 0;
}

//////////////////////////////////////////////////////////////
// FUNCTIONS /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

// Initial setup (prints title, instructions and asks for user names)
void initialSetup(Player* player1, Player* player2) {

    printf("------------------------------------------\n");

    printf("Welcome to Tic Tac Toe!\n");

    printf("------------------------------------------\n");

    printf("The instructions are as follows: \n");
    printf("1. In every move, you need to select a number from 1-9. The slots number starts from top-left and end in bottom-right.\n");
    printf("2. The first player to get 3 in a row wins.\n");

    printf("------------------------------------------\n");

    printf("Enter the name of player 1: ");

    scanf("%s", player1->name);
    player1->id = 1;

    printf("\nEnter the name of player 2: ");

    scanf("%s", player2->name);
    player2->id = 2;

    printf("------------------------------------------\n");

    printf("-------------- Let's start! --------------\n\n");
}

// Display game
void displayGame(GameBoard gameboard) {
    printf("\n------------------------------------------\n");
    for(int i = 0; i < GAMEBOARD_SIZE; i++) {
        printf("| ");
        for(int j = 0; j < GAMEBOARD_ROW_SIZE; j++) {
            printf(" %c ", gameboard[i][j]);
        }
        printf(" |");
        printf("\n\n");
    }
     printf("------------------------------------------\n");
}

// Check if player won after play
int checkIfWon(GameBoard gameboard, int playerId) {

    char goal = playerId == 1 ? PLAYER_1_MARKER : PLAYER_2_MARKER;

    //////////////////////////
    // Check rows and cols ///
    //////////////////////////

    // For each row => check if the entire row is this thang
    for(int i = 0; i < GAMEBOARD_SIZE; i++) {
        
        // Check row
        if(gameboard[i][0] == goal && gameboard[i][1] == goal && gameboard[i][2] == goal) {
            return 1;
        }

        // Check column
        if(gameboard[0][i] == goal && gameboard[1][i] == goal && gameboard[2][i] == goal) {
            return 1;
        }

    }

    ////////////////////////
    // Check diagonaly /////
    ////////////////////////
    
    // Check top left to bottom right
    if(gameboard[0][0] == goal && gameboard[1][1] == goal && gameboard[2][2] == goal) {
        return 1;
    }

    // Bottom left to top right
    if(gameboard[2][0] == goal && gameboard[1][1] == goal && gameboard[0][2] == goal) {
        return 1;
    }


    return 0;
}

// Ask for player to make a play
int* makePlay(GameBoard gameboard, int playerId) {

    // Print help
    printf("Player %d please choose a slot: ", playerId);

    int chosenSlot = 0;
    int hasValidChoice = 0;
    int* slots = (int*)malloc(sizeof(int));

    // While input is not valid => keep asking for input
    while(!hasValidChoice) {

        scanf("%d", &chosenSlot);

        if(chosenSlot < 1 || chosenSlot > 9) {
            printf("Please enter a valid slot number: ");
            continue;
        }

        chosenSlot -= 1;

        int normalizedSlot = chosenSlot;
        int row;
        
        if(normalizedSlot > 2) {
            row = chosenSlot % GAMEBOARD_SIZE;
            normalizedSlot-= (3 * row);
        } else {
            row = 0;
        }    

        if(gameboard[row][normalizedSlot] != '-') {
            printf("Please enter a valid slot number: ");
            continue;
        }
     
        hasValidChoice = 1;

        slots[0] = row;
        slots[1] = normalizedSlot;
    }

    return slots;
}

// Check if can still play (could be a tie)
int canStillPlay(GameBoard gameboard) {
    int occupiedSlots = 0;
    for(int i = 0; i < GAMEBOARD_SIZE; i++) {
        for(int j = 0; j < GAMEBOARD_ROW_SIZE; j++) {
            if(gameboard[i][j] != '-') {
                occupiedSlots++;
            }
        }
    }
    return occupiedSlots < 9;
}
