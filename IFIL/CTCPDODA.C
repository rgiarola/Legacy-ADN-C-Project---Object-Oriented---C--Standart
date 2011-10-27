#include <INCVIDEO.H>

VOID CTREE_cpydoda(transpdados)
VIDEO_TRANSP_DADOS *transpdados;
{
 IDE_DODA           *doda_destino,
                    *doda_origem;
 INT2                tamanho;


 while( transpdados->destino && transpdados->origem )
  {
   if ( ((doda_origem=CTREE_dodaend(transpdados->origem))!=
          VD_NILL(IDE_DODA))  &&
        ((doda_destino = CTREE_dodaend(transpdados->destino))!=
          VD_NILL(IDE_DODA)))
      {
       VIDEO_movbloco(doda_destino->fadr,
                      doda_origem->fadr,
                      min(doda_origem->flen,doda_destino->flen));
      }
   ++transpdados;
  }

}

