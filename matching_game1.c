#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARD_SIZE 4
#define MAX_NUM_FOUND 8 // The maximum number of numbers found

// Global variables
int board[BOARD_SIZE][BOARD_SIZE]; // Game board
bool visible[BOARD_SIZE][BOARD_SIZE]; // Visibility status of elements
int foundNumbers[MAX_NUM_FOUND]; // The array that will store the found numbers
int numFound = 0; // Variable that will hold the number of found numbers
int matchingCoordinates[MAX_NUM_FOUND][2];
int numMatchingCoordinates = 0;
int totalTries = 0;

// Function to initialize the game board with random numbers
void initializeBoard() {
    srand(time(NULL));
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = rand() % 10;
            visible[i][j] = false; // Initially all elements are hidden
        }
    }
}

// Function to print the game board
void printBoard() {
    printf("    0   1   2   3\n");
    printf("  -----------------\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d |", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (visible[i][j])
                printf(" %d |", board[i][j]);
            else
                printf(" ? |");
        }
        printf("\n  -----------------\n");
    }
}

// Function to update visibility status based on matching coordinates
void updateVisibility() {
    for (int i = 0; i < numMatchingCoordinates; i++) {
        int x = matchingCoordinates[i][0];
        int y = matchingCoordinates[i][1];
        visible[x][y] = false; // Make the item invisible
    }
}

// Function to store matching coordinates
void storeMatchingCoordinates(int x1, int y1, int x2, int y2) {
    matchingCoordinates[numMatchingCoordinates][0] = x1;
    matchingCoordinates[numMatchingCoordinates][1] = y1;
    numMatchingCoordinates++;
    matchingCoordinates[numMatchingCoordinates][0] = x2;
    matchingCoordinates[numMatchingCoordinates][1] = y2;
    numMatchingCoordinates++;
}

// Function to display the game board
void displayGameBoard() {
    printBoard();
}

// Function to check if all elements are found
bool allElementsFound() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!visible[i][j])
                return false;
        }
    }
    return true;
}

// Function to print the found numbers
void printFoundNumbers() {
    printf("Found numbers: ");
    for (int i = 0; i < numFound; i++) {
        printf("%d ", foundNumbers[i]);
    }
    printf("\n");
}

int main() {
    initializeBoard();
    displayGameBoard();

    while (!allElementsFound()) {
        printBoard();

        int x, y;
        printf("Enter the coordinates (x, y) of the item you want to reveal (-1 to quit): ");
        scanf("%d %d", &x, &y);

        if (x == -1 || y == -1)
            break;

        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
            printf("Invalid coordinates! Please try again.\n");
            continue;
        }

        if (visible[x][y]) {
            printf("This item is already visible. Please choose another one.\n");
            continue;
        }

        visible[x][y] = true;
        displayGameBoard();

        int a, b;
        printf("Enter the coordinates (x, y) of the second item (-1 to quit): ");
        scanf("%d %d", &a, &b);

        if (a == -1 || b == -1)
            break;

        if (a < 0 || a >= BOARD_SIZE || b < 0 || b >= BOARD_SIZE) {
            printf("Invalid coordinates! Please try again.\n");
            visible[x][y] = false; // Revert the visibility status of the first item
            continue;
        }

        if (visible[a][b]) {
            printf("This item is already visible. Please choose another one.\n");
            visible[x][y] = false; // Revert the visibility status of the first item
            continue;
        }

        visible[a][b] = true;

        if (board[x][y] == board[a][b]) {
            printf("CORRECT GUESS!\n");

            // Add the found numbers to the array
            foundNumbers[numFound++] = board[x][y];
            foundNumbers[numFound++] = board[a][b];
            
            // Print the found numbers on the screen
            printFoundNumbers();

            // Make the matching elements invisible
            visible[x][y] = false;
            visible[a][b] = false;


            // Update visibility status based on matching coordinates
            updateVisibility();
        } 
        else {
            printf("WRONG GUESS! Try again.\n");
            visible[x][y] = false;
            visible[a][b] = false;
        }
        
        totalTries++; 

    }

    printf("Congratulations! You found all matching numbers!\n");
    printf("Total number of tries: %d\n", totalTries);
    return 0;
}
