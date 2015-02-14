/**
  ******************************************************************************
  * @file    stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-May-2012
  * @brief   Main Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "main.h"

/** @addtogroup STM320518_EVAL_Demo
  * @{
  */
/** @addtogroup STM32F0XX_IT
  * @brief Interrupts driver modules
  * @{
  */
  
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
  
  
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles RTC interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{

}

/**
  * @brief  This function handles External line 0/1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_1_IRQHandler(void)
{
 
}

/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{

}

/**
  * @brief  This function handles TIM15 overflow and update interrupt request.
  * @param  None
  * @retval None
  */
void TIM15_IRQHandler(void)
{
 
}

#ifdef WAVERECORD_SUBDEMO 
/**
  * @brief  This function handles TIM3 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
 
}

/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM14_IRQHandler(void)
{
  

}

#endif /* WAVERECORD_SUBDEMO */

#ifdef THERMOMETER_SUBDEMO
/**
  * @brief  This function handles I2C1 Error interrupt request.
  * @param  None
  * @retval None
  */
void I2C1_IRQHandler(void)
{
  /* Check on I2C1 SMBALERT flag and clear it */
  if (I2C_GetITStatus(LM75_I2C, I2C_IT_ALERT))
  {
    I2C_ClearITPendingBit(LM75_I2C, I2C_IT_ALERT);
    SMbusAlertOccurred++;
  }
  
  /* Check on I2C1 Time out flag and clear it */
  if (I2C_GetITStatus(LM75_I2C, I2C_IT_TIMEOUT))
  {
    I2C_ClearITPendingBit(LM75_I2C, I2C_IT_TIMEOUT);
  }
  
  /* Check on I2C1 Arbitration Lost flag and clear it */
  if (I2C_GetITStatus(LM75_I2C, I2C_IT_ARLO))
  {
    I2C_ClearITPendingBit(LM75_I2C, I2C_IT_ARLO);
  }

  /* Check on I2C1 PEC error flag and clear it */
  if (I2C_GetITStatus(LM75_I2C, I2C_IT_PECERR))
  {
    I2C_ClearITPendingBit(LM75_I2C, I2C_IT_PECERR);
  }
  
  /* Check on I2C1 Overrun/Underrun error flag and clear it */
  if (I2C_GetITStatus(LM75_I2C, I2C_IT_OVR))
  {
    I2C_ClearITPendingBit(LM75_I2C, I2C_IT_OVR);
  }
  
  /* Check on I2C1 Bus error flag and clear it */
  if (I2C_GetITStatus(LM75_I2C, I2C_IT_BERR))
  {
    I2C_ClearITPendingBit(LM75_I2C, I2C_IT_BERR);
  }
}
#endif /* THERMOMETER_SUBDEMO */

#ifdef HDMICEC_SUBDEMO
/**
  * @brief  This function handles CEC interrupt request.
  * @param  None
  * @retval None
  */

void CEC_IRQHandler(void)
{
  /* Process the CEC Interrupts */
  HDMI_CEC_ProcessIRQSrc();
}
#endif /* HDMICEC_SUBDEMO */

#ifdef INFRALED_SUBDEMO
/**
  * @brief  This function handles TIM17 interrupt request.
  * @param  None
  * @retval None
  */
void TIM16_IRQHandler(void)
{
  if(RFDemoStatus == RC5DEMO)
  {
    RC5_Encode_SignalGenerate(RC5_FrameManchestarFormat);
  }
  
  if(RFDemoStatus == SIRCDEMO)
  {
    SIRC12_Encode_SignalGenerate(SIRC12_FramePulseWidthFormat);
  }
  
  /* Clear TIM16 update interrupt */
  TIM_ClearITPendingBit(TIM16, TIM_IT_Update);
}
#endif /* INFRALED_SUBDEMO */

