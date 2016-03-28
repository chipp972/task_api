// support for big files
#define _FILE_OFFSET_BITS 64
#define BUFFER_SIZE 2048

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <sys/stat.h>
#include <unistd.h>

#include "task_api.h"
#include "spliterTask.h"

struct spliter_params {
    char *filepath;
    int nb_parts;
    wchar_t *delimiter;
};

task_t *createSplitTask(const char *fp, int n, wchar_t *d, void *createTask)
{
    task_t *new_task;
    struct spliter_params *p;
    new_task = newBasicTask(spliter, createTask);

    new_task->params = malloc(sizeof(struct spliter_params));
    TEST_ALLOC(new_task->params, "new_task->params at createSplitTask");
    p = (struct spliter_params *)new_task->params;

    p->filepath = malloc(sizeof(char)*(strlen(fp)+1));
    TEST_ALLOC(p->filepath, "p->filepath at createSplitTask");
    strcpy(p->filepath, fp);
    p->nb_parts = n;
    if (d != NULL) {
        p->delimiter = malloc(sizeof(wchar_t)*(wcslen(d)+1));
        TEST_ALLOC(p->delimiter, "p->delimiter at createSplitTask");
        wcscpy(p->delimiter, d);
    } else {
        p->delimiter = malloc(sizeof(wcslen(L"\n")+1));
        TEST_ALLOC(p->delimiter, "p->delimiter at createSplitTask");
        wcscpy(p->delimiter, L"\n");
    }
    return new_task;
}


void spliter(task_queue_t *tq, task_t *task)
{
    struct stat st;
    long long start, part, nbWchar;
    FILE *in;
    wchar_t buffer[BUFFER_SIZE];
    int i, t;
    struct spliter_params *params;
    // pointeur sur fonction
    task_t* (*newTask) (const char*, long long, long long);

    // cast de la fonction et des parametres
    newTask = (task->createNextTask);
    params = (struct spliter_params *)task->params;

    setlocale(LC_ALL, "fr_FR.utf8");

    in = fopen(params->filepath, "r");
    TEST_ALLOC(in, "fopen input file in spliter");

    fwide(in, 1);

    // calcul de la taille minimale des parties
    if (stat(params->filepath, &st) != 0) {
        fprintf(stderr, "stat filename in spliter\n");
        exit(EXIT_FAILURE);
    }
    part = st.st_size/params->nb_parts;

    start = 0;
    for (i = 1, t = params->nb_parts; i <= t; i++) {
        // au cas ou il n'y a pas assez de partie delimitee
        // pour faire le nombre de parties demande
        if (start > part*i)
            continue;

        nbWchar = 0;

        while (1) {
            if (fgetws(buffer, BUFFER_SIZE, in) == NULL) {
                if (feof(in)) {
                    addTask(tq, (*newTask)(params->filepath, start, nbWchar));
                    break;
                } else {
                    fprintf(stderr, "fgetws in spliter\n");
                    exit(EXIT_FAILURE);
                }
            }
            nbWchar += wcslen(buffer);
            // si on atteint la fin d'une page et que la partie est assez grosse
            // on cree une tache de cleaner dans la file des taches
            if (nbWchar >= part && wcsstr(buffer, params->delimiter) != NULL) {
                addTask(tq, (*newTask)(params->filepath, start, nbWchar));
                break;
            }
        }
        if (feof(in))
            break;
        if ((start = ftello(in)) == -1) {
            fprintf(stderr, "ftello in spliter\n");
            exit(EXIT_FAILURE);
        }
    }
    fclose(in);
    free(params->filepath);
    free(params->delimiter);
    free(task->params);
    task->params = NULL;
}
