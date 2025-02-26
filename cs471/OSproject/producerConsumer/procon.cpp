// Libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include <sstream>


//Declares a vector named 'buffer' that will store integers
std::vector<int> buffer;

// Declares that bufferSize holds the maximum number of integers
int bufferSize = 5;

// A mutex is used to synchronize access to shared resources somultiple threads cannot access the buffer at once
std::mutex bufferMutex;

class ProducerThread {
public:
    // This function overloads the '()' operator and allows it to be called (if needed)
    void operator()() {
        // Infinite loop to continuously produce items
        while (true) {
            {
                // Locks mutex so it can safely access the shared buffer
                std::lock_guard<std::mutex> lock(bufferMutex);

                // Checks if the buffer has space to add more items
                if (buffer.size() < bufferSize) 
                {
                    // Generates a random integer between 1 and 100.
                    int item = rand() % 100 + 1;

                    // Adds the generated item to the buffer
                    buffer.push_back(item);

                    // Prints a message indicating the item produced by the producer
                    std::cout << "Producer produced: " << item << std::endl;
                }
            }
            // Pauses execution for a random period between 1 to 5 seconds.
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 5000 + 1000));
        }
    }
};

class ConsumerThread {
public:
    // This function overloads the '()' operator, making objects of this class callable.
    void operator()() {
        // Infinite loop to continuously consume items.
        while (true) {
            {
                // Locks the mutex to safely access the shared 'buffer'
                std::lock_guard<std::mutex> lock(bufferMutex);
                // Checks if the buffer is not empty.
                if (!buffer.empty()) 
                {
                    // Retrieves the first item from the buffer.
                    int item = buffer.front();
                    // Removes the consumed item from the buffer.
                    buffer.erase(buffer.begin());
                    // Prints a message indicating the item consumed by the consumer.
                    std::cout << "Consumer consumed: " << item << std::endl;
                }
            }
            // Pauses execution for a random period between 1 to 5 seconds.
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 5000 + 1000));
        }
    }
};

int main(const int argc, char const * const * argv) {
    
    // Check that a file path is provided
    if (argc < 2) {
        std::cerr << "Please provide an input file path." << std::endl;
        return 1;
    }

    // Path to the output file
    std::string outputFilePath = "output.txt";
    
    // Open the output file in write mode
    std::ofstream outputFile(outputFilePath);
    
    // Error message for the output file
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    // Redirect std::cout and std::cerr to the output file
    std::streambuf* originalCoutBuf = std::cout.rdbuf(outputFile.rdbuf());
    std::streambuf* originalCerrBuf = std::cerr.rdbuf(outputFile.rdbuf());

    // Path set for the input file
    std::string filePath = argv[1];
    
    // Opens the input file
    std::ifstream inputFile(filePath);
    
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }
    
    // Read each line from the file
    std::string line;
    while (std::getline(inputFile, line)) {
        // Process each line here
        std::istringstream iss(line);
        int numProducers, numConsumers;

        if (!(iss >> numProducers >> numConsumers)) {
            std::cerr << "Error reading input file." << std::endl;
            return 1;
        }

        // Creates producer threads
        for (int i = 0; i < numProducers; ++i) {
            std::thread producerThread(ProducerThread{});
            producerThread.detach();
        }

        // Creates consumer threads
        for (int i = 0; i < numConsumers; ++i) {
            std::thread consumerThread(ConsumerThread{});
            consumerThread.detach();
        }
    }

    // Closes the input file
    inputFile.close();
    
    // Reset std::cout and std::cerr to their original states
    std::cout.rdbuf(originalCoutBuf);
    std::cerr.rdbuf(originalCerrBuf);

    // Closes the output file
    outputFile.close();

    return 0;
}
