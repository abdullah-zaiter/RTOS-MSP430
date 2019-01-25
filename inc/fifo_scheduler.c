/*
 * fifo.c
 *
 *  Created on: Jan 25, 2019
 *      Author: Abdullah
 */
#include <msp430.h>
#include "task.h"
#include "fifo_scheduler.h"
#include <stdint.h>


task fifoGet(fifo* f)
{
    task aux = f->tasksfifo[f->head];
    f->size--;
    f->head = (f->head+1) % MAX_TASKS;
    return aux;
}

void fifoPut(fifo* f, task t)
{
    f->tasksfifo[f->tail] = t;
    f->size++;
    f->tail = (f->tail+1) % MAX_TASKS;
}

void registerTask(void (*p_Task), uint8_t priority, uint16_t quantum)
{
    static uint8_t pid = 1;
    if(fifos[priority].size < MAX_TASKS){

        task aux;
        aux.p_task = p_Task;

        aux.p_stack = (0x3200 + (0x80*(pid)));

        *(-- aux.p_stack) = (uint16_t) (p_Task);

        *(-- aux.p_stack) = (uint16_t) (GIE | (((uint32_t)(p_Task) >> 4) & 0xF000));

        aux.p_stack -= 24;
        aux.pid = pid;
        aux.quantum = quantum;
        aux.finished = 0;
        aux.priority = priority;
        fifoPut(&fifos[priority],aux);
        pid++;
    }
    else
    {
        return;
    }
}

void scheduler(void)
{
    static uint16_t quantum = 100;
    if(!(running_task.finished))
    {
        if(--quantum)
        {
            return;
        }
        else
        {
            fifoPut(&fifos[running_task.priority], running_task);
        }
    }
    for(uint8_t i = MAX_PRIORITY; i<=MIN_PRIORITY ; i++)
    {
        if(fifos[i].size>0)
        {
            running_task = fifoGet(&fifos[i]);
            quantum = running_task.quantum;
            break;
        }
    }
}
