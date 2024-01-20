# Basic Task Scheduler in C

This C program implements a basic task scheduler with multithreading capabilities. It allows users to schedule file and folder operations and execute Linux commands with specified delays.

## How to Run

1. **Clone the Repository and Execute:**

   ```bash
   git clone https://github.com/Thaman-N/Basic-Task-Scheduler.git
   cd Basic-Task-Scheduler
   gcc -o task_scheduler task_scheduler.c -pthread
   ./task_scheduler

## 2. Using Functions

Apart from the main program execution, you can also use the provided functions to interact with the task scheduler. These functions allow you to schedule tasks based on your specific requirements.

### Functions Available

#### 1. `void inserttask(int delay, void (*function)(char *, char *), char *arg1, char *arg2)`

This function allows you to manually insert tasks into the scheduler. It takes the following parameters:

- `delay`: The delay (in seconds) before the task is executed.
- `function`: The function pointer to the task you want to schedule.
- `arg1` and `arg2`: Additional arguments required by the scheduled function.

#### 2. `void executetasks()`

This function initiates the execution of all scheduled tasks in the background. It creates separate threads for each task, allowing them to run concurrently.

### Example

To use these functions, follow these steps:

1. **Include Headers:**

   Make sure to include the necessary headers at the beginning of your program.

   ```c
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <stdbool.h>
   #include <unistd.h>
   #include <pthread.h>

2. **Choose Function and pass arguments:**

  ```html
  1. Create file
  2. Rename file
  3. Delete file
  4. Execute Python file
  5. Execute Bash file
  6. Create folder
  7. Rename folder
  8. Delete folder
  Enter your choice: 1
  Enter delay (in seconds): 5
  Enter file name to create: my_file.txt
```

  ```html
  1. Create file
  2. Rename file
  3. Delete file
  4. Execute Python file
  5. Execute Bash file
  6. Create folder
  7. Rename folder
  8. Delete folder
  Enter your choice: 6
  Enter delay (in seconds): 2
  Enter folder name to create: my_folder
```
  ```html
  1. Create file
  2. Rename file
  3. Delete file
  4. Execute Python file
  5. Execute Bash file
  6. Create folder
  7. Rename folder
  8. Delete folder
  Enter your choice: 9
```

3. **Wait**
   The program may exit but the tasks will still be executed
