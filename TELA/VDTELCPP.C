#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_campo_posterior(campos,param)
BYTE              **campos;
VIDEO_NUCLEO_SERV **param;
{
 BYTE *inicio, *fim;

 inicio = fim = PTR_CAST(BYTE,(*param)->VIDEO_campos);
 fim += ((*param)->VIDEO_tamcampo * ((*param)->VIDEO_numcampos - 1));
 (*campos) = (*campos) >= fim ? inicio :
                              ((*campos) + (*param)->VIDEO_tamcampo);
 return(TRUE);
}
