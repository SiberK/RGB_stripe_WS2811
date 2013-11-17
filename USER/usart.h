#ifndef	USART_H
#define	USART_H
//=------------------------------------------
#ifdef __cplusplus
 extern "C" {
#endif 
//=------------------------------------------
void USART_Configuration(void)	;
int CommTest(void)				;
int GetKey (void)				;
int SendChar(int ch)			;
//=------------------------------------------
#ifdef __cplusplus
}
int USART_SendChar(int ch)		;
#endif 
#endif
