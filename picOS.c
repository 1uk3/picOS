#include "stm32f0xx.h"
#include "task_switch.h"
#include "picOS.h"

uint8_t task_count = 0;
int8_t current_task = -1;

task_t* task_list[TASK_LIMIT];

void switch_context(void);
void del_task(void);

uint32_t * os_stack;

void startOS(){
  //os_stack is a pointer to a valid stack address
  //it is used to reset the kernel stack before loading the task 
  __asm volatile{ MRS os_stack, msp};

  //TODO prevent systick before yield!
  SysTick_Config(4800000);    //100ms
  //yield();
  SCB->ICSR |= (1<<28); //switch the context
}

int create_task(task_t *task, void (*start)(void))
{
  if(task->stack == 0) return -1;    //invalid stack
  //TODO check for suspended tasks!
  if(task_count >= TASK_LIMIT) return -1;

  task->stack += STACK_SIZE - 32; //end of stack, minus what we are about to push

  task->stack[13]=(uint32_t)del_task; //delete function
  task->stack[14]=(unsigned int)start;
  task->stack[15]=0x21000000;

  task->PID = task_count;
  task->task_state = READY;
  task_list[task_count]=task;
  task_count ++;

  return 0;
}
 
//read the main stack pointer
static inline void * rd_stack_ptr(void){
  void * result=0;
  __asm volatile{ MRS result, msp}
  return result;
}
//write the main stack pointer
static inline void wr_stack_ptr(void * ptr){
  __asm volatile ("MSR msp, ptr\n\t" );
}
//read PSP register
static inline void * rd_task_stack_ptr(void){
  void * result=0;
  __asm volatile ("MRS result, psp\n\t");
  return(result);
}
 
//write stack pointer to the psp register
static inline void wr_task_stack_ptr(void * ptr){
    __asm volatile ("MSR psp, ptr\n\t" );
}
 
//interrupt the current task and load the next one
void SysTick_Handler(void){
  save_context();            //old task

  switch_context();

  wr_stack_ptr(os_stack);    //reset kernel stack
  load_context();            //new task
}
 
//yield has been called. reload systick timer to  
//guarantee correct round robin time
void SVC_Handler(void){
  SysTick->VAL   = 0;

  save_context();            //old task

  switch_context();

  wr_stack_ptr(os_stack);    //reset kernel stack
  load_context();            //new task
}

//load the first task. is invoked by startOS()
void PendSV_Handler(void){
  current_task++;
  wr_task_stack_ptr( task_list[current_task]->stack ); //write the value of the PSP to the new task
  wr_stack_ptr(os_stack);
  load_context();  //new task
}
 

//This is the context switcher
void switch_context(void){
  task_list[current_task]->stack = rd_task_stack_ptr(); //save exit point of the last task

  do{                                                  //find active task
    current_task++;
    if(current_task >= task_count) current_task=0;
  }while(task_list[current_task]->task_state!=READY);

  wr_task_stack_ptr( task_list[current_task]->stack ); //write the value of the PSP to the new task
}

//force task switch
void inline yield(void){
  __asm volatile("svc 0\n\t");
}

//This is called when the task returns
void del_task(void){
  task_list[current_task]->task_state=SUSPENDED;
  yield();
  while(1); //unreachable
}
