#include <stdlib.h>
#include <stdio.h>

#include "task_api.h"
#include "samplerTask.h"

int main(void)
{
    task_manager_t *tm;

    tm = startNewTaskManager(2, "shared string");

    addTask(tm->task_queue, createSamplerTask("1 _ This is a test"));
    addTask(tm->task_queue, createSamplerTask("2 _ This is a test"));
    addTask(tm->task_queue, createSamplerTask("3 _ This is a test"));
    addTask(tm->task_queue, createSamplerTask("4 _ This is a test"));

    stopTaskManager(tm);
    return EXIT_SUCCESS;
}
