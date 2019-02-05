/*
 * tasks.c
 *
 *  Created on: Jan 31, 2019
 *      Author: Abdullah
 */

#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/swi.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/cfg/global.h>
#include <ti/drivers/GPIO.h>
/* TI-RTOS Header files */
#include "Board.h"


Void redLED(void)
{
    //while (1) {
        //Task_sleep((unsigned int)1000);
        GPIO_toggle(Board_LED0);
    //}
}

void taskLEDS()
{
    for(;;){
        GPIO_toggle(Board_LED0);
        Semaphore_pend(sem, -1);
        GPIO_toggle(Board_LED1);
        Semaphore_pend(sem,-1);
    }
}

void freeSemaphore()
{
    Semaphore_post(sem);
}

Void greenLED(void)
{
    //while (1) {
     //  Task_sleep((unsigned int)1000);
       GPIO_toggle(Board_LED1);
    //}
}

//void tempRED(void)
//{
//    Swi_post(redLED_handle);
//}

//void tempGREEN(void)
//{
//    Swi_post(greenLED_handle);
//}
