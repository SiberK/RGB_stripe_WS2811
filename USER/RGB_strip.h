#ifndef	RGB_STRIP_H
#define	RGB_STRIP_H
#include	"EventGUI.h"
#include	"Effect.h"
//===========================================================================
class	TStrip{
private:
 TRGBY*		Array						;
 int		timFlash,timFade			;
 int		timDir,Dir					;
 static TStrip*	Instance				;
public:

		TStrip(void)					;
		
 void			Init(void)				;
 EVENT_TYPE		OnEvent(TEvent* Event)	;
 void			FOnTime(void)			;
 static	void	OnTime(void)			;
 
 void		ConvertWS(uint8_t* Buf,TRGBY* Arr,int CntPxl)	;
 void		ShowArr(void)				;
 void		SendPxl(uint32_t pxl)		;
 
 void		InitSPI(void)				; 
};
//===========================================================================
#endif
