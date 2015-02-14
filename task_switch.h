#ifndef TASK_SWITCH_HEADER_DEFINED
#define TASK_SWITCH_HEADER_DEFINED

unsigned int *switchTask(unsigned int *stack);
void yield(void);
void save_context(void);
void load_context(void);
void save_kernel_context(void);

#endif
