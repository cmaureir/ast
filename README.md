# Arithmetic expression evaluator

[![Build Status](https://travis-ci.org/cmaureir/ast.svg?branch=master)](https://travis-ci.org/cmaureir/ast)

## Requirements

> Create a C++ program that can parse and evaluate arithmetic expressions.
> Parsing and evaluating should be two independent steps that are separated by a data structure (the AST).
>
> The program should not use anything apart from the C++11 STL.
>
> Arithmetic expressions consist of decimal numbers combined using the binary
> operators +, *, /, - and parentheses and should respect the usual precedence relations.
>
> The program should detect invalid input and report an appropriate error.
>
> Unit tests are appreciated.
>
> Example:
>
> On input `(4 + 5 * (7 - 3)) - 2`, the program should output `22`

## Structure

The code is written in two steps:
1. [Shunting Yard Algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm):
   * The parsing process will create a string in [Reverse Polish Notation (RPN)](https://en.wikipedia.org/wiki/Reverse_Polish_notation),
    but also will populate an implementation of an [Abstract Syntax Tree (AST)](https://en.wikipedia.org/wiki/Shunting-yard_algorithm)
    using a stack.
2. Postfix Evaluation:
   * There are two methods to evaluate a RPN or an AST.

* Supported operations
   * Only `+`, `-`, `*` and `/` are supported, but it can be easily expanded.
* Supported numbers:
   * All the number are interpreted as `float`.
   * The format could be `1.2`, `99`, `101.`, etc.
   * The notation `.3` is not supported. The reason for this was that C++11 [regex](http://en.cppreference.com/w/cpp/regex)
     does not support *Negative Lookbehind*.
     If `boost` was allowed, one can easily replace the notation with:
     `/(?<!\d)[.](\d)")/0.\1/`.

## Compilation and execution

To compile the code, a `make` is enough.
The execution will look like:

```
$ ./arithmetic
(4 + 5 * (7 - 3)) - 2
22
```

The test can be compiled with `make test`.
The current code is using [Catch](https://github.com/philsquared/Catch)
as test framework.

```
% ./test
===============================================================================
All tests passed (44 assertions in 3 test cases)
```
## Licence

[tl;dr Apache 2.0](https://tldrlegal.com/license/apache-license-2.0-(apache-2.0))
```
Copyright (C) 2017 Cristián Maureira-Fredes

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
