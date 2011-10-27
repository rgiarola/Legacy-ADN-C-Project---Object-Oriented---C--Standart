#include <INCVIDEO.H>

VD_VOID VIDEO_borda(cor)
BYTE cor;
{
 _AH = 0X0B;
 _BH = 0X00;
 _BL = cor;
 geninterrupt(0X10);
}


