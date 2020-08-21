

f = open("task.txt","r")
header = f.readline(7)
thr = []
i = 0

while True:
    s = f.readline()
    a = s.split(' ')
    b = a[6:]
    if not s:
        break       
    thr[i] = b[6]
    i += 1

for i in range(len(thr)):
    print(thr[i])


