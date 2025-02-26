import threading
import time
import random
import datetime

t = 0
flag = [False, False]
current_res = False

mutex = thread.lock()

def get_current_time():
    current_time = datetime.datetime.now().strftime("%H:%M:%S.%f")
    return current_time[:-3]

def peterson_acquire(currentThread):
    newThread = 1 - currentThread
    flag[currentThread] = True
    t = newThread
    
    while flag[newThread] and t == newThread:
        pass

def peterson_release(currentThread):
    flag[currentThread] = False

# Print statements for the threads (current time and requested/released resources)
def prompt_res(currentThread):
    peterson_acquire(currentThread)
    print(f"Time: {get_current_time()} Thread {currentThread + 1} requested the resource")

def release_resource(currentThread):
    peterson_release(currentThread)
    print(f"Time: {get_current_time()} Thread {currentThread + 1} released the resource")

def thread_function(currentThread):
    for _ in range(3):
        prompt_res(currentThread)

        # Holds a resource for a specific time 
        time.sleep(random.uniform(1, 3))

        release_resource(currentThread)

        # Time before the next request is made
        time.sleep(random.uniform(1, 3))

# Creates a pair of threads
thread1 = threading.Thread(target=thread_function, args=(0,))
thread2 = threading.Thread(target=thread_function, args=(1,))

# Threads starting
thread1.start()
thread2.start()

# Threads joining the current thread
thread1.join()
thread2.join()
