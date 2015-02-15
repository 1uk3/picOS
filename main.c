
//#include "UART.h"
#include "stm32f0xx.h"
#include "picOS.h"

void on_func(void);
void off_func(void);
void LED_init(void);

#define TASK(name,ptr) \
    unsigned int name##_stack[STACK_SIZE];\
    task_t name##_task;  \
    name##_task.stack = name##_stack; \
    create_task(&name##_task,ptr);


int main (void) {

  SystemInit();

  LED_init();

  TASK(on,&on_func);
  TASK(off,&off_func);
  
  startOS();
  
  while(1){}

}


void off_func(void)
{
  while (1) {
    GPIOB->BSRR = GPIO_Pin_0;  //reset led
    //yield();
  }
}

void on_func(void)
{
  while (1) {
    GPIOB->BRR = GPIO_Pin_0;  //set led
    //yield();
  }
}

void LED_init(){
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
    
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
