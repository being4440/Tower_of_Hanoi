# Tower_of_Hanoi
The Tower of Hanoi is a mathematical puzzle:

You have 3 rods and n disks of different sizes.

Rules:
Only one disk can be moved at a time.

A move consists of taking the top disk from one rod and placing it on another rod.

No larger disk can be placed on top of a smaller disk.

The minimum number of moves required = 2ⁿ − 1.
---
## Versions

- [Console (C only)](https://github.com/being4440/Tower_of_Hanoi/tree/hanoi_terminal)
- [WebAssembly + HTML](https://github.com/being4440/Tower_of_Hanoi/tree/hanoi_web)
---
## Concepts Used

Recursion: Function calls itself to solve smaller subproblems.
Divide & Conquer: Breaks problem into moving n-1 disks.

It demonstrates the use of recursion and stack-like logic (without explicit push/pop) to solve the classical problem.
This program prints each move step-by-step in the terminal.

---

## Features

Console-based, no external libraries required.

User can specify the number of disks.

Displays each move in proper order.

Demonstrates recursive problem-solving using C.

---
##  Compile and Run
Use GCC (or any C compiler):

gcc hanoi.c -o hanoi

./hanoi
