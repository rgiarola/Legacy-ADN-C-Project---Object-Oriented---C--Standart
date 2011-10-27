#include <INCVIDEO.H>

VD_VOID VIDEO_inictabref()
{
 IDE_TABREFERDODA *work;
 INT2              conttab;

 work = VIDEO_bufparamarq->bufdodas;

 conttab = 0;
 while(conttab < VIDEO_bufparamarq->numtab)
  {
   if (!work->nome && conttab)
      break;
   work->nome     = PTR_CAST(char,(W(work->nome)+VIDEO_OFFSET_BUF));
   work->reduzido = PTR_CAST(char,(W(work->reduzido)+VIDEO_OFFSET_BUF));
   work->dodainic = PTR_CAST(char,(W(work->dodainic)+VIDEO_OFFSET_BUF));
   work->dodafim  = PTR_CAST(char,(W(work->dodafim)+VIDEO_OFFSET_BUF));
   if (work->tipo == 4)
       work->buffer = PTR_CAST(char,(W(work->buffer)+VIDEO_OFFSET_BUF));
   ++work;
   ++conttab;
  }
}


