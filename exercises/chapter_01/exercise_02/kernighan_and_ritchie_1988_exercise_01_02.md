# K&R Exercise 1.2

Solution to Exercise 1.2 from Kernighan and Ritchie (1988).

## Instruction

Experiment to find out what happens when `printf`'s argument string contains `\c`, where `c` is a character not listed as an escape sequence in the sections preceding this exercise.

## Solution

The escape sequences `\n` for new line, `-t` for tab, `\b` for backspace, `\"` for the double quote, and `\\` for the backslash itself are all mentioned in the book right before this exercise. All official escape sequences are listed in the ISO standards. For example in ISO (2011, § 5.2.2) we find additional escape sequences such as `\a` for audible or visible alert, and `\v` for vertical tab, among others. A given compiler can also support such as `\e` to mimic a press on the escape key.

The following program will test some different escape sequences including a test for what happens when including an experiment with a made-up `\z` escape sequence that is neither covered by the ISO (2011) nor a compiler extension.

<https://github.com/HenrikSamuelsson/kernighan-and-ritchie-1988/blob/460eff641b5e50ec475000bf53edf185736859b4/exercises/chapter_01/exercise_02/main.c#L1-L15>

## Answer

Experiment with some escape sequences showed that in a Windows 11 Command Prompt environment the following will occur:

- `\a` causes an sound effect being played vie the OS audio stack
- `\v` causes a vertical tab, which manifests as a normal line break, moving the cursor down to the start of the next line.
- Undefined escape sequences such as `\z` Undefined result in a diagnostic warning and are interpreted as the escaped character being printed.

## References

International Organization for Standardization. (2011). Programming languages — C (ISO/IEC 9899:2011, Committee Draft N1570). ISO/IEC JTC 1/SC 22/WG 14.

Kernighan, B. W., & Ritchie, D. M. (1988). *The C programming language* (2nd ed.). Prentice Hall.

GNU Project. (n.d.). Character escapes (Using the GNU Compiler Collection).
<https://gcc.gnu.org/onlinedocs/gcc/Character-Escapes.html>
