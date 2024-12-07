import re
# input

text = ""

with open('data.txt') as f:
    sum = 0
    flag = True
    for line in f:
        l = re.findall(r'mul\([0-9]{,3},[0-9]{,3}\)|do\(\)|don\'t\(\)', line)
        for i in l:
            if i == "do()":
                flag = True
            elif i == "don't()":
                flag = False
            else:
                if flag:
                    a = int(i.split(",")[0].split("(")[1])
                    b = int(i.split(",")[1].split(")")[0])
                    sum += a * b
    print(sum)
