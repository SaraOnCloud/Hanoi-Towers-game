# Tower of Hanoi Game

This project implements the classic Tower of Hanoi puzzle in the C programming language. The goal is to complete the stack data structure and its core operations (`peek`, `pop`, `moveDisk`, `push`, `isEmpty`). The remaining logic for displaying the stacks and handling input is already provided.

## Table of Contents

- [Introduction](#introduction)
- [Data Structures](#data-structures)
- [Stack Operations](#stack-operations)
- [Game Control Functions](#game-control-functions)
- [How to Compile and Run](#how-to-compile-and-run)
- [How to Play](#how-to-play)
- [License](#license)

## Introduction

The Tower of Hanoi is a mathematical puzzle where the objective is to move a stack of disks from one tower to another, following specific rules:
1. Only one disk can be moved at a time.
2. Each move consists of taking the top disk from one of the stacks and placing it on top of another stack.
3. No disk may be placed on top of a smaller disk.

## Data Structures

### Node

Each node in the singly linked list represents a disk.

```c
typedef struct Node {
    int disk;              // The disk's size (larger number means larger disk)
    struct Node *next;     // Pointer to the next node
} Node;
```

### Stack

Each tower is represented as a stack.

```c
typedef struct {
    Node *top;             // Pointer to the top node of the stack
} Stack;
```

## Stack Operations

- `void initStack(Stack *s);`
- `bool isEmpty(Stack *s);`
- `void push(Stack *s, int disk);`
- `int pop(Stack *s);`
- `int peek(Stack *s);`

## Game Control Functions

- `void printAllTowers(Stack *A, Stack *B, Stack *C);`
- `void printTower(Stack *tower, char name);`
- `bool isValidMove(Stack *from, Stack *to);`
- `bool moveDisk(Stack *from, Stack *to, char fromName, char toName);`
- `bool areAllDisksInOneTower(Stack *X, int n);`
- `void initializeGame(Stack *A, Stack *B, Stack *C, int n);`

## How to Compile and Run

1. Open a terminal and navigate to the project directory.
2. Compile the code using `gcc`:

    ```sh
    gcc hanoi_towers_game.c -o hanoi_towers_game
    ```

3. Run the executable:

    ```sh
    ./hanoi_towers_game
    ```

## How to Play

1. Enter the number of disks when prompted.
2. The game will display the initial state of the towers.
3. Enter your moves in the format `A B` to move the top disk from Tower A to Tower B.
4. The game continues until all disks are in one tower or you choose to quit by entering `Q`.



