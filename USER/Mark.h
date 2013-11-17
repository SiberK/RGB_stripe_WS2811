//------------------------------------------------------
//------------------------------------------------------
#ifndef	MARK_H
#define	MARK_H
//------------------------------------------------------
//------------------------------------------------------
#ifdef	BOARD_10xCx
#define	GPIO_LED1					GPIOA
#define GPIO_Pin_LED1				GPIO_Pin_8
#define	GPIO_LED2 					GPIO_LED1
#define GPIO_Pin_LED2				GPIO_Pin_1
#define	GPIO_LED3 					GPIO_LED1
#define GPIO_Pin_LED3				GPIO_Pin_2
#define	GPIO_LED4 					GPIO_LED1
#define GPIO_Pin_LED4				GPIO_Pin_3

#define	GPIO_MARK					GPIOA
#define	RCC_APB2Periph_GPIO_MARK	RCC_APB2Periph_GPIOA
#define GPIO_Pin_MARK0				GPIO_Pin_7
#define GPIO_Pin_MARK1				GPIO_Pin_6
#define GPIO_Pin_MARK2				GPIO_Pin_5
#define GPIO_Pin_MARK3				GPIO_Pin_4
//#define GPIO_Pin_MARK4				GPIO_Pin_3
//#define GPIO_Pin_MARK5				GPIO_Pin_2
//#define GPIO_Pin_MARK6				GPIO_Pin_1

#define	GPIO_Port_KEYA				GPIOA
#define GPIO_Pin_KEYA				GPIO_Pin_15
#define	RCC_APB2Periph_GPIO_KEYA	RCC_APB2Periph_GPIOA
#define	GPIO_Port_KEYB				GPIOB
#define GPIO_Pin_KEYB				GPIO_Pin_2
#define	RCC_APB2Periph_GPIO_KEYB	RCC_APB2Periph_GPIOB
#endif

