# K&R (2nd ed.) – The C Programming Language

This repository contains my notes, exercises, and small programs created while
working through *The C Programming Language* (2nd edition) by Kernighan and
Ritchie.

## Structure

- `notes/`  
  Chapter notes and summaries.

- `exercises/`  
  Exercise solutions, organized by chapter.

- `programs/`  
  Standalone programs and experiments.

- `tooling/`  
  Build/run helpers (Makefiles, scripts, formatting config), if needed.

## Build and run

Most examples are intended to be built with a standard C toolchain.

Example (GCC/Clang):

- Build: `cc -Wall -Wextra -Wpedantic -O2 -std=c11 file.c -o file`
- Run: `./file`

If a folder has its own `Makefile`, prefer:

- `make`
- `make clean`

## References

Kernighan, B. W., & Ritchie, D. M. (1988). *The C programming language* (2nd ed.).
Prentice Hall.
