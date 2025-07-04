# 项目简介

这是一个用于处理命题逻辑公式的项目，包含了真值表生成、最小析取范式（DNF）和最大合取范式（CNF）的计算、输入真值表生成对应命题公式，一组子句的归结推理以及王浩算法等功能。

## 目录结构

```
Homework/                           # 项目根目录
│   ├── src/                        # 源代码目录
│   │   ├── PropositionalFormula.h  # 命题公式类及其相关操作
│   │   ├── TruthTable.h            # 真值表类定义
│   │   ├── TruthTable.cpp          # 真值表相关功能实现
│   │   ├── DeductiveReasoning.h    # 归结推理相关类定义
│   │   ├── DeductiveReasoning.cpp  # 归结推理功能实现
│   │   ├── WangHaoAlgorithm.h      # 王浩算法相关类定义
│   │   ├── WangHaoAlgorithm.cpp    # 王浩算法功能实现
│   ├── bin/                                 # 编译生成的可执行文件目录
│   │   ├── task1_truth_table.exe            # 任务1：生成真值表的可执行文件
│   │   ├── task2_dnf_cnf.exe                # 任务2：计算最小析取范式和最大合取范式的可执行文件
│   │   ├── task3_truth_table_to_formula.exe # 任务3：从真值表生成命题公式的可执行文件
│   │   ├── task4_deductive_reasoning.exe    # 任务4：归结推理的可执行文件
│   │   ├── task5_wanghao_algorithm.exe      # 任务5：王浩算法的可执行文件
│   ├── doc/                        # 文档目录
│   │   ├── README.md               # 项目说明文档

```

## 文件说明

- `PropositionalFormula.h`：定义了命题公式类及其相关操作。
- `TruthTable.h`：定义了真值表类，用于计算命题公式的真值表。
- `TruthTable.cpp`：提供函数入口，实现了第一个任务所要求的三项具体功能。
- `DeductiveReasoning.h`：定义了归结推理相关的类。
- `DeductiveReasoning.cpp`：提供函数入口，实现了归结推理的具体功能。
- `WangHaoAlgorithm.h`：定义了王浩算法相关的类。
- `WangHaoAlgorithm.cpp`：提供函数入口，实现了王浩算法的具体功能。
- `Makefile`：定义了项目的编译规则。

## 功能说明

### 真值表生成

输入命题公式，可以进行适度的语法检查。对合法的公式，生成对应的真值表，并输出结果。

### 最小析取范式（DNF）和最大合取范式（CNF）

输入命题公式，同样进行适度的语法检查。对合法的公式，计算并输出命题公式的最小析取范式和最大合取范式。

### 由真值表生成命题公式

先输入变量的个数，变量的名称；接下来按照从小到大的顺序，输入真值表的各个取值。确认后，计算并输出命题公式（以析取范式的格式输出）

### 归结推理

输入一组子句，对每个子句进行析取范式的语法检查。对合法的一组析取子句，进行归结推理，判断结论的真假。

### 王浩算法

输入前提和结论，使用王浩算法进行定理证明。

## 使用说明

### 编译项目

在项目根目录下运行以下命令编译项目：

```sh
make all
```

### 运行程序

根据需要运行不同的任务：

- 生成真值表：

```sh
make task1
./main
```

- 计算最小析取范式和最大合取范式：

```sh
make task2
./main
```

- 从真值表生成命题公式：

```sh
make task3
./main
```

- 归结推理：

```sh
make task4
./main
```

- 王浩算法：

```sh
make task5
./main
```

### 清理编译文件

运行以下命令清理编译生成的文件：

```sh
make clean
```

## 输入输出样例

### 真值表生成

