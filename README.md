# Binary Multiples of 3 — DFA Lexical Analyzer

A simple lexical analyzer written in C that uses a **Deterministic Finite Automaton (DFA)** to recognize binary strings representing numbers divisible by 3. Implemented two ways: diagram-driven and table-driven.

---

## The DFA

The automaton has three states and operates on the alphabet `{0, 1}`:

```
        ┌───┐
   ┌─0──►   │
   │    │ S0◄──1──┐
   └────┤   │     │
        └─┬─┘     │
          │ 1     │
          ▼       │
        ┌───┐   ┌───┐
        │ S1├─0─► S2│
        │   ◄─0─┤   │
        └───┘   └─┬─┘
                  │
                  └─1──┐
                        │
                  ┌─────┘
                  ▼
                (self)
```

| State | On `0` | On `1` | Role |
|-------|--------|--------|------|
| **S0** | S0 | S1 | Start & Accept |
| **S1** | S2 | S0 | — |
| **S2** | S1 | S2 | — |

- **Start state**: S0  
- **Accepting state**: S0 (the number's remainder mod 3 equals 0)
- Any non-binary character (`a`–`z`, `2`–`9`, etc.) causes immediate rejection

---

## Why does this work?

Each state tracks the **remainder** of the current binary number when divided by 3:

- **S0** → remainder = 0
- **S1** → remainder = 1  
- **S2** → remainder = 2

Reading a new bit `b` appends it to the number, which doubles the value and adds `b`. In modular arithmetic: `new_remainder = (2 * old_remainder + b) mod 3`. The transition table encodes exactly this.

---

## Implementations

### Task 1 — Diagram-Driven (`main_Diagram_Driven.c`)

States and transitions are **explicitly coded** using an `enum` and a `switch` statement — mirroring the DFA diagram directly in code.

```c
enum State {S0, S1, S2} state = S0;

switch (state) {
    case S0: state = (ch == '1') ? S1 : S0; break;
    case S1: state = (ch == '1') ? S0 : S2; break;
    case S2: state = (ch == '1') ? S2 : S1; break;
}
```

### Task 2 — Table-Driven (`main_Table_Driven.c`)

The transition function is stored as a **2D array**. The next state is found by a simple lookup — no conditional branching on states.

```c
int table[3][2] = {
    {0, 1},  // S0: '0'->S0, '1'->S1
    {2, 0},  // S1: '0'->S2, '1'->S0
    {1, 2}   // S2: '0'->S1, '1'->S2
};

state = table[state][symbol]; // single lookup replaces all switch logic
```

The table-driven approach scales better — to support a new DFA, you only change the table data, not the program logic.

---

## Usage

### Compile

```bash
gcc main_Diagram_Driven.c -o diagram_driven
gcc main_Table_Driven.c   -o table_driven
```

### Run

```bash
./diagram_driven
# Enter input: 1001
# String Accepted

./table_driven
# Enter input: 101
# String Rejected
```

### Sample Inputs

| Input | Value | Div by 3? | Result |
|-------|-------|-----------|--------|
| `0` | 0 | ✅ | Accepted |
| `11` | 3 | ✅ | Accepted |
| `110` | 6 | ✅ | Accepted |
| `1001` | 9 | ✅ | Accepted |
| `1` | 1 | ❌ | Rejected |
| `10` | 2 | ❌ | Rejected |
| `1a0` | — | ❌ | Rejected (invalid symbol) |

---

## Project Structure

```
.
├── main_Diagram_Driven.c   # Task 1: switch-based DFA
├── main_Table_Driven.c     # Task 2: table-lookup DFA
└── README.md
```

---

## Language & Requirements

- **Language**: C (C99 or later)
- **Compiler**: GCC, Clang, or MSVC
- **Dependencies**: None (standard library only)
