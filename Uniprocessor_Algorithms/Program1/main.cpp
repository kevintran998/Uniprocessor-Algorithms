// File: main.cpp
// Author: Kevin Tran
//
// This program compares First-Come-First-Served (FCFS), Round Robin (RR),
// Shortest Process Next (SPN), and Shortest Remaining Time (SRT) algorithm
// and determining which algorithm is the most efficient based on turnaround
// time and relative turn around time.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    int execTime[5] = {0};
    int tempExecTime[5] = {0};
    int finishTime[5] = {0};
    int currentTime = 0;
    int currentExecTime = 0;
    double turnaroundTime = 0;
    double relativeTurnaroundTime = 0;
    
    bool end = false;
    int counter = 0;
    long int seed = time(0);
    srand (seed);
    int random;
    
    double FCFS_Total_Turnaround_Time = 0;
    double RR_Total_Turnaround_Time = 0;
    double SPN_Total_Turnaround_Time = 0;
    double SRT_Total_Turnaround_Time = 0;
    
    double FCFS_Total_Relative_Turnaround_Time = 0;
    double RR_Total_Relative_Turnaround_Time = 0;
    double SPN_Total_Relative_Turnaround_Time = 0;
    double SRT_Total_Relative_Turnaround_Time = 0;
    
    double FCFS_Avg_Turnaround_Time = 0;
    double RR_Avg_Turnaround_Time = 0;
    double SPN_Avg_Turnaround_Time = 0;
    double SRT_Avg_Turnaround_Time = 0;
    
    double FCFS_Avg_Relative_Turnaround_Time = 0;
    double RR_Avg_Relative_Turnaround_Time = 0;
    double SPN_Avg_Relative_Turnaround_Time = 0;
    double SRT_Avg_Relative_Turnaround_Time = 0;
    
    for(int z; z < 1000; z++)
    {
        // generate random integers (1-10)
        for(int x = 0; x < 5; x++)
        {
            random = rand() % 10 + 1;
            execTime[x] = random;
        }
        
        /**************** FCFS ****************/
        for(int x = 0; x < 5; x++)
        {
            currentExecTime = execTime[x];
            
            int y = 0;
            while(y < currentExecTime)
            {
                if(currentTime >= (x * 2))
                {
                    y++;
                }
                
                currentTime++;
            }
            
            turnaroundTime =  currentTime - (x * 2);
            relativeTurnaroundTime = turnaroundTime / execTime[x];
            FCFS_Total_Turnaround_Time += turnaroundTime;
            FCFS_Total_Relative_Turnaround_Time += relativeTurnaroundTime;
        }
        
        /**************** RR (q = 1) ****************/
        
        //copy execTime array to tempExecTime array
        for(int x = 0; x < 5; x++)
        {
            tempExecTime[x] = execTime[x];
        }
        
        int queue[5] = {0};
        currentTime = 0;
        bool insert = false;
        queue[0] = 1;
        
        // processes in the queue will be offset by +1 (process #1 starts at 1 instead of 0)
        while(end != true)
        {
            // set counter to first process in the queue
            counter = queue[0];
            // move processes up one in the queue
            for(int x = 0; x < 4; x++)
            {
                queue[x] = queue[x + 1];
                queue[x+1] = 0;
            }
            
            // decremement execution time for process and increment currentTime
            tempExecTime[counter - 1]--;
            currentTime++;
            
            // hardcoded to insert processes in the queue as they arrive
            if(currentTime == 2 || currentTime == 4 || currentTime == 6 || currentTime == 8)
            {
                int x = 0;
                insert = false;
                
                while(insert != true)
                {
                    // insert process into next the empty spot
                    if(queue[x] == 0)
                    {
                        queue[x] = (currentTime / 2) + 1;
                        insert = true;
                    }
                    x++;
                }
            }
            
            // if the process is done, add the finish time to the finishTime array
            if(tempExecTime[counter - 1] == 0)
            {
                finishTime[counter - 1] = currentTime;
            }
            // otherwise add the process back into the queue
            else
            {
                int x = 0;
                insert = false;
                
                while(insert != true)
                {
                    // insert process into the next empty spot
                    if(queue[x] == 0)
                    {
                        queue[x] = counter;
                        insert = true;
                    }
                    
                    x++;
                }
            }
            
            // test to see if all processes are done executing
            if(tempExecTime[0] == 0 && tempExecTime[1] == 0 && tempExecTime[2] == 0
               && tempExecTime[3] == 0 && tempExecTime[4] == 0)
            {
                end = true;
            }
        }
        
        // calculate turnaround time and relative turnaround time
        for(int x = 0; x < 5; x++)
        {
            turnaroundTime = finishTime[x] - (x * 2);
            relativeTurnaroundTime = turnaroundTime / execTime[x];
            RR_Total_Turnaround_Time += turnaroundTime;
            RR_Total_Relative_Turnaround_Time += relativeTurnaroundTime;
        }
        
        /**************** SPN ****************/
        
        //copy execTime array to tempExecTime array
        for(int x = 0; x < 5; x++)
        {
            tempExecTime[x] = execTime[x];
        }
        
        // reset finishTime array
        for(int x = 0; x < 5; x++)
        {
            finishTime[x] = 0;
        }
        
        // reset values
        currentTime = 0;
        counter = 0;
        
        for(int x = 0; x < 5; x++)
        {
            // if first process is finished, check for next process
            if (currentTime >= 2)
            {
                // loop through current arrived processes
                for(int next = 0; (next < (currentTime / 2)) && (next < 4); next++)
                {
                    if (tempExecTime[counter] > tempExecTime[next + 1])
                    {
                        counter = next + 1;
                    }
                }
            }
            // if-statement in case there are no arrived processes to execute, increment currentTime
            if (tempExecTime[counter] > 0)
            {
                // execute process to completion
                for(int y = 0; y < execTime[counter]; y++)
                {
                    currentTime++;
                    tempExecTime[counter]--;
                }
                finishTime[counter] = currentTime;
                tempExecTime[counter] = 99; // execution time of current process is set to 99
                // to make it easier to calculate the next shortest process
            }
            else
            {
                currentTime++;
            }
        }
        
        // calculate turnaround time and relative turnaround time
        for(int x = 0; x < 5; x++)
        {
            turnaroundTime = finishTime[x] - (x * 2);
            relativeTurnaroundTime = turnaroundTime / execTime[x];
            SPN_Total_Turnaround_Time += turnaroundTime;
            SPN_Total_Relative_Turnaround_Time += relativeTurnaroundTime;
        }
        /**************** SRT ****************/
        
        //copy execTime array to tempExecTime array
        for(int x = 0; x < 5; x++)
        {
            tempExecTime[x] = execTime[x];
        }
        
        // reset finishTime array
        for(int x = 0; x < 5; x++)
        {
            finishTime[x] = 0;
        }
        
        // reset values
        currentTime = 0;
        counter = 0;
        end = false;
        
        while(end != true)
        {
            // if first process is finished, check for next process
            if (currentTime >= 2)
            {
                if(tempExecTime[0] == 99 && tempExecTime[1] == 99 && tempExecTime[2] == 99
                   && tempExecTime[3] == 99 && tempExecTime[4] == 99)
                {
                    end = true;
                }
                
                counter = 0;
                // loop through current arrived processes
                for(int next = 0; (next < (currentTime / 2)) && (next < 4); next++)
                {
                    if (tempExecTime[counter] > tempExecTime[next + 1])
                    {
                        counter = next + 1;
                    }
                }
            }
            // if-statement in case there are no arrived processes to execute, increment currentTime
            if (tempExecTime[counter] > 0)
            {
                currentTime++;
                tempExecTime[counter]--;
                if(tempExecTime[counter] == 0)
                {
                    finishTime[counter] = currentTime;
                    tempExecTime[counter] = 99; // execution time of current process is set to 99
                    // to make it easier to calculate the next shortest process
                }
            }
            else
            {
                currentTime++;
            }
        }
        // calculate turnaround time and relative turnaround time
        for(int x = 0; x < 5; x++)
        {
            turnaroundTime = finishTime[x] - (x * 2);
            relativeTurnaroundTime = turnaroundTime / execTime[x];
            SRT_Total_Turnaround_Time += turnaroundTime;
            SRT_Total_Relative_Turnaround_Time += relativeTurnaroundTime;
        }
    }
  
    /**************** Calculate and Display Final Results ****************/
    
    FCFS_Avg_Turnaround_Time = FCFS_Total_Turnaround_Time / 1000;
    RR_Avg_Turnaround_Time = RR_Total_Turnaround_Time / 1000;
    SPN_Avg_Turnaround_Time = SPN_Total_Turnaround_Time / 1000;
    SRT_Avg_Turnaround_Time = SRT_Total_Turnaround_Time / 1000;
    
    FCFS_Avg_Relative_Turnaround_Time = FCFS_Total_Relative_Turnaround_Time / 1000;
    RR_Avg_Relative_Turnaround_Time = RR_Total_Relative_Turnaround_Time / 1000;
    SPN_Avg_Relative_Turnaround_Time = SPN_Total_Relative_Turnaround_Time / 1000;
    SRT_Avg_Relative_Turnaround_Time = SRT_Total_Relative_Turnaround_Time / 1000;
    
    cout << "FCFS Turnaround Time: " << FCFS_Avg_Turnaround_Time << endl;
    cout << "FCFS Relative Turnaround Time: " << FCFS_Avg_Relative_Turnaround_Time << endl;
    cout << "------------------------------------------" << endl;
    cout << "RR Turnaround Time: " << RR_Avg_Turnaround_Time << endl;
    cout << "RR Relative Turnaround Time: " << RR_Avg_Relative_Turnaround_Time << endl;
    cout << "------------------------------------------" << endl;
    cout << "SPN Turnaround Time: " << SPN_Avg_Turnaround_Time << endl;
    cout << "SPN Relative Turnaround Time: " << SPN_Avg_Relative_Turnaround_Time << endl;
    cout << "------------------------------------------" << endl;
    cout << "SRT Turnaround Time: " << SRT_Avg_Turnaround_Time << endl;
    cout << "SRT Relative Turnaround Time: " << SRT_Avg_Relative_Turnaround_Time << endl;
    
    return 0;
}
