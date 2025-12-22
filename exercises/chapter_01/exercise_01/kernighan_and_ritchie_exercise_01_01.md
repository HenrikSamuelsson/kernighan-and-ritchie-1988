# K&R Exercise 1.1

Solution to Exercise 1.1 from Kernighan and Ritchie (1988).

## Instruction

Compile and run a minimal "Hello world!" program written in C. After the program
successfully runs, intentionally introduce errors and observe the resulting
compiler diagnostics.

## Solution

There is an example program in the book but I implemented my own version of the program, using a slightly more modern style than the example shown in the book.

### Functional Version

<https://github.com/HenrikSamuelsson/kernighan-and-ritchie-1988/blob/46923bee0f96c26223326544df26b576ef843317/exercises/chapter_01/exercise_01/main.c#L1-L8>

This version compiles and runs as expected.

```powershell
> gcc -std=c11 -Wall -Wextra -Wpedantic main.c
PS C:\dev\kernighan-and-ritchie-1988\exercises\chapter_01\exercise_01> ./a.exe
Hello, world!
```

### Missing Semicolon

<https://github.com/HenrikSamuelsson/kernighan-and-ritchie-1988/blob/d217fa057e18fa36969fdc8c02687803b5231fdb/exercises/chapter_01/exercise_01/main_missing_semicolon.c#L1-L8>

```powershell
> gcc -std=c11 -Wall -Wextra -Wpedantic .\main_missing_semicolon.c
.\main_missing_semicolon.c: In function 'main':
.\main_missing_semicolon.c:8:1: error: expected ';' before '}' token
    8 | }
      | ^
```

## Answer

## References

Kernighan, B. W., & Ritchie, D. M. (1988). *The C programming language* (2nd ed.). Prentice Hall.
