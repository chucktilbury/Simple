
# Problems and thoughts...

## Function declaration vs. function definition
There are function declarations and function definitions. A function declaration does not have a body defined. It may have a single identitfier as it's symbol table name, or it could be a compound name. Also, the function parameters may have names and it may not, but the parameter types are always required because they are used to decorate the name. A function declaration always creates a symbol table entry. When a function declaration has a compound name, that name has to be looked up in the symbol table and the name has have already been declared. in the context specified by the name.

### Example 1:
```
class tha_name {
    defunct(integer)(string)
}

...

tha_name.defunct(integer num)(string str) {
    ; the function body
    integer a_number = num
    str = "formatted string %d"(a_number)
}
```
In this example, when the class is parsed, the function name is created in the symbol table without a body but with a complete name. When the function definition is encountered by the parser, the class name is found and the function signature is found to be a child of that class and so instead of creating a new symbol in the symbol table, the existing symbol gets the parameter names in its local table and the body is assigned to to the name.

### Example 2:
```
class tha_name (public poppa.bear as pops) {
    defunct(integer)(string)
    pops.defunct(integer)(string)
}

...

tha_name.defunct(integer num)(string str) {
    pops.defunct(num)(str)
    str = "formatted string %d"(num)
}
```
This example is a syntax error because there is no implementation of ``pops.defunct(integer)(string)``. The reference inside the other function is valid as far as it goes. For this to be valid, another function definition would be required such as ``tha_name.pops.defunct(integer iname)(string oname) { ... } `` to implement the function. Also in this example, the function name ``pops.defunct`` is an alias for a function that has already been defined in the class name ``poppa.bear``. This class would be found in a namespace ``poppa`` because classes cannot be nested. If that function has not been declared, then a syntax error is published because **this declaration is a reference**. But note that the function does not need to be implemented. It could just be a declaration as part of an interface. The syntax (runtime?) error arises when the function is referenced with no implementation.

### Example 3:
```
some_func(integer)(string)

...

some_func(integer num)(string str) {
    integer a_number = num
    str = "formatted string %d"(a_number)
}
```
In this example, we have a forward declaration of a function with the implementation following after some other code. Similar to the declaration inside a class, the actual parameter names and function body is assigned to the original declaration instead of creating a new symbol in the symbol table.

### Example 4:
```
class tha_name {
    defunct(integer num)(string str) {
        ; the function body
        integer a_number = num
        str = "formatted string %d"(a_number)
    }
}
```
In this example, the function declaration and the definition are totally within the class. This has exactly the same effect as in Example 1. 


## Re-thinking the AST definition.
The way the current AST is configure is that it follows the syntax of the input closely with the idea that subsequent passes will refine it to be closer to what is actually emitted. But now I am thinking that it should be compressed even further. Notice that there are similarities between the AST and the symbol table. They both essentially hold data in nodes that describe a nexus in the syntax that defines an identifier. So it seems as if a more targeted data structure than the generic boilerplate is beneficial. This new data structure will be centered around the names that are created, rather than the links to other nodes in the syntax tree. Instead of a list of nodes representing children, use a hash table instead. Nodes in the hash table have the children given by name in no particular order, so when order does matter, such as lines in a function definition, a hierarchy of lists must still be used.

### Name hierarchy
This is a description of the types of names that **could be** present in a type of item found in the syntax of the Simple language.

* module -- Contains the root or NULL namespace. 
    * namespace definition
    * function definition
    * variable definition
    * import
* namespace -- Used to separate names and prevent naming collisions.
    * namespace definition
    * class definition
    * function definition
    * variable definition
* class -- Used to define objects and sequester the state and methods associated with them.
    * function definition
    * variable definition
* function -- No global objects can be defined in or by a function. Functions can create objects and return them through a return parameter.
    * local name definitions only
* variable -- Denotes actual memory storage in a naming and object context.
* alias -- Where one name is used to reference another name, normally this is introduced with the ``as`` keyword but the import also aliases names.
* import -- Used to bring in data from another module into it's own mandatory name space so that the names can be accessed in the current module.

The nodes that represent the syntax that is being parsed are stored in the hash table instead of a list. All of the names themselves are global but their scope could be limited by the scope operators. This allows error messages to be generated and simplifies the code. Note that in Simple, a name does not need to be defined before it is referenced. Any name that is in the current symbolic scope can be referenced. The dot operator acts much like a path operator (i.e. a '/' or a '\\' in winders) for a file system when specifying a specific name to access.

## Symbol decorations
Symbol decorations include the type of the symbol as well as it's name. Both the decorated name and the undecorated names are stored and valid. I have only been intending to decorate function names to overload them, but it occurs to me that we could decorate variable names and class names as well as function names. To reference an overloaded function the types of the parameters in the call have to be looked up as well as the other information. This is done at compile time. For functions, it's pretty straightforward to do. For variables in the case of assignment, it's clear enough, but in the context of an expression it's ambiguous. To clarify the type that is intended would require complicated rules that look at the greater context of the reference. Classes are even worse because the only way to decorate is by the inheritance name and it's impossible to know which one is intended by how it's being used. Sticking with function names.

Also note that there is a difference between a function declaration and a function definition. In cases where the function or variable are defined in the context of a namespace or module, then the declaration and the definition are the same AST node. In cases where they are declared in a class and defined outside of the class, the definition must be treated as a reference to the name and it will have a compound name and definitions will have a simple identifier. However, the parser currently does not differentiate them. But the rule that compound names are always references seems valid.

Internally, the function decorations have to differentiate the name of the symbol and the parameters. But when the function name is emitted, it has to be emitted as a valid C identifier. Given a function prototype such as ``some_function(integer,some.obj.name,float)(dict)`` the internal representation could look exactly like that, which will help with error presentations. There are really no restrictions on what the hash table can use as a key. 

