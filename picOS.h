#include "stm32f0xx.h"

#ifndef PICOS_HEADER_DEFINED
#define PICOS_HEADER_DEFINED

/* Size of our user task stacks in words */
#define STACK_SIZE  64

/* Number of user task */
#define TASK_LIMIT  16

enum TASKSTATES{READY, WAITING, SUSPENDED};
typedef enum TASKSTATES state_t;

typedef struct{
  uint8_t PID;
  state_t task_state;
  unsigned int *stack;
}task_t;

int create_task(task_t *task, void (*start)(void));

void yield(void);
void startOS(void);

#endif
