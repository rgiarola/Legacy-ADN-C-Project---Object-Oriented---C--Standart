#include <INCVIDEO.H>

void interrupt VIDEO_VISUAL_nova_int05(void)
{
 static BOOLEAN flagint = FALSE;

 if (flagint)
    return;

 disable();
 flagint = TRUE;
 enable();

 if (CBYTE(MK_FP(0X0040,0X0017))&VD_B0)
    VIDEO_VISUAL_velha_int05();
  else
    {
     if (!VIDEO_CALC_backscan && !VIDEO_CALC_backascii)
        {
         VIDEO_CALC_backscan  = SCAN_SPOOL;
         VIDEO_CALC_backascii = ASCII_SPOOL;
        }
    }

 disable();
 flagint = FALSE;
 enable();
}


void interrupt VIDEO_VISUAL_nova_int24(bp,di,si,ds,es,dx,cx,bx,ax)
WORD bp,di,si,ds,es,dx,cx,bx,ax;
{
 if (VIDEO_VISUAL_flag_int)
    {
	 VIDEO_VISUAL_velha_int24();
     ax = _AX;
     bx = _BX;
     cx = _CX;
     dx = _DX;
     es = _ES;
     ds = _DS;
     si = _SI;
     di = _DI;
     bp = _BP;
     return;
	}

 disable();
 VIDEO_VISUAL_flag_erro = TRUE;
 ax = W(ax&W(B08|B09|B10|B11|B12|B13|B14|B15));
 enable();
}

void interrupt (*VIDEO_VISUAL_velha_int05)() = VD_NULO;

BOOLEAN VIDEO_VISUAL_flag_int  = TRUE,
        VIDEO_VISUAL_flag_erro = FALSE;

void interrupt (*VIDEO_VISUAL_velha_int24)() = VD_NULO;

