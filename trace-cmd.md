# Generate ftrace log data by using trace-cmd

1. start tracing
sudo trace-cmd start -e sched 

2. do something whatever you want

3. stop tracigng
sudo trace-cmd stop 

4. Extract the generated ftrace log data by using trace-cmd 
sudo trace-cmd extract -o [filename].dat 