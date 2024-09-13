# TODO list

This is a list of things that I actually intend to do in order of priority. When an item is complete, move it to the **Done** section.

* Switch the hashtable library to use String* as keys.

* Allow function definitions inside a class definition. There is no notion of an inline function because all function are held as pointers in the class and functions cannot be inlined if a pointer to them exists. 
    * This depends on reworking how the AST stores names. 
    * Function parameters require a variable name for definitions, but for declarations, the name should be optional.
    * The function definition node in the AST is the same for a declaration or a definition except that for a declaration, the function body is not defined.

* Function prototypes have to have the input and output parameters differentiated so that the AST traverse functions can tell them apart. Probably just add a flag of some kind.

* Directives for include paths, compiler options, and linker options. Could be new keywords that start with a ``.``.

* Built in class functions such as the ones in Python that handle stringalation, typealation, and comparisons.
    * Look into operator overloads. Monkey patch implications.

* Compress the AST structure so that it can be used as a symbol table. That means to concentrate all of the required information for a name into a single data structure and reference the children of the name by name instead of elements in an anonymous list. That way the AST can be used to look up names.

* Comprehensive testing.

* Change function declarations
    * get rid of the function_declaration non-terminal
    * make a new nterm where the var name in a parm decl is optional, with the list.
    * Switch over the definitions.
    * function body becomes optional
    * differentiate when there is a single name in the compound name for decl vs definition


## Done
* Implement aliases. An alias can appear anywhere in a module and it has the syntax of ``compound_name 'as' IDENT``. All it does is check the existence of the compound name and makes an entry in the symbol table that maps the IDENT to that name. An alias is required to define an inheritance specification, for example.

* Take function assignment to variables out of the syntax.

* Make tracing controllable from the command line. Unify the testing functionality into the main executable. The trace capability needs to be a stack so that the different subsystems can be isolated for trace. Separate test programs for AST, parser, and scanner become obsolete.

* Need to differentiate between a loop body and a function body. A loop body adds the keywords of ``break``, and ``continue``. Those cannot appear outside of a loop. Also note that the ``yield`` keyword has a different meaning inside a loop than it does outside of it. Maybe it is a loop-only construct. Yield keyword is for implementing iterators and it may not have a meaning outside of a loop. 

* Inheritance specifications need to include the scope of the symbol for example, ``public some.class.name as name``.
    * List of inheritance specifications can appear as part of a class definition to support multiple inheritance using a class pointer array in a class. 

* Need an ``iterator`` keyword to describe a function that can use the ``yield`` keyword. If the function does not use ``yield`` it should still operate as a normal function, but if a function is not an iterator and it uses ``yield`` then that should be an error.
    * Checking for the ``iterator`` and the ``yield`` in a function are done as AST passes.
    * **update:** Removed the iterator keyword. Will mark the function as an iterator if the yield keyword is found in a loop.

* Improve error message where final else is not the last one.

* Change if/else to be if/else/final

* Change switch/case/default to be switch/case/final and delete the 'default' keyword

* Simple assignment as in "name = name" appears to not be a function_body_item.

* **important** Improve error messages when a error token is received by the parser from the scanner. 
  * Example, when an invalid unsigned is scanned, such as 0xx123.
  * go through the scanner and map every instance of an TOK_ERROR return into the parser.
    * See func_body.inline for example

* String expressions such as ``strg == strg``, ``strg != strg``, ``strg = strg + strg``, and ``strg += strg``

* String expressions and other expressions cannot mix??
  * If this is a semantic question then strgs need to be added to the ``primary_expression`` productions.
  * Removed garbage collection and exceptions from the compiler.

* When the scanner receives a float with the format of 123.123.123, then it correctly scans the float and then returns the '.' as the next token. However, the parser does not produce a correct error in that case.

* Scanner incorrectly sees a number such as "123..123" as a float, when it should flag an error. and stop scanning at the first '.'

* Scanner incorrectly sees a number such as "123." as a float, when it should flag an error. and stop scanning at the first '.'

* Do not allow spaces around a '.' in a compound name or reference. **do not fix**


