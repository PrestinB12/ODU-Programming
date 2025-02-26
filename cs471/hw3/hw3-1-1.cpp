bool lock = false;

// Process 1
do 
{
    while (test_and_set(&lock)); // Entry
    // Critical section
    lock = false; // Exit
} 
while (true);

// Process 2
do 
{
    while (test_and_set(&lock));
    lock = false;
} 
while (true);

// Process 3
do 
{
    while (test_and_set(&lock));
    lock = false;
} 
while (true);