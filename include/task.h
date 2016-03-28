#ifndef TASK_H
#define TASK_H

typedef struct task {
    void *execTask; // function pointer (task to execute)
    void *createNextTask; // function pointer (next task to create)

    // structures managed by users to pass informations
    void *params; // specific parameters of a task
    void *shared_params; // parameters shared with all tasks
} task_t;

/**
 * Function that create a task and send back its address
 * taskFunction MUST have a prototype like :
 * void funcName(task_queue_t *tq, task_t *task)
 * nextTaskCreator MUST return a task_t*
 *
 * @param  taskFunction    the function to execute
 * @param  nextTaskCreator the next task to create or NULL
 * @return                 a pointer on the created task
 */
task_t *newBasicTask(void *taskFunction, void *nextTaskCreator);


#endif
