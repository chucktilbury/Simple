import re

def convert(str):

    s = "TOK"
    for c in str:
        if c == '!': s += "_BANG"
        elif c == '@': s += "_AT"
        elif c == '#': s += "_HASH"
        elif c == '$': s += "_DOLLAR"
        elif c == '%': s += "_PERCENT"
        elif c == '^': s += "_CARAT"
        elif c == '&': s += "_AMPERSAND"
        elif c == '*': s += "_STAR"
        elif c == '(': s += "_OPAREN"
        elif c == ')': s += "_CPAREN"
        elif c == '-': s += "_MINUS"
        elif c == '=': s += "_EQUAL"
        elif c == '+': s += "_PLUS"
        elif c == '[': s += "_OSBRACE"
        elif c == ']': s += "_CSBRACE"
        elif c == '{': s += "_OCBRACE"
        elif c == '}': s += "_CCBRACE"
        elif c == '\\': s += "_BSLASH"
        elif c == ':': s += "_COLON"
        elif c == ';': s += "_SEMICOLON"
        elif c == '\'': s += "_SQUOTE"
        elif c == '\"': s += "_DQUOTE"
        elif c == ',': s += "_COMMA"
        elif c == '<': s += "_OPBRACE"
        elif c == '.': s += "_DOT"
        elif c == '>': s += "_CPBRACE"
        elif c == '/': s += "_SLASH"
        elif c == '?': s += "_QUESTION"
        elif c == '~': s += "_TILDE"
    return s

with open("simple-grammar.txt", "r") as fp:
    grammar = [ s.strip() for s in fp.readlines() ]

terminals = []
non_terminals = []

for line in grammar:
    if len(line) > 0:
        if line[0] == ':' or line[0] == '|':
            res = re.findall(r"\'([^\']+)\'", line)
            for mat in res:
                if re.match(r"[a-z]+", mat):
                    s = "TOK_%s"%(mat.upper())
                    if not s in terminals:
                        terminals.append(s)
                else:
                    #print(mat)
                    s = convert(mat)
                    if not s in terminals:
                        terminals.append(s)
            res = re.findall(r"([A-Z_]+)", line)
            for mat in res:
                if mat != "_":
                    s = "TOK_"+mat
                    if not s in terminals:
                        terminals.append(s)
        elif line[0] == ';':
            #print("end:", line)
            pass
        else:
            #print("non terminal:", line)
            if not line in non_terminals:
                non_terminals.append(line)
            else:
                print("duplicate non terminal symbol is illegal")
                _exit(1)

with open("non_terminals.txt", "w") as fp:
    for item in non_terminals:
        fp.write("%s\n"%(item))

with open("terminals.txt", "w") as fp:
    for item in terminals:
        fp.write("%s\n"%(item))
