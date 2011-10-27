#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_primeiro_campo(campos,param)
BYTE              **campos;
VIDEO_NUCLEO_SERV **param;
{
 (*campos) = PTR_CAST(BYTE,(*param)->VIDEO_campos);
 return(TRUE);
}