```
Please input a proposition formula:
!(A&(B^(C|D)))~(A1&B1)
Truth table:
A       B       C       D       A1      B1      Result
0       0       0       0       0       0       0
0       0       0       0       0       1       0
0       0       0       0       1       0       0
0       0       0       0       1       1       1
0       0       0       1       0       0       0
0       0       0       1       0       1       0
0       0       0       1       1       0       0
0       0       0       1       1       1       1
0       0       1       0       0       0       0
0       0       1       0       0       1       0
0       0       1       0       1       0       0
0       0       1       0       1       1       1
0       0       1       1       0       0       0
0       0       1       1       0       1       0
0       0       1       1       1       0       0
0       0       1       1       1       1       1
0       1       0       0       0       0       0
0       1       0       0       0       1       0
0       1       0       0       1       0       0
0       1       0       0       1       1       1
0       1       0       1       0       0       0
0       1       0       1       0       1       0
0       1       0       1       1       0       0
0       1       0       1       1       1       1
0       1       1       0       0       0       0
0       1       1       0       0       1       0
0       1       1       0       1       0       0
0       1       1       0       1       1       1
0       1       1       1       0       0       0
0       1       1       1       0       1       0
0       1       1       1       1       0       0
0       1       1       1       1       1       1
1       0       0       0       0       0       1
1       0       0       0       0       1       1
1       0       0       0       1       0       1
1       0       0       0       1       1       0
1       0       0       1       0       0       1
1       0       0       1       0       1       1
1       0       0       1       1       0       1
1       0       0       1       1       1       0
1       0       1       0       0       0       1
1       0       1       0       0       1       1
1       0       1       0       1       0       1
1       0       1       0       1       1       0
1       0       1       1       0       0       1
1       0       1       1       0       1       1
1       0       1       1       1       0       1
1       0       1       1       1       1       0
1       1       0       0       0       0       0
1       1       0       0       0       1       0
1       1       0       0       1       0       0
1       1       0       0       1       1       1
1       1       0       1       0       0       1
1       1       0       1       0       1       1
1       1       0       1       1       0       1
1       1       0       1       1       1       0
1       1       1       0       0       0       1
1       1       1       0       0       1       1
1       1       1       0       1       0       1
1       1       1       0       1       1       0
1       1       1       1       0       0       1
1       1       1       1       0       1       1
1       1       1       1       1       0       1
1       1       1       1       1       1       0
```

### 最小析取范式（DNF）和最大合取范式（CNF）

```
((A&B)|C)^(D&!E)
Minimum DNF: m(0, 1, 2, 3, 6, 8, 9, 10, 11, 14, 16, 17, 18, 19, 22, 26, 30)
Maximum CNF: M(4, 5, 7, 12, 13, 15, 20, 21, 23, 24, 25, 27, 28, 29, 31)
```

### 由真值表生成命题公式

```
Please input the number of variables:
4
Please input the variables:
A B P Q
Plese input the values of the truth table in order:
(1 means true, 0 means false.)
1 0 0 1 0 1 0 0 1 0 1 0 1 1 1 1 
Your input truth table is:
A       B       P       Q       Result
0       0       0       0       1
0       0       0       1       0
0       0       1       0       0
0       0       1       1       1
0       1       0       0       0
0       1       0       1       1
0       1       1       0       0
0       1       1       1       0
1       0       0       0       1
1       0       0       1       0
1       0       1       0       1
1       0       1       1       0
1       1       0       0       1
1       1       0       1       1
1       1       1       0       1
1       1       1       1       1
Is the truth table correct? (1 for yes, 0 for no)
1
The formula is: (!A&!B&!P&!Q)|(!A&!B&P&Q)|(!A&B&!P&Q)|(A&!B&!P&!Q)|(A&!B&P&!Q)|(A&B&!P&!Q)|(A&B&!P&Q)|(A&B&P&!Q)|(A&B&P&Q)
```

### 归结推理

- 归结推理正确：
    ```
    Please input the set of clauses:
    Please input the number of clauses first:
    7
    Please input the set of clauses:
    (A|B|D)
    (!A|C)
    (!B|C|D)
    (!C|A|D)
    (B|!C)
    (A|!B|!D)
    (C|!A)
    Clause 1 is: ((A|B|D))
    Clause 2 is: ((!A|C))
    Clause 3 is: ((!B|C|D))
    Clause 4 is: ((!C|A|D))
    Clause 5 is: ((B|!C))
    Clause 6 is: ((A|!B|!D))
    Clause 7 is: ((C|!A))

    Summarize 1 and 2:
    Clause 1 is: (C|D|B)
    Clause 2 is: ((!B|C|D))
    Clause 3 is: ((!C|A|D))
    Clause 4 is: ((B|!C))
    Clause 5 is: ((A|!B|!D))
    Clause 6 is: ((C|!A))

    Summarize 1 and 2:
    Clause 1 is: (C|D)
    Clause 2 is: ((!C|A|D))
    Clause 3 is: ((B|!C))
    Clause 4 is: ((A|!B|!D))
    Clause 5 is: ((C|!A))

    Summarize 1 and 2:
    Clause 1 is: (A|D)
    Clause 2 is: ((B|!C))
    Clause 3 is: ((A|!B|!D))
    Clause 4 is: ((C|!A))

    Summarize 1 and 3:
    Clause 1 is: (!B|A)
    Clause 2 is: ((B|!C))
    Clause 3 is: ((C|!A))

    Summarize 1 and 2:
    Clause 1 is: (!C|A)
    Clause 2 is: ((C|!A))

    Summarize 1 and 2:
    Empty

    The conclusion is true!
    ```
