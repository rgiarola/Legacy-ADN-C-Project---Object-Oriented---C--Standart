#include <INCVIDEO.H>

INT2 VIDEO_CALC_fixa_decimais(campo,flag,param)
VIDEO_CAMPO_TELA  *campo;
INT2              flag;
VIDEO_NUCLEO_SERV *param;
{
 switch(I(param->VIDEO_servrec))
  {
   case I(VIDEO_MTTECLA(13      ,28)):
   case I(VIDEO_MTTECLA(10      ,28)):
   case I(VIDEO_MTTECLA(15      ,13)):param->VIDEO_servrec =
                                      VD_MTTECLA(VD_NULO,ALT_O);
  }
 return(TRUE);
}


