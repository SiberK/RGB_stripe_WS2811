//=====================================================================================================
#include "stm32f10x.h"
//=====================================================================================================
//#define	USE_HSE
#ifdef	BOARD_PORT103V
#define	USE_HSE
#define SYSCLK_FREQ_72MHz  	72000000
#define	SYSCLK_FREQ			SYSCLK_FREQ_72MHz
#endif

#ifdef	BOARD_F10xCx 
#define	USE_HSE
#define SYSCLK_FREQ_20MHz  	20000000UL
//#define SYSCLK_FREQ_24MHz  24000000UL
#define	SYSCLK_FREQ			SYSCLK_FREQ_20MHz
#endif
//=====================================================================================================
uint32_t SystemCoreClock = SYSCLK_FREQ;        /*!< System Clock Frequency (Core Clock) */
//=====================================================================================================
void SystemInit (void)
{
 RCC_DeInit()	;/* Reset the RCC clock configuration to the default reset state(for debug purpose) */

 FLASH->ACR |= FLASH_ACR_PRFTBE							; /* Enable Prefetch Buffer */
 FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY)	;
 if(SystemCoreClock<48000000)	   FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_0;/* Flash 0 wait state */
 else if(SystemCoreClock<72000000) FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_1;/* Flash 1 wait state */
 else							   FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;/* Flash 2 wait state */

 RCC_PCLK1Config(RCC_HCLK_Div2)		;
 RCC_ADCCLKConfig(RCC_PCLK2_Div8)	;
 
#ifdef	USE_HSE
 RCC_HSEConfig(RCC_HSE_ON)			;
 
#ifdef STM32F10X_MD_VL 
// RCC_PREDIV1Config(RCC_PREDIV1_Source_HSE,RCC_PREDIV1_Div2)	;// for STM32F100C4
// RCC_PLLConfig(RCC_PLLSource_PREDIV1,RCC_PLLMul_6)			;// for STM32F100C4
 RCC_PREDIV1Config(RCC_PREDIV1_Source_HSE,RCC_PREDIV1_Div1)	;// for STM32F100C4 (in  10MHz)
 RCC_PLLConfig(RCC_PLLSource_PREDIV1,RCC_PLLMul_2)			;// for STM32F100C4 (out 20MHz)
#else
// RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_6)		;// for F_OSC 12MHz
 RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9) 		;// for F_OSC 8MHz
#endif

#else
#ifdef STM32F10X_MD_VL 
 RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_6)			;// for STM32F100C4
#else
 RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_9) 		;
#endif
#endif		// USE_HSI
    
 RCC_PLLCmd(ENABLE)	;

    /* Wait till PLL is ready */
 while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET){}

    /* Select PLL as system clock source */
 RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK)	;
}
//=====================================================================================================
//=====================================================================================================
