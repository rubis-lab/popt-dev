1. Generate ftrace log data by using trace-cmd 

# start tracing
sudo trace-cmd start -e sched 

# do something whatever you want

# stop tracigng
sudo trace-cmd stop 

2. Extract the generated ftrace log data by using trace-cmd 
sudo trace-cmd extract -o [filename].dat 