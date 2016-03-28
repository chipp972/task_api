#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "task_config.h"
#include "task.h"
#include "task_queue.h"
#include "exit_task.h"
#include "task_manager.h"


void *worker(void *arg)
{
    struct task_manager_params *p;
    p = (struct task_manager_params*) arg;
    task_t *task;
    void (*execTask) (task_queue_t*, task_t*);

    while(1) {
        task = popTask(p->tq);
        execTask = task->execTask;
        // pass the shared variable
        task->shared_params = p->shared_params;
        execTask(p->tq, task);
    }
    pthread_exit(0);
}


void *taskManager(void *arg)
{
    pthread_t *th;
    int i;
    task_manager_params_t *p;
    p = (task_manager_params_t *) arg;

    if (p->workers_nb < 1) {
        fprintf(stderr, "Error: minimum workers number is 1\n");
        pthread_exit(0);
    }

    th = malloc(sizeof(pthread_t) * p->workers_nb);

    for (i = 0; i < p->workers_nb; i++)
        pthread_create(&th[i], NULL, worker, (void *)p);

    for (i = 0; i < p->workers_nb; i++)
        pthread_join(th[i], NULL);

    free(th);
    free(arg);
    pthread_exit(0);
}


task_manager_t *startNewTaskManager(int nb, void *shared_params)
{
    pthread_t *th;
    task_manager_t *tm;
    task_manager_params_t *params;

    params = malloc(sizeof(task_manager_params_t));
    TEST_ALLOC(params, "params in startTaskManager");

    params->workers_nb = nb;
    params->shared_params = shared_params;
    params->tq = newTaskQueue();
    TEST_ALLOC(params->tq, "Task queue in startNewtaskManager");


    th = malloc(sizeof(pthread_t));
    TEST_ALLOC(params, "th in startTaskManager");

    pthread_create(th, NULL, taskManager, (void *)params);

    tm = malloc(sizeof(task_manager_t));
    TEST_ALLOC(tm, "tm in startTaskManager");

    tm->thread = th;
    tm->task_queue = params->tq;
    tm->workers_nb = nb;
    return tm;
}


void stopTaskManager(task_manager_t *tm)
{
    addTask(tm->task_queue, createExitAllTask(tm->workers_nb));
    pthread_join(*(tm->thread), NULL);
    free(tm->thread);
    freeTaskQueue(tm->task_queue);
}
