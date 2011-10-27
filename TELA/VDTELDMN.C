#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_dispara_manutencao(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_CAMPO_CONSISTENCIA *consiste;
 VIDEO_NUCLEO_SERV        *nucleo;
 VIDEO_CAMPO_TELA         *campos;
 char                     *buffile,
                          *buffer;
 IDE_ARQUIVOS             *arquivo;
 long int                 offrec;
 INT2                     numarq,ret,
                          tmpfil,indice;
 VIDEO_IMAGEMTELA		  *imagem;

 imagem = (*tela)->imagem_ativa = (*tela)->imagens + (*tela)->imagem_accept;
 nucleo = imagem->campos;
 campos = PTR_CAST(VIDEO_CAMPO_TELA,nucleo->VIDEO_campos) +
                   nucleo->VIDEO_inicial;


 if ((consiste = campos->consiste) ==
      VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
      return(TRUE);

 do
  {
   if (consiste->tipocons == VIDEO_TELA_CONS_MANUT)
       {
        if (!VIDEO_CRG_carrega_objeto(consiste->objetocons.manutencao,1))
           {
            char buf[100];
            sprintf(buf,VIDEO_CARGA_mens_exec_tela,
                                   consiste->objetocons.manutencao->sistcrg,
                                   consiste->objetocons.manutencao->telacrg,
                                   isam_err);
            VIDEO_mostra_mens_erro(buf,VIDEO_ERRO_tela_manutencao);
            return(TRUE);
           }

        if (!VIDEO_CRG_prepara_tela(consiste->objetocons.manutencao))
           {
            char buf[100];
            sprintf(buf,VIDEO_CARGA_mens_exec_tela,
                                   consiste->objetocons.manutencao->sistcrg,
                                   consiste->objetocons.manutencao->telacrg,
                                   isam_err);
            VIDEO_mostra_mens_erro(buf,VIDEO_ERRO_prep_tela_manutencao);
			VIDEO_CRG_libera_tela(consiste->objetocons.manutencao);
            return(TRUE);
           }

		if (imagem->nmindarq)
           {
			indice = CTREE_keynm(imagem->nmindarq);
            numarq = CTREE_keyfil(indice);
            tmpfil = CTREE_tmpfil(numarq);

            ATIVA_BUF_DADOS;
            if ((buffer = CTREE_filbuf(numarq)) == VD_NULO)
               {
                char buf[100];
                sprintf(buffer,CTREE_MENS_mens_padrao_err,
							   VIDEO_mens_arquivo_invalido,
							   (VIDEO_bufparamarq->bufdodas+numarq)->reduzido,
                               ret,isam_err);
				VIDEO_mostra_mens_erro(buf,VIDEO_ERRO_buffer_arquivo_manut);
                VIDEO_CRG_libera_tela(consiste->objetocons.manutencao);
                return(TRUE);
               }

            if ((arquivo = CTREE_ifilend(numarq)) == VD_NULO)
               {
                char buf[100];
                sprintf(buffer,CTREE_MENS_mens_padrao_err,
							   VIDEO_mens_arquivo_invalido,
							   (VIDEO_bufparamarq->bufdodas+numarq)->reduzido,
                               ret,isam_err);
				VIDEO_mostra_mens_erro(buf,VIDEO_ERRO_ifil_arquivo_manut);
                VIDEO_CRG_libera_tela(consiste->objetocons.manutencao);
                return(TRUE);
               }

            if (VIDEO_ALLOC_MEM(buffile,arquivo->dreclen) == VD_NULO)
               {
                VIDEO_mostra_mens_erro_alloc(ALOCACAO_DISP_MANUTENCAO);
                VIDEO_CRG_libera_tela(consiste->objetocons.manutencao);
                return(TRUE);
               }

            VIDEO_movbloco(buffile,buffer,arquivo->dreclen);

            if ((offrec = CurrentFileOffset(tmpfil)) < 0L || isam_err)
               {
                char buf[100];

				sprintf(buffer,CTREE_MENS_mens_padrao_err,
							   VIDEO_mens_erro_offsetrec,
							   (VIDEO_bufparamarq->bufdodas+numarq)->reduzido,
							   I(offrec),isam_err);
				VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_offrec_arquivo_manut);
               }

           }

        VIDEO_CRG_dispara_tela(consiste->objetocons.manutencao);

        VIDEO_CRG_libera_tela(consiste->objetocons.manutencao);

		if (imagem->nmindarq)
           {
			if (offrec > 0L)
               {
                VIDEO_movbloco(buffer,buffile,arquivo->dreclen);
                if ((ret = SetRecord(tmpfil,offrec,buffer,arquivo->dreclen)) != 0)
                   {
                    char buf[100];

					sprintf(buffer,CTREE_MENS_mens_padrao_err,
								   VIDEO_mens_erro_offsetrec,
								   (VIDEO_bufparamarq->bufdodas+numarq)->reduzido,
								   ret,isam_err);
					VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_rest_offrec_arquivo_manut);
                   }
               }
            VIDEO_movbloco(buffer,buffile,arquivo->dreclen);
            VIDEO_FREE_ALLOC_MEM(buffile);
           }

        imagem->flagimagem |= (VIDEO_TELA_DISPCAMPOS);

        break;
       }
   ++consiste;
  }while(consiste->tipocons);
 return(TRUE);
}
