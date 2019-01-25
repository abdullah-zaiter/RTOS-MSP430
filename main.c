#include "inc/clock.h"
#include "inc/pmm.h"
#include "inc/fifo_scheduler.h"

/**
 * main.c
 */
/*****************************
 * Membros da dupla:
 *      Anderson Barros Rodrigues - 13/0141046
 *      Abdullah Zaiter - 15/0089392
 *
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


// finaliza todas as tasks de MID e MAX priority
void taskB(void)
{
    while(P2IN & BIT1);
    __delay_cycles(160000);
    while(fifos[MAX_PRIORITY].size){
        task aux = fifoGet(&fifos[MAX_PRIORITY]);
        aux.finished = 1;
    }
    while(fifos[MID_PRIORITY].size){
        task aux = fifoGet(&fifos[MID_PRIORITY]);
        aux.finished = 1;
    }
    running_task.finished = 1;
    for(;;);

}

//LED 1 pisca por um tempo e para
void taskC(void)
{
    uint16_t i = 100;

    while(i--)
    {
        uint16_t counter = 25000;
        while(counter--);
        P1OUT ^= (BIT0);
    }

    P1OUT &= ~(BIT0);
    running_task.finished = 1;
    for(;;);
}

//LED 2 pisca por um tempo e para
void taskD(void)
{
    uint16_t i = 250;

    while(i--)
    {
        uint16_t counter = 10000;
        while(counter--);
        P4OUT ^= (BIT7);
    }

    P4OUT &= ~(BIT7);
    running_task.finished = 1;
    for(;;);
}

//Registra as tasks que controlam os leds
void taskA(void)
{
    while(1)
    {
        while(P1IN & BIT1);
        __delay_cycles(160000);
        registerTask(taskC,MAX_PRIORITY,10);
        registerTask(taskD,MAX_PRIORITY,10);
    }
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
    registerTask(taskA,MID_PRIORITY,100);
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
