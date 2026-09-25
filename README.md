# Compiler Design Lab

C++ implementations of the experiments from my **Compiler Design Laboratory** course. The programs cover the front-end of a compiler — lexical analysis (character/word counting, comment detection, identifier validation, operator recognition, NFA/DFA-based tokenizing) and parsing preliminaries (left factoring, left-recursion elimination, and FIRST/FOLLOW set computation).

All programs are written in standard C++ and compiled with `g++`. Programs that process source text read from a per-experiment `inputN.txt` file in the working directory. Experiments 11 and 14 read `input11.txt` and `input14.txt`; experiment 15 reads a grammar file plus an interactive target string.

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
| 11 | Left factoring of a grammar | [11_left_factoring.cpp](11_left_factoring.cpp) | `input11.txt` |
| 12 | Compute FIRST sets of a grammar | [12_find_FIRST_values.cpp](12_find_FIRST_values.cpp) | `input12.txt` |
| 13 | Compute FOLLOW sets of a grammar | [13_find_FOLLOW_values.cpp](13_find_FOLLOW_values.cpp) | `input13.txt` |
| 14 | Eliminate direct left recursion from a grammar | [14_left_recursion.cpp](14_left_recursion.cpp) | `input14.txt` |
| 15 | Perform leftmost derivation for a target string | [15_leftmost_derivation.cpp](15_leftmost_derivation.cpp) | `input15.txt` + target from stdin |

## Building and Running

Any program can be compiled directly with `g++` (C++11 or later):

```bash
g++ 12_find_FIRST_values.cpp -o 12_find_FIRST_values
./12_find_FIRST_values
```

For the file-driven programs, make sure the matching `inputN.txt` is present in the current directory (see the table above), then just run the executable — it reads the file and prints the result.

Experiment 11 reads one production per line from `input11.txt`. Use single uppercase
letters for input non-terminals, with all alternatives for a head on one line.
Spaces and tabs are ignored. Use `e` alone for epsilon (`eS` still contains the
terminal `e`). Alternatives sharing a prefix are grouped and factored; unrelated
alternatives remain. New rules are factored again when needed.

Example input:

```
S -> iEtS | iEtSeS | a
E-> b
```

Output (`e` alone means epsilon):

```
S -> iEtSS' | a
S' -> e | eS
E -> b
```

Experiment 14 reads one production per line
from `input14.txt`, with `|` separating alternatives and `e` representing epsilon.
Spaces and tabs are ignored. For this introductory implementation, input
non-terminals are single uppercase letters without apostrophes. Put all
alternatives for each head on one line. It removes direct
left recursion; indirect recursion through other non-terminals is not eliminated.
For example:

```
A -> Aabb | BC
B-> Bca | C
```

Output:

```
Direct Left Recursion Removal Result:
A -> BCA'
A' -> abbA' | e
B -> CB'
B' -> caB' | e
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

Experiment 15 reads productions from `input15.txt` in the same space-separated
format as experiments 12 and 13. The first production head is the start symbol;
symbols appearing as production heads are non-terminals. Enter a target such as
`id + id * id` at the prompt, or `e` for the empty string. The program prints a
derivation that replaces the leftmost non-terminal at every step. A recursive
function tries each alternative and backtracks when a choice fails. Simple
vectors store the production heads, rules, and derivation steps. It searches
up to 10,000 expansions and 100 production steps along a path; if either limit prevents
a conclusion, it reports that the search was inconclusive.

```
├── 2_count_char_word_line.cpp   … 14_left_recursion.cpp   # experiment sources
├── input*.txt                                             # sample inputs
├── List.txt                                               # course experiment list
└── README.md
```

## Notes

- Built and tested with `g++` on Windows; the code is standard C++ and portable to Linux/macOS.
- Experiment numbering follows the course list in [List.txt](List.txt) (experiment 1 is a written/theory task, so there is no source file for it).
