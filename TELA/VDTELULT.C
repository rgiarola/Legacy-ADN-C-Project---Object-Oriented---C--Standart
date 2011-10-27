#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_ultimo_campo(campos,param)
BYTE              **campos;
VIDEO_NUCLEO_SERV **param;
{
 (*campos) = PTR_CAST(BYTE,(*param)->VIDEO_campos) +
             ((*param)->VIDEO_tamcampo * ((*param)->VIDEO_numcampos - 1));
 return(TRUE);
}
