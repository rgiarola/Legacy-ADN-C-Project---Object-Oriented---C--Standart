#include <INCVIDEO.H>

INT2 VIDEO_TELA_confirma_saida(VIDEO_IMAGEMTELA *imagem);

INT2 VIDEO_TELA_processa_subfile(VIDEO_IMAGEMTELA         *imagem,
                                VIDEO_TELA_ENTRADA_DADOS *tela,
                                VIDEO_NUCLEO_SERV        *param,
                                INT2                      flagfunc,
                                INT2                      flag_pai,
                                INT2                      flagproc);

INT2 VIDEO_TELA_termina_edicao(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_IMAGEMTELA *imagem,
                  *imagwork;
 char             buffer[100];
 INT2              ret;

 imagem    = (*tela)->imagem_ativa;

 if ((imagem->tipotela == 2) &&
     ((*param)->VIDEO_servrec == VIDEO_MTTECLA(VD_NULO,ALT_O)))
    return(TRUE);

 if (((imagem->tipotela == 1)                    ||
      (imagem->tipotela == 7)                    ||
      (imagem->tipotela == 4))                   &&
     ((*param)->VIDEO_servrec == VIDEO_MTTECLA(VD_NULO,ALT_O)))
      if (!VIDEO_TELA_consiste_all(*tela,TRUE))
          return(TRUE);

 if (imagem->segsub)
    {
     INT2 ret, flag;

     flag = !VIDEO_TELA_testa_segconst_sub(imagem) ? 1 : 2;
     
     if ((*param)->VIDEO_servrec != VIDEO_MTTECLA(VD_NULO,ALT_O))
        {
         flag = 2;
         for (ret = (*tela)->imagem_accept,imagwork = imagem;
                     ret < (*tela)->num_imagens;ret++,imagwork++)
             {
              if (imagwork->segsub && imagwork->flagimagem&VIDEO_TELA_FLAGREGALT)
                 {
                  char buffer[100];

                  if (VIDEO_TELA_testa_segconst_sub(imagwork))
                     break;

                  strcpy(buffer,VIDEO_CONF_DESPRESA_SUBFILE);
                  if (imagwork->ident)
                      sprintf(&buffer[strlen(buffer)]," [%s]",imagwork->ident);

                  strcat(buffer,VIDEO_retorna_operacao);
                  if ((flag = VD_telaconf((80-strlen(buffer))/2,
                                   10,buffer,VIDEO_COR_EXC_REGISTRO)) == 1)
                     {
                      // Aten‡„o: Altera‡„o Realizada (FOR€A F7, ALT_O)
                      VIDEO_NUCLEO_SERV *nucleo;

                      nucleo = *param;
                      nucleo->VIDEO_servrec = I(VD_MTTECLA(VD_NULO,ALT_O));
                      nucleo->VIDEO_repdisp = TRUE;
                      // Fim de Altera‡„o

                      VIDEO_TELA_accept_tela_2(tela,param);
                     }
                  break;
                 }
             }
        }
      else
        {
         BOOLEAN flag_naoalterou = TRUE;

         for (ret = (*tela)->imagem_accept,imagwork = imagem;
                     ret < (*tela)->num_imagens;ret++,imagwork++)
              if (imagwork->segsub && imagwork->flagimagem&VIDEO_TELA_FLAGREGALT)
                  flag_naoalterou = FALSE;

         if (flag_naoalterou)
             flag = VD_telaconf((80-strlen(VIDEO_TELA_confirma_preocessa))/2,
                         10,VIDEO_TELA_confirma_preocessa,
                         VIDEO_COR_EXC_REGISTRO);
        }

     if (flag == 1)
          flag = VIDEO_TELA_processa_subfile(imagem,*tela,*param,FALSE,TRUE,TRUE);

	 if (flag)
        {
         INT2 imagem_accept;
         imagem_accept = (*tela)->imagem_accept;

         for (ret = (*tela)->imagem_accept,imagwork = imagem;
                     ret < (*tela)->num_imagens;ret++,imagwork++)
             {
              (*tela)->imagem_ativa = imagwork;
              (*tela)->imagem_accept= ret;

              VIDEO_TELA_libera_subfile(*tela,TRUE);
              VIDEO_TELA_desativa_status(imagwork);
              imagem->flagimagem              |=
                        (VIDEO_TELA_STATUS    |
                         VIDEO_TELA_DISPCAMPOS|
                         VIDEO_TELA_DISPIMAGEM|
                         VIDEO_TELA_INICIMAGEM);
              imagem->flagimagem &= ~VIDEO_TELA_FLAGREGALT;
              imagem->seqdisp = 0;

              if (!(*tela)->imagem_accept)
                 {
                  if ((*tela)->flagtela&VIDEO_TELA_FLAGPOPWIN)
                     VD_POPWIN();
                  return(FALSE);
                 }
             }
         (*tela)->imagem_accept = imagem_accept;
         (*tela)->imagem_ativa  = imagem;
         VIDEO_TELA_testa_imagem_pai(*tela,3);
        }

     VIDEO_TELA_desativa_status(imagem);
     (*param)->VIDEO_repdisp = TRUE;
     (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,ALT_R);

     return(TRUE);
    }

 if ((*param)->VIDEO_servrec != VIDEO_MTTECLA(VD_NULO,ALT_O) &&
     (imagem->flagimagem&VIDEO_TELA_ACCEPTCAMPOS)            &&
     VIDEO_TELA_confirma_saida(imagem) != TRUE)
     return(TRUE);

 for (ret = 0,imagwork = (*tela)->imagens;
              ret < (*tela)->num_imagens;ret++,imagwork++)
      if (imagwork->segsub)
         {
          INT2 accept,flag;

          if (imagwork->flagimagem&VIDEO_TELA_FLAGREGALT)
            {
             if (VIDEO_TELA_testa_segconst_sub(imagwork))
                break;

              strcpy(buffer,VIDEO_CONF_DESPRESA_SUBFILE);
              if (imagwork->ident)
                  sprintf(&buffer[strlen(buffer)]," [%s]",imagwork->ident);
              strcat(buffer,VIDEO_retorna_operacao);
              switch(VD_telaconf((80-strlen(buffer))/2,
                               10,buffer,VIDEO_COR_EXC_REGISTRO))
               {
                case 1:(*tela)->imagem_accept = 0;
                       (*tela)->imagem_ativa  = (*tela)->imagens;
                       if (VIDEO_TELA_processa_subfile(imagem,*tela,*param,
                                                       TRUE,TRUE,TRUE))
						   break;

                case 0:(*param)->VIDEO_repdisp = TRUE;
                       (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,ALT_R);
                       return(TRUE);
               }

              break;
             }
         }

 VIDEO_TELA_libera_subfile(*tela,FALSE);

 if ((*tela)->flagtela&VIDEO_TELA_FLAGPOPWIN)
    VD_POPWIN();
  else
    VIDEO_TELA_desativa_status((*tela)->imagem_ativa);

 return(FALSE);
}

