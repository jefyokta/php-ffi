#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    char* task_name;
    int is_done;
} AsyncTask;

void* async_task(void* arg) {
    AsyncTask* task = (AsyncTask*) arg;
    printf("⏳ C: Async task %s is running...\n", task->task_name);
    fflush(stdout);
    sleep(2); // simulasi kerja
    printf("✅ C: Async task %s done!\n", task->task_name);
    fflush(stdout);
    task->is_done = 1;
    return NULL;
}

AsyncTask* run_async(const char* name) {
    pthread_t tid;
    AsyncTask* task = malloc(sizeof(AsyncTask));
    task->task_name = strdup(name);
    task->is_done = 0;
    pthread_create(&tid, NULL, async_task, task);
    pthread_detach(tid);
    return task;
}

int task_done(AsyncTask* task) {
    return task->is_done;
}
