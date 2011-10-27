#include <INCVIDEO.H>

VD_VOID VIDEO_inicdodanome(VD_VOID)
{
 IDE_DODA *dodas;

 dodas = VIDEO_bufparamarq->dodas;

 while(dodas->fsymb)
  {
   dodas->fsymb = PTR_CAST(TEXT,(W(dodas->fsymb)+VIDEO_OFFSET_BUF));
   ++dodas;
  }
}

