#include "stm32f10x.h"
#include	<stdio.h>
//#include	"FiFo.h"
//******************************************************************************
#define		USART_X				USART1
#define		USART_X_IRQn		USART1_IRQn
#define		USART_X_IRQHandler	USART1_IRQHandler
//******************************************************************************
#define		USART_F				USART1
#define		USART_F_IRQn		USART1_IRQn
#define		USART_F_IRQHandler	USART1_IRQHandler
//******************************************************************************
//char			BuffTX[200],BuffRX[200]	;
//extern TFiFo	TxBuf,RxBuf				;
//extern TFiFo	TxBuf_F,RxBuf_F			;
/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configure USART1 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
extern "C" void USART_Configuration(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure; 

//  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */  
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USARTy Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = USART_X_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);

//  NVIC_InitStructure.NVIC_IRQChannel = USART_F_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

  if(USART_X == USART1 || USART_F == USART1){  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  }
  if(USART_X == USART2 || USART_F == USART2){  
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,ENABLE)	;
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2,ENABLE)	;
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;	         
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	        
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  }

  USART_InitStructure.USART_BaudRate = 1500000;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx;

  USART_Init(USART_X, &USART_InitStructure); 
//  USART_ITConfig(USART_X, USART_IT_RXNE, ENABLE);
//  USART_ITConfig(USART_X, USART_IT_TXE, ENABLE);
  USART_Cmd(USART_X, ENABLE);
}
//******************************************************************************
extern "C" void USART_X_IRQHandler(void)
{
//  if(USART_GetITStatus(USART_X, USART_IT_RXNE) != RESET){    
//	if(!RxBuf.Full()) RxBuf.In(USART_ReceiveData(USART_X))				;/* Read one byte from the receive data register */
//	if( RxBuf.Full()) USART_ITConfig(USART_X, USART_IT_RXNE, DISABLE)	;/* Disable the USARTy Receive interrupt */
//  }
// 
//  if(USART_GetITStatus(USART_X, USART_IT_TXE) != RESET){   
//	if(!TxBuf.Empty())  USART_SendData(USART_X, TxBuf.Out())		;/* Write one byte to the transmit data register */
//    if( TxBuf.Empty())  USART_ITConfig(USART_X, USART_IT_TXE, DISABLE)		;/* Disable the USARTy Transmit interrupt */
//  }
}
//******************************************************************************
int USART_SendChar(int ch)
{ 
 int	result = 1	;
 if(USART_GetFlagStatus(USART_X, USART_FLAG_TXE) != RESET){
   USART_SendData(USART_X,ch)			;}
 else result = 0	;
  
 return result		;
}
//******************************************************************************
//******************************************************************************
extern "C" int SendChar(int ch)
{ 
// if(!TxBuf.Full()) TxBuf.In(ch)	;

// if(USART_GetITStatus(USART_X,USART_IT_TXE) == RESET) USART_ITConfig(USART_X, USART_IT_TXE, ENABLE)			;
//  
 return ch;
}
//******************************************************************************
extern "C" int SendChar_F(int ch)
{ 
// if(!TxBuf_F.Full()) TxBuf_F.In(ch)	;

// if(USART_GetITStatus(USART_F,USART_IT_TXE) == RESET) USART_ITConfig(USART_F, USART_IT_TXE, ENABLE)			;
//  
 return ch;
}
//******************************************************************************
void	xputs_F(const char* str)
{ while(*str) SendChar_F(*str++)	;}
//******************************************************************************
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
//extern "C" int fputc(int ch, FILE *f)
extern "C" int SendChar1(int ch)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);
  
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}
//******************************************************************************
extern "C" int GetKey (void)  {

  while (!(USART1->SR & USART_FLAG_RXNE));

  return ((int)(USART1->DR & 0x1FF));
}
//******************************************************************************
extern "C" int CommTest(void)
{
 return ( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET ) ? 0 : 1;
}
//******************************************************************************