INT2 VIDEO_TELA_confirma_saida(imagem)
VIDEO_IMAGEMTELA *imagem;
{
 INT2            col,lin,aux,ret;
 VIDEO_INFO_MENU *menu;
 VIDEO_ESTMANUT  menu_sai_tela;

 ret = TRUE;
 if ((imagem->linf -1) != imagem->lini)
    {
     VIDEO_setmem(&menu_sai_tela,sizeof(VIDEO_ESTMANUT),0);

     menu_sai_tela.sistcrg = VIDEO_padrao_projeto;
     menu_sai_tela.telacrg = "SIM_NAO_SAI_TELA";

     VD_PUSHWIN(imagem->colf-5,imagem->colf,
                imagem->lini,imagem->lini);

     VD_PUSHWIN(imagem->coli,imagem->colf,
                imagem->linf,imagem->linf);

     VIDEO_TELA_desativa_status(imagem);

     if ((col = imagem->colf-16) < 1)
        col = 1;

     if (((lin = imagem->lini)+5) > 24)
        lin = 19;

     ++lin;
     if (VIDEO_CRG_carrega_objeto(&menu_sai_tela,2))
        {
         VIDEO_CRG_prepara_menu(&menu_sai_tela);
         menu = PTR_CAST(VIDEO_INFO_MENU,(
                         PTR_CAST(char,menu_sai_tela.strtelacrg)+
                         sizeof(VIDEO_NUCLEO_SERV)));
         aux = menu->colf - menu->coli;
         menu->coli = col;
         menu->colf = col + aux;

         aux = menu->linf - menu->lini;
         menu->lini = lin;
         menu->linf = lin + aux;

         menu->col = col;
         menu->lin = lin;
         ret = VIDEO_CRG_dispara_menu(&menu_sai_tela,TRUE,TRUE,TRUE);
         VD_POPWIN();
         VIDEO_CRG_libera_tela(&menu_sai_tela);
        }
      else
        {
         char *mens;

         mens = "SAIR DA TELA";
         ret = VD_telaconf((80-strlen(mens))/2,7,mens,VIDEO_COR_EXC_REGISTRO);
        }

     VD_POPWIN();
     VD_POPWIN();
    }
 return(ret);
}

