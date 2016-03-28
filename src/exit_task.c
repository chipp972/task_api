#include <stdlib.h>
#include <stdio.h>

#include "task_config.h"
#include "task.h"
#include "task_queue.h"
#include "exit_task.h"


task_t *createExitTask()
{
    task_t *new_task;
    new_task = newBasicTask(exiter, NULL);
    return new_task;
}


void exiter(task_queue_t *tq, task_t *task)
{
    pthread_exit(0);
}


task_t *createExitAllTask(int nb)
{
    task_t *new_task;
    struct exit_all_params *p;
    new_task = newBasicTask(allExiter, createExitTask);

    new_task->params = malloc(sizeof(struct exit_all_params));
    TEST_ALLOC(new_task->params, "new_task->params at createExitAllTask");
    p = (struct exit_all_params *)new_task->params;

    p->workers_nb = nb;

    return new_task;
}


void allExiter(task_queue_t *tq, task_t *task)
{
    int i;
    struct exit_all_params *params;
    params = (struct exit_all_params *)task->params;
    task_t* (*newTask) ();
    newTask = (task->createNextTask);

    for (i = 0; i < params->workers_nb; i++)
        addTask(tq, (*newTask)());
    free(task->params);
}
