#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// Struct represents a process
struct Process {
    // Process ID
    int pid; 
    
    // Arrival time
    int arrivalTime; 
    
    // Priority
    int priority;
    
    // CPU burst time
    int burstTime; 
    
    // Start time
    int startTime; 
   
    // Waiting time
    int waitingTime; 
    
    // Turnaround time
    int turnaroundTime; 

 //Constructor
    Process(int id, int at, int bt, int prio) : pid(id), arrivalTime(at), burstTime(bt), priority(prio),
        startTime(0), waitingTime(0), turnaroundTime(0) {}
};

//Read simulated processes data from file and store them in a queue
void readProcessesFromFile(queue<Process>& processes) {
    //Use ifstream to read the text data file
    ifstream inputFile("datafile.txt");
    if (!inputFile) {
        //Error when file is not open after execution
        cerr << "Error: Unable to open file!" << endl;
        exit(1);
    }
    
    //Variables to store process attributes
    int id = 0, arrivalTime, burstTime, priority;
    
    //Read Process data from the file until the end of file is reached
    while (inputFile >> arrivalTime >> burstTime >> priority) {
        //Create a process object with the read data and push it to the queue 
        processes.push(Process(id, arrivalTime, burstTime, priority));
        //Increment id -- next process
        ++id;

        //cout << processes.size() << "\n";
    }
    inputFile.close();
}


// Compares processes based on their arrival times
struct ArrivalComparator {
    bool operator()(const Process& p1, const Process& p2) const {
        return p1.arrivalTime > p2.arrivalTime;
    }
};

// Compares processes based on their burst times for SJF
struct BurstTimeComparator {
    bool operator()(const Process& p1, const Process& p2) const {
        return p1.burstTime > p2.burstTime;
    }
};

// Compares processes based oon priorities for Priority Scheduling
struct PriorityComparator {
    bool operator()(const Process& p1, const Process& p2) const {
        return p1.priority > p2.priority;
    }
};

// Function to simulate the CPU scheduler using FIFO algorithm
static queue<Process> simulateFIFO(queue<Process>& processes) {
    
    //Queue to store completed processes
    std::queue<Process> completed;
    //Current time initialization
    int currentTime = 0;

    //Using while loop until process queue is empty 
    while (!processes.empty()) {

        //Get first process from queue
        Process currentProcess = processes.front();
        processes.pop();

        //If arrivial time of current process > current time, update
        //current time to the arrical time of current process
        if (currentProcess.arrivalTime > currentTime) {
            currentTime = currentProcess.arrivalTime;
        }

        //Set the start time of the current process to current time
        currentProcess.startTime = currentTime;
        
        //Calculate turnarounf time for current process
        currentProcess.turnaroundTime = currentTime + currentProcess.burstTime - currentProcess.arrivalTime;
        
        // Calculate waiting time for the current process
        currentProcess.waitingTime = currentProcess.startTime - currentProcess.arrivalTime;
        
        // Update the current time by adding the burst time of the current process
        currentTime += currentProcess.burstTime;

        // Push the completed current process into the completed queue
        completed.push(currentProcess);
    }

    //Return queue of the completed process
    return completed;
}

// Function to simulate the CPU scheduler using SJF algorithm (Non-preemptive)
static queue<Process> simulateSJF(queue<Process>& processes) {
    //Queue to store completed processes
    std::queue<Process> completed2;

    int currentTime = 0;

     // Priority queue to store processes sorted based on burst times
    priority_queue<Process, vector<Process>, BurstTimeComparator> readyQueue;
    

    // Loop until both the incoming processes queue and ready queue are empty
    while (!processes.empty() || !readyQueue.empty()) {

         // Add arriving processes to the ready queue
        while (!processes.empty() && processes.front().arrivalTime <= currentTime) {
            readyQueue.push(processes.front());
            processes.pop();
        }

        // If there are processes ready to execute
        if (!readyQueue.empty()) 
        {
            // Get the process with the shortest burst time from the ready queue
            Process currentProcess = readyQueue.top();
            readyQueue.pop();

            // Set the start time of the current process to the current time
            currentProcess.startTime = currentTime;

            // Calculate turnaround time for the current process
            currentProcess.turnaroundTime = currentTime + currentProcess.burstTime - currentProcess.arrivalTime;

            // Calculate waiting time for the current process
            currentProcess.waitingTime = currentProcess.startTime - currentProcess.arrivalTime;

            // Update the current time by adding the burst time of the current process
            currentTime += currentProcess.burstTime;

            // Push the completed current process into the completed queue
            completed2.push(currentProcess);
        } 

        // If there are no processes ready to execute, update the current time
            // to the arrival time of the next incoming process
        else 
        {
            currentTime = processes.front().arrivalTime;
        }
    }

    return completed2;
}

