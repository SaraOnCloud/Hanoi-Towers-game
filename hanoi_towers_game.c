
/**This project implements the classic Tower of Hanoi puzzle in the C programming language. 
However, the code is partially unfinished: your goal is to complete the stack data structure and its core operations (peek, pop, moveDisk, push, isEmpty). 
The remaining logic for displaying the stacks, and the handling input is already provided.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//////////////////////////////////////////////////////
// Data Structures for Stack (using Linked Nodes)
//////////////////////////////////////////////////////

// Node in a singly linked list (each node represents a disk)
typedef struct Node {
    int disk;              // The disk's size (larger number means larger disk)
    struct Node *next;     // Pointer to the next node
} Node;

// Stack structure (each tower is one stack)
typedef struct {
    Node *top;             // Pointer to the top node of the stack
} Stack;

//////////////////////////////////////////////////////
// Prototypes for Stack Operations
//////////////////////////////////////////////////////
void initStack(Stack *s);
bool isEmpty(Stack *s);
void push(Stack *s, int disk);
int  pop(Stack *s);
int  peek(Stack *s);

//////////////////////////////////////////////////////
// Prototypes for Game Control
//////////////////////////////////////////////////////
void printAllTowers(Stack *A, Stack *B, Stack *C);
void printTower(Stack *tower, char name);
bool isValidMove(Stack *from, Stack *to);
bool moveDisk(Stack *from, Stack *to, char fromName, char toName);
bool areAllDisksInOneTower(Stack *X, int n);
void initializeGame(Stack *A, Stack *B, Stack *C, int n);

//////////////////////////////////////////////////////
// MAIN FUNCTION
//////////////////////////////////////////////////////
int main(void) {
    Stack A, B, C;  // Towers
    initStack(&A);
    initStack(&B);
    initStack(&C);

    int n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);

    // Initialize tower A with n disks (largest at the bottom, smallest at the top)
    initializeGame(&A, &B, &C, n);

    // Interactive loop
    char input[10];
    bool quit = false;

    // Print initial state
    printAllTowers(&A, &B, &C);

    // The game continues until user quits or all disks are in one tower
    while (!quit && !areAllDisksInOneTower(&C, n)) {
        printf("Enter your move (e.g., 'A B' to move top disk from Tower A to Tower B), or 'Q' to quit:\n> ");
        scanf("%s", input);

            // If the user typed 'Q' or 'q', we quit
            if (input[0] == 'Q' || input[0] == 'q') {
                quit = true;
                break;
            }
    
            // We expect something like "AB" or "B C" or "C A"
            if (strlen(input) != 2) {
                printf("Invalid command format. Please use two letters like 'AB'.\n");
                continue;
            }

            char fromChar = input[0];
            char toChar   = input[1];

            // Map fromChar and toChar to the actual stacks
            Stack *fromTower = NULL;
            Stack *toTower   = NULL;

            if (fromChar == 'A' || fromChar == 'a') fromTower = &A;
            if (fromChar == 'B' || fromChar == 'b') fromTower = &B;
            if (fromChar == 'C' || fromChar == 'c') fromTower = &C;

            if (toChar == 'A' || toChar == 'a') toTower = &A;
            if (toChar == 'B' || toChar == 'b') toTower = &B;
            if (toChar == 'C' || toChar == 'c') toTower = &C;

            // Check if the user typed something valid
            if (fromTower == NULL || toTower == NULL) {
                printf("Invalid towers. Please type letters from {A, B, C}.\n");
                continue;
            }
            if (fromTower == toTower) {
                printf("Cannot move from and to the same tower.\n");
                continue;
            }

            // Attempt to move
            if (!moveDisk(fromTower, toTower, fromChar, toChar)) {
                printf("Invalid move: you cannot place a bigger disk on a smaller disk.\n");
            }

            // Print state after the move
            printAllTowers(&A, &B, &C);
        }

    if (areAllDisksInOneTower(&C, n)) {
        printf("Congratulations! All disks are in one tower.\n");
    } else {
        printf("You chose to quit the game.\n");
    }
    
    return 0;
}

//////////////////////////////////////////////////////
// Implementation of Stack Operations
// (Using linked nodes with dynamic memory allocation)
//////////////////////////////////////////////////////

// Initialize the stack to be empty
void initStack(Stack *s) {
    s->top = NULL;
}

// Check if the stack is empty
bool isEmpty(Stack *s) {
    return s->top == NULL;
}

// Push a new disk onto the top of the stack
void push(Stack *s, int disk) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        return;
    }
    newNode->disk = disk;
    newNode->next = s->top;
    s->top = newNode;
}

// Pop the top disk from the stack and return its value (-1 if the stack is empty)
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow error\n");
        return -1; // Indicate an error
    }
    Node *temp = s->top;
    int disk = temp->disk;
    s->top = s->top->next;
    free(temp);
    return disk;
}

// Peek the top disk (without removing it)
/**
 * Peek the top disk of the stack without removing it.
 *
 * This function returns the value of the top disk in the stack.
 * If the stack is empty, it returns -1 and prints an error message.
 *
 * @param s The stack to peek.
 * @return The value of the top disk, or -1 if the stack is empty.
 */
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1; // Indicate an error
    }
    return s->top->disk;
}

