#include <INCVIDEO.H>

INT2 VIDEO_TELA_data_base_adm_pri(campos, param)
VIDEO_CAMPO_TELA  **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_CAMPO_CONSISTENCIA *consiste;
 INT2        ret;

 if ((consiste = (*campos)->consiste) ==
      VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
     return(TRUE);

 while( consiste->tipocons )
  {
   if( consiste->tipocons==VIDEO_TELA_CONS_POSICIONA_DB
       && consiste->objetocons.consdb)
     {
      if ((ret=CTREE_find( consiste->objetocons.consdb->indice,
                           consiste->objetocons.consdb->segchave,
                           FIND_PRIMEIRO, CT_LE_EXTRA_REPASSA ))
          == FALSE)
         {
          if (consiste->objetocons.consdb->transpdados)
              CTREE_cpydoda(consiste->objetocons.consdb->transpdados);

          (*param)->VIDEO_inicial = (*campos)->objeto_num -
           PTR_CAST(VIDEO_CAMPO_TELA,(*param)->VIDEO_campos)->objeto_num;
#ifdef DATABASE_CTREE
		  consiste->objetocons.consdb->posicao =
		  DATABASE_CurrentFileOffset(CTREE_tmpfil(CTREE_keyfil(consiste->objetocons.consdb->indice)));
#endif
          return(FALSE);
         }
        else
         {
          char buffer[200];

          sprintf(buffer,CTREE_MENS_mens_padrao_err,
                         VIDEO_mens_arquivo_vazio,
                         (VIDEO_bufparamarq->bufdodas+
                         CTREE_keyfil(consiste->objetocons.consdb->indice))->reduzido,
                         ret,isam_err);
          VIDEO_mostra_mens_erro(buffer,
                                 ret      != 101             ?
                                 VIDEO_ERRO_arquivo_vazio_pri:
                                 TRUE                        );
         }
       return( TRUE );
     }
   ++consiste;
  }

 return(TRUE);
}

