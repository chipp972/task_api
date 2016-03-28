#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H


// the data of a task manager
typedef struct task_manager_t {
    pthread_t *thread;
    task_queue_t *task_queue;
    int workers_nb;
} task_manager_t;

// parameters of a task manager
typedef struct task_manager_params {
    task_queue_t *tq;
    int workers_nb;

    // pointeur qui sera transmis a tous les workers
    // permet de transmettre des infos partage par toutes les taches
    void *shared_params;
} task_manager_params_t;

/**
 * Thread de travaille cree par le task manager pour realiser les
 * taches dans la file d'attente
 *
 * @param  arg les parametres fournis au task manager
 */
void *worker(void *arg);

/**
 * Thread gestionnaire de tache
 * Cree les threads de travail (nb_threads) et attend leur
 * terminaison
 *
 * @param  arg une variable de type struct params remplis
 */
void *taskManager(void *arg);

/**
 * Initialize and start the task manager
 * @param  nb            number of working threads
 * @param  shared_params the variable shared between all threads
 * @return               the task queue to add tasks to
 */
task_manager_t *startNewTaskManager(int nb, void *shared_params);


/**
 * Stop and free the task manager
 * @param tm the struct containing the task manager informations
 */
void stopTaskManager(task_manager_t *tm);


#endif
