//////////////////////////////////////////////////////////////
// LIBRARIES /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

#include<stdlib.h>

//////////////////////////////////////////////////////////////
// CONSTANTS /////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

const int GAMEBOARD_SIZE = 3;
const int GAMEBOARD_ROW_SIZE = 3;

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

//////////////////////////////////////////////////////////////
// MAIN FUNCTION /////////////////////////////////////////////
//////////////////////////////////////////////////////////////  

int main() {

    // Declare the players
    Player player1;
    Player player2;

    // Declare game board
    GameBoard gameboard = {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'}
    };

    // Initial setup
    initialSetup(&player1, &player2);

    // Loop until game ends
    displayGame(gameboard);

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

    printf("\nEnter the name of player 2: ");

    scanf("%s", player2->name);

    printf("------------------------------------------\n");

    printf("-------------- Let's start! --------------\n\n");
}

// Display game
void displayGame(GameBoard gameboard) {
    for(int i = 0; i < GAMEBOARD_SIZE; i++) {
        printf("| ");
        for(int j = 0; j < GAMEBOARD_ROW_SIZE; j++) {
            printf(" %c ", gameboard[i][j]);
        }
        printf(" |");
        printf("\n\n");
    }
}


//TODO Check if player won after play

//TODO Ask for player to make a play

