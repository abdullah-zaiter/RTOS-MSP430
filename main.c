#include "inc/clock.h"
#include "inc/pmm.h"
#include "inc/fifo_scheduler.h"

/**
 * main.c
 */

__attribute__ ((naked))
__attribute__ ((interrupt(WDT_VECTOR)))
void WDT_ISR(void)
{
    asm("PUSHM.A #12, R15");
    asm("MOVX.A SP, %0" :"+m"(running_task.p_stack) );    //salvar a pilha da tarefa
    asm("MOVX.A %0, SP" : :"m"(scheduling_algorithm_sp) ); //restaurar a pilha do escalonador 0x2500
    scheduler();
    asm("MOVX.A SP, %0" :"+m"(scheduling_algorithm_sp) );//salva a pilha do escalonador
    asm("MOVX.A %0, SP" : :"m"(running_task.p_stack) );//restaurar a pilha da nova tarefa
    asm("POPM.A #12, R15");
    asm("RETI");
}

void taskIDLE(void)
{
    __low_power_mode_0();
}

void taskA(void)
{
    while(P1IN & BIT1); // em intervalos periódicos
    __delay_cycles(160000);
    P4OUT ^= (BIT7);
    while(!(P1IN & BIT1));
    __delay_cycles(160000);
    running_task.finished = 1;
    for(;;);
}

void taskB(void)
{
    while(P2IN & BIT1); // em intervalos periódicos
    __delay_cycles(160000);
    P1OUT ^= (BIT0);
    while(!(P2IN & BIT1));
    __delay_cycles(160000);
    running_task.finished = 1;
    for(;;);
}

void config(void)
{
    scheduling_algorithm_sp = 0x3000;
    WDTCTL = WDTPW | WDTTMSEL | WDTSSEL__ACLK | WDTIS_7; //activation of watchdog timer with 1.95ms counting
    SFRIFG1 &= ~WDTIFG;
    SFRIE1 |=  (WDTIE);                                  //enabling the interruption of the watchdog
    clockInit();                                         // initializing clock's system

    for(uint8_t i=0; i<3 ; i++)
    {
        fifos[i].size = 0;
        fifos[i].head = 0;
        fifos[i].tail = 0;
    }

    P1DIR |= BIT0; // red led as output
    P4DIR |= BIT7; //green led as output

    P1DIR &= ~BIT1; //buttons as input
    P2DIR &= ~BIT1;

    P1REN |= BIT1; // pulldown/down activation
    P2REN |= BIT1;

    P1OUT |= (BIT1); //pulldown selection
    P2OUT |= (BIT1);

    P4OUT &= ~(BIT7);
    P1OUT &= ~(BIT0);
}

int main(void)
{
    config();
    registerTask(taskA,MAX_PRIORITY,100);
    registerTask(taskB,MID_PRIORITY,100);
    registerTask(taskIDLE,MIN_PRIORITY,1);
    running_task = fifoGet(&fifos[MAX_PRIORITY]);

    asm("MOVX.A %0, SP" : :"m"(running_task.p_stack) );   //restaurar a pilha da nova tarefa
    asm("POPM.A #12, R15");
    //__enable_interrupt();
    asm("RETI");
	for(;;);
	return 0;
}
