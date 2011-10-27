#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_consiste_campo(campos,param)
VIDEO_CAMPO_TELA  **campos;
VIDEO_NUCLEO_SERV **param;
{
 return(VIDEO_TELA_consiste_camp_imagem(campos,TRUE,param));
}

INT2 VIDEO_TELA_consiste_camp_imagem(campos,flagmens,param)
VIDEO_CAMPO_TELA  **campos;
INT2               flagmens;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_CAMPO_CONSISTENCIA *consiste;
 VIDEO_INFO_MENU          *menu;
 VIDEO_CAMPO_TELA         *campo;
 unsigned long            check_offset_file,
                          posvalkey;
 double                   valor_teste;
 INT2                      flagtipo  ,obrigatorio,
                          retorno   ,ret        ,
                          arquivo    ,
                          tmpfil    ,tamaux     ,
                          flagaux   ,indice     ;
 char                     *buffer_rec,
                          *buffer_aux;
 IDE_ARQUIVOS             *work_ifil;

 campo         = (*campos);
 if ((consiste = campo->consiste) ==
      VIDEO_NILL(VIDEO_CAMPO_CONSISTENCIA))
    if (param)
       {
        if ((*param)->VIDEO_servrec != VD_MTTECLA(VD_NULO,ALT_S))
           {
            (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,DIREITA);
            (*param)->VIDEO_repdisp = TRUE;
            return(TRUE);
           }
        return(FALSE);
       }
      else
        return(FALSE);

 flagtipo = TRUE;
 switch(campo->tipo)
  {
   case VIDEO_CAMPO_BYTE:
		valor_teste = D(CBYTE(campo->buffer_binario));
		break;
   case VIDEO_CAMPO_WORD:
        valor_teste = D(CWORD(campo->buffer_binario));
		break;
   case VIDEO_CAMPO_DWORD:
        valor_teste = D(CDWORD(campo->buffer_binario));
		break;
   case VIDEO_CAMPO_SHINT:
		valor_teste = D(CCHAR(campo->buffer_binario));
		break;
   case VIDEO_CAMPO_INT:
		valor_teste = D(CINT(campo->buffer_binario));
		break;
   case VIDEO_CAMPO_LONG:
		valor_teste = D(CLONG(campo->buffer_binario));
		break;
   case VIDEO_CAMPO_DOUBLE:
		valor_teste = CDOUBLE(campo->buffer_binario);
		break;
   case VIDEO_CAMPO_DATA:
        valor_teste = D(CDWORD(campo->buffer_binario));
		break;
   case VIDEO_CAMPO_TIME:
        valor_teste = D(CDWORD(campo->buffer_binario));
		break;
   case VIDEO_CAMPO_STRING:
        flagtipo = FALSE;
		break;
   case VIDEO_CAMPO_CARACTER:
        flagtipo = 2;
		break;
  }

 obrigatorio = FALSE;

 do
  {
   switch(consiste->tipocons)
	{
     case  VIDEO_TELA_CONS_OBRIGATORIO:
           VIDEO_mensagem_default.cor = consiste->objetocons.mens->cor;
           obrigatorio = TRUE;
           switch(flagtipo)
            {
             char *aux;
             case 1:if (valor_teste == D(0))
                       {
                        if (flagmens)
							VIDEO_mostra_mens_erro(consiste->objetocons.mens->mensagem,TRUE);
                        return(TRUE);
                       }
                    break;
             case 0:aux = campo->buffer_binario;
                    while(*aux == ' ')
                          ++aux;
                    if (!*aux)
                       {
                        if (flagmens)
                            VIDEO_mostra_mens_erro(consiste->objetocons.mens->mensagem,TRUE);
                        return(TRUE);
                       }
                    break;

             case 2:if (*campo->buffer_binario == ' ' || !*campo->buffer_binario)
                       {
                        if (flagmens)
                            VIDEO_mostra_mens_erro(consiste->objetocons.mens->mensagem,TRUE);
                        return(TRUE);
                       }
                    break;
            }
           break;

     case  VIDEO_TELA_CONS_MENU:
           menu = consiste->objetocons.menu;

           if (flagtipo == 1)
              {
               if (VIDEO_TELA_consiste_tabela(PTR_CAST(char,&valor_teste) ,
                   menu->opcoes,VIDEO_TELA_compara_numero,campo->tamanho) &&
                   (valor_teste != 0 || obrigatorio))
                   if (!flagmens ||
                       VIDEO_TELA_consiste_tabela_menu(campos,menu))
                       return(TRUE);
              }
            else
              {
               char *aux,
                    buffer_aux[10];

               if (flagtipo)
                  {
                   aux = buffer_aux;
                   buffer_aux[0] = *campo->buffer_binario,
                   buffer_aux[1] = '\0';
                   tamaux = 1;
                  }
                else
                  {
                   if ((tamaux = strlen(campo->buffer_binario)) <
                        campo->tamanho);
                       VIDEO_setmem(campo->buffer_binario+tamaux,
                              campo->tamanho-tamaux,' ');
                   aux = campo->buffer_binario;
                   *(aux + campo->tamanho) = '\0';
                  }
               flagaux = TRUE;
               if (VIDEO_TELA_consiste_tabela(aux,menu->opcoes,memcmp,
                                          flagtipo ? campo->tamanho : -1))
                  {
                   *(aux + tamaux) = '\0';
                   flagaux = TRUE;
                   if (strlen(aux) || obrigatorio)
                       if (!flagmens ||
                           VIDEO_TELA_consiste_tabela_menu(campos,menu))
                               return(TRUE);
                  }

               if (flagaux)
                  {
                   aux = campo->buffer_binario + campo->tamanho - 1;
                   while((*aux == ' ') && (aux != campo->buffer_binario))
                    {
                     *aux = '\0';
                     --aux;
                    }
                   if (aux != campo->buffer_binario)
                      if (*(aux+1) == ' ')
                          *(aux+1) = '\0';
                  }
              }
           break;
/*=============================================================================
                             CONSISTENCIA DE FAIXA
=============================================================================*/
     case  VIDEO_TELA_CONS_FAIXA:
           if (flagtipo == 1)
              {
               if ((valor_teste != 0 || obrigatorio) &&
                    VIDEO_TELA_consiste_faixa(PTR_CAST(char,&valor_teste),
                    consiste->objetocons.faixa->faixa,VIDEO_TELA_faixa_numero))
                  {
                   if (flagmens)
                       VIDEO_TELA_display_faixa(
                              consiste->objetocons.faixa->faixa);
                   return(TRUE);
                  }
              }
            else
              {
               char *aux,
                    buffer_aux[10];
               if (flagtipo == 2)
                  {
                   aux = buffer_aux;
                   buffer_aux[0] = *campo->buffer_binario,
                   buffer_aux[1] = '\0';
                  }
                else
                  aux = campo->buffer_binario;

                if ((strlen(aux) || obrigatorio) &&
                     VIDEO_TELA_consiste_faixa(aux,
                     consiste->objetocons.faixa->faixa,
                     VIDEO_TELA_faixa_texto)                  
                    )
                   {
                    if (flagmens)
                        VIDEO_TELA_display_faixa(
                              consiste->objetocons.faixa->faixa);
                    return(TRUE);
                   }
              }
           break;

     case  VIDEO_TELA_VALKEY:
           /* FUNCAO RELACIONAL DO BANCO DE DADOS.*/

           retorno = FALSE;
           switch( flagtipo )
            {
              char *buffer;
              case TRUE:
                        if (valor_teste==0.00)
                           retorno=TRUE;
                         break;

              case FALSE:
                         buffer=campo->buffer_binario;
                         while( *buffer && *buffer ==' ' )
                            ++buffer;
                         retorno=!(*buffer);
                         break;

              case     2:
                         retorno= ( *campo->buffer_binario==' ' ||
                                    *campo->buffer_binario=='0' ||
                                    !(*campo->buffer_binario) );
                         break;
            }

           if (retorno)
              {
               VIDEO_inic_transp(consiste->objetocons.consdb->transpdados);
               break;
              }

           if (consiste->objetocons.consdb)
              {
               VIDEO_CAMPO_CONSISTENCIA *consiste_valkey;

               indice = consiste->objetocons.consdb->indice;

               if ((ret = CTREE_find(indice,
                                     consiste->objetocons.consdb->segchave,
                                     FIND_IGUAL, CT_LE_DADOS)) != FALSE)
                   {
                    VIDEO_inic_transp(consiste->objetocons.consdb->transpdados);

                    if (flagmens)
                        if (ret != 101)
                           {
                            char buffer[200];
                            sprintf(buffer,CTREE_MENS_mens_padrao_err,
                                           VIDEO_erro_validacao,
                                           (VIDEO_bufparamarq->bufdodas+CTREE_keyfil(indice))->reduzido,
                                           ret,isam_err);
                            VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_cons_validacao);
                           }
                         else
                           VIDEO_mostra_mens_erro(
                                  consiste->objetocons.consdb->mensagem->mensagem,TRUE);
                    return(TRUE);
                   }
                 else
                   {
                    if (consiste->objetocons.consdb->transpdados)
                        CTREE_cpydoda(consiste->objetocons.consdb->transpdados);

                    consiste_valkey = campo->consiste;

                    arquivo = CTREE_keyfil(indice);
                    tmpfil  = CTREE_tmpfil(arquivo);

                    while(consiste_valkey->tipocons)
                     {
                      if ((consiste_valkey->tipocons == VIDEO_TELA_CONS_POSICIONA_DB) &&
                          (CTREE_keyfil(consiste_valkey->objetocons.consdb->indice) ==
                           arquivo))
                          {
                           consiste_valkey->objetocons.consdb->posicao =
                           DATABASE_CurrentFileOffset(tmpfil);
                           break;
                          }
                      ++consiste_valkey;
                     }
                   }
               break;
              }

     case  VIDEO_TELA_DUPKEY:

           /* Consegue atual posicao no arquivo.*/

           if (consiste->objetocons.consdb)
              {
/*---------------------------------------------------------------------------
   Caso CTREE_MULT_USER Ativo Define Variavel Para Buffer Isam
---------------------------------------------------------------------------*/
#ifdef CTREE_MULTI_USER
               char *buffer_isam;
#endif
/*-------------------------------------------------------------------------*/
               // VD_gtxy(1,1); printf ("Consistiu...");getch();
               arquivo   = CTREE_keyfil(consiste->objetocons.consdb->indice);
			   tmpfil	 = CTREE_tmpfil(arquivo);
			   work_ifil = CTREE_ifilend(arquivo);

			   ATIVA_BUF_DADOS;
			   buffer_rec = CTREE_filbuf(arquivo);

/*---------------------------------------------------------------------------
   Caso CTREE_MULT_USER Ativo Aloca Memoria e Salva Buffer Isam
---------------------------------------------------------------------------*/
#ifdef CTREE_MULTI_USER
			   if (VIDEO_ALLOC_MEM(buffer_isam,work_ifil->dreclen) == VD_NULO)
				  {
				   VIDEO_mostra_mens_erro_alloc(ALOCACAO_BUFFER_ISAM);
				   return(TRUE);
				  }
			   VIDEO_movbloco(buffer_isam,buffer_rec+work_ifil->dreclen*2,
							  work_ifil->dreclen);
#endif
/*-------------------------------------------------------------------------*/

			   check_offset_file = DATABASE_CurrentFileOffset(tmpfil);
               if ((ret = CTREE_find(consiste->objetocons.consdb->indice,
                                     VD_NILL(VIDEO_SEG_CHAVE), FIND_IGUAL,
                                     CT_LE_EXTRA )) <= 0)
                   {
                    char  buffer[100];

                    if (!(*(consiste->objetocons.consdb->situacao)&VIDEO_TELA_STATUS)
                        && !ret && (*(consiste->objetocons.consdb->situacao+1) > 1))
                       {
                        unsigned long atual_offset_file;

                        atual_offset_file = DATABASE_CurrentFileOffset(tmpfil);

                        if (DATABASE_CmpFileOffset(atual_offset_file,
                                                   check_offset_file))
                           {
                            DATABASE_FreeCurrentFileOffset(atual_offset_file);
/*---------------------------------------------------------------------------
   Caso CTREE_MULT_USER Ativo Restaura Buffer Isam
---------------------------------------------------------------------------*/
#ifdef CTREE_MULTI_USER
							VIDEO_movbloco(buffer_rec+work_ifil->dreclen*2,buffer_isam,
										   work_ifil->dreclen);
							VIDEO_FREE_ALLOC_MEM(buffer_isam);
#endif
                            break;
                           }
                        DATABASE_FreeCurrentFileOffset(atual_offset_file);
                       }

                    if (flagmens)
                       {
                        if (ret < 0)
                           {
                            char buffer[200];
                            sprintf(buffer,CTREE_MENS_mens_padrao_err,
                                           VIDEO_erro_dupkey,
                                           (VIDEO_bufparamarq->bufdodas+arquivo)->reduzido,
                                           ret,isam_err);
                            VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_cons_dupkey);
                           }
                         else
                           {
                            VIDEO_NUCLEO_SERV *nucleo;
                            /* Vers„o Anterior
                            VIDEO_mostra_mens_erro(consiste->objetocons.consdb->mensagem->mensagem,TRUE);
                             */
                            strcpy (buffer,consiste->objetocons.consdb->mensagem->mensagem);
                            nucleo = *param;
                            if (nucleo->VIDEO_servrec != I(VD_MTTECLA(VD_NULO,ALT_S)))
                               {
                                strcat (buffer," Carregar?");
                                if (VD_telaconf((80-strlen(buffer))/2,
                                                 10,
                                                 buffer,
                                                 VIDEO_COR_EXC_REGISTRO) == 1)
                                   {
                                    // Aten‡„o: Altera‡„o Realizada (FOR€A ALT_B)

                                    nucleo->VIDEO_servrec = I(VD_MTTECLA(VD_NULO,ALT_B));
                                    nucleo->VIDEO_repdisp = TRUE;
                                    // return (TRUE); -> Se Retornar, Desalocar
                                    // Fim de Altera‡„o
                                   }
                                }
                              else
                                {
                                 VIDEO_mostra_mens_erro(consiste->objetocons.consdb->mensagem->mensagem,TRUE);
                                }
                           }
                       }

                    // VD_gtxy(1,1); printf ("Passou   ...");getch();

                    CTREE_cpybuf(arquivo,FALSE);
                    if (check_offset_file)
                        if ((ret = DATABASE_SetRecord(tmpfil,check_offset_file,
                                  buffer_rec,work_ifil->dreclen)) != FALSE)
                           {
                            if (flagmens)
                               {
                                char buffer[100];
                                sprintf(buffer,CTREE_MENS_mens_padrao_err,
                                               VIDEO_erro_ret_pos_dupkey,
                                               (VIDEO_bufparamarq->bufdodas+arquivo)->reduzido,
                                               ret,isam_err);
                                VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_cons_ret_dupkey);
                               }
                            DATABASE_FreeCurrentFileOffset(check_offset_file);
                            CTREE_cpybuf(arquivo,TRUE);
/*---------------------------------------------------------------------------
   Caso CTREE_MULT_USER Ativo Restaura Buffer Isam
---------------------------------------------------------------------------*/
#ifdef CTREE_MULTI_USER
							VIDEO_movbloco(buffer_rec+work_ifil->dreclen*2,buffer_isam,
										   work_ifil->dreclen);
							VIDEO_FREE_ALLOC_MEM(buffer_isam);
#endif
/*-------------------------------------------------------------------------*/
                            return(TRUE);
                           }
                         else
                           DATABASE_ReReadRecord(tmpfil,buffer_rec);

                    CTREE_cpybuf(arquivo,TRUE);
                    DATABASE_FreeCurrentFileOffset(check_offset_file);

/*---------------------------------------------------------------------------
   Caso CTREE_MULT_USER Ativo Restaura Buffer Isam
---------------------------------------------------------------------------*/
#ifdef CTREE_MULTI_USER
					VIDEO_movbloco(buffer_rec+work_ifil->dreclen*2,buffer_isam,
								   work_ifil->dreclen);
					VIDEO_FREE_ALLOC_MEM(buffer_isam);
#endif
/*-------------------------------------------------------------------------*/
                    return(TRUE);
                   }
