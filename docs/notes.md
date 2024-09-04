
# Problems and thoughts...

## Parser State
This is information that can be taken by the parser implementation. 

* Symbol table creation.
* Tracking the scope of symbols that are created.

## Symbol table.
A symbol table stores the names that are defined in a program such that the scope and type of a name can be verified when a reference to it is encountered. A symbol is a single word that exists in a context of other single words. Each word represents a name that has a type and other attributes according to its definition. Some symbols can host other symbols. For example a class is used to define other names that are exclusive to the class. Other symbols can only represent themselves, such as a variable name. Functions have one or more anonymous symbol scopes. A reference to a name in an anonymous scope can be defined in an outer anonymous scope. Functions also have input and output parameters defined. Those have their own special access rules and are defined in the outermost anonymous scope of the function. Input parameters are read only and output parameters are both read and write. All other names have access parameters specified in their definition. For a function that is declared in a class, the variables declared in the class are also considered local to an anonymous scope in a function. When there is a name defined in an anonymous scope that has already been declared in an outer scope, a warning is issued and the name used is the most local one. 

The symbol table is implemented as a hash table where sibling names are in the same table. Names that can have child names have their own hash table in which names are kept and so on. Every name has a type and access rules. 

## Implement the debugger
The debugger information will be implemented as text messages sent over an ethernet connection. The application side software is implemented in the runtime to interpret debugger commands and run the program line by line using a function that waits after each line of source code. When the line is run, then the runtime debugger reports that it's done back to the debugger UI. Design the protocol and messages. The runtime is smart enough to be able to run if the debugger is not active. 

## Things to fix.

* Need to differentiate between a loop body and a function body. A loop body adds the keywords of "break", and "continue". Those cannot appear outside of a loop. Also note that the "yield" keyword has a different meaning inside a loop than it does outside of it. Maybe it is a loop-only construct. Yield keyword is for implementing iterators and it may not have a meaning outside of a loop.
* Make tracing controllable from the command line. Unify the testing functionality into the main executable. The trace capability needs to be a stack so that the different subsystems can be isolated for trace.