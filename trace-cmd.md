# Generate ftrace log data by using trace-cmd

1. start tracing
    - sudo trace-cmd start -e sched 

2. do something whatever you want

3. stop tracigng
    - sudo trace-cmd stop 

4. Extract the generated ftrace log data by using trace-cmd 
    - sudo trace-cmd extract -o [filename]

5. See the log data by using kernel shark
    - kernelshark [fiename]


## Generate ftrace log data of our tasks

*Problem is this command can't provide proper log data.*
    - sudo trace-cmd record -e sched -F /home/rubis/rt-preempt-docs/eg1/EG1 /home/rubis/rt-preempt-docs/eg1/sample.json