- 归结推理错误：
    ```
    Please input the set of clauses:
    Please input the number of clauses first:
    6
    Please input the set of clauses:
    (X|Y|W)
    (!X|Z)
    (!Y|Z|W)
    (!Z|X|W)
    (Y|!Z)
    (X|!Y|!W)
    Clause 1 is: ((X|Y|W))
    Clause 2 is: ((!X|Z))
    Clause 3 is: ((!Y|Z|W))
    Clause 4 is: ((!Z|X|W))
    Clause 5 is: ((Y|!Z))
    Clause 6 is: ((X|!Y|!W))

    Summarize 1 and 2:
    Clause 1 is: (Z|Y|W)
    Clause 2 is: ((!Y|Z|W))
    Clause 3 is: ((!Z|X|W))
    Clause 4 is: ((Y|!Z))
    Clause 5 is: ((X|!Y|!W))

    Summarize 1 and 2:
    Clause 1 is: (Z|W)
    Clause 2 is: ((!Z|X|W))
    Clause 3 is: ((Y|!Z))
    Clause 4 is: ((X|!Y|!W))

    Summarize 1 and 2:
    Clause 1 is: (X|W)
    Clause 2 is: ((Y|!Z))
    Clause 3 is: ((X|!Y|!W))

    Summarize 1 and 3:
    Clause 1 is: (!Y|X)
    Clause 2 is: ((Y|!Z))

    Summarize 1 and 2:
    Clause 1 is: (!Z|X)

    The conclusion is false!
    ```
### 王浩算法

