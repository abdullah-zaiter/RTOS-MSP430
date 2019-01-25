**RTOS-MSP430**

**Alunos:**

​	Anderson Barros Rodrigues - 13/0141046
​	Abdullah Zaiter - 15/0089392



**Funcionamento:**

 - 3 *tasks* são registradas automaticamente na *main*:
     - *Task* A e *task* B com prioridade média;
     - *Task* idle com prioridade minima.
- *Task* A:
  - Monitora o botão ligado a porta 1.1;
  - Quando o botão é apertado duas *tasks* são registradas com prioridade máxima, *tasks* C e D.
- *Task* B:
  - Monitora o botão ligado a porta 2.1;
  - Quando o botão é apertado faz *finished* igual a *true* em todas as *tasks* de prioridade máxima e média, inclusive em si mesma.
- *Tasks* C e D:
  - Fazem os *leds* piscarem, cada task controla um *led*. Os led piscam em frequências diferentes.