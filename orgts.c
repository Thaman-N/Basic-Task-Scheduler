#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define maxt 50

typedef struct {
    int delay;
    void (*function)(char *, char *);
    char arg1[100];
    char arg2[100];
} task;

task tasks[maxt];
int sheap = 0;

void swap(task *a, task *b){
    task temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int i){
    int mnmm = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < sheap && tasks[l].delay < tasks[mnmm].delay)
        mnmm = l;
    if (r < sheap && tasks[r].delay < tasks[mnmm].delay)
        mnmm = r;
    if (mnmm != i) {
        swap(&tasks[i], &tasks[mnmm]);
        heapify(mnmm);
    }
}

void inserttask(int delay, void (*function)(char *, char *), char *arg1, char *arg2){
    if (sheap >= maxt) {
        printf("task queue is full.\n");
        return;
    }
    tasks[sheap].delay = delay;
    tasks[sheap].function = function;
    strcpy(tasks[sheap].arg1, arg1);
    strcpy(tasks[sheap].arg2, arg2);
    int i = sheap;
    while (i > 0 && tasks[(i - 1) / 2].delay > tasks[i].delay) {
        swap(&tasks[i], &tasks[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    sheap++;
}

void *taskExecutor(void *arg){
    task *curtask = (task *)arg;
    sleep(curtask->delay);
    curtask->function(curtask->arg1, curtask->arg2);
    return NULL;
}

void executetasks() {
    for (int i = 0; i < sheap; ++i) {
        pthread_t tid;
        pthread_create(&tid, NULL, taskExecutor, &tasks[i]);
        pthread_join(tid, NULL);
    }
}

void filecreate(char *rootn, char *filen){
    char command[500];
    snprintf(command, sizeof(command), "mkdir -p %s && touch %s && echo 'a=5' > %s", rootn, filen, filen);
    system(command);
}

void filerename(char *rootn, char *oldn){
    char newn[200];
    printf("Enter desired new name:\n");
    scanf("%199s", newn);
    char command[500];
    snprintf(command, sizeof(command), "mv %s %s", oldn, newn);
    system(command);
}

void delfile(char *rootn, char *filen){
    char command[500];
    snprintf(command, sizeof(command), "rm %s", filen);
    system(command);
}

void executepy(char *rootf, char *fname){
    char command[500];
    snprintf(command, sizeof(command), "python3 %s", fname);
    system(command);
}

void eexecbash(char *rootf, char *fname){
    char command[500];
    snprintf(command, sizeof(command), "bash %s", fname);
    system(command);
}

void foldercreate(char *rootn, char *folderName){
    char command[500];
    snprintf(command, sizeof(command), "mkdir -p %s", folderName);
    system(command);
}

void folderrename(char *rootn, char *oldn){
    char newn[200];
    printf("Enter desired new name:\n");
    scanf("%199s", newn);
    char command[500];
    snprintf(command, sizeof(command), "mv %s %s", oldn, newn);
    system(command);
}

void delfolder(char *rootn, char *folderName){
    char command[500];
    snprintf(command, sizeof(command), "rm -r %s", folderName);
    system(command);
}

/*
int main() {
    char root_folder[] = "root_folder";

    inserttask(0, foldercreate, root_folder, "folder_1");
    inserttask(2, foldercreate, root_folder, "folder_2");
    inserttask(4, filecreate, root_folder, "folder_1/file_1.txt");
    inserttask(6, filecreate, root_folder, "folder_1/file_2.txt");
    inserttask(8, filecreate, root_folder, "folder_2/file_3.txt");
    inserttask(10, folderrename, root_folder, "folder_1");
    inserttask(12, filerename, root_folder, "folder_2/file_3.txt");
    // Add other tasks as needed

    // Execute scheduled tasks
    executetasks();

    return 0;
}
*/

int main() {
    int choice, delay;
    char arg1[100], arg2[100];
    char root_folder[] = "root_folder";

    while (1) {
        printf("\n1. Create file\n");
        printf("2. Rename file\n");
        printf("3. Delete file\n");
        printf("4. Execute Python file\n");
        printf("5. Execute Bash file\n");
        printf("6. Create folder\n");
        printf("7. Rename folder\n");
        printf("8. Delete folder\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 9) {
            break;  // Exit the loop and end the program
        }

        printf("Enter delay (in seconds): ");
        scanf("%d", &delay);

        switch (choice) {
            case 1:
                printf("Enter file name to create: ");
                scanf("%99s", arg1);
                inserttask(delay, filecreate, root_folder, arg1);
                break;
            case 2:
                printf("Enter old file name to rename: ");
                scanf("%99s", arg1);
                filerename(root_folder, arg1);
                break;
            case 3:
                printf("Enter file name to delete: ");
                scanf("%99s", arg1);
                inserttask(delay, delfile, root_folder, arg1);
                break;
            case 4:
                printf("Enter Python file name to execute: ");
                scanf("%99s", arg1);
                inserttask(delay, executepy, root_folder, arg1);
                break;
            case 5:
                printf("Enter Bash file name to execute: ");
                scanf("%99s", arg1);
                inserttask(delay, eexecbash, root_folder, arg1);
                break;
            case 6:
                printf("Enter folder name to create: ");
                scanf("%99s", arg1);
                inserttask(delay, foldercreate, root_folder, arg1);
                break;
            case 7:
                printf("Enter old folder name to rename: ");
                scanf("%99s", arg1);
                folderrename(root_folder, arg1);
                break;
            case 8:
                printf("Enter folder name to delete: ");
                scanf("%99s", arg1);
                inserttask(delay, delfolder, root_folder, arg1);
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    // Execute scheduled tasks
    executetasks();

    return 0;
}