#if defined (INFRALED_SUBDEMO) || defined (HDMICEC_SUBDEMO)
/**
  * @brief  This function handles TIM14 overflow and update interrupt request.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
  /* Clear the TIM2 Update pending bit */
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  
  if(RFDemoStatus == RC5DEMO)
  {
    /* - Timer Falling Edge Event:
    The Timer interrupt is used to measure the period between two 
    successive falling edges (The whole pulse duration).
    
    - Timer Rising Edge Event:  
    It is also used to measure the duration between falling and rising 
    edges (The low pulse duration).
    The two durations are useful to determine the bit value. Each bit is 
    determined according to the last bit. 
    
    Update event:InfraRed decoders time out event.
    ---------------------------------------------
    It resets the InfraRed decoders packet.
    - The Timer Overflow is set to 3.6 ms .*/
    /* IC1 Interrupt*/
    if((TIM_GetFlagStatus(IR_TIM, TIM_FLAG_CC2) != RESET))
    {
      TIM_ClearFlag(IR_TIM, TIM_FLAG_CC2);
      /* Get the Input Capture value */
      ICValue2 = TIM_GetCapture2(IR_TIM);
      /* RC5 */
      RC5_DataSampling( ICValue2 - ICValue1 , 0);
      
    }  /* IC2 Interrupt */   
    else  if((TIM_GetFlagStatus(IR_TIM, TIM_FLAG_CC1) != RESET))
    {
      TIM_ClearFlag(IR_TIM, TIM_FLAG_CC1);
      /* Get the Input Capture value */
      ICValue1 = TIM_GetCapture1(IR_TIM);
      RC5_DataSampling(ICValue1 , 1);
    } 
    /* Checks whether the IR_TIM flag is set or not.*/
    else if ((TIM_GetFlagStatus(IR_TIM, TIM_FLAG_Update) != RESET))
    { 
      /* Clears the IR_TIM's pending flags*/
      TIM_ClearFlag(IR_TIM, TIM_FLAG_Update);
      
      RC5_ResetPacket(); 
    }
  }
  if (RFDemoStatus == SIRCDEMO)
  {
    /*The Timer interrupt is used to measure the different period between 
    two successive falling edges in order to identify the frame bits.
    
    We measure the low pulse duration:
    - If the period measured is equal to T = 1200 µs and the low pulse 
    duration is equal to T/2 = 600µs => the bit is logic '0'. 
    - If the period measured is equal to 3T/2 = 1800µs and the low pulse 
    duration is equal to T = 1200µs => the bit is logic '1'.
    - If the whole period measured is equal to 3000µs and the low pulse 
    duration is equal to 2400µs => the bit is ‘start bit’.
    
    Update event:InfraRed decoders time out event
    ----------------------------------------------
    It resets the InfraRed decoders packet.                 
    - The Timer Overflow is set to 4 ms.  */
    
    
    /* IC1 Interrupt */
    if((TIM_GetFlagStatus(IR_TIM, TIM_FLAG_CC2) != RESET))
    {
      TIM_ClearFlag(IR_TIM, TIM_FLAG_CC2);
      /* Get the Input Capture value */
      ICValue2 = TIM_GetCapture2(IR_TIM);
      SIRC_DataSampling(ICValue1, ICValue2); 
    }  /* IC2 Interrupt*/   
    else  if((TIM_GetFlagStatus(IR_TIM, TIM_FLAG_CC1) != RESET))
    {
      TIM_ClearFlag(IR_TIM, TIM_FLAG_CC1);
      /* Get the Input Capture value */
      ICValue1 = TIM_GetCapture1(IR_TIM);
    } 
    /* Checks whether the IR_TIM flag is set or not. */
    else if ((TIM_GetFlagStatus(IR_TIM, TIM_FLAG_Update) != RESET))
    { 
      /* Clears the IR_TIM's pending flags*/
      TIM_ClearFlag(IR_TIM, TIM_FLAG_Update);
      
      SIRC_ResetPacket();
    }
  }
  else
  {}
}
#endif /* INFRALED_SUBDEMO, HDMICEC_SUBDEMO */


/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
