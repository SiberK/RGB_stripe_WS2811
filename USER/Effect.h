#ifndef		EFFECT_H
#define		EFFECT_H
//======================================================
#include	"EventGUI.h"
//======================================================
#pragma	pack(push,1)
//===========================================================================
struct	TByteWS{
 uint16_t		bit0 : 3	;
 uint16_t		bit1 : 3	;
 uint16_t		bit2 : 3	;
 uint16_t		bit3 : 3	;
 uint16_t		bit4 : 3	;
 uint16_t		bit5 : 3	;
 uint16_t		bit6 : 3	;
 uint16_t		bit7 : 3	;
 
				TByteWS(uint8_t val=0){*this = val	;}

 TByteWS& operator = (uint8_t val)
  {bit7 = (val&0x01) ? 3 : 1	; bit6 = (val&0x02) ? 3 : 1	;
   bit5 = (val&0x04) ? 3 : 1	; bit4 = (val&0x08) ? 3 : 1	;
   bit3 = (val&0x10) ? 3 : 1	; bit2 = (val&0x20) ? 3 : 1	;
   bit1 = (val&0x40) ? 3 : 1	; bit0 = (val&0x80) ? 3 : 1	;
   return *this	;}
};
//===========================================================================

//===========================================================================
struct	TRGBY{
 uint8_t	R,G,B			;
 int8_t		Y				;
 
		TRGBY(uint32_t val=0){*(uint32_t*)this = val	;}
		TRGBY(uint8_t r,uint8_t g,uint8_t b,uint8_t y){ R=r ; B=b ; G=g ; Y=y ;}
		
 operator uint32_t(){ return *(uint32_t*)this	;}
};
//======================================================

//======================================================
//======================================================
struct	TEffItem{
 uint8_t		clIx			;// начальный цвет (из таблицы)
 uint8_t		Eff				;
 int8_t			Arg				;
};
//======================================================
class	TEffect{
// TEffItem*		Item	;

public:
			TEffect(void){}
 TRGBY*			InitArray(TRGBY* Array,int SizeArr,const TEffItem* EffItem)	;
 TRGBY*			Step(TRGBY* Array,int SizeArr,const TEffItem* EffItem)	;
};
//======================================================

//======================================================
enum	TEff{efNone=0,efMove=1,efJump=2,efFade=3};
//======================================================
static const TRGBY clBlack = 0;
static const TRGBY clGray 	= 0xFF808080;
static const TRGBY clLtGray = 0xFFC0C0C0;
static const TRGBY clWhite 	= 0xFFFFFFFF;

static const TRGBY clMaroon = 0xFF000080;
static const TRGBY clGreen 	= 0xFF008000;
static const TRGBY clNavy 	= 0xFF800000;
static const TRGBY clOlive 	= 0xFF008080;
static const TRGBY clPurple = 0xFF800080;
static const TRGBY clTeal 	= 0xFF808000;

static const TRGBY clRed 	= 0xFF0000FF;
static const TRGBY clLime 	= 0xFF00FF00;
static const TRGBY clBlue 	= 0xFFFF0000;
static const TRGBY clYellow = 0xFF00FFFF;
static const TRGBY clFuchsia= 0xFFFF00FF;
static const TRGBY clAqua 	= 0xFFFFFF00;

static const TRGBY clMoneyGreen=0xFFC0DCC0;
static const TRGBY clSkyBlue= 0xFFF0CAA6;
static const TRGBY clCream 	= 0xFFF0FBFF;

//=========================================================
static const TRGBY	Colors[]={clBlack,clMaroon,clGreen,clNavy,clOlive,clPurple,clTeal,clGray,
							  clLtGray,clRed,clLime,clBlue,clYellow,clFuchsia,clAqua,clWhite};
//=========================================================
//static const uint8_t	tabFade[] = {0 ,1  ,2  ,3 ,4 ,6 ,8 ,12,18,22,32,40,64,80,128,160,
//									255,160,128,80,64,40,32,22,18,12,8 ,6 ,4 ,3 ,2  ,1};
extern uint8_t	tabFade[64]	;
//=============================================================
#define		CntRGBY		60
#define		CntWS		CntRGBY*9
//======================================================
extern const TEffItem	EffItem1[];
extern const TEffItem	EffItemJump2[];
extern 		 TEffItem	EffItemFade1[];
//=============================================================
#pragma	pack(pop)
#endif
