#include <INCVIDEO.H>

INT2 VIDEO_processa_subfile(INT2 origem,INT2 destino,
							VIDEO_SEG_CHAVE    *segorigem,
							VIDEO_SEG_CHAVE    *segdestino,
							VIDEO_TRANSP_DADOS *transpdados);

INT2 VIDEO_getchave(INT2 indice,char *buffer,BOOLEAN flag);

INT2 VIDEO_TELA_salva_subfile(imagem)
VIDEO_IMAGEMTELA *imagem;
{
 char buffer[100];
 INT2  ret;

 if ((ret = VIDEO_processa_subfile(
                        CTREE_keynm(imagem->nmindsub),
                        CTREE_keynm(imagem->nmindarq),
						VD_NULO,
                        imagem->segsub,
						VD_NULO)) != FALSE)
    {
     sprintf(buffer,VIDEO_TELA_mens_balance_line,ret,isam_err);
	 VIDEO_mostra_mens_erro(buffer,ret > 0 ? 0-ret:ret);
     return(FALSE);
    }

/*****************************************************************************
                                 ROTINA ANTIGA
 ****************************************************************************
 if ((ret = CTREE_dlall(CTREE_keynm(imagem->nmindarq),
                        imagem->segsub,
                        VD_NULO)) != 101)
    {
	 sprintf(buffer,CTREE_MENS_mens_padrao_err,
					VIDEO_TELA_mens_delsub,
					(VIDEO_bufparamarq->bufdodas+CTREE_keyfil(CTREE_keynm(imagem->nmindarq)))->reduzido,
					ret,isam_err);
	 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_del_arq_sub);
     return(FALSE);
    }

 if ((ret = CTREE_copy(CTREE_keynm(imagem->nmindarq),
					   CTREE_keynm(imagem->nmindsub),
			imagem->segsub,FALSE,VD_NULO)) != 101)
    {
	 sprintf(buffer,CTREE_MENS_mens_padrao_err,
					VIDEO_TELA_mens_copysub,
					(VIDEO_bufparamarq->bufdodas+CTREE_keyfil(CTREE_keynm(imagem->nmindarq)))->reduzido,
					ret,isam_err);
	 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_copy_arq_sub);
     return(FALSE);
    }
*/

 return(TRUE);
}

INT2 VIDEO_processa_subfile(origem,destino,segorigem,segdestino,transpdados)
INT2               origem,destino;
VIDEO_SEG_CHAVE    *segorigem,*segdestino;
VIDEO_TRANSP_DADOS *transpdados;
{
 BOOLEAN	   flagorigem,flagleorigem,
			   flagdestino,flagledestino,
               flagposicao;
 DWORD         pos_destino;
 IDE_INDEX     *work_index;
 IDE_CHAVES    *work_chaves;
 IDE_ARQUIVOS  *ifil_destino;
 INT2          arquivo_origem,
               arquivo_destino,
               tmp_origem,tmp_destino,
               ret_origem,ret_destino,tamanho,
               leit_origem,leit_destino,ret,cont;
 char          *buf_destino,*chave_destino,
               *buf_origem ,*chave_origem ,
               *buf_arquivo;

/*-----------------------------------------------------------------------------
						  INICIALIZA VARIAVEIS
		  FLAGOPERACAO SETA TRUE PARA BALANCE LINE NO MESMO ARQUIVO
-----------------------------------------------------------------------------*/

 if ((arquivo_origem = CTREE_keyfil(origem)) < 0 ||
     (arquivo_destino = CTREE_keyfil(destino)) < 0)
    return(VIDEO_ERRO_arquivo_balance_line);

 tmp_origem   = CTREE_tmpfil(arquivo_origem);

 tmp_destino  = CTREE_tmpfil(arquivo_destino);
 ifil_destino = CTREE_ifilend(arquivo_destino);

 leit_origem  = CT_LE_EXTRA;
 ATIVA_BUF_EXTRA;
 buf_origem = CTREE_filbuf(arquivo_origem);

 leit_destino = CT_LE_DADOS;
 ATIVA_BUF_DADOS;
 buf_destino = CTREE_filbuf(arquivo_destino);

 flagdestino = FALSE;
 flagorigem  = FALSE;

/*-----------------------------------------------------------------------------
						  PEGA POSICOES NOS ARQUIVOS
-----------------------------------------------------------------------------*/
 ret_origem = CTREE_find(origem ,segorigem ,FIND_PRIMEIRO,leit_origem );

 ret_destino = CTREE_find(destino,segdestino,FIND_PRIMEIRO,leit_destino);

/*-----------------------------------------------------------------------------
					   ALOCA MEMORIA PARA AS CHAVES
-----------------------------------------------------------------------------*/
 if (VIDEO_ALLOC_MEM(chave_origem,128) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_BALANCE_LINE);
     return(VIDEO_ERRO_alocacao_chave_origem);
    }

 if (VIDEO_ALLOC_MEM(chave_destino,128) == VD_NULO)
    {
	 VIDEO_FREE_ALLOC_MEM(buf_origem);
	 VIDEO_mostra_mens_erro_alloc(ALOCACAO_BALANCE_LINE);
     return(VIDEO_ERRO_alocacao_chave_destino);
    }

