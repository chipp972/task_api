#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "task_config.h"
#include "task.h"
#include "task_queue.h"


task_queue_t *newTaskQueue()
{
    task_queue_t *newTq;
    newTq = malloc(sizeof(task_queue_t));
    TEST_ALLOC(newTq, "newTq at newTaskQueue");
    newTq->first = NULL;
    newTq->last = NULL;
    newTq->done = NULL;
    // mutex pour modifier la file
    newTq->lock = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(newTq->lock, NULL);
    // semaphore partagee entre threads
    newTq->not_empty = malloc(sizeof(sem_t));
    sem_init(newTq->not_empty, 0, 0);
    return newTq;
}

void addTask(task_queue_t *tq, task_t *new_task)
{
    queue_element_t *newElement;

    pthread_mutex_lock(tq->lock);
    newElement = malloc(sizeof(queue_element_t));
    TEST_ALLOC(newElement, "newElement at addTask");
    newElement->task = new_task;
    newElement->next = NULL;

    if (tq->first == NULL) {
        tq->first = newElement;
        tq->last = newElement;
    } else {
        tq->last->next = newElement;
        tq->last = newElement;
    }
    sem_post(tq->not_empty);
    pthread_mutex_unlock(tq->lock);
}

task_t *popTask(task_queue_t *tq)
{
    queue_element_t *el, *tmp;

    sem_wait(tq->not_empty);
    pthread_mutex_lock(tq->lock);
    el = tq->first;
    tq->first = el->next;
    tmp = tq->done;
    tq->done = el;
    el->next = tmp;
    pthread_mutex_unlock(tq->lock);
    return el->task;
}

void freeTaskQueue(task_queue_t *tq)
{
    queue_element_t *tmp, *next;
    tmp = tq->done;
    while (tmp != NULL) {
        next = tmp->next;
        free(tmp->task);
        free(tmp);
        tmp = next;
    }
    tmp = tq->first;
    while (tmp != NULL) {
        next = tmp->next;
        free(tmp->task);
        free(tmp);
        tmp = next;
    }
    sem_destroy(tq->not_empty);
    pthread_mutex_destroy(tq->lock);
    free(tq->lock);
    free(tq->not_empty);
    free(tq);
    tq = NULL;
}
