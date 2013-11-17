//=============================================================
#include <stm32f10x.h>
#include	<String.h>
#include	<Math.h>
#include	"Effect.h"
//=============================================================
//=============================================================
//=========================================================
uint8_t	tabFade[64]	;
//=============================================================
TRGBY*	TEffect::InitArray(TRGBY* Array,int SizeArr,const TEffItem* EffItem)
{if(!EffItem) EffItem = (TEffItem*)EffItem1	;
 for(int px=0;px<SizeArr;px++){
   Array[px] = Colors[EffItem[px].clIx]	;}
 
 for(int px=0;px<32;px++){
   tabFade[px] = uint8_t(exp(px*6.0/31-6)*255+0.5)	;
   tabFade[63-px] = tabFade[px]			;
 }
 
// for(int px=0;px<10;px++){
//   EffItemFade1[px]   .clIx = EffItemFade1[20+px].clIx = EffItemFade1[40+px].clIx = 
//   EffItemFade1[19-px].clIx = EffItemFade1[39-px].clIx = EffItemFade1[59-px].clIx =
//     px * 6 + 1	;
// }
 for(int px=0;px<30;px++){
   EffItemFade1[px]   .clIx = EffItemFade1[59-px].clIx = 
     px * 2 + 1	;
 }
 
 return Array	;}
//=============================================================
TRGBY*	TEffect::Step(TRGBY* Array,int SizeArr,const TEffItem* EffItem)
{int			px,cx,flPh=0,tPh		;
 static	uint8_t	Ph=0					; 
 TRGBY			prArr[CntRGBY]			;
 
 memcpy(prArr,Array,sizeof(prArr))		;
 if(!EffItem) EffItem = EffItem1		;
 
 for(px=0;px<SizeArr;px++){
   if(EffItem[px].Eff == efJump){
     cx = px+EffItem[px].Arg			;
	 Array[cx].R = prArr[px].R			;
	 Array[cx].G = prArr[px].G			;
	 Array[cx].B = prArr[px].B			;
   }
   else if(EffItem[px].Eff == efFade){
     tPh = (EffItem[px].Arg * Ph + EffItem[px].clIx)		;
	 while(tPh <  0) tPh += 64	;
	 while(tPh > 63) tPh -= 64	;
	 Array[px].Y = tPh	;
	 flPh = 1	;
   }
 }
 if(flPh){ Ph++	;}
 
 return Array	;}