- 可以被证明：
  ```
    Please input the premise:
    (P|Q)&(P^R)&(Q^S)
    Please input the consequence: 
    S|R

    Theorem Prover Set:
    1) (P|Q)&(P^R)&(Q^S) ==> S|R

    Theorem Prover Set:
    1) (P^R)&(Q^S), (P|Q) ==> S|R

    Theorem Prover Set:
    1) (P|Q), (Q^S), (P^R) ==> S|R

    Theorem Prover Set:
    1) (Q^S), (P^R), Q ==> S|R
    2) (Q^S), (P^R), P ==> S|R

    Theorem Prover Set:
    1) (P^R), Q, S ==> S|R
    2) (Q^S), (P^R), P ==> S|R
    3) (P^R), Q ==> S|R, Q

    Theorem Prover Set:
    1) Q, S, R ==> S|R
    2) (Q^S), (P^R), P ==> S|R
    3) (P^R), Q ==> S|R, Q
    4) Q, S ==> S|R, P

    Theorem Prover Set:
    1) Q, S, R ==> R, S
    2) (Q^S), (P^R), P ==> S|R
    3) (P^R), Q ==> S|R, Q
    4) Q, S ==> S|R, P

    Theorem Prover Set:
    1) Q, S, R ==> R, S
    2) (P^R), P, S ==> S|R
    3) (P^R), Q ==> S|R, Q
    4) Q, S ==> S|R, P
    5) (P^R), P ==> S|R, Q

    Theorem Prover Set:
    1) Q, S, R ==> R, S
    2) P, S, R ==> S|R
    3) (P^R), Q ==> S|R, Q
    4) Q, S ==> S|R, P
    5) (P^R), P ==> S|R, Q
    6) P, S ==> S|R, P

    Theorem Prover Set:
    1) Q, S, R ==> R, S
    2) P, S, R ==> R, S
    3) (P^R), Q ==> S|R, Q
    4) Q, S ==> S|R, P
    5) (P^R), P ==> S|R, Q
    6) P, S ==> S|R, P

    Theorem Prover Set:
    1) Q, S, R ==> R, S
    2) P, S, R ==> R, S
    3) Q, R ==> S|R, Q
    4) Q, S ==> S|R, P
    5) (P^R), P ==> S|R, Q
    6) P, S ==> S|R, P
    7) Q ==> S|R, Q, P

    Theorem Prover Set:
    1) Q, S, R ==> R, S
    2) P, S, R ==> R, S
    3) Q, R ==> Q, R, S
    4) Q, S ==> S|R, P
    5) (P^R), P ==> S|R, Q
    6) P, S ==> S|R, P
    7) Q ==> S|R, Q, P

    Theorem Prover Set:
    1) Q, S, R ==> R, S
    2) P, S, R ==> R, S
    3) Q, R ==> Q, R, S
    4) Q, S ==> P, R, S
    5) (P^R), P ==> S|R, Q
    6) P, S ==> S|R, P
    7) Q ==> S|R, Q, P

    Theorem Prover Set:
    1) Q, S, R ==> R, S
    2) P, S, R ==> R, S
    3) Q, R ==> Q, R, S
    4) Q, S ==> P, R, S
    5) P, R ==> S|R, Q
    6) P, S ==> S|R, P
    7) Q ==> S|R, Q, P
    8) P ==> S|R, Q, P

    Theorem Prover Set:
    1) Q, S, R ==> R, S
    2) P, S, R ==> R, S
    3) Q, R ==> Q, R, S
    4) Q, S ==> P, R, S
    5) P, R ==> Q, R, S
    6) P, S ==> S|R, P
    7) Q ==> S|R, Q, P
    8) P ==> S|R, Q, P

    Theorem Prover Set:
    1) Q, S, R ==> R, S
    2) P, S, R ==> R, S
    3) Q, R ==> Q, R, S
    4) Q, S ==> P, R, S
    5) P, R ==> Q, R, S
    6) P, S ==> P, R, S
    7) Q ==> S|R, Q, P
    8) P ==> S|R, Q, P

    Theorem Prover Set:
    1) Q, S, R ==> R, S
    2) P, S, R ==> R, S
    3) Q, R ==> Q, R, S
    4) Q, S ==> P, R, S
    5) P, R ==> Q, R, S
    6) P, S ==> P, R, S
    7) Q ==> Q, P, R, S
    8) P ==> S|R, Q, P

    Theorem Prover Set:
    1) Q, S, R ==> R, S
    2) P, S, R ==> R, S
    3) Q, R ==> Q, R, S
    4) Q, S ==> P, R, S
    5) P, R ==> Q, R, S
    6) P, S ==> P, R, S
    7) Q ==> Q, P, R, S
    8) P ==> Q, P, R, S

    Proved!
  ```
