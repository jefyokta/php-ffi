#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    char* task_name;
    int is_done;
} AsyncTask;

typedef struct {
    AsyncTask* task;
    int delay;
} AsyncTaskParam;

void* async_task(void* arg) {
    AsyncTaskParam* param = (AsyncTaskParam*) arg;
    AsyncTask* task = param->task;

    printf("C: Async task %s is running...\n", task->task_name);
    fflush(stdout);
    sleep(param->delay); 
    printf("C: Async task %s done!\n", task->task_name);
    fflush(stdout);
    task->is_done = 1;

    free(param);
    return NULL;
}

AsyncTask* run_async(const char* name, int delay) {
    pthread_t tid;

    AsyncTask* task = malloc(sizeof(AsyncTask));
    task->task_name = strdup(name);
    task->is_done = 0;

    AsyncTaskParam* param = malloc(sizeof(AsyncTaskParam));
    param->task = task;
    param->delay = delay;

    pthread_create(&tid, NULL, async_task, param);
    pthread_detach(tid);
    return task;
}

int task_done(AsyncTask* task) {
    return task->is_done;
}