/*-----------------------------------------------------------------------------
				  ALOCA MEMORIA PARA O BUFFER DO ARQUIVO DESTINO
-----------------------------------------------------------------------------*/
 if (VIDEO_ALLOC_MEM(buf_arquivo,ifil_destino->dreclen) == VD_NULO)
    {
	 VIDEO_FREE_ALLOC_MEM(buf_destino);
	 VIDEO_FREE_ALLOC_MEM(buf_origem);
	 VIDEO_mostra_mens_erro_alloc(ALOCACAO_BALANCE_LINE);
     return(VIDEO_ERRO_alocacao_chave_destino);
    }

 if (!ret_origem)
	 flagorigem  = TRUE;

 if (!ret_destino)
	 flagdestino = TRUE;

/*-----------------------------------------------------------------------------
		  SE CONSEGUIU LER UM DOS ARQUIVOS ENTRA BALANCE LINE
-----------------------------------------------------------------------------*/

 if (flagorigem || flagdestino)
    {
/*-----------------------------------------------------------------------------
							PEGA TAMANHO DA CHAVE
-----------------------------------------------------------------------------*/
     work_index = (ifil_destino->ix + (destino-arquivo_destino-1));
     work_chaves = work_index->seg;
     for (tamanho = ret = 0;ret < work_index->inumseg;ret++,work_chaves++)
          tamanho += work_chaves->slength;

     do
      {
       pos_destino = DATABASE_CurrentFileOffset(tmp_destino);
       VIDEO_cont_proc_tela();

/*-----------------------------------------------------------------------------
				   SE LEU ORIGEM PEGA CHAVE NO BUFFER EXTRA
-----------------------------------------------------------------------------*/
       if (flagorigem && ((ret = VIDEO_getchave(origem,chave_origem,
                                  TRUE)) != FALSE))
          {
		   VIDEO_FREE_ALLOC_MEM(buf_arquivo);
           VIDEO_FREE_ALLOC_MEM(chave_destino);
           VIDEO_FREE_ALLOC_MEM(chave_origem);
           return(ret);
          }

/*-----------------------------------------------------------------------------
				   SE LEU DESTINO PEGA CHAVE NO BUFFER DADOS
-----------------------------------------------------------------------------*/
	   if (flagdestino && (ret = VIDEO_getchave(destino,chave_destino,
                                  FALSE)) != FALSE)
          {
		   VIDEO_FREE_ALLOC_MEM(buf_arquivo);
           VIDEO_FREE_ALLOC_MEM(chave_destino);
           VIDEO_FREE_ALLOC_MEM(chave_origem);
           return(ret);
          }

/*---------------------------------------------------------------------------
       for (cont = 0;cont < 44;cont++)
            if (!*(chave_origem+cont))
               VIDEO_plotcarac(1+cont,1,254,PD_COR_01);
             else
               VIDEO_plotcarac(1+cont,1,*(chave_origem+cont),PD_COR_01);

       for (cont = 0;cont < 44;cont++)
            if (!*(chave_destino+cont))
               VIDEO_plotcarac(1+cont,2,254,PD_COR_01);
             else
               VIDEO_plotcarac(1+cont,2,*(chave_destino+cont),PD_COR_01);
---------------------------------------------------------------------------*/

       if (flagdestino)
           if (flagorigem)
/*-----------------------------------------------------------------------------
					 LEU DESTINO E ORIGEM E COMPARA AS CHAVES
-----------------------------------------------------------------------------*/
               ret = memcmp(chave_origem,chave_destino,tamanho);
             else
/*-----------------------------------------------------------------------------
						  LEU DESTINO E ORIGEM ACABOU
-----------------------------------------------------------------------------*/
               ret = 1000;
         else
           if (flagorigem)
/*-----------------------------------------------------------------------------
						  LEU ORIGEM E DESTINO ACABOU
-----------------------------------------------------------------------------*/
               ret = -1000;
             else
/*-----------------------------------------------------------------------------
						   ORIGEM E DESTINO ACABOU
-----------------------------------------------------------------------------*/
               ret = 0;


/*-----------------------------------------------------------------------------
						   SE ORIGEM E DESTINO ACABOU
						   TERMINA BALANCE LINE
-----------------------------------------------------------------------------*/
       if (!flagdestino && !flagorigem)
           break;

/*-----------------------------------------------------------------------------
					   SALVA BUFFER DO ARQUIVO DESTINO
-----------------------------------------------------------------------------*/
       VIDEO_movbloco(buf_arquivo,buf_destino,ifil_destino->dreclen);


/*-----------------------------------------------------------------------------
       VD_gtxy(1,3);
       printf("[ RET %3d %3d ]\n",ret,++cont);
       printf("[%20s][%20s]\n[%20s][%20s]\n[%4d][%4d][%4d]\n",
                                    VD_GETEND("SEGCHAVE_projeto",char),
                                    VD_GETEND("SEGCHAVE_projeto",char)+128,
                                    VD_GETEND("SEGCHAVE_referencia",char),
                                    VD_GETEND("SEGCHAVE_referencia",char)+128,
                                    VD_GETBUF("SEGCHAVE_numero",int),
                                    CINT(VD_GETEND("SEGCHAVE_numero",char)+128),
                                    tamanho);
       getch();
-----------------------------------------------------------------------------*/

       if (ret >= 0)
          {
           if (ret)
              {
/*-----------------------------------------------------------------------------
						 DELETA REGISTRO NO DESTINO
-----------------------------------------------------------------------------*/
			   if ((ret = CTREE_dlrec(arquivo_destino)) != FALSE)
				  {
                   char buffer[100];

                   VIDEO_FREE_ALLOC_MEM(chave_destino);
				   VIDEO_FREE_ALLOC_MEM(chave_origem);
                   sprintf(buffer,"Erro Dlrec ST[%d/%d]",ret,isam_err);
                   VIDEO_grava_erro(buffer);
                   return(VIDEO_ERRO_dlrec_balance_line);
				  }
               flagleorigem  = FALSE;
               flagledestino = TRUE;
			  }
            else
			  {
/*-----------------------------------------------------------------------------
						 SE HOUVE ALTERACAO OU TRANSPDADOS
						 ALTERA REGISTRO
-----------------------------------------------------------------------------*/
               if (memcmp(buf_destino,buf_origem ,ifil_destino->dreclen) ||
                   transpdados)
                  {
                   VIDEO_movbloco(buf_destino,buf_origem ,ifil_destino->dreclen);
                   if (transpdados)
                       CTREE_cpydoda(transpdados);
                   if ((ret = CTREE_rewrec(arquivo_destino)) != FALSE)
                      {
                       char buffer[100];

                       VIDEO_FREE_ALLOC_MEM(buf_arquivo);
                       VIDEO_FREE_ALLOC_MEM(chave_destino);
                       VIDEO_FREE_ALLOC_MEM(chave_origem);
                       sprintf(buffer,"Erro Rewrec ST[%d/%d]",ret,isam_err);
                       VIDEO_grava_erro(buffer);
                       return(VIDEO_ERRO_rewrec_balance_line);
                      }
                  }

               flagleorigem  = TRUE;
               flagledestino = TRUE;
			  }
		  }
		else
		  {
/*-----------------------------------------------------------------------------
							   INCLUI REGISTRO
-----------------------------------------------------------------------------*/
           VIDEO_movbloco(buf_destino,buf_origem ,ifil_destino->dreclen);
           if (transpdados)
               CTREE_cpydoda(transpdados);

           if ((ret = CTREE_adrec(arquivo_destino)) != FALSE)
			  {
               char buffer[100];
               VIDEO_FREE_ALLOC_MEM(buf_arquivo);
			   VIDEO_FREE_ALLOC_MEM(chave_destino);
			   VIDEO_FREE_ALLOC_MEM(chave_origem);
               sprintf(buffer,"Erro Adrec ST[%d/%d][%d]",ret,isam_err,arquivo_destino);
               VIDEO_grava_erro(buffer);
               return(VIDEO_ERRO_adrec_balance_line);
			  }

/*-----------------------------------------------------------------------------
						  RESTAURA POSICAO NO DESTINO
-----------------------------------------------------------------------------*/
           if (flagdestino)
              {
               DATABASE_SetRecord(tmp_destino,pos_destino,
                                  buf_arquivo,ifil_destino->dreclen);
               DATABASE_ReReadRecord(tmp_destino,buf_destino);
#ifdef CTREE_MULTI_USER
               VIDEO_movbloco(buf_destino+(ifil_destino->dreclen*2),
                              buf_destino,ifil_destino->dreclen);
#endif
              }
           flagleorigem  = TRUE;
		   flagledestino = FALSE;
		  }

/*-----------------------------------------------------------------------------
								LE ORIGEM
-----------------------------------------------------------------------------*/
       if (flagleorigem)
           if ((ret_origem = CTREE_find(origem ,segorigem ,
                                         FIND_PROXIMO,leit_origem )) == FALSE)
               flagorigem = TRUE;
             else
               flagorigem = FALSE;

/*-----------------------------------------------------------------------------
								LE DESTINO
-----------------------------------------------------------------------------*/
       if (flagledestino)
           if ((ret_destino = CTREE_find(destino,segdestino,
                                         FIND_PROXIMO,leit_destino)) == FALSE)
               flagdestino = TRUE;
             else
               flagdestino = FALSE;

      }while(flagdestino || flagorigem);
    }

/*-----------------------------------------------------------------------------
								TERMINA
-----------------------------------------------------------------------------*/
 VIDEO_FREE_ALLOC_MEM(buf_arquivo);
 VIDEO_FREE_ALLOC_MEM(chave_destino);
 VIDEO_FREE_ALLOC_MEM(chave_origem);
 return(FALSE);
}


INT2 VIDEO_getchave(indice,buffer,flag)
INT2    indice;
char    *buffer;
BOOLEAN flag;
{
 int real_indice;

 if (CTREE_getchave(indice,buffer,
            flag ? BUFFER_EXTRA : BUFFER_DADOS) != FALSE)
     return(VIDEO_ERRO_getchave_balance_line);

 if ((real_indice = CTREE_tmpkey(indice)) < 0)
     return(VIDEO_ERRO_getchave_balance_line);

 if (DATABASE_TransformKey(real_indice, buffer ) == VD_NULO)
     return(VIDEO_ERRO_getchave_balance_line);

 return(FALSE);
}
