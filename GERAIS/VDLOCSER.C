#include <INCVIDEO.H>

VIDEO_TABSERV *VIDEO_localiza_servico(servico,tabserv)
WORD          servico;
VIDEO_TABSERV *tabserv;
{
 INT2 *servnucleo,servtrat;

 while(tabserv->VIDEO_servico)
  {
   servnucleo = tabserv->VIDEO_servico;
   while(*servnucleo)
    {
     if (servico == *servnucleo)
        return(tabserv);
     ++servnucleo;
    }
   ++tabserv;
  }

 return(VD_NULO);
}


