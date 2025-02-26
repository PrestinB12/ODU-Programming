bool lock = false;

// For Process P1
do 
{
    flag[x] = true;
    turn = x;
    while (flag[y] && turn == y);

    while (compare_and_swap(&lock, false, true) != false); // Entry section
    
    // Critical section
    lock = false; 

    // Exit section
    flag[x]
}