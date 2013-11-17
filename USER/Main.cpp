//=====================================================================
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include "stm32f10x.h"
//=====================================================================
#include	"systick.h"
#include	"EventGUI.h"
//#include	"Mark.h"
#include	"RGB_strip.h"
//=====================================================================
void	TIM_MS_Init(void)			;
//=====================================================================
#define			TIM_LED1		1000	// 1сек
//=====================================================================
TEvent			FEvent				;
TStrip			Strip				;
//=====================================================================
void	Init(void)
{
//#define		MCO_ON 
#ifdef		MCO_ON 
 GPIO_InitTypeDef GPIO_InitStructure					;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)	;
 GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8				;
 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP		;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz		;
 GPIO_Init(GPIOA, &GPIO_InitStructure)					;
 RCC_MCOConfig(RCC_MCO_SYSCLK)							;
#endif
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE)	;

 delay_init()				;

 Strip.Init()				;
 
 TIM_MS_Init()				;
// MARK_Init()				;
}
//=====================================================================
int		main(void)
{TEvent*			Event = &FEvent	;
// EVENT_TYPE			prevType = 0	;

 if(SysTick_Config(2400))// Setup SysTick Timer for 0.1 msec interrupts  
   while (1)			;// Capture error
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);/*!< 3 bits for pre-emption priority
                                                            1 bits for subpriority */

 Init()	;
 
 for(;1;){
   Strip.OnEvent(Event)	;
 }
}
//=====================================================================
//=====================================================================

//=====================================================================
//=====================================================================
//------------------------------------------------------
#define	TIM_MS					TIM3
#define	RCC_APB1Periph_TIM_MS 	RCC_APB1Periph_TIM3
#define	TIM_MS_IRQn				TIM3_IRQn
#define	TIM_MS_IRQHandler		TIM3_IRQHandler
#if defined	(STM32F10X_LD_VL) || defined (STM32F10X_MD_VL)
#define	PRSC_1M					24
#else
#define	PRSC_1M					72
#endif
//------------------------------------------------------
// таймер для милисекундных отсчётов
void	TIM_MS_Init(void)
{TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure	;
// TIM_OCInitTypeDef			TIM_OCInitStructure		;
// TIM_BDTRInitTypeDef		TIM_BDTRInitStructure	;
 NVIC_InitTypeDef NVIC_InitStructure;

   /* TIM_MS clock enable */
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM_MS ,ENABLE);

  /* Enable the TIM2 gloabal Interrupt */
 NVIC_InitStructure.NVIC_IRQChannel = TIM_MS_IRQn;
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

 NVIC_Init(&NVIC_InitStructure);

  /* TIM_MS Peripheral Configuration */ 
 TIM_DeInit(TIM_MS);

  /* Time Base configuration */
 TIM_TimeBaseStructure.TIM_Prescaler         = PRSC_1M-1;
 TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;
 TIM_TimeBaseStructure.TIM_Period            = 999;
 TIM_TimeBaseStructure.TIM_ClockDivision     = 0x0;
 TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;

 TIM_TimeBaseInit(TIM_MS,&TIM_TimeBaseStructure);
  /* TIM IT enable */
 TIM_ITConfig(TIM_MS,TIM_IT_Update, ENABLE)		;

  /* TIM_MS counter enable */
 TIM_Cmd(TIM_MS,ENABLE);

}
//------------------------------------------------------
extern "C" 
void TIM_MS_IRQHandler(void)
{
 if(TIM_GetITStatus(TIM_MS,TIM_IT_Update) != RESET){
   TIM_ClearITPendingBit(TIM_MS,TIM_IT_Update)		;
//   MARK_1H
   TStrip::OnTime()	;
//   MARK_1L
 }
}
//------------------------------------------------------
