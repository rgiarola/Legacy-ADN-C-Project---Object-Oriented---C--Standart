#include <INCVIDEO.H>

WORD VIDEO_IMPRESS_status(impressora)
int  impressora;
{
 WORD ret;
#ifdef MS_C
 union REGS regs;
 if (!impressora)
     return(VIDEO_IMPRESS_envia(0X0D,0));

 regs.h.ah = VIDEO_IMPRESSORA_STATUS;
 regs.x.dx = --impressora;
 int86(VIDEO_IMPRESSORA_INT,&regs,&regs);
 return(I(regs.h.ah));
#else
 if (!impressora)
     return(VIDEO_IMPRESS_envia(0X0D,0));
 _DX = --impressora;
 _AH = VIDEO_IMPRESSORA_STATUS;
 geninterrupt(VIDEO_IMPRESSORA_INT);
 ret  = _AX;
 _AL ^= _AL;
 return(ret);
#endif
}

