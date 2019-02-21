# Simple Matrix

Simple Matrix lib for **Programming competency test**

- Supported numerical types (```int```, ```long```, ```float```, ```double```, ```complex```,....)
- Supported algebraic expressions including ```+``` and ```*```, ```+=``` and ```*=```
- fits in one header file
- provides test header in test directory

# How To Compile!
    1. make
    2. ./bin/Simple_Matrix

# Speed Test in milliseconds

#### Addition

| Type       | Shape       | Execution time (in ms)  |Execution time for assignment (in ms) |
| :--------: | :---------: | :-----------------------|:----------------------------------:|
| `int`      | (1000,1000) |0                        |0                                   |
| `complex`  | (1000,1000) | 0                       |54                                   |

#### Subtraction

| Type       | Shape       | Execution time (in ms)  |Execution time for assignment (in ms)  |
| :--------: | :---------: | :-----------------------|:----------------------------------:|
| `int`      | (1000,1000) |0                        |0                                   |
| `complex`  | (1000,1000) |0                        |55                                  |

#### Multiplication

| Type       | Shape       | Execution time (in ms)  |Execution time for assignment (in ms)  |
| :--------: | :---------: | :---------------------: |:----------------------------------:|
| `int`      | (1000,1000) | 0                       |13479                                   |
| `complex`  | (1000,1000) | 0                       |30137                                   |

# System Specs
- OS: MacOS
- Processor: 2.5 GHz Intel Core i7