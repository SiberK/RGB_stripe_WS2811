#include <stm32f10x.h>
#include		"RGB_Strip.h"
#include		"Math.h"
//=========================================================
#define		GPIO_ACC	GPIOA
#define		SPI_ACC		SPI1
#define		MOSI_ACC	GPIO_Pin_7
#define		MISO_ACC	GPIO_Pin_6
#define		CLK_ACC		GPIO_Pin_5

#define	RCC_APB2Periph_ACC	RCC_APB2Periph_GPIOA
//#define	RCC_APB1Periph_SPI	RCC_APB1Periph_SPI2
#define	RCC_APB2Periph_SPI	RCC_APB2Periph_SPI1
//=========================================================
#define		TIM_FLASH		50
#define		TIM_FADE		100
#define		TIM_DIR			1000

#define		SQR(X)		((X)*(X))

#define SPI_MASTER_DMA               DMA1
#define SPI_MASTER_DMA_CLK           RCC_AHBPeriph_DMA1  
#define SPI_MASTER_Tx_DMA_Channel    DMA1_Channel3
#define SPI_MASTER_Tx_DMA_FLAG       DMA1_FLAG_TC3  
#define SPI_MASTER_DR_Base           0x4001300C


//=========================================================
TRGBY		ArrayRGBY[CntRGBY]	;
uint8_t		BufWS[CntWS*2]		;

//=========================================================
TStrip*	TStrip::Instance = 0		;
//=========================================================
	TStrip::TStrip(void)
{ Instance = this	; Array = ArrayRGBY	;}
//=========================================================
void			TStrip::Init(void)
{TEffect		Effect			;
 InitSPI()	;
 Effect.InitArray(Array,CntRGBY,EffItemJump2)		;
 ConvertWS(BufWS,Array,CntRGBY)	;
} 
//=========================================================
EVENT_TYPE		TStrip::OnEvent(TEvent* Event)
{TEffect		Effect			;
 int			flConv = 0		;
// if(!(SPI_ACC->SR & SPI_SR_BSY)) SPI_ACC->DR = 0x9A	;

 if(!timDir){ timDir = Dir? TIM_DIR	: TIM_DIR/4	; Dir ^= 1	;}
 
 if(!timFlash){ timFlash = TIM_FLASH	; flConv = 1	;
   Effect.Step(Array,CntRGBY,EffItemJump2)				;}
   
 if(!timFade){ timFade = TIM_FADE		; flConv = 1	;
   Effect.Step(Array,CntRGBY,EffItemFade1)				;}   
   
 if(flConv){
   ConvertWS(BufWS,Array,CntRGBY)						;
   
   DMA_Cmd(SPI_MASTER_Tx_DMA_Channel, DISABLE)			;
   SPI_MASTER_Tx_DMA_Channel->CNDTR = CntWS	+ 3			;
   SPI_MASTER_Tx_DMA_Channel->CMAR  = (uint32_t)BufWS	;
   DMA_Cmd(SPI_MASTER_Tx_DMA_Channel, ENABLE)			;
 }
 return	Event->Type	;} 
//=========================================================
void	TStrip::ConvertWS(uint8_t* Buf,TRGBY* Arr,int CntPxl)
{TByteWS*	ByteWS = (TByteWS*)Buf	;

 for(int px=0;px<CntPxl;px++){
   int	Fade = (Arr[px].Y < 0 || Arr[px].Y >= sizeof(tabFade)) ? 0xFF : tabFade[Arr[px].Y]	;
   ByteWS[px*3+0] = Fade == 0xFF ? Arr[px].G : (Arr[px].G * Fade+127)/255 	;
   ByteWS[px*3+1] = Fade == 0xFF ? Arr[px].R : (Arr[px].R * Fade+127)/255	;
   ByteWS[px*3+2] = Fade == 0xFF ? Arr[px].B : (Arr[px].B * Fade+127)/255	;
 }
 ByteWS[CntPxl*3] = 0x00		;   
}
//=========================================================
void	TStrip::FOnTime(void)
{
 if(timFlash){ timFlash--	;}
 if(timDir)  { timDir--  	;}
 if(timFade) { timFade--  	;}
} 
//=========================================================
void	TStrip::OnTime(void)
{if(Instance) Instance->FOnTime()	;} 
//=========================================================

//=========================================================
void	TStrip::InitSPI(void)
{GPIO_InitTypeDef GPIO_InitStructure		;
 SPI_InitTypeDef  FSPI_InitStruct			;
 SPI_InitTypeDef* SPI_InitStruct = &FSPI_InitStruct	;

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ACC, ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI, ENABLE);  /* Enable SPI Clock */
 SPI_StructInit(SPI_InitStruct)		;
   
// SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;/* SPI_Direction member */
 SPI_InitStruct->SPI_Direction 			= SPI_Direction_1Line_Tx;/* SPI_Direction member */
 SPI_InitStruct->SPI_Mode 				= SPI_Mode_Master		;/* SPI_Mode member */
 SPI_InitStruct->SPI_DataSize 			= SPI_DataSize_8b		;/* SPI_DataSize member */
 SPI_InitStruct->SPI_CPOL 				= SPI_CPOL_High			;/* SPI_CPOL member */
 SPI_InitStruct->SPI_CPHA 				= SPI_CPHA_2Edge		;/* SPI_CPHA member */
 SPI_InitStruct->SPI_NSS 				= SPI_NSS_Soft			;/* SPI_NSS member */
 SPI_InitStruct->SPI_BaudRatePrescaler 	= SPI_BaudRatePrescaler_32;/*SPI_BaudRatePrescaler member */
 SPI_InitStruct->SPI_FirstBit 			= SPI_FirstBit_LSB		;/* SPI_FirstBit member */
 SPI_InitStruct->SPI_CRCPolynomial 		= 7						;/* SPI_CRCPolynomial member */
 SPI_Init(SPI_ACC,SPI_InitStruct)	;

//  RCC->APB2ENR|= RCC_APB2ENR_AFIOEN; // Тактирование альтернативных функций GPIO.
//  GPIOA->CRL |= GPIO_CRL_MODE4 | GPIO_CRL_MODE5 | GPIO_CRL_MODE7 ; // Выводы PA.4 PA.5 PA.7 - на выход.
//  GPIOA->CRL &=~GPIO_CRL_CNF4	; // General выход.
//  GPIOA->CRL &=~GPIO_CRL_CNF5	; GPIOA->CRL |= GPIO_CRL_CNF5_1	; // Альтернативный выход.
//  GPIOA->CRL &=~GPIO_CRL_CNF7	; GPIOA->CRL |= GPIO_CRL_CNF7_1	; // Альтернативный выход.
//GPIO_Mode_IPU 
 GPIO_InitStructure.GPIO_Pin   = MOSI_ACC | CLK_ACC	;
 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP	;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz	;
 GPIO_Init(GPIO_ACC, &GPIO_InitStructure)			;

 GPIO_InitStructure.GPIO_Pin   = MISO_ACC			;
 GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU		;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz	;
 GPIO_Init(GPIO_ACC, &GPIO_InitStructure)			;
 
 DMA_InitTypeDef    DMA_InitStructure;
 
 RCC_AHBPeriphClockCmd(SPI_MASTER_DMA_CLK, ENABLE)	;

  /* SPI_MASTER_Tx_DMA_Channel configuration ---------------------------------*/
 DMA_DeInit(SPI_MASTER_Tx_DMA_Channel);  
 DMA_InitStructure.DMA_PeripheralBaseAddr 	= (uint32_t)SPI_MASTER_DR_Base;
 DMA_InitStructure.DMA_MemoryBaseAddr 		= (uint32_t)BufWS;
 DMA_InitStructure.DMA_DIR 					= DMA_DIR_PeripheralDST;
 DMA_InitStructure.DMA_BufferSize 			= CntWS;
 DMA_InitStructure.DMA_PeripheralInc 		= DMA_PeripheralInc_Disable;
 DMA_InitStructure.DMA_MemoryInc 			= DMA_MemoryInc_Enable;
 DMA_InitStructure.DMA_PeripheralDataSize 	= DMA_PeripheralDataSize_Byte;
 DMA_InitStructure.DMA_MemoryDataSize 		= DMA_MemoryDataSize_Byte;
 DMA_InitStructure.DMA_Mode 				= DMA_Mode_Normal;
 DMA_InitStructure.DMA_Priority 			= DMA_Priority_High;
 DMA_InitStructure.DMA_M2M 					= DMA_M2M_Disable;
 DMA_Init(SPI_MASTER_Tx_DMA_Channel, &DMA_InitStructure);

 SPI_I2S_DMACmd(SPI_ACC, SPI_I2S_DMAReq_Tx, ENABLE);/* Enable SPI_MASTER DMA Tx request */
 
 SPI_Cmd (SPI_ACC,ENABLE);

// DMA_Cmd(SPI_MASTER_Tx_DMA_Channel, ENABLE);
// while(!DMA_GetFlagStatus(SPI_MASTER_Tx_DMA_FLAG));
}
//--------------------------------------------------------
