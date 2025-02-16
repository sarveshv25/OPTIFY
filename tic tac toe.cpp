#include <stdio.h>

// Global Variables
char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
char marker[2] = {'X', 'O'};
int current_player = 0;

// Function to display the board
void displayBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

// Function to place a marker on the board
int placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (slot < 1 || slot > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
        return 0; // Invalid move
    }

    board[row][col] = marker[current_player];
    return 1; // Successful move
}

// Function to check for a win
int checkWin() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
            return 1;
        }
    }

    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return 1;
    }

    return 0; // No winner yet
}

int main() {
    printf("Welcome to Tic Tac Toe!\n\n");

    int turns = 0;
    int winner = 0;

    // Game loop
    while (turns < 9 && winner == 0) {
        displayBoard();
        printf("Player %d (%c), enter your slot (1-9): ", current_player + 1, marker[current_player]);

        int slot;
        scanf("%d", &slot);

        if (!placeMarker(slot)) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        winner = checkWin();
        if (winner == 0) {
            current_player = 1 - current_player; // Switch player
        }
        turns++;
    }

    displayBoard();

    if (winner) {
        printf("Congratulations! Player %d (%c) wins!\n", current_player + 1, marker[current_player]);
    } else {
        printf("It's a tie!\n");
    }

    return 0;
}


