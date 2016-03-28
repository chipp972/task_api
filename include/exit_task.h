#ifndef EXIT_TASK_H
#define EXIT_TASK_H

struct exit_all_params {
    int workers_nb;
};

/**
 * Create a task to exit a worker
 * @return the task created
 */
task_t *createExitTask();

void exiter(task_queue_t *tq, task_t *task);

task_t *createExitAllTask(int nb);

void allExiter(task_queue_t *tq, task_t *task);

#endif