INT2 VIDEO_TELA_processa_subfile(imagem,tela,param,flagfunc,flag_pai,flagproc)
VIDEO_IMAGEMTELA         *imagem;
VIDEO_TELA_ENTRADA_DADOS *tela;
VIDEO_NUCLEO_SERV        *param;
INT2                      flagfunc,
                         flag_pai,
                         flagproc;
{
 VIDEO_TABFUNCAO  *tabfuncuser;
 VIDEO_IMAGEMTELA *imagem_pai,
				  *imagem_filha;
 INT2              imagem_accept,
				  flag_filha,
				  accept_pai,
                  accept_filha,
                  indice,arquivo,
                  tmpfil, ret, flagprocsub;
 char			  *bufarq,*ptraux;
 long int         posarq = 0L;
 IDE_ARQUIVOS     *auxifil;

 imagem_accept = tela->imagem_accept;
/*                      TESTA IMAGEM PAI*/

 if (imagem->nmindsub && VIDEO_TELA_testa_segconst_sub(imagem))
    return(TRUE);

 flag_pai = imagem_accept > 0 && flag_pai;

 if (flag_pai &&
     ((flag_pai = VIDEO_TELA_testa_imagem_pai(tela,3)) == TRUE))
	 {
	  if (!VIDEO_TELA_testa_imagem_pai(tela,1))
		 {
		  tela->imagem_accept = imagem_accept;
		  tela->imagem_ativa = imagem;
		  return(FALSE);
		 }
      imagem_pai = tela->imagem_ativa;
      accept_pai = tela->imagem_accept;
	 }

/*                      TESTA IMAGEM FILHA*/

 tela->imagem_ativa = imagem;
 tela->imagem_accept = imagem_accept;

 flag_filha = FALSE;
 if (((imagem_accept +1) < tela->num_imagens) &&
     ((flag_filha = VIDEO_TELA_testa_imagem_pai(tela,4)) == TRUE))
    {
     flag_filha = FALSE;
     imagem_filha = tela->imagem_ativa;
     accept_filha = tela->imagem_accept;
     if (!VIDEO_TELA_testa_segconst_sub(imagem_filha))
        {
         flag_filha = TRUE;

         if (!flagproc)
            {
             char buffer[100];

             strcpy(buffer,VIDEO_CONF_DESPRESA_SUBFILE);
             sprintf(&buffer[strlen(buffer)]," [%s]",(imagem_filha->ident) ?
                                                      imagem_filha->ident :
                                                      " TELA SEGUINTE");
             switch(VD_telaconf((80-strlen(buffer))/2,
                              10,buffer,VIDEO_COR_EXC_REGISTRO))
              {
               case 1:flag_filha = TRUE;
                      break;

               case 2:flag_filha = FALSE;
                      break;

               case 0:tela->imagem_ativa = imagem;
                      tela->imagem_accept = imagem_accept;
                      return(FALSE);
              }
            }
        }
    }

/*                      TESTA IMAGEM ATUAL*/

 tela->imagem_ativa  = imagem;
 tela->imagem_accept = imagem_accept;

 if (flag_filha)
	{
	 if (!VIDEO_TELA_testa_imagem_pai(tela,1) ||
		 !VIDEO_TELA_testa_imagem_pai(tela,2))
		return(FALSE);
	}

 if (flag_pai)
	{
	 tela->imagem_ativa  = imagem_pai;
	 tela->imagem_accept = accept_pai;
	 if (!VIDEO_TELA_testa_imagem_pai(tela,2))
		return(FALSE);
	}

 tela->imagem_ativa  = imagem;
 tela->imagem_accept = imagem_accept;

 if (flag_filha && imagem->nmindsub)
	{
     indice  = CTREE_keynm(imagem->nmindsub);
     arquivo = CTREE_keyfil(indice);
     tmpfil  = CTREE_tmpfil(arquivo);

     if ((auxifil = CTREE_ifilend(arquivo)) == VD_NULO)
        {
         char buffer[100];
		 sprintf(buffer,CTREE_MENS_mens_padrao_err,
						VIDEO_mens_arquivo_invalido,
						(VIDEO_bufparamarq->bufdodas+arquivo)->reduzido,
						1,isam_err);
		 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_ifil_arquivo_tela);
         return(FALSE);
        }

	 if ((posarq = DATABASE_CurrentFileOffset(tmpfil)) <= VD_NULO)
        {
         char buffer[100];
		 sprintf(buffer,CTREE_MENS_mens_padrao_err,
						VIDEO_mens_erro_posiciona,
						(VIDEO_bufparamarq->bufdodas+arquivo)->reduzido,
						I(posarq),isam_err);
		 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_posicao_arquivo_tela);
         return(FALSE);
        }

     if (VIDEO_ALLOC_MEM(bufarq,auxifil->dreclen) == VD_NULO)
        {
         VIDEO_mostra_mens_erro_alloc(ALOCACAO_SALVA_SUBFILE);
         return(FALSE);
        }

     if ((ptraux = CTREE_filbuf(arquivo)) == VD_NULO)
        {
         char buffer[100];
		 sprintf(buffer,CTREE_MENS_mens_padrao_err,
						VIDEO_mens_arquivo_invalido,
						(VIDEO_bufparamarq->bufdodas+arquivo)->reduzido,
						1,isam_err);
		 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_ifil_sub_tela);
         VIDEO_FREE_ALLOC_MEM(bufarq);
         return(FALSE);
        }

	 VIDEO_movbloco(bufarq,ptraux,auxifil->dreclen);
	}

 if (flagfunc)
    {
	 if (imagem->userfunc)
		{
		 tabfuncuser = VIDEO_funcao_tabfuncuser(imagem->userfunc);
		 if ((imagem->flagimagem&VIDEO_TELA_FDISPPOS) &&
			 (tabfuncuser) && (tabfuncuser->userfunc))
			{
			 param->VIDEO_servrec = VD_MTTECLA(VD_NULO,ALT_O);
			 (tabfuncuser->userfunc)(&imagem,VIDEO_TELA_FDISPPOS,&param);
			}

		 if (imagem->transpdados)
			 CTREE_cpydoda(imagem->transpdados);
		}
    }

 if (imagem->nmindsub)
    {
     char buffer[100];

     strcpy(buffer,VIDEO_CONF_PROCESSA_SUBFILE);
     sprintf(&buffer[strlen(buffer)]," [%s] [ ]",(tela->imagem_ativa->ident) ?
                                                   tela->imagem_ativa->ident  :
                                                  " TELA");
     VD_telprocessa(buffer,VIDEO_COR_EXC_REGISTRO);

     VIDEO_TELA_salva_subfile(imagem);

     VD_POPWIN();
    }

 if (flag_filha && imagem->nmindsub && posarq)
	{
	 VIDEO_movbloco(ptraux,bufarq,auxifil->dreclen);
     DATABASE_SetRecord(tmpfil,posarq,bufarq,auxifil->dreclen);
     VIDEO_FREE_ALLOC_MEM(bufarq);
     posarq = 0L;
	}

 if (flag_filha)
	{
	 tela->imagem_ativa  = imagem_filha;
	 tela->imagem_accept = accept_filha;
	 if (!VIDEO_TELA_processa_subfile(imagem_filha,tela,param,flagfunc,
                                 FALSE,flagproc))
		{
		 tela->imagem_ativa  = imagem;
		 tela->imagem_accept = imagem_accept;
		 return(FALSE);
		}
	}


 if (imagem->segsub)
	{
	 VIDEO_TELA_libera_subfile(tela,TRUE);
	 imagem->flagimagem 			 |=
			   (VIDEO_TELA_STATUS	 |
				VIDEO_TELA_DISPCAMPOS|
				VIDEO_TELA_DISPIMAGEM|
				VIDEO_TELA_INICIMAGEM);
     imagem->flagimagem &= ~VIDEO_TELA_FLAGREGALT;
	 imagem->seqdisp = 0;
	}

 tela->imagem_ativa  = imagem;
 tela->imagem_accept = imagem_accept;
 return(TRUE);
}

