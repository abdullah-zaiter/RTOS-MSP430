/*
 * task.h
 *
 *  Created on: Jan 25, 2019
 *      Author: Abdullah
 */

#ifndef TASK_H_
#define TASK_H_
#include <stdint.h>

#define MAX_TASKS 8

#define MAX_PRIORITY 0
#define MID_PRIORITY 1
#define MIN_PRIORITY 2

typedef struct
{
    void (*p_task) (void);
    uint16_t* p_stack;
    uint8_t pid;
    uint8_t priority;
    uint16_t quantum;
    uint8_t finished;
}task;

#endif /* TASK_H_ */
