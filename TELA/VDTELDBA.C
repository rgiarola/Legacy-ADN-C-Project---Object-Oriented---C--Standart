#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_chama_data_base_adm(campos,param)
VIDEO_CAMPO_TELA  **campos;
VIDEO_NUCLEO_SERV **param;
{
 (*param)->VIDEO_inicial = (*campos)->objeto_num -
  PTR_CAST(VIDEO_CAMPO_TELA,(*param)->VIDEO_campos)->objeto_num;
 return(FALSE);
}
