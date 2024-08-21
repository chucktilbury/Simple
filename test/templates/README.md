# DO NOT RUN THIS SCRIPT
### Unless you plan to reset the AST and the parser and LOSE ALL MANUAL CHANGES

This script automates creating the token, parser, and AST files as much as possible without actually trying to create the parser. The grammar is read (in the docs directory) and processed into the boilerplate files. This script generates almost 200 files that would otherwise have to be created by hand. None of those files have any actual functionality. They must receive extensive modifications to actually implement the parser. 

There is almost no checking done on the grammar to ensure that it's formatted correctly. Extensive checking has been done manually to make sure that correct output is produced. Re-running this script after changing the grammar is discouraged. There are no doubt errors in the grammar. The recommended procedure for correcting it is to first correct the grammar and then manually correct the tokens, parser, and AST in that order. 