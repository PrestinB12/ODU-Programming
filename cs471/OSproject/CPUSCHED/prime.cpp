#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include "scheduler.cpp"
using namespace std;


int main() {
    //Output File Creation Function
    ofstream outFile("output.txt");
    if (!outFile) {
        cerr << "Error: Unable to create text file" << endl;
        return 1; // Return an error code indicating failure
    }
    queue<Process> processes;
    readProcessesFromFile(processes);

    // Simulate FIFO scheduling
    queue<Process> fifoProcesses = processes; // Copy processes for FIFO
    auto completed = simulateFIFO(fifoProcesses);
    cout << "FIFO Scheduling Results:" << endl;

   
    printStatistics(completed, outFile);
    cout << endl;

    
    // Simulate SJF scheduling
    queue<Process> sjfProcesses = processes; // Copy processes for SJF
    auto completed2 = simulateSJF(sjfProcesses);
    cout << "SJF Scheduling Results:" << endl;
    printStatistics(completed2, outFile);
    cout << endl;

    // Simulate Priority scheduling
    queue<Process> priorityProcesses = processes; // Copy processes for Priority
    auto completed3 = simulatePriority(priorityProcesses);
    cout << "Priority Scheduling Results:" << endl;
    printStatistics(completed3, outFile);
    cout << endl;

    

    return 0;
}