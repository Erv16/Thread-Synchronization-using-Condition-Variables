# Thread-Synchronization-using-Condition-Variables

PART I: on-demand 2-thread synchronization
In the ﬁrst part of the program named “cv-sync-1”,  two new threads (t1 and t2) are creates at runtime, and  it achieves an execution order for the two new threads according to user input. Speciﬁcally, this program takes three inputs from user: 
• total runs: a positive integer that speciﬁes the total number of runs of t1 and t2 before the program ends. 
• t1 runs: a non-negative integer that speciﬁes the number of consecutive runs for t1 before switching to t2. 
• t2 runs: a non-negative integer that speciﬁes the number of consecutive runs for t2 before switching back to t1.
t1 runs and t2 runs cannot be zero at the same time. 
Additional requirements for the the program: 
• When a child thread runs, it just prints the global index of the run (starting from 1), its name, and its thread ID. 
• When the total number runs of t1 and t2 reaches total run , t1 and t2 terminate. Then the main thread reports the numbers of runs by t1 and t2 respectively, and exits.
The following are the several examples for the expected output:
Example 1: 
$ ./cv-sync-1 5 1 1 
01: IN T1, TID=140067072816896 
02: IN T2, TID=140067064424192 
03: IN T1, TID=140067072816896 
04: IN T2, TID=140067064424192
 05: IN T1, TID=140067072816896 
In main thread: T1 printed 3 times. T2 printed 2 times.

Example 2: 
$ ./cv-sync-1 10 1 3 
01: IN T1, TID=140168770496256 
02: IN T2, TID=140168762103552 
03: IN T2, TID=140168762103552 
04: IN T2, TID=140168762103552 
05: IN T1, TID=140168770496256 
06: IN T2, TID=140168762103552 
07: IN T2, TID=140168762103552 
08: IN T2, TID=140168762103552
09: IN T1, TID=140168770496256 
10: IN T2, TID=140168762103552 
In main thread: T1 printed 3 times. T2 printed 7 times.

Example 3: 
$ ./cv-sync-1 5 1 0 
01: IN T1, TID=140435419703040 
02: IN T1, TID=140435419703040 
03: IN T1, TID=140435419703040 
04: IN T1, TID=140435419703040 
05: IN T1, TID=140435419703040 
In main thread: T1 printed 5 times. T2 printed 0 times.

PART II: on-demand 3-thread synchronization
The second part of the program named “cv-sync-2” is very similar to the previous program. The diﬀerence being that this program performs synchronization among three runtime-created threads instead of two. Some examples of the program are as follows:
Example 1: 
$ ./cv-sync-2 8 1 1 1 
01: IN T1, TID=140232873666304 
02: IN T2, TID=140232865273600 
03: IN T3, TID=140232856880896 
04: IN T1, TID=140232873666304 
05: IN T2, TID=140232865273600 
06: IN T3, TID=140232856880896 
07: IN T1, TID=140232873666304 
08: IN T2, TID=140232865273600
 In main thread: T1 printed 3 times. T2 printed 3 times. T3 printed 2 times

Example 2: 
$ ./cv-sync-2 15 3 2 1 
01: IN T1, TID=140720261293824 
02: IN T1, TID=140720261293824 
03: IN T1, TID=140720261293824 
04: IN T2, TID=140720252901120 
05: IN T2, TID=140720252901120 
06: IN T3, TID=140720244508416 
07: IN T1, TID=140720261293824 
08: IN T1, TID=140720261293824 
09: IN T1, TID=140720261293824 
10: IN T2, TID=140720252901120 
11: IN T2, TID=140720252901120 
12: IN T3, TID=140720244508416 
13: IN T1, TID=140720261293824 
14: IN T1, TID=140720261293824 
15: IN T1, TID=140720261293824 
In main thread: T1 printed 9 times. T2 printed 4 times. T3 printed 2 times

Example 3:
 $ ./cv-sync-2 5 1 1 0 
01: IN T1, TID=140167402538752 
02: IN T2, TID=140167394146048 
03: IN T1, TID=140167402538752 
04: IN T2, TID=140167394146048 
05: IN T1, TID=140167402538752 
In main thread: T1 printed 3 times. T2 printed 2 times. T3 printed 0 times
