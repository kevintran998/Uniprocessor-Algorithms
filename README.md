# Uniprocessor-Algorithms

***** DESCRIPTION *****
This program compares First-Come-First-Served (FCFS), Round Robin (RR),
Shortest Process Next (SPN), and Shortest Remaining Time (SRT) algorithm
and determining which algorithm is the most efficient based on turnaround
time and relative turn around time.

***** PROGRAM SPECIFICATIONS *****
- Generates random test data for 1000 different simulations with 20 processes
(5 per algorithm) for each simulation
- No user input is required
- Outputs a chart displaying Turnaround Time and Relative Turnaround Time
for each of the four algorithms

***** PROGRAMING LANGUAGE AND TOOLS *****
- Written in C++
- Xcode

***** WHAT I LEARNED *****
I learned how the four algorithms process data and which one would be the 
most efficient to implement in a uniprocessor system.

***** STEP BY STEP DESCRIPTION *****
The first step in creating this program is to generate random integers for our test data. The test data must be consistent for all algorithms within a single simulation, so five randomly generated integers are placed in an array and kept constant throughout the duration of the current simulation. Next, the test data will run through the algorithms one by one: FCFS, RR, SPN, and SRT, in that order. At the end of each algorithm, a running total for the turnaround time and relative turnaround time is kept for calculations at the end of the program. The program will then loop for 1000 simulations, using different test data each time. At the end of the program, average turnaround time and average relative turnaround time are calculated for each algorithm and output to the screen in a table. After executing the program several times and comparing the output data, I came to an interesting conclusion. First-come-first-served was the least efficient by far. Then round robin and shortest remaining time were tied for second. The average turnaround time and average relative turnaround time for these two algorithms were very similar. Shortest process next was the most efficient algorithm in all of my tests, so I conclude that SPN is the most efficient algorithm of the four.
