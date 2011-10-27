/* ============================================================================
   CONSEGUE DATA DO SISTEMA.
   Retorna uma computacional RTREE data (DATET).
   Em erro retorna exibe mensagem.
   ============================================================================ */
#include <INCVIDEO.H>

DATET VIDEO_sysdate(void)
{
  VD_date dataaux;
  DATET   rtree_data;
  VD_getdate(&dataaux);

  if((rtree_data =
        datein(VD_dateYea(dataaux),VD_dateMon(dataaux),VD_dateDay(dataaux)))<=0)
    {
     /*
     char buffer[200];
     sprintf(buffer,VIDEO_GERAIS_sysdate,
                   rtree_data,VD_dateYea(dataaux),VD_dateMon(dataaux),VD_dateDay(dataaux));
     VD_gtxy(1,1);
     printf("Erro Data %s",buffer);
//     VIDEO_mostra_mens_erro(buffer,TRUE);
     */
     return (-1);
    }
  return(rtree_data);
}

