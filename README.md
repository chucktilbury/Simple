# Simple
The **Simple** programming language. 
"ELF" stands for Simple Language Framework.

This is a very simple object-oriented programming language compiler which is written in C. It's a fun hobby project. See the grammar [here](docs/elf-grammar.txt). It's pretty complete and I am actively working on a parser and AST for it. (September, 2024)

The language is a synthesis or Python and C. It has the object model of Python but shares a lot of syntax with both C and C++.

General features in no particular order.
* Curly braces to delimit blocks. Semicolons are used to introduce single-line comments. Whitespace is completely ignored except to separate some tokens.
* Simplified type system, but is strongly typed with casting.
* Durable typing. Once a type is specified, it cannot be changed. Casting is supported and a different var can be created with the different type. The exception to this is the ``nothing`` type. This allows the type to be assigned at runtime, and once it is assigned, then the type of the variable becomes durable and is enforced at runtime.
* Function overloads by parameter type. Functions have a syntax of ``name(input parameters)(output parameters)``. Input parameters are passed to the function by value and output parameters are passed as references. Outputs not assigned in the function is a warning. Outputs accessed by value in a function is a syntax error, and duplicate names are a syntax error. This means that a function does not "return" anything. A syntax such as ``name.name.func()().name`` makes no sense. Use exceptions to communicate errors and such.
* Functions can be overridden by the signature, including the return values.
* The ``nothing`` type takes the place of the ``void`` type in C. This is used to allow an data object to have a type assigned at run time.
* Classes with multiple inheritance. Class definitions can contain no assignments but it may contain function definitions. The parent attributes and methods are accessed by name with the '.' operator.
* All class methods are virtual. No keyword is needed to override a method to to define an interface. Syntax errors for referencing a method that has not been implemented are delayed as long as possible to allow flexibility in the definitions.
* The default scope is ``private``. When a scope keyword appears it remains in effect until another one is used. A scope keyword can appear almost anywhere except inside a function definition.
* Membership is given by the '.' operator and spaces are allowed before or after it.
* Supports dictionaries and lists natively.
* String is a native data type and all strings can be formatted without an explicit method call.
* The compiler and the runtime library both use managed memory implemented by the Boehm-Demers-Weiser Garbage Collector found here: https://www.hboehm.info/gc/
* Exceptions using the non-local goto feature of ANSI C. A string error message is passed back to the exception handler.
* Support for external libraries using an ``inline`` keyword that causes literal code to be copied directly to the output without any checking. This is implemented as a scanner feature.
* Constant values cannot be changed once they are assigned, but they are assigned at runtime.

Features that are specifically not supported.

* Pointers.

This multi-pass compiler accepts Simple source code and outputs C source code. The output should be compilable by any modern ANSI C compiler. The output is not really intended to be human readable, but the #line directives are used to aid debugging. The generated code favors efficiency over readability. The goal is that there should be no way for the compiler to output incorrect code. All semantic errors are caught before emitting any output, except for the inline functionality. No checking or parsing is done on that whatsoever.

# This repo
(assuming you know how to use github)
This repo has not nor ever will be built by me under any version of Windows. It should be usable on other operating systems. I don't have a MAC, so I can't test anything. In general it should build under Linux without problems. There are a couple of files to make it easier to use. After you clone it, take a look at the .project_env file to see if it matches your setup. If it does, then you can just run ``./scripts/setup`` to check out the sub projects and create a sub-shell with some paths set up. To make the repo perfectly clean, run the ``./scripts/clean`` script or delete the docs/out, build, lib, and bin directories.

## required packages
This requires an ANSI C compiler and friends, [gc](https://github.com/chucktilbury/bdwgc.git), cmake, graphiz, and doxygen. No other libraries or tools should be required.

## Feedback is most welcome
I would also welcome some help. Compilers are such a slog....

# Grammar
This is the complete and updated [grammar for **Simple**](docs/elf-grammar.txt) 