// Function to simulate the CPU scheduler using Priority Scheduling algorithm (Preemptive)
static queue<Process> simulatePriority(queue<Process>& processes) 
{
    //Queue to store completed processes
    std::queue<Process> completed3;
    
    int currentTime = 0;
    
    // Priority queue to store processes sorted based on burst times
    priority_queue<Process, vector<Process>, PriorityComparator> readyQueue;

    // Loop until both the incoming processes queue and the ready queue are empty
    while (!processes.empty() || !readyQueue.empty()) 
    {
        // Process all arriving processes until the current time
        // Update the ready queue accordingly
        while (!processes.empty() && processes.front().arrivalTime <= currentTime) {
            readyQueue.push(processes.front());
            processes.pop();
        }

        // If there are processes ready to execute in the ready queue
        if (!readyQueue.empty()) {

            // Get the process with the shortest burst time from the ready queue
            Process currentProcess = readyQueue.top();
            readyQueue.pop();

            // Set the start time of the current process to the current time
            currentProcess.startTime = currentTime;

            // Calculate turnaround time for the current process
            currentProcess.turnaroundTime = currentTime + currentProcess.burstTime - currentProcess.arrivalTime;

            // Calculate waiting time for the current process
            currentProcess.waitingTime = currentProcess.startTime - currentProcess.arrivalTime;

             // Update the current time by adding the burst time of the current process
            currentTime += currentProcess.burstTime;
            
            // Push the completed current process into the completed queue
            completed3.push(currentProcess);
        } else {

            // If there are no processes ready to execute, update the current time
            // to the arrival time of the next incoming process
            currentTime = processes.front().arrivalTime;
        }

        
    }
    
    return completed3;
}


//Print Statistics function
void printStatistics(const queue<Process>& processes, ofstream& outFile) {

    // Initialize variables to store statistical information
    int totalElapsed = 0;
    int totalBurstTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;
    int numProcesses = processes.size();

    queue<Process> tempQueue = processes;
    while (!tempQueue.empty()) {
        
        // Retrieve the next process from the queue
        Process process = tempQueue.front();
        
        // Update total burst time and total elapsed time
        totalBurstTime += process.burstTime;
        totalElapsed = max(totalElapsed, process.arrivalTime + process.burstTime);
        
         // Calculate waiting time, turnaround time, and response time for the process
        totalWaitingTime += (totalElapsed - process.arrivalTime - process.burstTime);
        totalTurnaroundTime += (totalElapsed - process.arrivalTime);
        totalResponseTime += (totalElapsed - process.arrivalTime);
        tempQueue.pop();
    }
    
     // Calculate metrics based on collected statistics
    double throughput = static_cast<double>(totalBurstTime) / numProcesses;
    double cpuUtilization = static_cast<double>(totalBurstTime) / totalElapsed;
    double avgWaitingTime = static_cast<double>(totalWaitingTime) / numProcesses;
    double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / numProcesses;
    double avgResponseTime = static_cast<double>(totalResponseTime) / numProcesses;

    // Print statistics to terminal
    cout << "Number of processes: " << numProcesses << endl;
    cout << "Total elapsed time: " << totalElapsed << endl;
    cout << "Throughput: " << throughput << endl;
    cout << "CPU utilization: " << cpuUtilization << endl;
    cout << "Average waiting time: " << avgWaitingTime << endl;
    cout << "Average turnaround time: " << avgTurnaroundTime << endl;
    cout << "Average response time: " << avgResponseTime << endl;

    // Write statistics to output file
    outFile << "Number of processes: " << numProcesses << endl;
    outFile << "Total elapsed time: " << totalElapsed << endl;
    outFile << "Throughput: " << throughput << endl;
    outFile << "CPU utilization: " << cpuUtilization << endl;
    outFile << "Average waiting time: " << avgWaitingTime << endl;
    outFile << "Average turnaround time: " << avgTurnaroundTime << endl;
    outFile << "Average response time: " << avgResponseTime << endl;
    outFile << endl;
}