//=============================================================
const TEffItem	EffItem1[]={
{ 1,efJump,+1},{ 1,efJump,+1},{ 1,efJump,+1},{ 1,efJump,+1},{ 1,efJump,+1},
{ 2,efJump,+1},{ 2,efJump,+1},{ 2,efJump,+1},{ 2,efJump,+1},{ 2,efJump,+1},
{ 3,efJump,+1},{ 3,efJump,+1},{ 3,efJump,+1},{ 3,efJump,+1},{ 3,efJump,+1},
{ 4,efJump,+1},{ 4,efJump,+1},{ 4,efJump,+1},{ 4,efJump,+1},{ 4,efJump,+1},
{ 5,efJump,+1},{ 5,efJump,+1},{ 5,efJump,+1},{ 5,efJump,+1},{ 5,efJump,+1},
{ 6,efJump,+1},{ 6,efJump,+1},{ 6,efJump,+1},{ 6,efJump,+1},{ 6,efJump,+1},
{ 9,efJump,+1},{ 9,efJump,+1},{ 9,efJump,+1},{ 9,efJump,+1},{ 9,efJump,+1},
{10,efJump,+1},{10,efJump,+1},{10,efJump,+1},{10,efJump,+1},{10,efJump,+1},
{11,efJump,+1},{11,efJump,+1},{11,efJump,+1},{11,efJump,+1},{11,efJump,+1},
{12,efJump,+1},{12,efJump,+1},{12,efJump,+1},{12,efJump,+1},{12,efJump,+1},
{13,efJump,+1},{13,efJump,+1},{13,efJump,+1},{13,efJump,+1},{13,efJump,+1},
{14,efJump,+1},{14,efJump,+1},{14,efJump,+1},{14,efJump,+1},{14,efJump,-59}
};
//=============================================================
const TEffItem	EffItemJump2[]={
{14,efJump,+1},{14,efJump,+1},{14,efJump,+1},{14,efJump,+1},{14,efJump,+1},
{13,efJump,+1},{13,efJump,+1},{13,efJump,+1},{13,efJump,+1},{13,efJump,+1},
{12,efJump,+1},{12,efJump,+1},{12,efJump,+1},{12,efJump,+1},{12,efJump,+1},
{11,efJump,+1},{11,efJump,+1},{11,efJump,+1},{11,efJump,+1},{11,efJump,+1},
{10,efJump,+1},{10,efJump,+1},{10,efJump,+1},{10,efJump,+1},{10,efJump,+1},
{ 9,efJump,+1},{ 9,efJump,+1},{ 9,efJump,+1},{ 9,efJump,+1},{ 9,efJump,-29},
{ 9,efJump,+29},{ 9,efJump,-1},{ 9,efJump,-1},{ 9,efJump,-1},{ 9,efJump,-1},
{10,efJump,-1},{10,efJump,-1},{10,efJump,-1},{10,efJump,-1},{10,efJump,-1},
{11,efJump,-1},{11,efJump,-1},{11,efJump,-1},{11,efJump,-1},{11,efJump,-1},
{12,efJump,-1},{12,efJump,-1},{12,efJump,-1},{12,efJump,-1},{12,efJump,-1},
{13,efJump,-1},{13,efJump,-1},{13,efJump,-1},{13,efJump,-1},{13,efJump,-1},
{14,efJump,-1},{14,efJump,-1},{14,efJump,-1},{14,efJump,-1},{14,efJump,-1}
};
//=============================================================
TEffItem	EffItemFade1[]={
{ 2,efFade,+1},{ 4,efFade,+1},{ 6,efFade,+1},{ 8,efFade,+1},{10,efFade,+1},
{12,efFade,+1},{14,efFade,+1},{16,efFade,+1},{18,efFade,+1},{20,efFade,+1},
{22,efFade,+1},{24,efFade,+1},{26,efFade,+1},{28,efFade,+1},{30,efFade,+1},
{28,efFade,+1},{26,efFade,+1},{24,efFade,+1},{22,efFade,+1},{20,efFade,+1},
{18,efFade,+1},{16,efFade,+1},{14,efFade,+1},{12,efFade,+1},{10,efFade,+1},
{ 8,efFade,+1},{ 6,efFade,+1},{ 4,efFade,+1},{ 2,efFade,+1},{ 0,efFade,+1},
{ 2,efFade,+1},{ 4,efFade,+1},{ 6,efFade,+1},{ 8,efFade,+1},{10,efFade,+1},
{12,efFade,+1},{14,efFade,+1},{16,efFade,+1},{18,efFade,+1},{20,efFade,+1},
{22,efFade,+1},{24,efFade,+1},{26,efFade,+1},{28,efFade,+1},{30,efFade,+1},
{28,efFade,+1},{26,efFade,+1},{24,efFade,+1},{22,efFade,+1},{20,efFade,+1},
{18,efFade,+1},{16,efFade,+1},{14,efFade,+1},{12,efFade,+1},{10,efFade,+1},
{ 8,efFade,+1},{ 6,efFade,+1},{ 4,efFade,+1},{ 2,efFade,+1},{ 0,efFade,+1}
};
//=============================================================
const TEffItem	EffItemFade3[]={
{ 2,efFade,+1},{ 4,efFade,+1},{ 6,efFade,+1},{ 8,efFade,+1},{10,efFade,+1},
{12,efFade,+1},{14,efFade,+1},{16,efFade,+1},{18,efFade,+1},{20,efFade,+1},
{22,efFade,+1},{24,efFade,+1},{26,efFade,+1},{28,efFade,+1},{30,efFade,+1},
{28,efFade,+1},{26,efFade,+1},{24,efFade,+1},{22,efFade,+1},{20,efFade,+1},
{18,efFade,+1},{16,efFade,+1},{14,efFade,+1},{12,efFade,+1},{10,efFade,+1},
{ 8,efFade,+1},{ 6,efFade,+1},{ 4,efFade,+1},{ 2,efFade,+1},{ 0,efFade,+1},
{ 2,efFade,-1},{ 4,efFade,-1},{ 6,efFade,-1},{ 8,efFade,-1},{10,efFade,-1},
{12,efFade,-1},{14,efFade,-1},{16,efFade,-1},{18,efFade,-1},{20,efFade,-1},
{22,efFade,-1},{24,efFade,-1},{26,efFade,-1},{28,efFade,-1},{30,efFade,-1},
{28,efFade,-1},{26,efFade,-1},{24,efFade,-1},{22,efFade,-1},{20,efFade,-1},
{18,efFade,-1},{16,efFade,-1},{14,efFade,-1},{12,efFade,-1},{10,efFade,-1},
{ 8,efFade,-1},{ 6,efFade,-1},{ 4,efFade,-1},{ 2,efFade,-1},{ 0,efFade,-1},
};
//=============================================================
const TEffItem	EffItemFade2[]={
{ 1,efFade,+1},{ 2,efFade,+1},{ 3,efFade,+1},{ 4,efFade,+1},{ 5,efFade,+1},
{ 6,efFade,+1},{ 7,efFade,+1},{ 8,efFade,+1},{ 9,efFade,+1},{10,efFade,+1},
{ 9,efFade,+1},{ 8,efFade,+1},{ 7,efFade,+1},{ 6,efFade,+1},{ 5,efFade,+1},
{ 4,efFade,+1},{ 3,efFade,+1},{ 2,efFade,+1},{ 1,efFade,+1},{ 0,efFade,+1},
{ 1,efFade,-1},{ 2,efFade,-1},{ 3,efFade,-1},{ 4,efFade,-1},{ 5,efFade,-1},
{ 6,efFade,-1},{ 7,efFade,-1},{ 8,efFade,-1},{ 9,efFade,-1},{10,efFade,-1},
{ 9,efFade,-1},{ 8,efFade,-1},{ 7,efFade,-1},{ 6,efFade,-1},{ 5,efFade,-1},
{ 4,efFade,-1},{ 3,efFade,-1},{ 2,efFade,-1},{ 1,efFade,-1},{ 0,efFade,-1},
{ 1,efFade,+1},{ 2,efFade,+1},{ 3,efFade,+1},{ 4,efFade,+1},{ 5,efFade,+1},
{ 6,efFade,+1},{ 7,efFade,+1},{ 8,efFade,+1},{ 9,efFade,+1},{10,efFade,+1},
{ 9,efFade,+1},{ 8,efFade,+1},{ 7,efFade,+1},{ 6,efFade,+1},{ 5,efFade,+1},
{ 4,efFade,+1},{ 3,efFade,+1},{ 2,efFade,+1},{ 1,efFade,+1},{ 0,efFade,+1},
{ 1,efFade,-1},{ 2,efFade,-1},{ 3,efFade,-1},{ 4,efFade,-1},{ 5,efFade,-1},
{ 6,efFade,-1},{ 7,efFade,-1},{ 8,efFade,-1},{ 9,efFade,-1},{10,efFade,-1},
{ 9,efFade,-1},{ 8,efFade,-1},{ 7,efFade,-1},{ 6,efFade,-1},{ 5,efFade,-1},
{ 4,efFade,-1},{ 3,efFade,-1},{ 2,efFade,-1},{ 1,efFade,-1},{ 0,efFade,-1}
};
//=============================================================
//=============================================================
