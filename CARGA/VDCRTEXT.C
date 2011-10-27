#include <INCVIDEO.H>

INT2 VIDEO_CRG_executa_tela(tela)
VIDEO_ESTMANUT *tela;
{
 if (VIDEO_CRG_carrega_objeto(tela,1))
    {
     INT2 ret;
     ret = FALSE;
     if (VIDEO_CRG_prepara_tela(tela))
         ret = VIDEO_CRG_dispara_tela(tela);
     VIDEO_CRG_libera_tela(tela);
     return(ret);
    }
  else
    if (isam_err)
       {
        char buffer[200];
        if (CDWORD(&tela->telacrg) > 1000L)
            sprintf(buffer,VIDEO_CARGA_mens_exec_tela,
                           tela->sistcrg,tela->telacrg,isam_err);
          else
           {
            char numtela[10];
            ultoa(CDWORD(&tela->telacrg),numtela,10);
            sprintf(buffer,VIDEO_CARGA_mens_exec_tela,
                           tela->sistcrg,numtela,isam_err);
           }
        VIDEO_mostra_mens_erro(buffer,
                               VIDEO_ERRO_tela_nao_encontrada);
       }
 return(FALSE);
}







