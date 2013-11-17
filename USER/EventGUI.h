//--------------------------------------------------------------
//		miniGUI.h
//--------------------------------------------------------------
#ifndef		EVENT_GUI_H
#define		EVENT_GUI_H
//--------------------------------------------------------------
#include "stm32f10x.h"
//#include	"Mark.h"
//--------------------------------------------------------------
#pragma pack(push,1)
//=========================================================
//--------------------------------------------------------------
//#ifdef __cplusplus
// extern "C" {
//#endif
//--------------------------------------------------------------
struct	TPosition{
 int16_t	X,Y		;
};
//--------------------------------------------------------------
struct	TRegion{
  int16_t	Left,Top,Right,Bottom	;

  int16_t	Width() {return Right -Left+1	;}
  int16_t	Height(){return Bottom-Top +1	;}
  int16_t	Area()  {return Width()*Height();}
};
//--------------------------------------------------------------
struct	TPoint{
 int16_t	X,Y		;

 		TPoint(int16_t x,int16_t y):X(x),Y(y){}
		TPoint(void){X=Y=0	;}
};
//--------------------------------------------------------------
struct	TRect{
  int16_t	Left,Top,Right,Bottom	;

  TRect(void):Left(0),Top(0),Right(0),Bottom(0){}
  TRect(int16_t left,int16_t top,int16_t right,int16_t bottom)
  {Left  = left<=right ? left  : right	;
   Right = left<=right ? right : left	;
   Top   = top <=bottom ? top  : bottom	;
   Bottom= top <=bottom ? bottom : top	;}

  int32_t	Width() {return Right -Left+1	;}
  int32_t	Height(){return Bottom-Top +1	;}
  int32_t	Area()  {return Width()*Height();}
  int	Overlap(const TPoint& pnt)
  { return Left > pnt.X || pnt.X > Right ||
  		   Top  > pnt.Y || pnt.Y > Bottom ? 0 : 1	;}
  int	Overlap(const TPosition& pnt)
  { return Left > pnt.X || pnt.X > Right ||
  		   Top  > pnt.Y || pnt.Y > Bottom ? 0 : 1	;}
};
//--------------------------------------------------------------
typedef		uint16_t	EVENT_TYPE	;
typedef		uint16_t	MSG			;
//--------------------------------------------------------------

//--------------------------------------------------------------
//--------------------------------------------------------------
typedef	EVENT_TYPE	(*ON_EVENT)(EVENT_TYPE EvType)	;
//--------------------------------------------------------------------------------
enum	{mdShowTerm,mdShowSec,mdNorm,mdSetMin,mdSetHour,mdSetDay,mdSetMon,mdSetYear,mdEnd};
enum	{KeyNO=-1	,NoEvent=0,
		 KeyUp=1	,KeyDown=2	,KeyLeft=3	,KeyRight=4	,
		 KeyEnter=5	,KeyEsc=6	,KeyPlus=7	,KeyMinus=8	,
		 KeyPwr=9 	,Key1=10  	,Key2=11   	,
		 KeyUpLeft=12,KeyUpRight=13,KeyDownLeft=14,KeyDownRight=15,KeyLcdBright,
		 KeyPwrOn,KeyPwrOff,
		 KeyDemoLED,KeyTstBattery,KeyNegCH,KeyIMI,KeyFFT,
		 TP_PenDown,TP_PenUp,TP_NoEvent,TP_Left,TP_Right,TP_Top,TP_Bottom,
		 evGetEvent,evAccl0,evAccl1,evAdcRdy,evTermMsr,evSetTermo,evShowRepaint,
		 evUseFake,evDistantion,
		 MENU_Repaint,MENU_MainMenu,evOscShow,
		 Key3,Key4,Key5,Key6,Key7,Key8,
		 FILE_Write,evSetFreq,evSetBand,evShowBand,
		 KeyNA};
//==================================================
enum {ftNONE=0,ftECG,ftFCG,ftPW,ftECG_FCG,ftECG_PW,ftFCG_PW,ftECG_FCG_PW};
//--------------------------------------------------------------
//    case	ecSendData:Event->Type = SendData() ? ecTxStart : ecTxBreak		; break	;
//    
//    case evGetEvent: 
// 	 if(flTxEnd   ){flTxEnd   = 0		; Event->Type = ecTxEnd		;}
// 	 if(flLedTxOff){flLedTxOff= 0		; Event->Type = 	;}
// 	 if(flLedRxOn ){flLedRxOn = 0		; Event->Type = 	;}
// 	 if(flRxEnd   ){flRxEnd   = 0		; Event->Type = 	;}
//==================================================
struct	TEvent{
  EVENT_TYPE	Type		;
  union{
	MSG			Msg			;
	uint16_t	Len			;
	short		Value		;
	bool		Checked		;
  };
  union{
	TPosition	Pos			;
	TRegion		Regi		;
	int			Angle[2]	;
	int			LValue[2]	;
	short		shData[4]	;
	void*		Data		;
	char*		strData[2]	;
  };

  			TEvent(EVENT_TYPE _type=0,MSG _msg=0):Type(_type),Msg(_msg){}
			TEvent(EVENT_TYPE _type,uint16_t _len,void* _data):Type(_type),Len(_len),Data(_data){}
			TEvent(EVENT_TYPE _type,TPosition _pos):Type(_type),Pos(_pos){}
			TEvent(EVENT_TYPE _type,TRegion   _reg):Type(_type),Regi(_reg){}
};
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
#define	SIZE_ARRAY(AR)	(sizeof(AR)/sizeof(*AR))
//--------------------------------------------------------------
extern	volatile int	flBackupStored	;
//--------------------------------------------------------------
//#ifdef __cplusplus
// }
//#endif
#pragma pack(pop)
//=========================================================
#endif
