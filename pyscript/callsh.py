import os
from datetime import datetime
from time import time
import math


print("hi")

for _ in range(1, 11):
    os.system("sh test.sh 1 2")
    print('{}\'s shell script finished'.format(_))

exit()
