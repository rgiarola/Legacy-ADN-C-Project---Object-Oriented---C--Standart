#include <INCVIDEO.H>

INT2 VIDEO_PESQUISA_accept_tela(pesquisa,param)
VIDEO_PESQUISA_PLANILHA *pesquisa;
VIDEO_NUCLEO_SERV       *param;
{
 VIDEO_TELA_ENTRADA_DADOS *telacampos;
 VIDEO_IMAGEMTELA         *imagem;
 BYTE                     ascii, scan;
 INT2                      ret;
 BOOLEAN                  flagvazio,
                          flagtela;
 VIDEO_TABFUNCAO          *tabfuncuser;

 flagvazio = FALSE;

 param->VIDEO_servrec = FALSE;

 pesquisa->flagplanilha |= VIDEO_PESQUISA_ATIVADA;
 if (!pesquisa->tela->tela)
    {
     if (!VIDEO_CRG_carrega_objeto(pesquisa->tela,1))
        {
         char buf[100];
                 sprintf(buf,VIDEO_PESQ_mens_accept_tela,
                                pesquisa->tela->sistcrg,
                                                                pesquisa->tela->telacrg,isam_err);
                 VIDEO_mostra_mens_erro(buf,VIDEO_ERRO_tela_plan_nao_encontrada);
         param->VIDEO_servrec = VD_MTTECLA(ESCAPE ,ESCAPESCAN);
         return(TRUE);
        }

     if (!VIDEO_CRG_prepara_tela(pesquisa->tela))
        {
         char buf[100];
         sprintf(buf,VIDEO_PESQ_mens_prep_tela,
                                pesquisa->tela->sistcrg,
                                pesquisa->tela->telacrg);
                 VIDEO_mostra_mens_erro(buf,VIDEO_ERRO_tela_plan_nao_encontrada);
         param->VIDEO_servrec = VD_MTTECLA(ESCAPE ,ESCAPESCAN);
         return(TRUE);
        }
    }

 telacampos = PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,pesquisa->tela->tela);
 imagem     = telacampos->imagens;

 /* Localiza User FUNCTION (Se Alguma).*/

 if (imagem->userfunc)
     tabfuncuser = VIDEO_funcao_tabfuncuser(imagem->userfunc);

 if (imagem->flagimagem&VIDEO_TELA_FDISPANT && imagem->userfunc)
         if (!tabfuncuser || !tabfuncuser->userfunc)
                {
                 char buffer[200];
                 sprintf(buffer,VIDEO_funcao_nao_enc,imagem->userfunc);
                 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_funcao_nao_encontrada);
                }
          else
        (tabfuncuser->userfunc)(&pesquisa,VIDEO_TELA_FDISPANT,&param);

 VIDEO_mensagem_default.lin = (imagem->linf-1 == imagem->lini) ?
                               imagem->linf : imagem->linf-1;
 VIDEO_mensagem_default.col = imagem->coli+1;

 /* Start Ponto para Iniciar a Busca.*/
 if (pesquisa->flagplanilha&VIDEO_PESQUISA_INICIALIZA)
    {
     VIDEO_SEG_CHAVE *segchave;
     char            *buffer;
     INT2             indice;

     ATIVA_BUF_DADOS;

     VD_tcursor(0x20,0X20);

     if (pesquisa->buffer_rec)
        {
         VIDEO_FREE_ALLOC_MEM(pesquisa->buffer_rec);
         pesquisa->buffer_rec = VD_NULO;
        }

     pesquisa->numrec = VD_NULO;

     indice    = CTREE_keynm(pesquisa->nomeindice);
     if ((ret=CTREE_find(indice,pesquisa->segchave,
                     FIND_MAIOR_IGUAL, CT_LE_EXTRA_REPASSA))!=FALSE)
        if (ret==101 || ret==100)
           {
            if ((ret = CTREE_find(indice,pesquisa->segchave,
                                   FIND_MENOR_IGUAL,CT_LE_EXTRA_REPASSA)) != 0)
                flagvazio = TRUE;
           }
         else
           flagvazio = TRUE;

     pesquisa->flagplanilha &= ~VIDEO_PESQUISA_INICIALIZA;
     pesquisa->flagplanilha |= VIDEO_PESQUISA_INICDISP;
    }

/* VD_tprt_l(1,3,"INICIALIZA",7);*/
 if (pesquisa->flagplanilha&VIDEO_PESQUISA_INICBUFFER)
    {
     IDE_ARQUIVOS     *arquivo;
     VIDEO_CAMPO_TELA *campo;
     INT2              cont;

     pesquisa->flagplanilha &= ~VIDEO_PESQUISA_INICBUFFER;
     campo = PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos);
     for (cont = 0;cont < imagem->campos->VIDEO_numcampos;cont++,campo++)
          campo->buffer_binario = CTREE_dodaend(campo->dodacampo)->fadr+
                                  campo->offsetbuffer;
    }

 if (pesquisa->flagplanilha&VIDEO_PESQUISA_SALVATELA)
    {
     pesquisa->flagplanilha |= VIDEO_PESQUISA_POPWIN;

     VD_PUSHWIN(imagem->coli,imagem->colf+(imagem->colf<80),
                imagem->lini,imagem->linf+(imagem->linf<25));
     pesquisa->flagplanilha &= ~VIDEO_PESQUISA_SALVATELA;
    }

/* VD_tprt_l(1,4,"SALVA TELA",7);*/

 if (pesquisa->flagplanilha&VIDEO_PESQUISA_DISPIMAGEM &&
     (!isam_err || isam_err==100 || isam_err==101)    )
    {
     pesquisa->flagplanilha &= ~VIDEO_PESQUISA_DISPIMAGEM;
     VIDEO_PESQUISA_display_imagem(pesquisa,param);
    }

