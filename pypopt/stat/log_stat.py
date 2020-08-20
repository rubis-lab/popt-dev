

f = open("task.txt","r")
for i in range(0, 6):
    header = f.readline()
    

while True:
    s = f.readline()
    a = s.split(' ')
    b = a[6:]
    if not s:
        break       
    print(b[6])