There may be several ways to construct the emitted version. 
* One method could be to simply replace the parenthesis, dots, and commas with underscore characters. Replacing the characters with simple underscores is unique and repeatable but could make for long symbol names. But they will be human-readable. An example of the above might look like ``_some_function__integer_some_obj_name_float__dict_``.
* Replace the punctuation characters with numbers such that the original prototype can be rebuilt. For example ``some_function0integer4some6obj6name4float10dict1``, may be useful when writing the debugger. The numbers are the ASCII codes for the characters they replace -40 in decimal. In other words, 40 == '(' and 41 == ')'.
* Another may be to replace the input and output parameters with the hex value of the pointer to them. A pointer is guaranteed to be unique and consistent, but will be different between builds. 
* Creating a hash of the name and parameter types is not guaranteed to be unique.
* Creating a random GUID could work, but the function names will be completely unreadable. However, using some kind of GUID is required to implement anonymous namespaces for variables defined inside of the function body, so it's not like it requires a special library.

## Function definitions in classes
Currently this is not allowed. A class can only contain declarations. If function definitions are allowed inside the class definition, then the definition and the declaration have to be separate items and the declaration has to be created artificially. If the definition appears outside of the class definition, then it will have to be linked/added to the class anyway. When a class member function is emitted, a pointer to it is emitted in the struct that implements the class. 
* When a class method is declared, it looks exactly like a definition, but without the completed symbol table. When the definition is encountered, then the symbol table is filled in. 
* Ideally, a method declaration should accept parameter names but ignore them and only keep the type information in the form of a decorated name. The parameter names are completed when the definition is parsed.

### Emitted classes and function calls
Functions cannot be defined in a struct in C. Therefore all functions that are associated with a class have to be defined as pointers. These pointers are kept in an array of void pointers so that they can be reassigned during runtime. For example:

```
// code emitted to define a function and a class
typedef void (*func_name)(struct class_name* self, int invar1, int invar2, int* outv1, int *outv2);
typedef struct class_name {
    ...
    // dynamically sized table for function pointers.
    void** ftable;
    int ftable_cap;
    int ftable_len;
    ...
} class_name;
```

When the default class constructor is called, the struct is allocated and that pointer is stored in a global table of void pointers. 

```
// global class table holds all of the classes defined for the module.
typedef void** class_table;
```

The pointers are cast to the correct type when they are referenced.

```
// class function reference.
(*((func_name)((class_table[12])->ftable[3])))((class_name*)class_table[12], 123, 8, &var1, &var2);
```

The default constructor allocates the class, assigns it a slot in the global class table and assigns the function pointers to the ftable. After that it calls the correct overloaded class constructor. If there is a parent class then the constructor is called for that class and stored in this class as an object. So a class defined in emitted code is a generic typedef data structure that has tables in it that hold the state and methods.

## Notes on class and object model
All built in types are handled as objects with built in class definitions. Operator overloading is not explicitly supported but all operators are implemented as class methods.

I was thinking to keep the class model simple, but now I am thinking about expanding it to allow things like monkey patching. If a class does not have a variable name of ``abc`` defined and a construct such as ``class_object.abc = 123`` is encountered, then should it be that now that object has a attribute named ``abc`` with a type of ``integer`` as if it were placed there in the source code?

The implication is that keywords such as ``integer`` and ``list`` define classes and that when a variable is defined with these types then that is an object that is defined by the internal class definition of the type. That implies that it should be possible to monkey-patch internally defined types as well as user-defined types, and that internally defined type names can be inherited by child classes.

## Iterators
An iterator is a special function that, unlike other functions in Simple, it returns a value. It retains its state between returns. This state of having returned a value and retaining its state is implemented using the ``yield`` keyword. The ``yield`` keyword is only valid inside a loop. When the loop ends, then the loop inside the 

## Parser Mode
The parser state is the current mode that the parser is in. 
* Normal. This is the state where all of the code that is input is stored in the AST.
* Import. In this mode, the parser reads all of the input but only stores names that are defined. The assumption is made that another module has the definition for the symbol and it will be resolved at link time. Symbols are imported as if the imported module has its own namespace.
* Include mode is not really a separate mode, but the included source code is read in as if it was a part of the current module into the root namespace.

## Symbol table.
A symbol table stores the names that are defined in a program such that the scope and type of a name can be verified when a reference to it is encountered. A symbol is a single word that exists in a context of other single words. Each word represents a name that has a type and other attributes according to its definition. Some symbols can host other symbols. For example a class is used to define other names that are exclusive to the class. Other symbols can only represent themselves, such as a variable name. Functions have one or more anonymous symbol scopes. A reference to a name in an anonymous scope can be defined in an outer anonymous scope. Functions also have input and output parameters defined. Those have their own special access rules and are defined in the outermost anonymous scope of the function. Input parameters are read only and output parameters are both read and write. All other names have access parameters specified in their definition. For a function that is declared in a class, the variables declared in the class are also considered local to an anonymous scope in a function. When there is a name defined in an anonymous scope that has already been declared in an outer scope, a warning is issued and the name used is the most local one. 

The symbol table is implemented as a hash table where sibling names are in the same table. Names that can have child names have their own hash table in which names are kept and so on. Every name has a type and access rules. 

## Implement the debugger
The debugger information will be implemented as text messages sent over an ethernet connection. The application side software is implemented in the runtime to interpret debugger commands and run the program line by line using a function that waits after each line of source code. When the line is run, then the runtime debugger reports that it's done back to the debugger UI. Design the protocol and messages. The runtime is smart enough to be able to run if the debugger is not active. 