/* VD_tprt_l(1,5,"DISP IMAGEM",7);*/

 if (flagvazio)
    {
     char buffer[200];

         sprintf(buffer,CTREE_MENS_mens_padrao_err,
                                        VIDEO_PESQ_mens_accept_arqvazio,
                                        (VIDEO_bufparamarq->bufdodas+
                    CTREE_keyfil(CTREE_keynm(pesquisa->nomeindice)))->reduzido,
                                        ret,isam_err);

     ret = VIDEO_mostra_mens_erro(buffer,
                                  ret != 101 && ret      != 100     ?
                                  VIDEO_ERRO_arquivo_planilha_vazio :
                                  TRUE                          );

     pesquisa->flagplanilha |= (VIDEO_PESQUISA_INICIALIZA|
                                VIDEO_PESQUISA_FLAGVAZIO);

     switch(ret)
      {
       case I(VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTCLICK)):
       case I(VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTCLICK)):
       case I(VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTTRV))  :
       case I(VD_MTTECLA(ENTER ,ENTERSCAN))    :
       case I(VD_MTTECLA(10    ,ENTERSCAN))    :
            ret = I(VD_MTTECLA(ESCAPE ,ESCAPESCAN));

       case I(VD_MTTECLA(ESCAPE ,ESCAPESCAN))  :
       case I(VD_MTTECLA(VD_NULO,ALT_M))       :
       case I(VD_MTTECLA(VD_NULO,F6))          :
       case I(VD_MTTECLA(VD_NULO,ALT_MAIS))    :
       case I(VD_MTTECLA(VD_NULO,F4))          :
       case I(VD_MTTECLA(VD_NULO,F1))          :
       case I(VD_MTTECLA(2,VIDEO_MOUSE_BOTTRV)):
       case I(VD_MTTECLA(VD_NULO,F5))          :
       case I(VD_MTTECLA(VD_NULO,ALT_MENOS))   :
            break;

       default:ret = I(VD_MTTECLA(ESCAPE ,ESCAPESCAN));
      }

     param->VIDEO_servrec = ret;

     return(FALSE);
    }

 if (pesquisa->flagplanilha&VIDEO_PESQUISA_DISPCAMPOS)
    {
     VIDEO_PESQUISA_display_imagem(pesquisa,param);
     VIDEO_PESQUISA_display_campos_posterior(pesquisa,param);
     pesquisa->flagplanilha &= ~VIDEO_PESQUISA_DISPCAMPOS;
    }

/* VD_tprt_l(1,6,"DISP CAMPOS",7);*/

 if (pesquisa->flagplanilha&VIDEO_PESQUISA_DISPLINHA)
    {
     VIDEO_TELA_display_campos(
              PTR_CAST(VIDEO_CAMPO_TELA,imagem->campos->VIDEO_campos),
              imagem->campos->VIDEO_numcampos,imagem->campos,
                                     VIDEO_FLAGVALIDA_CAMPO |
                                     VIDEO_FLAGUSER_CAMPO   |
                                     VIDEO_TELA_FLAGRESETDISPLAY);
     pesquisa->flagplanilha &= ~VIDEO_PESQUISA_DISPLINHA;
    }


/* VD_tprt_l(1,7,"DISP LINHA",7);*/

 if (pesquisa->flagplanilha&VIDEO_PESQUISA_DISPCURSOR)
    {
     VD_setatrib(imagem->coli+1,imagem->colf-1,
                 pesquisa->linatual,pesquisa->linatual,
     PTR_CAST(VIDEO_CAMPO_TELA,
              imagem->campos->VIDEO_campos)->entrada);
     pesquisa->flagplanilha &= ~VIDEO_PESQUISA_DISPCURSOR;
    }

/* VD_tprt_l(1,8,"DISP CURSOR",7);*/


#ifdef VIDEO_DOS
 if (VIDEO_MOUSE_ativo > 0)
    {
     VIDEO_MOUSE_habcursor();
     VIDEO_MOUSE_flagtravado = TRUE;
     VIDEO_MOUSE_timetrav = 10;
    }
#endif

#ifdef VIDEO_UNIX
 VIDEO_UNIX_refresh_tela();
#endif

 VIDEO_getkbd(&ascii,&scan);

#ifdef VIDEO_DOS
 if (VIDEO_MOUSE_ativo > 0)
     VIDEO_MOUSE_deshabcursor();
#endif

 param->VIDEO_servrec = VIDEO_MTTECLA(ascii,scan);

 if (imagem->flagimagem&VIDEO_TELA_FDISPPOS && imagem->userfunc)
         if (!tabfuncuser || !tabfuncuser->userfunc)
                {
                 char buffer[200];
                 sprintf(buffer,VIDEO_funcao_nao_enc,imagem->userfunc);
                 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_funcao_nao_encontrada);
                }
      else
        (tabfuncuser->userfunc)(&pesquisa,VIDEO_TELA_FDISPPOS,&param);

 switch(I(param->VIDEO_servrec))
  {
   case I(VD_MTTECLA(VD_NULO,F5)):
        param->VIDEO_servrec = VD_MTTECLA(VD_NULO,ALT_MENOS);
        break;

   case I(VD_MTTECLA(VD_NULO,F6)):
        param->VIDEO_servrec = VD_MTTECLA(VD_NULO,ALT_MAIS);
        break;
  }

 return(TRUE);
}

