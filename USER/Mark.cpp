//------------------------------------------------------
//------------------------------------------------------
#include	<stdio.h>
#include	<string.h>

#include "stm32f10x.h"
//#include "GLCD.h"
#include	"Mark.h"
//------------------------------------------------------
//extern TLCD			LCD					;
//------------------------------------------------------
void MARK_Init(void)
{GPIO_InitTypeDef		GPIO_InitStructure		;

if(GPIO_MARK == GPIOA
	|| GPIO_Port_KEYA == GPIOA || GPIO_Port_KEYB == GPIOA
	|| GPIO_LED1 == GPIOA      || GPIO_LED2 == GPIOA)
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
if(GPIO_MARK == GPIOB
	|| GPIO_Port_KEYA == GPIOB || GPIO_Port_KEYB == GPIOB
	|| GPIO_LED1 == GPIOB      || GPIO_LED2 == GPIOB)
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
if(GPIO_MARK == GPIOC
	|| GPIO_Port_KEYA == GPIOC || GPIO_Port_KEYB == GPIOC
	|| GPIO_LED1 == GPIOC      || GPIO_LED2 == GPIOC)
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
if(GPIO_MARK == GPIOD
	|| GPIO_Port_KEYA == GPIOD || GPIO_Port_KEYB == GPIOD
	|| GPIO_LED1 == GPIOD      || GPIO_LED2 == GPIOD)
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
 
 GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_MARK0
#ifdef GPIO_Pin_MARK1
 							   | GPIO_Pin_MARK1 
#endif
#ifdef GPIO_Pin_MARK2
 							   | GPIO_Pin_MARK2
#endif
#ifdef GPIO_Pin_MARK3
 							   | GPIO_Pin_MARK3
#endif
#ifdef GPIO_Pin_MARK4
 							   | GPIO_Pin_MARK4
#endif
#ifdef GPIO_Pin_MARK5
 							   | GPIO_Pin_MARK5
#endif
#ifdef GPIO_Pin_MARK6
 							   | GPIO_Pin_MARK6
#endif
													;
 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP	;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz	;
 GPIO_Init(GPIO_MARK, &GPIO_InitStructure)			;

#ifdef STM32F10X_LD_VL
 GPIO_PinRemapConfig(GPIO_Remap_PD01,ENABLE)			;// !!!!!!!!!!!!!!!!!!! 
#endif

#ifdef GPIO_Pin_KEYA
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_KEYA, ENABLE);
 GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_KEYA			;
#ifdef STM32F10X_MD_VL
 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING	;
#else
 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU			;
#endif
 GPIO_Init(GPIO_Port_KEYA, &GPIO_InitStructure)			;
 GPIO_SetBits  (GPIO_Port_KEYA,GPIO_Pin_KEYA)			;
#endif
 
#ifdef GPIO_Pin_KEYB
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_KEYB, ENABLE);
 GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_KEYB			;
#ifdef STM32F10X_MD_VL
 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING	;
#else
 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU			;
#endif
 GPIO_Init(GPIO_Port_KEYB, &GPIO_InitStructure)			;
 GPIO_SetBits  (GPIO_Port_KEYB,GPIO_Pin_KEYB)			;
#endif
 
 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP	;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz	;
#if defined GPIO_Pin_LED1
 GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_LED1		;
 GPIO_Init(GPIO_LED1, &GPIO_InitStructure)			;
 LED1_OFF
#endif
#if defined GPIO_Pin_LED2
 GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_LED2		;
 GPIO_Init(GPIO_LED2, &GPIO_InitStructure)			;
 LED2_OFF
#endif
#if defined GPIO_Pin_LED3
 GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_LED3		;
 GPIO_Init(GPIO_LED3, &GPIO_InitStructure)			;
 LED3_OFF
#endif
#if defined GPIO_Pin_LED4
 GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_LED4		;
 GPIO_Init(GPIO_LED4, &GPIO_InitStructure)			;
 LED4_OFF
#endif
}
//------------------------------------------------------
volatile int	flKeyA = -10,flKeyB = -10	;
volatile int	flKeyA_UP=0,flKeyB_UP=0		;
volatile int	flKeyA_DN=0,flKeyB_DN=0		;
//------------------------------------------------------
int		OnTimer_KeyAB(void)
{int result=0	;
#ifdef GPIO_Pin_KEYA
  if(KEYA_STATE == KEY_STATE_DN){
    if(flKeyA>0) 		  flKeyA = 0	;
	else if(flKeyA >-10){ flKeyA--		;
	  if(flKeyA == -10)   flKeyA_DN = 1	;}}
  else{
    if(flKeyA<0) 		  flKeyA = 0	;
	else if(flKeyA < 10){ flKeyA++		;
	  if(flKeyA == 10)    flKeyA_UP = 1	;}}
#endif
#ifdef GPIO_Pin_KEYB
  if(KEYB_STATE == KEY_STATE_DN){
    if(flKeyB>0) 		  flKeyB = 0	;
	else if(flKeyB >-10){ flKeyB--		;
	  if(flKeyB == -10)   flKeyB_DN = 1	;}}
  else{
    if(flKeyB<0)		  flKeyB = 0	;
	else if(flKeyB < 10){ flKeyB++		;
	  if(flKeyB == 10)	  flKeyB_UP = 1	;}}
#endif
 return result	;}
//------------------------------------------------------
/*void PowerSwitch_Init(void)
{GPIO_InitTypeDef		GPIO_InitStructure			;

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_PWR_SW, ENABLE);
 
 GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_PWR_ON	;
 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP	;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz	;
 GPIO_Init(GPIO_PWR_ON, &GPIO_InitStructure)		;

 GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_PWR_SW	;
 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD		;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz	;
 GPIO_Init(GPIO_PWR_ON, &GPIO_InitStructure)		;

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_LED,ENABLE);
 
 GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_LED1 | GPIO_Pin_LED2	;
 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP	;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz	;
 GPIO_Init(GPIO_LED, &GPIO_InitStructure)			;
}
//------------------------------------------------------
void	PowerOn(void)
{GPIO_SetBits(GPIO_PWR_ON,GPIO_Pin_PWR_ON)			;}
//------------------------------------------------------
void	PowerOff(void)
{GPIO_ResetBits(GPIO_PWR_ON,GPIO_Pin_PWR_ON)		;}
//------------------------------------------------------
int PowerSwDown(int vDly)
{static	int CntSw  = 0		;
 int		result = 0		;
// char		str[20]			;

 result = GPIO_ReadInputData(GPIO_PWR_SW)			;

 if(GPIO_ReadInputDataBit(GPIO_PWR_SW,GPIO_Pin_PWR_SW)){
   if(CntSw < vDly){ 
     CntSw++				;
	 if(CntSw > vDly-50) CntSw = vDly	;}
 }
 else{
   if(CntSw){  
     CntSw--	; 
	 if(CntSw < 50) CntSw = 0			;}
 }

 result = CntSw > vDly-50 ? 1 : 0		;

 return result			;}
//------------------------------------------------------
*/
