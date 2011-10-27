#include <INCVIDEO.H>

INT2 VIDEO_enddodabuf(work,buffer)
IDE_TABREFERDODA *work;
TEXT             *buffer;
{
 IDE_DODA *dodas;

 if ((dodas = CTREE_dodaend(work->dodainic)) == VD_NULO)
    {
     char buflocal[100];
     sprintf(buflocal,VIDEO_CARGA_mens_doda_inicio,
                      work->dodainic);
     VIDEO_mostra_mens_erro(buflocal,VIDEO_ERRO_doda_ini_nao_encontrado);
     return(FALSE);
    }

 if (!dodas->fadr)
    do
     {
      dodas->fadr = buffer;
      buffer     += dodas->flen;

      if (!strcmp(work->dodafim,dodas->fsymb))
         break;

      if (!((++dodas)->fsymb))
         {
          char buflocal[100];
          sprintf(buflocal,VIDEO_CARGA_mens_doda_fim,
                          work->dodafim);
          VIDEO_mostra_mens_erro(buflocal,VIDEO_ERRO_doda_fim_nao_encontrado);
          return(FALSE);
         }
     }while(TRUE);

 return(TRUE);
}

