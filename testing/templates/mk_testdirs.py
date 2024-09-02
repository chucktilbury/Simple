import os

with open("non-terminals.txt", "r") as fp:
    lines = [s.strip() for s in fp.readlines() ]

for item in lines:
    print(item)
    os.system("mkdir -p ../inputs/%s/err"%(item))
    os.system("mkdir -p ../inputs/%s/tst"%(item))