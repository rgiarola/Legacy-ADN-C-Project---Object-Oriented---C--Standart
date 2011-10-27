#include <INCVIDEO.H>

VD_VOID VIDEO_inic_transp(transpdados)
VIDEO_TRANSP_DADOS *transpdados;
{
 IDE_DODA *doda;

 if (!transpdados)
    return;

 while(transpdados->destino)
  {
   if ((doda=CTREE_dodaend(transpdados->destino)) != VD_NILL(IDE_DODA))
       VIDEO_setmem(doda->fadr,doda->flen,0);
   ++transpdados;
  }
}



