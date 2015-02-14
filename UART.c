#include "stm32f0xx.h"
#include "UART.h"

/*----------------------------------------------------------------------------
 *      Mail Queue creation & usage
 *---------------------------------------------------------------------------*/
 

void serial_init(void);

#define MAILQUEUE_OBJECTS      16                               // number of Message Queue Objects
typedef struct {                                                // object data type
	uint8_t cmd;
	uint8_t argc;
  uint8_t args[8];
	uint8_t cnt;
} UARTQUEUE_OBJ_t;



void UART_Init (void) {

	
	serial_init();

}

UARTQUEUE_OBJ_t tmpObj;

void USARTx_IRQHandler(void const *argument) {

	if(USART_GetFlagStatus(USARTx,USARTx_FLAG_RXNE) == SET)
	{
		
		uint8_t in = USART_ReceiveData(USARTx);
		if(tmpObj.cnt==0)tmpObj.cmd=in;
		else if(tmpObj.cnt==1)tmpObj.argc=in;
		else tmpObj.args[tmpObj.cnt-2]=in;
		tmpObj.cnt++;	
		
		if(tmpObj.cnt == tmpObj.argc+2){
			
			tmpObj.argc=0;
			tmpObj.cnt=0;
		}
	}
    

    //osThreadYield();                                            // suspend thread
}

void Thread_UARTProcessQueue(void const *argument) {
 
  while(1) {
   
  }
}

void serial_init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

	  USART_InitTypeDef USART_InitStructure;

	  USART_InitStructure.USART_BaudRate = 115200;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	  //   GPIO_InitTypeDef GPIO_InitStructure;
	  //configure clock for USART
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	  //configure clock for GPIO
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	  //configure AF
	  GPIO_PinAFConfig(UART_PORT,USARTx_RX_SOURCE,GPIO_AF_1);
	  GPIO_PinAFConfig(UART_PORT,USARTx_TX_SOURCE,GPIO_AF_1);

	  //configure ports, &GPIO_InitStructure);
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	  GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;				//TX
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(UART_PORT, &GPIO_InitStructure);

	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;				//RX
	  GPIO_Init(UART_PORT, &GPIO_InitStructure);

	  USART_Init(USARTx, &USART_InitStructure);

	  /* Enable the USARTx Interrupt */
	  NVIC_InitTypeDef NVIC_InitStructure_UART;
	  NVIC_InitStructure_UART.NVIC_IRQChannel = USARTx_IRQn;
	  NVIC_InitStructure_UART.NVIC_IRQChannelPriority = 0;
	  NVIC_InitStructure_UART.NVIC_IRQChannelCmd =  ENABLE;
	  NVIC_Init(&NVIC_InitStructure_UART);


	  // Enable USART
	  USART_Cmd(USARTx, ENABLE);

	  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
}

int UARTsend(uint8_t cmd, uint8_t wait)
{
	
	while(!USART_GetFlagStatus(USARTx,USART_FLAG_TXE)){}
	USART_SendData(USARTx,cmd);
	while(wait && !USART_GetFlagStatus(USARTx,USART_FLAG_TC)){}
	
	return 0;
}
