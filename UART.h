#include "stm32f0xx.h"

void UART_Init(void);
int UARTsend(uint8_t cmd, uint8_t wait);
//void LWL_SendBlock(uint8_t *buffer, uint32_t BufferSize);

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
typedef enum {INIT=0,IDLE=1,ACTIVE=2} State;
typedef enum {EMPTY=0,SAMPLE=1,SET_LIMIT=2,GET_LIMIT=3,GET_AVG=4,GET_PEAK=5,RST_STATS=6,MIDI=7} Commands;

 #define TEST_DATA_SIZE 16
 #define UART_PORT	GPIOA

 #define USARTx                           USART1
  #define USARTx_CLK                       RCC_USART1CLK_SYSCLK
  #define USARTx_CLK_INIT                  RCC_USARTCLKConfig
	//RCC_APB2PeriphClockCmd
  #define USARTx_IRQn                      USART1_IRQn
  #define USARTx_IRQHandler                USART1_IRQHandler
	#define USARTx_FLAG_RXNE									USART_FLAG_RXNE

  #define USARTx_TX_PIN                    GPIO_Pin_9                
  #define USARTx_TX_GPIO_PORT              GPIOA                       
  #define USARTx_TX_GPIO_CLK               RCC_AHBPeriph_GPIOA
  #define USARTx_TX_SOURCE                 GPIO_PinSource9
  #define USARTx_TX_AF                     GPIO_AF_0

  #define USARTx_RX_PIN                    GPIO_Pin_10                
  #define USARTx_RX_GPIO_PORT              GPIOA                    
  #define USARTx_RX_GPIO_CLK               RCC_AHBPeriph_GPIOA
  #define USARTx_RX_SOURCE                 GPIO_PinSource10
  #define USARTx_RX_AF                     GPIO_AF_0

  /* Definition for DMAx resources **********************************************/
  #define USARTx_DR_ADDRESS                ((uint32_t)USART1 + 0x04) 
