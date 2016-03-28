#ifndef SAMPLER_TASK_H
#define SAMPLER_TASK_H

void sampler(task_queue_t *tq, task_t *task);

task_t *createSamplerTask(char *str_to_pass);

#endif
