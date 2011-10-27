#include <INCVIDEO.H>

INT2 VIDEO_TELA_busca_pesquisa(tela, param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_CAMPO_CONSISTENCIA *consiste;
 VIDEO_IMAGEMTELA         *imagem;
 VIDEO_CAMPO_TELA         *campo;
 INT2					  ret,numpesq,
                          contpesq;
 VIDEO_NUCLEO_SERV        *nucleo;
 VIDEO_PESQUISA_PLANILHA  *planilha,
                          *pesqsel;
 long int                 numrec = 0L;
 char					  **buffer_rec = VD_NULO,
						  *buffer = VD_NULO;
 IDE_ARQUIVOS			  *work_ifil;
 INT2                     tmpfil,resetbuf;

/*-----------------------------------------------------------------------------
            PEGA IMAGEM CORRENTE PARA SUAVISAR REFERENCIA POINTER
-----------------------------------------------------------------------------*/
 imagem = (*tela)->imagem_ativa;

 campo  = PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos) +
          imagem->campos->VIDEO_inicial;

/*-----------------------------------------------------------------------------
                               TESTA SE A CONSISTEMCIA
-----------------------------------------------------------------------------*/
 if ((consiste = campo->consiste) ==
      VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
     return(TRUE);

/*-----------------------------------------------------------------------------
                               CONTA NUMERO DE PESQUISA
-----------------------------------------------------------------------------*/
 numpesq = 0;
 while( consiste->tipocons )
  {
   numpesq += ((consiste->tipocons == VIDEO_TELA_CONS_BUSCA_DB) &&
       consiste->objetocons.planilha);
    ++consiste;
  }

/*-----------------------------------------------------------------------------
                       SE NAO HA PESQUISA TESTA SE HA MENU
-----------------------------------------------------------------------------*/
 if (!numpesq)
    {
     if ((consiste = campo->consiste) ==
          VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
         return(TRUE);

     numpesq = 0;
     while( consiste->tipocons )
      {
       if ((consiste->tipocons == VIDEO_TELA_CONS_MENU) &&
           consiste->objetocons.menu)
          {
           ++numpesq;
           break;
          }
        ++consiste;
      }

     if (numpesq)
         VIDEO_TELA_consiste_tabela_menu(&campo,consiste->objetocons.menu);

     return(TRUE);
    }

/*-----------------------------------------------------------------------------
          ALOCA POINTER BUFFER PARA CADA ARQUIVO DE PESQUISA MAIS UM PARA
          O ARQUIVO DA IMAGEM
-----------------------------------------------------------------------------*/
 if (VIDEO_ALLOC_MEM(buffer_rec,(numpesq+1)*sizeof(char *)) == VD_NULO)
	{
	 VIDEO_mostra_mens_erro_alloc(ALOCACAO_TELDBU_4);
	 return(TRUE);
	}

 VIDEO_setmem(buffer_rec,(numpesq+1)*sizeof(char *),0);

/*-----------------------------------------------------------------------------
                SE IMAGEM POSSUI ARQUIVO ALOCA BUFFER PARA ARQUIVO
-----------------------------------------------------------------------------*/
 numrec = 0L;

 if (imagem->arquivo > -1)
    {
     ATIVA_BUF_DADOS;
     buffer    = CTREE_filbuf(imagem->arquivo);
     tmpfil    = CTREE_tmpfil(imagem->arquivo);
     work_ifil = CTREE_ifilend(imagem->arquivo);
     numrec    = DATABASE_CurrentFileOffset(tmpfil);

/*-----------------------------------------------------------------------------
           ALLOCA MEMORIA PARA O BUFFER DO ARQUIVO CORRENTE E PARA
           O BUFFER DE EDICAO
-----------------------------------------------------------------------------*/
     if (VIDEO_ALLOC_MEM(*buffer_rec,work_ifil->dreclen*2) == VD_NULO)
        {
         VIDEO_mostra_mens_erro_alloc(ALOCACAO_TELDBU_1);
		 VIDEO_FREE_ALLOC_MEM(buffer_rec);
         return(TRUE);
        }

/*-----------------------------------------------------------------------------
                           GUARDA BUFFER DE EDICAO
-----------------------------------------------------------------------------*/
     VIDEO_movbloco(*buffer_rec,buffer,work_ifil->dreclen);

/*-----------------------------------------------------------------------------
                      GUARDA BUFFER DO REGISTRO CORRENTE
-----------------------------------------------------------------------------*/
     if (DATABASE_ReReadRecord(tmpfil,(*buffer_rec)+work_ifil->dreclen))
         SetRecord(tmpfil,numrec,buffer,work_ifil->dreclen);
    }

/*-----------------------------------------------------------------------------
                     ALOCA BUFFER PARA ESTRUTURA DE PESQUISA
-----------------------------------------------------------------------------*/
 if (VIDEO_ALLOC_MEM(planilha,(numpesq*sizeof(VIDEO_PESQUISA_PLANILHA)))
     == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_TELDBU_2);
	 if (*buffer_rec)
		 VIDEO_FREE_ALLOC_MEM(*buffer_rec);
     VIDEO_FREE_ALLOC_MEM(buffer_rec);
     return(TRUE);
    }

/*-----------------------------------------------------------------------------
                            ALLOCA BUFFER PARA O NUCLEO
-----------------------------------------------------------------------------*/
 if (VIDEO_ALLOC_MEM(nucleo,sizeof(VIDEO_NUCLEO_SERV)) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_TELDBU_3);
	 if (*buffer_rec)
		 VIDEO_FREE_ALLOC_MEM(*buffer_rec);
     VIDEO_FREE_ALLOC_MEM(buffer_rec);
     VIDEO_FREE_ALLOC_MEM(planilha);
     return(TRUE);
    }

 nucleo->VIDEO_numcampos = numpesq;
 nucleo->VIDEO_inicial   = 0;
 nucleo->VIDEO_tamcampo  = sizeof(VIDEO_PESQUISA_PLANILHA);
 nucleo->VIDEO_tabserv   = VIDEO_PESQUISA_tabserv_navegacao;
 nucleo->VIDEO_campos    = PTR_CAST(VIDEO_TAB_FUNC,planilha);

 if ((consiste = campo->consiste) ==
      VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
    {
	 if (*buffer_rec)
		 VIDEO_FREE_ALLOC_MEM(*buffer_rec);
     VIDEO_FREE_ALLOC_MEM(buffer_rec);
     VIDEO_FREE_ALLOC_MEM(planilha);
     VIDEO_FREE_ALLOC_MEM(nucleo);
     return(TRUE);
    }

 contpesq = 0;

/*-----------------------------------------------------------------------------
                                 PREPARA PESQUISAS
-----------------------------------------------------------------------------*/
 while( consiste->tipocons )
  {
   if (consiste->tipocons == VIDEO_TELA_CONS_BUSCA_DB &&
       consiste->objetocons.planilha)
      {
       *(planilha+contpesq) = *consiste->objetocons.planilha;

       (planilha+contpesq)->flagplanilha =
       (CTREE_keyfil(CTREE_keynm((planilha+contpesq)->nomeindice)) !=
         (imagem->nmindsub ? CTREE_keyfil(CTREE_keynm(imagem->nmindsub))
                           : CTREE_keyfil(CTREE_keynm(imagem->nmindarq))));

       (planilha+contpesq)->flagplanilha |=  (VIDEO_PESQUISA_DISPCURSOR |
                                             VIDEO_PESQUISA_DISPIMAGEM |
                                             VIDEO_PESQUISA_INICIALIZA |
                                             VIDEO_PESQUISA_DISPCAMPOS |
                                             VIDEO_PESQUISA_INICBUFFER |
                                             ((numpesq == 1)           ?
                                             VIDEO_PESQUISA_SALVATELA  :
                                             FALSE)                    |
                               ((imagem->flagimagem&VIDEO_TELA_STATUS) ?
                                 VIDEO_PESQUISA_STATUSTELA             :
                                 FALSE)                                |
                                 VIDEO_PESQUISA_SALVAADISP);
       (planilha+contpesq)->buffer_rec  = VD_NULO;
       (planilha+contpesq)->buffer_pesq = VD_NULO;
       (planilha+contpesq)->numrec      = VD_NULO;
       (planilha+contpesq)->numrecpesq  = VD_NULO;

       ++contpesq;
      }
   ++consiste;
  }
 
/*-----------------------------------------------------------------------------
                            SALVA BUFFER E BUFFER ISAM
-----------------------------------------------------------------------------*/
 for (contpesq = 0;contpesq < numpesq;contpesq++)
	 {
      IDE_ARQUIVOS *auxifil;
	  int		   arquivo;

/*---------------------------------------------------------------------------
         Caso CTREE_MULT_USER Ativo Aloca Memoria Para Buffer Isam
---------------------------------------------------------------------------*/
#ifdef CTREE_MULTI_USER
#define NUMBUFFER  2
#else
#define NUMBUFFER  1
#endif

      ATIVA_BUF_DADOS;
      arquivo = CTREE_keyfil(CTREE_keynm((planilha+contpesq)->nomeindice));
      auxifil = CTREE_ifilend(arquivo);

      if (VIDEO_ALLOC_MEM(*(buffer_rec+contpesq+1),auxifil->dreclen*NUMBUFFER) == VD_NULO)
         {
          VIDEO_mostra_mens_erro_alloc(ALOCACAO_TELDBU_5);
          for (numpesq = 0;numpesq <= contpesq;numpesq++)
              if (*(buffer_rec+numpesq))
                  VIDEO_FREE_ALLOC_MEM(*(buffer_rec+numpesq));
           VIDEO_FREE_ALLOC_MEM(buffer_rec);
           VIDEO_FREE_ALLOC_MEM(planilha);
           VIDEO_FREE_ALLOC_MEM(nucleo);
           return(TRUE);
          }

      ATIVA_BUF_DADOS;
      VIDEO_movbloco(*(buffer_rec+contpesq+1),CTREE_filbuf(arquivo),auxifil->dreclen);
/*---------------------------------------------------------------------------
   Caso NULT_USER Ativo Salva Buffer Isam
---------------------------------------------------------------------------*/
#ifdef CTREE_MULTI_USER
      VIDEO_movbloco(*(buffer_rec+contpesq+1)+auxifil->dreclen,
                      CTREE_filbuf(arquivo)+auxifil->dreclen*2,
                      auxifil->dreclen);
#endif
     }

 if (numpesq > 1)
    VD_PUSHWIN(1,80,1,25);
  else
    {
     VD_PUSHWIN(imagem->colf-7,imagem->colf,imagem->lini,imagem->lini);
     VD_PUSHWIN(imagem->coli,imagem->colf,imagem->linf,imagem->linf);
    }

 VIDEO_TELA_desativa_status(imagem);

 ret = VIDEO_NUCLEO_servidor_mspas(nucleo);

 if (numpesq > 1)
     VD_POPWIN();
   else
    {
     VD_POPWIN();
     VD_POPWIN();
    }

 pesqsel = planilha + nucleo->VIDEO_inicial;

 resetbuf = TRUE;

/*-----------------------------------------------------------------------------
                          REPOSICIONA SE SELECAO NA PLANILHA
-----------------------------------------------------------------------------*/
 if ((ret != VD_MTTECLA(VD_NULO,ESCAPESCAN)) &&
     (ret != VD_MTTECLA(ESCAPE ,ESCAPESCAN)))
     {
      if ((consiste = campo->consiste) !=
           VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
         {
#ifdef DATABASE_CTREE
          do
           {
            if (consiste->tipocons == VIDEO_TELA_CONS_POSICIONA_DB)
               {
                consiste->objetocons.consdb->posicao =
                          DATABASE_CurrentFileOffset(CTREE_tmpfil(
                                                     CTREE_keyfil(
                                    consiste->objetocons.consdb->indice)));
                break;
               }
           }while((++consiste)->tipocons);
#endif
          if (!(pesqsel->flagplanilha&VIDEO_PESQUISA_MANUTENCAO))
             {
              (*param)->VIDEO_servrec = VD_MTTECLA(B(0X0F),B(0X0F));
              (*param)->VIDEO_repdisp = TRUE;
             }
         }

      if (!(pesqsel->flagplanilha&VIDEO_PESQUISA_MANUTENCAO) &&
            imagem->arquivo > -1 && (CTREE_keyfil(CTREE_keynm(pesqsel->nomeindice)) ==
         (imagem->nmindsub ? CTREE_keyfil(CTREE_keynm(imagem->nmindsub))
                           : CTREE_keyfil(CTREE_keynm(imagem->nmindarq)))))
         {
          resetbuf = FALSE;
          VIDEO_TELA_seta_alteracao(*tela);
         }

      imagem->flagimagem |= VIDEO_TELA_DISPCAMPOS;
     }

 if (resetbuf && (imagem->arquivo > -1))
    {
/*-----------------------------------------------------------------------------
                       RESTAURA BUFFER DO REGISTRO CORRENTE
-----------------------------------------------------------------------------*/
     VIDEO_movbloco(buffer,(*buffer_rec)+work_ifil->dreclen,
                                         work_ifil->dreclen);
     if (numrec)
         if ((resetbuf = SetRecord(tmpfil,numrec,
                            buffer,work_ifil->dreclen)) != 0)
             {
              char   buffer[200];
              sprintf(buffer,CTREE_MENS_mens_padrao_err,
                             VIDEO_mens_erro_posiciona,
                             (VIDEO_bufparamarq->bufdodas+imagem->arquivo)->reduzido,
                             ret,isam_err);
              VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_posiciciona_disp_pesq);
             }
           else
             if (DATABASE_ReReadRecord(tmpfil,(*buffer_rec)+work_ifil->dreclen) != FALSE)
                 SetRecord(tmpfil,numrec,buffer,work_ifil->dreclen);

/*-----------------------------------------------------------------------------
                         RESTAURA BUFFER DE EDICAO
-----------------------------------------------------------------------------*/
     VIDEO_movbloco(buffer,*buffer_rec,work_ifil->dreclen);
    }

 for (contpesq = 0;contpesq < numpesq;contpesq++)
     {
      IDE_ARQUIVOS *auxifil;
      int          arquivo;

      arquivo = CTREE_keyfil(CTREE_keynm((planilha+contpesq)->nomeindice));
      auxifil = CTREE_ifilend(arquivo);

      if ((ret != VD_MTTECLA(VD_NULO,ESCAPESCAN)) &&
          (ret != VD_MTTECLA(ESCAPE ,ESCAPESCAN)))
         {
          if (contpesq == nucleo->VIDEO_inicial)
             {
              if (pesqsel->transpdados)
                   CTREE_cpydoda(pesqsel->transpdados);
             }
           else
             {
			  ATIVA_BUF_DADOS;
			  VIDEO_movbloco(CTREE_filbuf(arquivo),
							 *(buffer_rec+contpesq+1),auxifil->dreclen);

/*---------------------------------------------------------------------------
   Caso NULT_USER Ativo Restaura Buffer Isam
---------------------------------------------------------------------------*/
#ifdef CTREE_MULTI_USER
              VIDEO_movbloco(CTREE_filbuf(arquivo)+auxifil->dreclen*2,
							 *(buffer_rec+contpesq+1)+auxifil->dreclen,
							 auxifil->dreclen);
#endif
			 }
		 }
	   else
		 {
/*---------------------------------------------------------------------------
   Caso NULT_USER Ativo Restaura Buffer Isam
---------------------------------------------------------------------------*/
#ifdef CTREE_MULTI_USER
           ATIVA_BUF_DADOS;
		   VIDEO_movbloco(CTREE_filbuf(arquivo)+auxifil->dreclen*2,
						  *(buffer_rec+contpesq+1)+auxifil->dreclen,
						  auxifil->dreclen);
#endif
           ATIVA_BUF_DADOS;
           VIDEO_movbloco(CTREE_filbuf(arquivo),
                          *(buffer_rec+contpesq+1),auxifil->dreclen);
		 }
       VIDEO_FREE_ALLOC_MEM(*(buffer_rec+contpesq+1));
      }

 if (*buffer_rec)
     VIDEO_FREE_ALLOC_MEM(*buffer_rec);

 VIDEO_FREE_ALLOC_MEM(buffer_rec);
 VIDEO_FREE_ALLOC_MEM(planilha);
 VIDEO_FREE_ALLOC_MEM(nucleo);

 imagem->flagimagem |= (VIDEO_TELA_DISPCAMPOS);

 return(TRUE);
}

