#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task_config.h"
#include "task.h"


task_t *newBasicTask(void *taskFunction, void *nextTaskCreator)
{
    task_t *new_task;
    new_task = malloc(sizeof(task_t));
    TEST_ALLOC(new_task, "new_task in newBasicTask");
    new_task->execTask = taskFunction;
    new_task->createNextTask = nextTaskCreator;
    new_task->params = NULL;
    new_task->shared_params = NULL;
    return new_task;
}
