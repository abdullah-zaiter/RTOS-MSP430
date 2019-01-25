/*
 * fifo.h
 *
 *  Created on: Jan 25, 2019
 *      Author: Abdullah
 */

#ifndef FIFO_SCHEDULER_H_
#define FIFO_SCHEDULER_H_

#include "task.h"
#include <stdint.h>

typedef struct
{
    uint8_t head;
    uint8_t tail;
    uint8_t size;
    task tasksfifo[MAX_TASKS];
}fifo;

fifo fifos[3];
uint32_t  scheduling_algorithm_sp;
task running_task;

task fifoGet(fifo* f);
void fifoPut(fifo* f, task t);
void registerTask(void (*p_Task), uint8_t priority, uint16_t quantum);
void scheduler(void);

#endif /* FIFO_SCHEDULER_H_ */
