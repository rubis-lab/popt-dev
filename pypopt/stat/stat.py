import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import tikzplotlib
import numpy as np
############ Base
print("stat")

'''
Generator - mstgen
min_exec_time = 50
max_exec_time = 150
min_deadline = 100
max_deadline = 500
min_period = 100
max_period = 500
implicit_deadline = False
constrained_deadline = True
tot_util = 4.0
util_over = True
implicit_deadline = False
constrained_deadline = True
min_seg_size = 20
max_seg_size = 80
max_option = 4
overhead = 0.3
variance = 0.7
'''

single_ydata=[1, 1, 0.982049553, 0.954088846, 0.947046539, 0.937889921, 0.925010106, 0.908357199, 0.891198441, 0.862872594, 0.825712708, 0.805799517, 0.784850133, 0.733536033, 0.672586822, 0.592030487, 0.504694999, 0.431020008, 0.354033197, 0.282248251, 0.216654793, 0.167553634, 0.114991705, 0.074902282, 0.046984185, 0.028590426, 0.016282613, 0.006141445, 0.004107365, 0.001402525, 0.000735971, 0.000269397, 0.000172191, 0.000169000, 0, 0, 0, 0, 0, 0]
max_ydata=[1, 1, 1, 1, 1, 1, 1, 0.999088779, 0.992140305, 0.978497393, 0.949092294, 0.901284824, 0.830271954, 0.740910855, 0.641687574, 0.537340376, 0.434513459, 0.341262068, 0.246214327, 0.171965318, 0.11208739, 0.069848661, 0.045577578, 0.025634033, 0.014711291, 0.007883739, 0.004189678, 0.002111122, 0.000764161, 0.000093500, 0.000183993, 0.000089800, 0, 0, 0, 0, 0, 0, 0, 0]
random_ydata=[1, 1, 0.998988707, 0.997023588, 0.996643795, 0.993414668, 0.984638189, 0.968497787, 0.941149724, 0.896414086, 0.827218484, 0.748505279, 0.640812618, 0.519407427, 0.403340816, 0.297720131, 0.213118175, 0.147334546, 0.090346535, 0.051642835, 0.030079949, 0.015965408, 0.011263424, 0.004272339, 0.002574476, 0.000949848, 0.0009522, 0.00019192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
cho_ydata=[1, 1, 1, 1, 1, 1, 1, 1, 0.999740175, 0.999227451, 0.996318395, 0.989823178, 0.973583436, 0.941260189, 0.890730226, 0.827238083, 0.73861028, 0.647474465, 0.525844496, 0.41945543, 0.320747249, 0.243389323, 0.172181961, 0.113262431, 0.071257815, 0.044642857, 0.024090649, 0.009883888, 0.005444646, 0.001870033, 0.001103956, 0.000538793, 0.000172191, 0.000168819, 0, 0, 0, 0, 0, 0]
x=list(np.arange(0,4,0.1))

plt.plot(x,single_ydata,'ko-',label='Single',markerfacecolor='none',linewidth=0.5)
plt.plot(x,max_ydata,'k^-',label='Max',markerfacecolor='none',linewidth=0.5)
plt.plot(x,random_ydata,'ks-',label='Random',markerfacecolor='none',linewidth=0.5)
plt.plot(x,cho_ydata,'kx-',label='Ours',markerfacecolor='none',linewidth=0.5)
#plt.rcParams[“font.family”] = ‘Courier New’
#print(plt.rcParams[‘font.family’])
plt.xlabel('util')
plt.ylabel('sched')
plt.axis([0.0 , 4.0 , 0 ,1.0])
plt.legend(edgecolor='none')
tikzplotlib.save("ext_base.tex")
plt.show()