//////////////////////////////////////////////////////
// Game Control Functions
//////////////////////////////////////////////////////

// Print the state of all towers (A, B, C)
void printAllTowers(Stack *A, Stack *B, Stack *C) {
    printTower(A, 'A');
    printTower(B, 'B');
    printTower(C, 'C');
    printf("------------------------------------------------\n");
}

// Print one tower's contents from top to bottom
void printTower(Stack *tower, char name) {
    printf("Tower %c: ", name);

    if (isEmpty(tower)) {
        printf("[empty]\n");
        return;
    }

    // We have to traverse from top to bottom
    Node *current = tower->top;
    printf("[Top -> ");
    while (current != NULL) {
        printf("%d ", current->disk);
        current = current->next;
    }
    printf("]\n");
}

// Check if moving the top disk from stack 'from' to stack 'to' is valid
bool isValidMove(Stack *from, Stack *to) {
    if (isEmpty(from)) {
        // Can't move from an empty tower
        return false;
    }
    if (isEmpty(to)) {
        // If 'to' is empty, any disk can be placed there
        return true;
    }

    // Otherwise, compare top disks
    int fromTop = peek(from);
    int toTop   = peek(to);
    if (fromTop < toTop) {
        return true;  // It's a valid move if the moving disk is smaller
    }
    return false;      // Invalid if fromTop >= toTop
}


// Move the top disk from one tower to another (if valid)
bool moveDisk(Stack *from, Stack *to, char fromName, char toName) {
    if (!isValidMove(from, to)) {
        return false;
    }
    // Perform the move
    int disk = pop(from);
    push(to, disk);
    printf("Moved disk %d from Tower %c to Tower %c\n", disk, fromName, toName);
    return true;
}

// Check if all disks (n total) are in exactly one tower
// This means either A has n disks, or B has n disks, or C has n disks
bool areAllDisksInOneTower(Stack *X, int n) {
    int countX = 0;
    Node *current;

    current = X->top;
    while (current != NULL) {
        countX++;
        current = current->next;
    }

    // If any tower has exactly n disks, game is "solved" in that sense
    return countX == n;
}

// Put n disks in tower A, largest at the bottom, smallest at the top
void initializeGame(Stack *A, Stack *B, Stack *C, int n) {
    // Clear all towers
    initStack(A);
    initStack(B);
    initStack(C);

    // The largest disk is n, and the smallest is 1
    // We push from largest to smallest so that the top of the stack is the smallest disk
    for (int i = n; i >= 1; i--) {
        push(A, i);
    }
}