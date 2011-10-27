#include <INCVIDEO.H>

VD_VOID VIDEO_inicarqnome(VD_VOID)
{
 INT2          contind,
              contarq;
 IDE_ARQUIVOS *arquivos;
 IDE_INDEX    *indices;
 IDE_CHAVES   *chaves;

 arquivos = VIDEO_bufparamarq->arquivos;
 indices  = VIDEO_bufparamarq->indices;
 chaves   = VIDEO_bufparamarq->chaves;
 contarq = 0;
 while(contarq < VIDEO_bufparamarq->numarq)
  {
   if (!arquivos->pfilnam && contarq)
      break;

   arquivos->rfstfld = PTR_CAST(TEXT,(W(arquivos->rfstfld)+VIDEO_OFFSET_BUF));
   arquivos->rlstfld = PTR_CAST(TEXT,(W(arquivos->rlstfld)+VIDEO_OFFSET_BUF));
   arquivos->pfilnam = PTR_CAST(TEXT,(W(arquivos->pfilnam)+VIDEO_OFFSET_BUF));

   indices = arquivos->ix = (W(arquivos->ix)+VIDEO_bufparamarq->indices);

   for (contind = 0;contind < arquivos->dnumidx;contind++,indices++)
       {
        indices->seg     = W(indices->seg)+chaves;
        indices->ridxnam = PTR_CAST(TEXT,(W(indices->ridxnam)+VIDEO_OFFSET_BUF));
       }
   ++contarq;
   ++arquivos;
  }
}


