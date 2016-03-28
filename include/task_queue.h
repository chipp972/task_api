#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <pthread.h>
#include <semaphore.h>

typedef struct queue_element {
    task_t *task;
    struct queue_element *next;
} queue_element_t;

typedef struct task_queue {
    queue_element_t *first, *last, *done;
    sem_t *not_empty;
    pthread_mutex_t *lock;
} task_queue_t;


/**
 * create and return a new empty task queue
 *
 * @return the address of the empty task queue
 */
task_queue_t *newTaskQueue();


/**
 * Add the task new_task to the task queue tq
 *
 * @param tq       the task queue to which you add a task
 * @param new_task the task to add
 */
void addTask(task_queue_t *tq, task_t *new_task);


/**
 * Return the first task of the queue tq and
 * put the task in the done list of the task queue
 * blocking function (semaphore)
 *
 * @param  tq the task from which we take an element
 * @return    the task poped
 */
task_t *popTask(task_queue_t *tq);


/**
 * Free the task queue tq
 * call it only when the task manager
 * has returned
 *
 * @param tq the queue to free ressources
 */
void freeTaskQueue(task_queue_t *tq);


#endif