/*---------------------------------------------------------------------------
   Caso CTREE_MULT_USER Ativo Restaura Buffer Isam
---------------------------------------------------------------------------*/
#ifdef CTREE_MULTI_USER
			   VIDEO_movbloco(buffer_rec+work_ifil->dreclen*2,buffer_isam,
							  work_ifil->dreclen);
			   VIDEO_FREE_ALLOC_MEM(buffer_isam);
#endif
/*-------------------------------------------------------------------------*/
              }
          break;

     case VIDEO_TELA_CONS_POSICIONA_DB:
     case VIDEO_TELA_CONS_BUSCA_DB:
     case VIDEO_TELA_CONS_MANUT:
          break;

     case VIDEO_TELA_CONS_USER_FUNC:
          if (consiste->objetocons.user_cons)
             {
              VIDEO_TABFUNCAO *tabfuncuser;

              if ((tabfuncuser = VIDEO_funcao_tabfuncuser(consiste->objetocons.user_cons))
                 != VD_NILL(VIDEO_TABFUNCAO) && tabfuncuser->userfunc)
                 {
                  if ((*tabfuncuser->userfunc)(campos,flagmens,param))
                      return(TRUE);
                    else
                      break;
                 }
               else
                 if (flagmens)
                    {
                     char buffer[200];
                     sprintf(buffer,VIDEO_funcao_nao_enc,
                                    consiste->objetocons.user_cons);
                     VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_funcao_consistencia);
                    }
             }
          break;

     case VIDEO_TELA_CONS_INUSADO:break;

     case VIDEO_TELA_CONS_OLD_BUFFER:break;

     default : VIDEO_mostra_mens_erro(VIDEO_erro_tipo_consistencia,
									  VIDEO_ERRO_tipo_consistencia_invalido);
	}
   ++consiste;
  }while(consiste->tipocons);

 if (param)
    {
     if ((*param)->VIDEO_servrec != VD_MTTECLA(VD_NULO,ALT_S))
        {
         VIDEO_TELA_campo_posterior(PTR_CAST(BYTE far *,campos),param);
         VIDEO_TELA_chama_data_base_adm(campos,param);
         return(TRUE);
        }
     return(FALSE);
    }
   else
     return(FALSE);
}










