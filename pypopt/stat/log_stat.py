import matplotlib
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np

f = open("task.txt","r")
for i in range(6):
    header = f.readline()

thr = []
y_data = []
x_data = []
x = list(np.arange(0,0.4,0.1))

while True:
    s = f.readline()
    a = s.split(' ')
    b = a[6:]
    if not s:
        break    
    thr.append(b)    

temp = float(thr[0][4])
for i in range(len(thr)):    
    print(float(thr[i][4]))
    y_data.append(float(thr[i][6]))
    x_data.append(float(thr[i][4])-temp)

print()
print(y_data)
#print(x_data)

plt.bar(x_data,y_data,width=0.000002)
#plt.bar(x,y_data,width=0.05)
plt.show()



