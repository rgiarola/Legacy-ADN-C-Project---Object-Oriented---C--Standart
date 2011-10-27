#include <INCVIDEO.H>

IDE_TABREFERDODA *VIDEO_locitemtab(item)
char *item;
{
 IDE_TABREFERDODA *work;
 INT2              conttab;

 work = VIDEO_bufparamarq->bufdodas;
 conttab = 0;
 while(work->nome && conttab < VIDEO_bufparamarq->numtab)
  {
   if (!strcmp(item,work->nome))
      return(work);
   ++work;
   ++conttab;
  }
 return(VD_NILL(IDE_TABREFERDODA));
}


