#ifndef TASK_CONFIG_H
#define TASK_CONFIG_H

#include <stdlib.h>
#include <errno.h>

#define TEST_ALLOC(ptr, msg) if(ptr == NULL) { \
                                fprintf(stderr, "%s\n", msg); \
                                perror("Allocation failed :"); \
                                exit(EXIT_FAILURE); \
                            }

#endif
