#include <INCVIDEO.H>

WORD VIDEO_IMPRESS_inicializa(impressora)
int impressora;
{
 WORD ret;
#ifdef MS_C
 union REGS regs;
 if (!impressora)
     return(VIDEO_IMPRESSORA_OK);
 regs.h.ah = VIDEO_IMPRESSORA_INIC;
 regs.x.dx = --impressora;
 int86(VIDEO_IMPRESSORA_INT,&regs,&regs);
 return(I(regs.h.ah));
#else
 if (!impressora)
     return(VIDEO_IMPRESSORA_OK);
 _DX = --impressora;
 _AH = VIDEO_IMPRESSORA_INIC;
 geninterrupt(VIDEO_IMPRESSORA_INT);
 ret  = _AX;
 _AL ^= _AL;
 return(ret);
#endif
}

