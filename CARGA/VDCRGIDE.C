#include <INCVIDEO.H>

INT2 VIDEO_inicdodaespelho(VD_VOID)
{
 INT2              conttab,ret;
 IDE_TABREFERDODA *work,
                  *ptrerro;
 char             buflocal[100];

 conttab = 0;
 work  = VIDEO_bufparamarq->bufdodas;
 while(work->nome && conttab < VIDEO_bufparamarq->numtab)
  {
   if (work->tipo == 4)
      {
       ptrerro = VIDEO_bufparamarq->bufdodas;
       while(ptrerro->nome)
        {
         if (!strcmp(ptrerro->reduzido,work->buffer))
            {
             work->buffer = ptrerro->buffer;
             break;
            }
         ++ptrerro;
        }

       if (!ptrerro->nome)
          {
           sprintf(buflocal,VIDEO_CARGA_mens_espelho,
                           work->buffer,work->nome);
           VIDEO_mostra_mens_erro(buflocal,VIDEO_ERRO_end_espelho);
           ptrerro = VIDEO_bufparamarq->bufdodas;
           while(ptrerro != work)
            {
             if (work->tipo == 1 || work->tipo == 3)
                 VIDEO_free_alloc_parametros(work->buffer);
             ++ptrerro;
            }
           return(VIDEO_ERRO_end_espelho);
          }

       ptrerro = VIDEO_bufparamarq->bufdodas;
       if (!VIDEO_enddodabuf(work,PTR_CAST(TEXT,work->buffer)))
          {
           while(ptrerro != work)
            {
             if (work->tipo == 1 || work->tipo == 3)
                 VIDEO_free_alloc_parametros(work->buffer);
             ++ptrerro;
            }
           return(VIDEO_ERRO_carga_end_doda_espelho);
          }
      }
   ++conttab;
   ++work;
  }
 return(FALSE);
}

