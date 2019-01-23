#include <msp430.h> 
#include "inc/clock.h"
#include "inc/pmm.h"

/**
 * main.c
 */

#define MAX_TASKS 8

typedef struct
{
    void (*p_task) (void);
    uint16_t* p_stack;
}task;


task tasks[MAX_TASKS];
uint16_t n_regtasks;
uint8_t current_task;
uint32_t  scalling_algorithm_sp;

__attribute__ ((naked))
__attribute__ ((interrupt(WDT_VECTOR)))
void WDT_ISR(void)
{
    asm("PUSHM.A #12, R15");
    asm("MOVX.A SP, %0" :"+m"(tasks[current_task].p_stack) );    //salvar a pilha da tarefa
    asm("MOVX.A %0, SP" : :"m"(scalling_algorithm_sp) ); //restaurar a pilha do escalonador 0x2500
    current_task = (current_task==0) ? 1 : 0 ;    //executar escalonador
    asm("MOVX.A SP, %0" :"+m"(scalling_algorithm_sp) );//salva a pilha do escalonador
    asm("MOVX.A %0, SP" : :"m"(tasks[current_task].p_stack) );//restaurar a pilha da nova tarefa
    asm("POPM.A #12, R15");
    asm("RETI");
}
void registerTask(void (*p_Task))
{
    if(n_regtasks < MAX_TASKS){
        tasks[n_regtasks].p_task = p_Task;
        tasks[n_regtasks].p_stack = (0x2800 + (0x80*(n_regtasks)));
        *(--tasks[n_regtasks].p_stack) = (uint16_t) (tasks[n_regtasks].p_task);
        *(--tasks[n_regtasks].p_stack) = (uint16_t) (GIE | (((uint32_t)(p_Task) >> 4) & 0xF000));
        tasks[n_regtasks].p_stack -= 24;
        n_regtasks++;
    }
    else
    {
        return;
    }
}
void config()
{
    n_regtasks = 0;
    current_task = 0;
    scalling_algorithm_sp = 0x2500;
    WDTCTL = WDTPW | WDTTMSEL | WDTSSEL__ACLK | WDTIS_7; //activation of watchdog timer with 1.95ms counting
    SFRIFG1 &= ~WDTIFG;
    SFRIE1 |=  (WDTIE);                                  //enabling the interruption of the watchdog
    clockInit();                                         // initializing clock's system

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

void taskA()
{
   for(;;)
   {
        while(P1IN & BIT1); // em intervalos periódicos
        __delay_cycles(160000);
        P4OUT ^= (BIT7);
        while(!(P1IN & BIT1));
        __delay_cycles(160000);
   }
}
void taskB()
{
    for(;;)
    {
        while(P2IN & BIT1); // em intervalos periódicos
        __delay_cycles(160000);
        P1OUT ^= (BIT0);
        while(!(P2IN & BIT1));
        __delay_cycles(160000);
    }
}

int main(void)
{
    config();
    registerTask(taskA);
    registerTask(taskB);
    asm("MOVX.A %0, SP" : :"m"(tasks[current_task].p_stack) );   //restaurar a pilha da nova tarefa
    asm("POPM.A #12, R15");
    //__enable_interrupt();
    asm("RETI");
	for(;;);
	return 0;
}
