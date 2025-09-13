# 3-CNFy: CNF to 3-CNF Encoder

**3-CNFy** is a command-line tool for converting general CNF (Conjunctive Normal Form) formulas into equivalent 3-CNF formulas. This is useful for SAT solvers and research in computational complexity, where in some cases formulas with exactly three literals per clause are required.

## Features

- Converts any CNF file to 3-CNF format (CNF file with clauses of exactly 3 literals)
- Handles (non-empty) clauses of any length.
- Reports statistics: number of clauses, auxiliary variables, average clause size, etc.

## Usage

### Build

To build the project, run:

```sh
make
```

### Run

To encode a CNF file:

```sh
./build/encoder3 <input_cnf_file> [output_cnf3_file]
```

- If `output_cnf3_file` is not specified, the default is `cnf3.cnf`.

Example:

```sh
./build/encoder3 test.cnf result.cnf
```

#### File Format

- **Input:** Standard DIMACS CNF format (each clause on a line, literals separated by spaces, ending with `0`)
- **Output:** 3-CNF in DIMACS format

### Test

To run all unit tests:

```sh
make run-tests
```

## Output

After running, you will see a summary table like:

```
------------------------------
Result                              Value
-----------------------------------------------
Output written to:             result.cnf
Original number of clauses:          100
Average original clause size:        4.2
Number of clauses generated:         180
Auxiliary variables introduced:      80
Maximal auxiliary variable used:     180
-----------------------------------------------
```

## Development

- C++23
- Google Test for unit testing
- See `Makefile` for build and test automation