// #define GPIO_Pin_PWR_SW				GPIO_Pin_12
// #define GPIO_Pin_PWR_ON				GPIO_Pin_15
// #define	GPIO_PWR_ON					GPIOB
// #define	GPIO_PWR_SW					GPIOB
// #define	RCC_APB2Periph_GPIO_PWR_SW	RCC_APB2Periph_GPIOB
//------------------------------------------------------
#ifdef GPIO_Pin_MARK0
#define	MARK_0H   GPIO_MARK->BSRR = GPIO_Pin_MARK0		;//GPIO_SetBits  (GPIO_MARK,GPIO_Pin_MARK0);
#define	MARK_0L   GPIO_MARK->BRR  = GPIO_Pin_MARK0		;//GPIO_ResetBits(GPIO_MARK,GPIO_Pin_MARK0);
#define	MARK_0X	  {if(GPIO_MARK->IDR & GPIO_Pin_MARK0) MARK_0L  else MARK_0H  }
//{if(GPIO_ReadInputDataBit(GPIO_MARK,GPIO_Pin_MARK0)) MARK_0L  else MARK_0H  }
#endif
#ifdef GPIO_Pin_MARK1
#define	MARK_1H   GPIO_MARK->BSRR = GPIO_Pin_MARK1		;//GPIO_SetBits  (GPIO_MARK,GPIO_Pin_MARK1);
#define	MARK_1L   GPIO_MARK->BRR  = GPIO_Pin_MARK1		;//GPIO_ResetBits(GPIO_MARK,GPIO_Pin_MARK1);
#define	MARK_1X	  {if(GPIO_MARK->IDR & GPIO_Pin_MARK1) MARK_1L  else MARK_1H  }
//{if(GPIO_ReadInputDataBit(GPIO_MARK,GPIO_Pin_MARK1)) MARK_1L  else MARK_1H  }
#endif
#ifdef GPIO_Pin_MARK2
#define	MARK_2H   GPIO_MARK->BSRR = GPIO_Pin_MARK2		;//GPIO_SetBits  (GPIO_MARK,GPIO_Pin_MARK2);
#define	MARK_2L   GPIO_MARK->BRR  = GPIO_Pin_MARK2		;//GPIO_ResetBits(GPIO_MARK,GPIO_Pin_MARK2);
#define	MARK_2X	  {if(GPIO_MARK->IDR & GPIO_Pin_MARK2) MARK_2L  else MARK_2H  }
//{if(GPIO_ReadInputDataBit(GPIO_MARK,GPIO_Pin_MARK2)) MARK_2L  else MARK_2H  }
#endif
#ifdef GPIO_Pin_MARK3
#define	MARK_3H   GPIO_MARK->BSRR = GPIO_Pin_MARK3		;//GPIO_SetBits  (GPIO_MARK,GPIO_Pin_MARK3);
#define	MARK_3L   GPIO_MARK->BRR  = GPIO_Pin_MARK3		;//GPIO_ResetBits(GPIO_MARK,GPIO_Pin_MARK3);
#define	MARK_3X	  {if(GPIO_ReadInputDataBit(GPIO_MARK,GPIO_Pin_MARK3)) MARK_3L  else MARK_3H  }
#endif
#ifdef GPIO_Pin_MARK4
#define	MARK_4H   GPIO_SetBits  (GPIO_MARK,GPIO_Pin_MARK4);
#define	MARK_4L   GPIO_ResetBits(GPIO_MARK,GPIO_Pin_MARK4);
#define	MARK_4X	  {if(GPIO_ReadInputDataBit(GPIO_MARK,GPIO_Pin_MARK4)) MARK_4L  else MARK_4H  }
#endif
#ifdef GPIO_Pin_MARK5
#define	MARK_5H   GPIO_SetBits  (GPIO_MARK,GPIO_Pin_MARK5);
#define	MARK_5L   GPIO_ResetBits(GPIO_MARK,GPIO_Pin_MARK5);
#define	MARK_5X	  {if(GPIO_ReadInputDataBit(GPIO_MARK,GPIO_Pin_MARK5)) MARK_5L  else MARK_5H  }
#endif
#ifdef GPIO_Pin_MARK6
#define	MARK_6H   GPIO_SetBits  (GPIO_MARK,GPIO_Pin_MARK6);
#define	MARK_6L   GPIO_ResetBits(GPIO_MARK,GPIO_Pin_MARK6);
#define	MARK_6X	  {if(GPIO_ReadInputDataBit(GPIO_MARK,GPIO_Pin_MARK6)) MARK_6L  else MARK_6H  }
#endif
//------------------------------------------------------
#if defined (GPIO_Pin_LED1)
#define	LED1_ON   GPIO_SetBits  (GPIO_LED1,GPIO_Pin_LED1);
#define	LED1_OFF  GPIO_ResetBits(GPIO_LED1,GPIO_Pin_LED1);
#endif
#if defined (GPIO_Pin_LED2)
#define	LED2_OFF  GPIO_SetBits  (GPIO_LED2,GPIO_Pin_LED2);
#define	LED2_ON   GPIO_ResetBits(GPIO_LED2,GPIO_Pin_LED2);
#endif
#if defined (GPIO_Pin_LED3)
#define	LED3_OFF  GPIO_SetBits  (GPIO_LED3,GPIO_Pin_LED3);
#define	LED3_ON   GPIO_ResetBits(GPIO_LED3,GPIO_Pin_LED3);
#endif
#if defined (GPIO_Pin_LED4)
#define	LED4_OFF  GPIO_SetBits  (GPIO_LED4,GPIO_Pin_LED4);
#define	LED4_ON   GPIO_ResetBits(GPIO_LED4,GPIO_Pin_LED4);
#endif
//------------------------------------------------------
#ifdef GPIO_Pin_KEYA
#define	KEYA_STATE	GPIO_ReadInputDataBit(GPIO_Port_KEYA,GPIO_Pin_KEYA)
#endif
//------------------------------------------------------
#ifdef GPIO_Pin_KEYB
#define	KEYB_STATE	GPIO_ReadInputDataBit(GPIO_Port_KEYB,GPIO_Pin_KEYB)
#endif
//------------------------------------------------------
#if defined (BOARD_10xCx)
#define	KEY_STATE_DN	Bit_SET
#endif
//------------------------------------------------------
extern	volatile int	flKeyA   ,flKeyB	;
extern	volatile int	flKeyA_UP,flKeyB_UP	;
extern	volatile int	flKeyA_DN,flKeyB_DN	;
//------------------------------------------------------
void MARK_Init(void)			;
// void 	PowerSwitch_Init(void)	;
// void	PowerOn(void)			;
// void	PowerOff(void)			;
// int 	PowerSwDown(int vDly)	;
int		OnTimer_KeyAB(void)		;// отслеживать нажатие польз.кнопокк
//------------------------------------------------------
//------------------------------------------------------
#endif
//------------------------------------------------------
