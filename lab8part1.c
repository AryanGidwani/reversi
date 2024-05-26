//
// Author: Aryan Gidwani
//
#include "lab8part1.h"
#include <stdio.h>
#include <stdlib.h>
char board[26][26]; // static memory, initialized outside of main
int direction[][2] = {{1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}};

// computer validity
void computerValid(char board[][26], int n, char answerOne, char answerTwo, char answerThree) {
    bool checkMove;
    int rowIndex, colIndex, rIndex, cIndex;
    int count = 0;
    rowIndex = answerTwo - 'a';
    colIndex = answerThree - 'a';
    // using direction and row index and col index, we should be able to trace back using a while loop and replace all colours
    if (board[rowIndex][colIndex] == 'U') {
        for (int dir = 0; dir < 8; dir ++) {
            rIndex = rowIndex;
            cIndex = colIndex;
            checkMove = checkLegalInDirection(board, n, rowIndex, colIndex, answerOne, direction[dir][0], direction[dir][1]);
            if (checkMove == true) {
                count++;
                while (true) {
                    rIndex += direction[dir][0];
                    cIndex += direction[dir][1];
                    if (board[rIndex][cIndex] != answerOne) {
                        board[rIndex][cIndex] = answerOne;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
    
    if (count == 0) {
        printf("%c player has no valid move.\n", answerOne);
    }

    else {
        board[rowIndex][colIndex] = answerOne;
        printf("Computer places %c at %c%c.\n", answerOne, answerTwo, answerThree);
        printBoard(board, n);
    }

}

// user validity
void userValid(char board[][26], int n, char answerOne, char answerTwo, char answerThree) {
    char letter;
    bool checkMove;
    int rowIndex, colIndex, rIndex, cIndex;
    int count = 0;
    rowIndex = answerTwo - 'a';
    colIndex = answerThree - 'a';
    // using direction and row index and col index, we should be able to trace back using a while loop and replace all colours
    if (board[rowIndex][colIndex] == 'U') {
        for (int dir = 0; dir < 8; dir ++) {
            rIndex = rowIndex;
            cIndex = colIndex;
            checkMove = checkLegalInDirection(board, n, rowIndex, colIndex, answerOne, direction[dir][0], direction[dir][1]);
            if (checkMove == true) {
                count++;
                while (true) {
                    rIndex += direction[dir][0];
                    cIndex += direction[dir][1];
                    if (board[rIndex][cIndex] != answerOne) {
                        board[rIndex][cIndex] = answerOne;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
    
    if (count == 0) {
        if (answerOne == 'B') {
            letter = 'W';
        }

        else {
            letter = 'B';
        }

        printf("Invalid move. \n");
        printf("%c player wins. ", letter);
    }

    else {
        board[rowIndex][colIndex] = answerOne;
        printBoard(board, n);
    }

}


void fillBoard(char board[][26], int n) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            board[row][col] = 'U';
        }
    }
    board[n/2][n/2] = 'W';
    board[n/2][(n/2)-1] = 'B';
    board[(n/2)-1][(n/2)-1] = 'W';
    board[(n/2)-1][n/2] = 'B';
}

void printBoard(char board[][26], int n) {
    printf("   ");
    for (int i = 0; i < n; i++) {
        printf("%c", 'a'+(i));
    }
    printf("\n");
    for (int row = 0; row < n; row++) {
        printf("%c", 'a'+(row));
        printf("  ");
        for(int col = 0; col < n; col++) { 
            printf("%c", board[row][col]); // prints out each element of the board: assume n < 26 and is even
        }
        printf("\n");
    }
}
bool positionInBounds(int n, int row, int col) {
    return ((0 <= row && row < n) && (0 <= col && col < n));
    
}
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    // checks each direction numerous times
    int count = 0;
    bool legality = true;
    if (board[row][col] != 'U') {
        return false;
    }

    if (colour == 'W') {
        while(legality) {
            row += deltaRow;
            col += deltaCol;
            if (positionInBounds(n, row, col) && board[row][col] == 'B') { // reads first condition and exits completely
                count += 1;
            }

            else {
                legality = false;
            }
        }
        if ((positionInBounds(n, row, col)) && (count > 0) && (board[row][col] == colour)) {
            return true;
        }

        else {
            legality = false;
            return legality;
        }

    }
    else if (colour == 'B'){
        while(legality) {
            row += deltaRow;
            col += deltaCol;
            if (positionInBounds(n, row, col) && board[row][col] == 'W') {
                count += 1;
            }

            else {
                legality = false;
            }
        }
        if ((positionInBounds(n, row, col)) && (count > 0) && (board[row][col] == colour)) {
            return true;
        }

        else {
            legality = false;
            return legality;
        }
    }
}

bool userMove(char board[][26], int n, char userColour, char computerColour) {
    int rowIndex, colIndex, legalSquares = 0, rIndex, cIndex;
    char firstLetter, secondLetter;
    // first see if theres any legal moves, before asking for user input: should return true based on the message printed
    for (int row =  0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (board[row][col] == 'U') {
                for (int dir = 0; dir < 8; dir ++) {
                    if (checkLegalInDirection(board, n, row, col, userColour, direction[dir][0], direction[dir][1])) {
                        //printf("%d%d", row, col);
                        legalSquares += 1; // number of times direction is satisfied, not number
                        break;
                        
                    }
                }

            }
            
        }
    }
    
    if (legalSquares == 0) {
        printf("%c player has no valid move. \n", userColour);
        return true;

    }

    printf("Enter move for colour %c (RowCol): ", userColour);
    scanf(" %c%c", &firstLetter, &secondLetter);
    // is it invalid input? if invalid, return false
    rowIndex = firstLetter - 'a';
    colIndex = secondLetter - 'a';
    bool check = true;
    
    if (positionInBounds(n, rowIndex, colIndex) == false) {
        check = false; // returns false when it realizes its a completely invalid input
    }

    else {
        for (int dir = 0; dir < 8; dir++) {
            if (checkLegalInDirection(board, n, rowIndex, colIndex, userColour, direction[dir][0], direction[dir][1]) == false) {
                check = false;
            }   

            else {
                check = true;
                break;
            }
        }
    }
    
    if ((check == true) && positionInBounds(n, rowIndex, colIndex)) {
        if (board[rowIndex][colIndex] == 'U') {
            check = true;
            userValid(board, n, userColour, firstLetter, secondLetter);

        }
    }
    // return true
    return check;
}

void computerMove(char board[][26], int n, char userColour, char computerColour) {
    int tiles, tempTiles;
    int currentAmount = 0;
    int idealRow, idealCol, row, col;
    char firstLetter, secondLetter;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'U') {
                tiles = 0; // resets once 
                for (int dir = 0; dir < 8; dir++) {
                    row = i; // variables used so the values of i and j don't change
                    col = j;
                    if ((checkLegalInDirection(board, n, i, j, computerColour, direction[dir][0], direction[dir][1]))) {
                        tempTiles = tiles;
                        while (true) { // cant be either 'U' and has to check if computerColour ever appears
                            row += direction[dir][0];
                            col += direction[dir][1];
                            if ((board[row][col] == userColour)) {
                                if (positionInBounds(n, row, col)) {
                                    //board[i][j] = computerColour;
                                    tiles+=1; // increments number of tiles flipped on that square`` keeps on adding before it reaches if statement; hence incorrect
                                }
                            }

                            else if ((board[row][col] == computerColour) && (tiles >= 1) && (positionInBounds(n, row, col))) {
                                break;
                            }

                            else if(board[row][col] == 'U') {
                                tiles = tempTiles;
                                break;
                            }

                            else {
                                break;
                            }
                        }

                    }
                if (tiles > currentAmount) {
                    currentAmount = tiles; // stores the number of tiles in the variable that will help the computer decide what move to play, based off score
                    idealRow = i;
                    idealCol = j; // idealRow and idealCol should store the final row and final column
                    //printf("%d%d", idealRow, idealCol);
                }
            }
            }
        }
    }
    //printf("%d%d", idealRow, idealCol);
    firstLetter = idealRow + 'a';
    secondLetter = idealCol + 'a';
 
    //printf("Computer places %c at %c%c\n", computerColour, firstLetter, secondLetter);
    computerValid(board, n, computerColour, firstLetter, secondLetter); 
}

bool gameOver(char board[][26], int n, char computerColour, char userColour) {
    int counter = 0, computer = 0,  user = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'U') {
                counter++;
            }

            else if(board[i][j] == computerColour) {
                computer+=1;
            }

            else {
                user+=1;
            }
        }
    }
    if (counter == 0) {
        if (computer > user) {
            printf("%c player wins.", computerColour);
            printf("\n");
            return false;

        }

        else if (user > computer) {
            printf("%c player wins.", userColour);
            printf("\n");
            return false;
        }

        else {
            printf("Its a tie!??");
            return false;
        }
    }
}

int main(void) {
    int n, rowIndex, colIndex, count;
    char firstLetter, secondLetter, thirdLetter, computerColour, userColour;
    char answerOne, answerTwo, answerThree;
    printf("Enter the board dimension: "); // asks the user to input size of board
    scanf(" %d", &n);
    printf("Computer plays (B/W): ");
    scanf(" %c", &computerColour);
    if (computerColour == 'W') {
        userColour = 'B';
        count = 0;
    }

    else {
        userColour = 'W';
        count = 1;
    }
    fillBoard(board, n);
    printBoard(board, n); // calls printBoard function
    while (gameOver(board, n, computerColour, userColour)) {
        if (count % 2 == 0) {
            //userMove(board, n, userColour, computerColour);
            if (userMove(board, n, userColour, computerColour) == false) {
                printf("Invalid move. \n");
                printf("%c player wins.", computerColour);
                break;
            }
        }
                
        else {
            computerMove(board, n, userColour, computerColour);
        }
        count++;  
        }
    return 0;   
    }

