# Compiler Design Lab

C++ implementations of the experiments from my **Compiler Design Laboratory** course. The programs cover the front-end of a compiler — lexical analysis (character/word counting, comment detection, identifier validation, operator recognition, NFA/DFA-based tokenizing) and parsing preliminaries (left factoring, left-recursion elimination, and FIRST/FOLLOW set computation).

All programs are written in standard C++ and compiled with `g++`. Programs that process source text read from a per-experiment `inputN.txt` file in the working directory; the two grammar-transformation programs (11 and 14) read the grammar interactively from standard input.

## Experiments

| #  | Experiment | Source | Input |
|----|------------|--------|-------|
| 1  | Importance and rationale of the Compiler Design Laboratory (theory) | — | — |
| 2  | Count characters, words, and lines in a file | [2_count_char_word_line.cpp](2_count_char_word_line.cpp) | `input.txt` |
| 3  | Identify whether a line is a comment (single-line / multi-line / inline) | [3_identify_comment.cpp](3_identify_comment.cpp) | `input2.txt` |
| 4  | Test whether an identifier is valid | [4_valid_identifier.cpp](4_valid_identifier.cpp) | `input3.txt` |
| 5  | Recognize strings under the patterns `a`, `a*b+`, and `abb` | [5_pattern_match.cpp](5_pattern_match.cpp) | `input7.txt` |
| 6  | Lexical analyzer for validating operators | [6_validating_operators.cpp](6_validating_operators.cpp) | `input5.txt` |
| 7  | Count the number of operators in a string | [7_count_operator.cpp](7_count_operator.cpp) | `input4.txt` |
| 8  | NFA that recognizes identifiers | [8_NFA.cpp](8_NFA.cpp) | `input8.txt` |
| 9  | DFA that recognizes identifiers, constants, and operators | [9_DFA.cpp](9_DFA.cpp) | `input9.txt` |
| 10 | Lexical analyzer that ignores spaces, tabs, newlines, and comments | [10_ignore_space_tab.cpp](10_ignore_space_tab.cpp) | `input10.txt` |
| 11 | Left factoring of a grammar | [11_left_factoring.cpp](11_left_factoring.cpp) | interactive (stdin) |
| 12 | Compute FIRST sets of a grammar | [12_find_FIRST_values.cpp](12_find_FIRST_values.cpp) | `input12.txt` |
| 13 | Compute FOLLOW sets of a grammar | [13_find_FOLLOW_values.cpp](13_find_FOLLOW_values.cpp) | `input13.txt` |
| 14 | Eliminate left recursion from a grammar | [14_left_recursion.cpp](14_left_recursion.cpp) | interactive (stdin) |

## Building and Running

Any program can be compiled directly with `g++` (C++11 or later):

```bash
g++ 12_find_FIRST_values.cpp -o 12_find_FIRST_values
./12_find_FIRST_values
```

For the file-driven programs, make sure the matching `inputN.txt` is present in the current directory (see the table above), then just run the executable — it reads the file and prints the result.

The interactive programs (11 and 14) prompt for the grammar. For example, eliminating left recursion from `E -> E + T | T`:

```
Enter number of alternatives: 2
Enter production head: E
Enter 2 alternatives:
Alternative 1: E+T
Alternative 2: T

Left Recursion Removal Result:
E --> TE'
E' --> +TE' | e
```

### Grammar format (programs 12 & 13)

The FIRST/FOLLOW programs read productions from a text file, one head per line, using `->` for the arrow, `|` to separate alternatives, and `e` for ε. Symbols are space-separated, and a symbol starting with an uppercase letter is treated as a non-terminal:

```
E  -> T E'
E' -> + T E' | e
T  -> F T'
T' -> * F T' | e
F  -> ( E ) | id
```

## Repository Structure

```
├── 2_count_char_word_line.cpp   … 14_left_recursion.cpp   # experiment sources
├── input*.txt                                             # sample inputs
├── List.txt                                               # course experiment list
└── README.md
```

## Notes

- Built and tested with `g++` on Windows; the code is standard C++ and portable to Linux/macOS.
- Experiment numbering follows the course list in [List.txt](List.txt) (experiment 1 is a written/theory task, so there is no source file for it).