- 不能被证明：
    ```
    Please input the premise: 
    (a&(!b|c)~d)
    Please input the consequence:
    (a&(b|(c&(!d^e))))

    Theorem Prover Set:
    1) a&(!b|c)~d ==> a&(b|(c&(!d^e)))

    Theorem Prover Set:
    2) d, a&(!b|c) ==> a&(b|(c&(!d^e)))
    3) Empty ==> a&(b|(c&(!d^e))), d, a&(!b|c)

    Theorem Prover Set:
    4) d, (!b|c), a ==> a&(b|(c&(!d^e)))
    5) Empty ==> a&(b|(c&(!d^e))), d, a&(!b|c)

    Theorem Prover Set:
    6) d, a, c ==> a&(b|(c&(!d^e)))
    7) Empty ==> a&(b|(c&(!d^e))), d, a&(!b|c)
    8) d, a, !b ==> a&(b|(c&(!d^e)))

    Theorem Prover Set:
    9) d, a, c ==> (b|(c&(!d^e)))
    10) Empty ==> a&(b|(c&(!d^e))), d, a&(!b|c)
    11) d, a, !b ==> a&(b|(c&(!d^e)))
    12) d, a, c ==> a

    Theorem Prover Set:
    13) d, a, c ==> (c&(!d^e)), b
    14) Empty ==> a&(b|(c&(!d^e))), d, a&(!b|c)
    15) d, a, !b ==> a&(b|(c&(!d^e)))
    16) d, a, c ==> a

    Theorem Prover Set:
    17) d, a, c ==> b, (!d^e)
    18) Empty ==> a&(b|(c&(!d^e))), d, a&(!b|c)
    19) d, a, !b ==> a&(b|(c&(!d^e)))
    20) d, a, c ==> a
    21) d, a, c ==> b, c

    Theorem Prover Set:
    22) d, a, c, !d ==> b, e
    23) Empty ==> a&(b|(c&(!d^e))), d, a&(!b|c)
    24) d, a, !b ==> a&(b|(c&(!d^e)))
    25) d, a, c ==> a
    26) d, a, c ==> b, c

    Theorem Prover Set:
    27) d, a, c ==> b, e, d
    28) Empty ==> a&(b|(c&(!d^e))), d, a&(!b|c)
    29) d, a, !b ==> a&(b|(c&(!d^e)))
    30) d, a, c ==> a
    31) d, a, c ==> b, c

    Theorem Prover Set:
    32) d, a, c ==> b, e, d
    33) Empty ==> d, a&(!b|c), (b|(c&(!d^e)))
    34) d, a, !b ==> a&(b|(c&(!d^e)))
    35) d, a, c ==> a
    36) d, a, c ==> b, c
    37) Empty ==> d, a&(!b|c), a

    Theorem Prover Set:
    38) d, a, c ==> b, e, d
    39) Empty ==> d, (b|(c&(!d^e))), (!b|c)
    40) d, a, !b ==> a&(b|(c&(!d^e)))
    41) d, a, c ==> a
    42) d, a, c ==> b, c
    43) Empty ==> d, a&(!b|c), a
    44) Empty ==> d, (b|(c&(!d^e))), a

    Theorem Prover Set:
    45) d, a, c ==> b, e, d
    46) Empty ==> d, (!b|c), (c&(!d^e)), b
    47) d, a, !b ==> a&(b|(c&(!d^e)))
    48) d, a, c ==> a
    49) d, a, c ==> b, c
    50) Empty ==> d, a&(!b|c), a
    51) Empty ==> d, (b|(c&(!d^e))), a

    Theorem Prover Set:
    52) d, a, c ==> b, e, d
    53) Empty ==> d, (c&(!d^e)), b, c, !b
    54) d, a, !b ==> a&(b|(c&(!d^e)))
    55) d, a, c ==> a
    56) d, a, c ==> b, c
    57) Empty ==> d, a&(!b|c), a
    58) Empty ==> d, (b|(c&(!d^e))), a

    Theorem Prover Set:
    59) d, a, c ==> b, e, d
    60) Empty ==> d, b, c, !b, (!d^e)
    61) d, a, !b ==> a&(b|(c&(!d^e)))
    62) d, a, c ==> a
    63) d, a, c ==> b, c
    64) Empty ==> d, a&(!b|c), a
    65) Empty ==> d, (b|(c&(!d^e))), a
    66) Empty ==> d, b, c, !b, c

    Theorem Prover Set:
    67) d, a, c ==> b, e, d
    68) b ==> d, b, c, (!d^e)
    69) d, a, !b ==> a&(b|(c&(!d^e)))
    70) d, a, c ==> a
    71) d, a, c ==> b, c
    72) Empty ==> d, a&(!b|c), a
    73) Empty ==> d, (b|(c&(!d^e))), a
    74) Empty ==> d, b, c, !b, c

    Theorem Prover Set:
    75) d, a, c ==> b, e, d
    76) b, !d ==> d, b, c, e
    77) d, a, !b ==> a&(b|(c&(!d^e)))
    78) d, a, c ==> a
    79) d, a, c ==> b, c
    80) Empty ==> d, a&(!b|c), a
    81) Empty ==> d, (b|(c&(!d^e))), a
    82) Empty ==> d, b, c, !b, c

    Theorem Prover Set:
    83) d, a, c ==> b, e, d
    84) b ==> d, b, c, e, d
    85) d, a, !b ==> a&(b|(c&(!d^e)))
    86) d, a, c ==> a
    87) d, a, c ==> b, c
    88) Empty ==> d, a&(!b|c), a
    89) Empty ==> d, (b|(c&(!d^e))), a
    90) Empty ==> d, b, c, !b, c

    Theorem Prover Set:
    91) d, a, c ==> b, e, d
    92) b ==> d, b, c, e, d
    93) d, a ==> a&(b|(c&(!d^e))), b
    94) d, a, c ==> a
    95) d, a, c ==> b, c
    96) Empty ==> d, a&(!b|c), a
    97) Empty ==> d, (b|(c&(!d^e))), a
    98) Empty ==> d, b, c, !b, c

    Theorem Prover Set:
    99) d, a, c ==> b, e, d
    100) b ==> d, b, c, e, d
    101) d, a ==> b, (b|(c&(!d^e)))
    102) d, a, c ==> a
    103) d, a, c ==> b, c
    104) Empty ==> d, a&(!b|c), a
    105) Empty ==> d, (b|(c&(!d^e))), a
    106) Empty ==> d, b, c, !b, c
    107) d, a ==> b, a

    Theorem Prover Set:
    108) d, a, c ==> b, e, d
    109) b ==> d, b, c, e, d
    110) d, a ==> b, (c&(!d^e)), b
    111) d, a, c ==> a
    112) d, a, c ==> b, c
    113) Empty ==> d, a&(!b|c), a
    114) Empty ==> d, (b|(c&(!d^e))), a
    115) Empty ==> d, b, c, !b, c
    116) d, a ==> b, a

    Theorem Prover Set:
    117) d, a, c ==> b, e, d
    118) b ==> d, b, c, e, d
    119) d, a ==> b, b, (!d^e)
    120) d, a, c ==> a
    121) d, a, c ==> b, c
    122) Empty ==> d, a&(!b|c), a
    123) Empty ==> d, (b|(c&(!d^e))), a
    124) Empty ==> d, b, c, !b, c
    125) d, a ==> b, a
    126) d, a ==> b, b, c

    Theorem Prover Set:
    127) d, a, c ==> b, e, d
    128) b ==> d, b, c, e, d
    129) d, a, !d ==> b, b, e
    130) d, a, c ==> a
    131) d, a, c ==> b, c
    132) Empty ==> d, a&(!b|c), a
    133) Empty ==> d, (b|(c&(!d^e))), a
    134) Empty ==> d, b, c, !b, c
    135) d, a ==> b, a
    136) d, a ==> b, b, c

    Theorem Prover Set:
    137) d, a, c ==> b, e, d
    138) b ==> d, b, c, e, d
    139) d, a ==> b, b, e, d
    140) d, a, c ==> a
    141) d, a, c ==> b, c
    142) Empty ==> d, a&(!b|c), a
    143) Empty ==> d, (b|(c&(!d^e))), a
    144) Empty ==> d, b, c, !b, c
    145) d, a ==> b, a
    146) d, a ==> b, b, c

    Theorem Prover Set:
    147) d, a, c ==> b, e, d
    148) b ==> d, b, c, e, d
    149) d, a ==> b, b, e, d
    150) d, a, c ==> a
    151) d, a, c ==> b, c
    152) Empty ==> d, a, (!b|c)
    153) Empty ==> d, (b|(c&(!d^e))), a
    154) Empty ==> d, b, c, !b, c
    155) d, a ==> b, a
    156) d, a ==> b, b, c
    157) Empty ==> d, a, a

    Theorem Prover Set:
    158) d, a, c ==> b, e, d
    159) b ==> d, b, c, e, d
    160) d, a ==> b, b, e, d
    161) d, a, c ==> a
    162) d, a, c ==> b, c
    163) Empty ==> d, a, c, !b
    164) Empty ==> d, (b|(c&(!d^e))), a
    165) Empty ==> d, b, c, !b, c
    166) d, a ==> b, a
    167) d, a ==> b, b, c
    168) Empty ==> d, a, a

    Theorem Prover Set:
    169) d, a, c ==> b, e, d
    170) b ==> d, b, c, e, d
    171) d, a ==> b, b, e, d
    172) d, a, c ==> a
    173) d, a, c ==> b, c
    174) b ==> d, a, c
    175) Empty ==> d, (b|(c&(!d^e))), a
    176) Empty ==> d, b, c, !b, c
    177) d, a ==> b, a
    178) d, a ==> b, b, c
    179) Empty ==> d, a, a

    Not proved! Because of the theorem 6) is against the axiom.
    ```

## 其他
- 鉴于时间有限和逻辑的复杂性，归结推理证明的前处理工作——将一个命题公式化简为一个简单的合取范式——这一工作尚未完成。大致思路是：依次消去~、^两个逻辑联结词，得到一个只含由&、|、!三个联结词的范式，之后运用分配律按照一定规律将|联结词分配到括号内。最后一个分配律的函数尚未完成，在源码中也有标记。前三个函数都已完成，但尚未完整测试，劳烦助教查看。
- 王浩算法中，输入的是相继式格式。理论上证明的定理不一定是相继式格式。同样由于工作量原因，将任意格式的定理转换为相继式的工作尚未完成。