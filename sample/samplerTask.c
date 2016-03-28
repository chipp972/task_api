#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "task_api.h"
#include "samplerTask.h"

struct sampler_params {
    char *str;
};

// create the task
task_t *createSamplerTask(char *str_to_pass)
{
    task_t *new_task;
    struct sampler_params *p;
    new_task = newBasicTask(sampler, NULL);

    new_task->params = malloc(sizeof(struct sampler_params));
    TEST_ALLOC(new_task->params, "new_task->params at createSamplerTask");
    p = (struct sampler_params *)new_task->params;

    p->str = malloc(sizeof(char)*(strlen(str_to_pass)+1));
    TEST_ALLOC(p->str, "p->str at createSamplerTask");
    strcpy(p->str, str_to_pass);

    return new_task;
}

// task function
void sampler(task_queue_t *tq, task_t *task)
{
    struct sampler_params *params;
    params = (struct sampler_params *)task->params;
    char *shrd;
    int t;

    t = 5;
    shrd = (char *)task->shared_params; // cast of the shared variable

    printf("%s\n", params->str);
    printf("%s\n", shrd);
    printf("I'm gonna wait %dsec so you can see the other threads coming...\n", t);
    sleep(t);
}
