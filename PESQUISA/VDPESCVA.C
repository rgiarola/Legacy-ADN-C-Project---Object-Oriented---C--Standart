#include <INCVIDEO.H>

INT2 VIDEO_PESQUISA_seleciona_proxima(VIDEO_PESQUISA_PLANILHA **telapesq,
                                     VIDEO_NUCLEO_SERV       **param);

INT2 VIDEO_PESQUISA_seleciona_anterior(VIDEO_PESQUISA_PLANILHA **telapesq,
                                      VIDEO_NUCLEO_SERV       **param);

INT2 VIDEO_PESQUISA_seleciona_pesquisa(VIDEO_PESQUISA_PLANILHA **telapesq,
                                      VIDEO_NUCLEO_SERV       **param,
                                      INT2                     posicao);

INT2 VIDEO_PESQUISA_mouse_posiciona(VIDEO_PESQUISA_PLANILHA **telapesq,
                                   VIDEO_NUCLEO_SERV       **param);

INT2 VIDEO_PESQUISA_mouse_help(VIDEO_PESQUISA_PLANILHA **telapesq,
                              VIDEO_NUCLEO_SERV       **param);

INT2 VIDEO_PESQUISA_seleciona(VIDEO_PESQUISA_PLANILHA **telapesq,
                             VIDEO_NUCLEO_SERV       **param);

INT2 VIDEO_PESQUISA_tabserv_LINPOS[] = {VD_MTTECLA(VD_NULO,TABSCAN),
                                        VD_MTTECLA(VD_TAB ,TABSCAN),
                                        VD_MTTECLA(VD_NULO,CTRL_DIR),
                                        VD_MTTECLA(VD_NULO,DIREITA),
                                        VD_MTTECLA(VD_NULO,DESCE),VD_NULO},

    VIDEO_PESQUISA_tabserv_LINANT[] = {VD_MTTECLA(VD_NULO,CTRL_ESQ),
                                       VD_MTTECLA(VD_NULO,ESQUERDA),
                                       VD_MTTECLA(VD_NULO,SOBE),VD_NULO},

    VIDEO_PESQUISA_tabserv_PAGPOS[] = {VD_MTTECLA(VD_NULO,PGDN),
                                       VD_MTTECLA(VD_NULO,ALT_D),VD_NULO},

    VIDEO_PESQUISA_tabserv_PAGANT[] = {VD_MTTECLA(VD_NULO,PGUP),
                                       VD_MTTECLA(VD_NULO,ALT_U),VD_NULO},

    VIDEO_PESQUISA_tabserv_ULT[] = {VD_MTTECLA(VD_NULO,CTRL_PGDN),
                                    VD_MTTECLA(VD_NULO,ALT_L),VD_NULO},

    VIDEO_PESQUISA_tabserv_PRI[] = {VD_MTTECLA(VD_NULO,CTRL_PGUP),
                                    VD_MTTECLA(VD_NULO,ALT_P),VD_NULO},

    VIDEO_PESQUISA_tabserv_TER[] = {VD_MTTECLA(VD_NULO,ESCAPESCAN),
                                    VD_MTTECLA(ESCAPE ,ESCAPESCAN),VD_NULO},

    VIDEO_PESQUISA_tabserv_selec_reg[] = {VD_MTTECLA(ENTER ,ENTERSCAN),
                                          VD_MTTECLA(10    ,ENTERSCAN),VD_NULO},

    VIDEO_PESQUISA_tabserv_MANUT[] = {VD_MTTECLA(VD_NULO,ALT_M),
                                      VD_NULO},

    VIDEO_PESQUISA_tabserv_seleciona[] = {VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTCLICK),
                                          VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTCLICK),
                                          VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTTRV),
                                                    VD_NULO},

    VIDEO_PESQUISA_tabserv_help[] =      {VD_MTTECLA(VD_NULO,F1),
                                          VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTTRV),
                                          VD_NULO};

    VIDEO_PESQUISA_tabserv_proxima[] = {VD_MTTECLA(VD_NULO,F6),
                                        VD_MTTECLA(VD_NULO,ALT_MAIS),
                                        VD_NULO};

    VIDEO_PESQUISA_tabserv_calculad[] =      {VD_MTTECLA(VD_NULO,F4),VD_NULO},

    VIDEO_PESQUISA_tabserv_anterior[] = {VD_MTTECLA(VD_NULO,F5),
                                         VD_MTTECLA(VD_NULO,ALT_MENOS),
                                                    VD_NULO};

VIDEO_TABSERV VIDEO_PESQUISA_tabserv_navegacao[] = {
{   VIDEO_PESQUISA_tabserv_LINPOS   , VIDEO_PESQUISA_linha_posterior     },
{   VIDEO_PESQUISA_tabserv_LINANT   , VIDEO_PESQUISA_linha_anterior      },
{   VIDEO_PESQUISA_tabserv_PAGPOS   , VIDEO_PESQUISA_pagina_posterior    },
{   VIDEO_PESQUISA_tabserv_PAGANT   , VIDEO_PESQUISA_pagina_anterior     },
{   VIDEO_PESQUISA_tabserv_ULT      , VIDEO_PESQUISA_ultimo_registro     },
{   VIDEO_PESQUISA_tabserv_PRI      , VIDEO_PESQUISA_primeiro_registro   },
{   VIDEO_PESQUISA_tabserv_TER      , VIDEO_PESQUISA_termina             },
{   VIDEO_PESQUISA_tabserv_MANUT    , VIDEO_PESQUISA_manutencao          },
{   VIDEO_PESQUISA_tabserv_seleciona, VIDEO_PESQUISA_seleciona           },
{   VIDEO_PESQUISA_tabserv_help     , VIDEO_PESQUISA_mouse_help          },
{   VIDEO_PESQUISA_tabserv_proxima  , VIDEO_PESQUISA_seleciona_proxima   },
{   VIDEO_PESQUISA_tabserv_anterior , VIDEO_PESQUISA_seleciona_anterior  },
{   VIDEO_PESQUISA_tabserv_selec_reg, VIDEO_PESQUISA_seleciona_registro  },
{   VIDEO_PESQUISA_tabserv_calculad , VIDEO_CALC_dispara                 },
{   VIDEO_PESQUISA_tabserv_userserv , VIDEO_PESQUISA_dispara_userserv    },
{   VIDEO_VISUAL_tabserv_spool      , VIDEO_VISUAL_dispara_spool         },
{   VD_NULO                         , VD_NULO                            }};


INT2 VIDEO_PESQUISA_mouse_posiciona(telapesq,param)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
{
 VIDEO_TELA_ENTRADA_DADOS *telacampos;
 VIDEO_IMAGEMTELA         *imagem;
 INT2                      servrec;

 servrec = FALSE;

 telacampos = PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,(*telapesq)->tela->tela);
 imagem     = telacampos->imagens;

 if (VIDEO_MOUSE_linha_atual == imagem->linf)
    {
     if ((VIDEO_MOUSE_coluna_atual >= imagem->coli)   &&
         (VIDEO_MOUSE_coluna_atual <= (imagem->coli+3)))
          servrec = VD_MTTECLA(VD_NULO,PGUP);

     if ((VIDEO_MOUSE_coluna_atual >= (imagem->coli+5)) &&
         (VIDEO_MOUSE_coluna_atual <= (imagem->coli+8)))
          servrec = VD_MTTECLA(VD_NULO,PGDN);

     if ((VIDEO_MOUSE_coluna_atual >= (imagem->coli+10)) &&
         (VIDEO_MOUSE_coluna_atual <= (imagem->coli+17)))
          servrec = VD_MTTECLA(VD_NULO,CTRL_PGUP);

     if ((VIDEO_MOUSE_coluna_atual >= (imagem->coli+19)) &&
         (VIDEO_MOUSE_coluna_atual <= (imagem->coli+24)))
          servrec = VD_MTTECLA(VD_NULO,CTRL_PGDN);

     if ((*telapesq)->flagplanilha&VIDEO_PESQUISA_MANUTENCAO)
        {
         if ((VIDEO_MOUSE_coluna_atual >= (imagem->colf-9)) &&
             (VIDEO_MOUSE_coluna_atual <= imagem->colf))
             servrec = VD_MTTECLA(VD_NULO,ALT_M);
        }
    }

 if (VIDEO_MOUSE_linha_atual == imagem->lini)
     if ((VIDEO_MOUSE_coluna_atual >= (imagem->colf-5))     &&
         (VIDEO_MOUSE_coluna_atual <= (imagem->colf-1)))
           servrec = VIDEO_MTTECLA(ESCAPE,ESCAPESCAN);

 if (servrec)
    {
     (*param)->VIDEO_servrec = servrec;
     (*param)->VIDEO_repdisp = TRUE;
    }

 return(TRUE);
}

INT2 VIDEO_PESQUISA_mouse_help(telapesq,param)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
{
 VIDEO_PESQUISA_PLANILHA *pesquisa;
 VIDEO_IMAGEMTELA        *imagem;

 pesquisa = *telapesq;

 if (pesquisa->nomehelp)
    {
     imagem = PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,pesquisa->tela->tela)->imagens;

     VD_PUSHWIN(imagem->colf-7,imagem->colf,imagem->lini,imagem->lini);
     VD_PUSHWIN(imagem->coli,imagem->colf,imagem->linf,imagem->linf);
     VIDEO_TELA_desativa_status(imagem);
     VIDEO_VISUAL_dispara_visual(pesquisa->nomehelp,VD_NULO,TRUE,
                                 &VIDEO_HELP_imagem_padrao,
                                 VIDEO_VISUAL_menu,FALSE);
     VD_POPWIN();
     VD_POPWIN();
    }
 return(TRUE);
}

INT2 VIDEO_PESQUISA_seleciona_proxima(telapesq,param)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
{
 VIDEO_PESQUISA_seleciona_pesquisa(telapesq,param,TRUE);
 return(TRUE);
}

INT2 VIDEO_PESQUISA_seleciona_anterior(telapesq,param)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
{
 VIDEO_PESQUISA_seleciona_pesquisa(telapesq,param,FALSE);
 return(TRUE);
}

INT2 VIDEO_PESQUISA_seleciona_pesquisa(telapesq,param,posicao)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
INT2                     posicao;
{
 VIDEO_PESQUISA_PLANILHA *pesquisa;
 VIDEO_NUCLEO_SERV       *nucleo;
 IDE_ARQUIVOS            *workifil;
 INT2                     arquivo,ret,
                         tmpfil;
 char                    *buffer;

 pesquisa = *telapesq;
 nucleo   = *param;

 if (posicao)
    {
     if ((nucleo->VIDEO_inicial+1) >= nucleo->VIDEO_numcampos)
        return(TRUE);
    }
  else
     if (!nucleo->VIDEO_inicial)
        return(TRUE);

 ATIVA_BUF_DADOS;
 arquivo  = CTREE_keyfil(CTREE_keynm(pesquisa->nomeindice));
 tmpfil   = CTREE_tmpfil(arquivo);
 workifil = CTREE_ifilend(arquivo);
 buffer   = CTREE_filbuf(arquivo);

 if (VIDEO_ALLOC_MEM(pesquisa->buffer_pesq,workifil->dreclen) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_PESQUISA_VAR);
     return(TRUE);
    }

 pesquisa->numrecpesq = CurrentFileOffset(tmpfil);
 VIDEO_movbloco(pesquisa->buffer_pesq,buffer,workifil->dreclen);

 VIDEO_TELA_desativa_status(PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,
                                     pesquisa->tela->tela)->imagens);
 VIDEO_CRG_libera_tela(pesquisa->tela);
 pesquisa = posicao ? ++*telapesq : --*telapesq;

 ATIVA_BUF_DADOS;
 arquivo  = CTREE_keyfil(CTREE_keynm(pesquisa->nomeindice));
 workifil = CTREE_ifilend(arquivo);
 buffer   = CTREE_filbuf(arquivo);
 tmpfil   = CTREE_tmpfil(arquivo);

 if (pesquisa->numrecpesq > 0)
    {
     VIDEO_movbloco(buffer,pesquisa->buffer_pesq,workifil->dreclen);
     if ((ret = SetRecord(tmpfil,pesquisa->numrecpesq,
                              buffer,workifil->dreclen)) != 0)
        {
         char   buffer[200];
         sprintf(buffer,CTREE_MENS_mens_padrao_err,
                        VIDEO_PESQ_mens_troca_pesq,
                        (VIDEO_bufparamarq->bufdodas+arquivo)->reduzido,
                        ret,isam_err);
         VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_posic_planilha_errado);
         pesquisa->flagplanilha |=  VIDEO_PESQUISA_DISPCURSOR |
                                    VIDEO_PESQUISA_DISPCAMPOS;
        }
    }

 if (pesquisa->buffer_pesq)
    {
     VIDEO_movbloco(buffer,pesquisa->buffer_pesq,workifil->dreclen);
     VIDEO_FREE_ALLOC_MEM(pesquisa->buffer_pesq);
    }

 pesquisa->buffer_pesq = VD_NULO;
 pesquisa->numrecpesq  = VD_NULO;

 nucleo->VIDEO_inicial = posicao                 ?
                         ++nucleo->VIDEO_inicial :
                         --nucleo->VIDEO_inicial ;

 pesquisa->flagplanilha |=  (VIDEO_PESQUISA_DISPCURSOR |
                             VIDEO_PESQUISA_DISPIMAGEM |
                             VIDEO_PESQUISA_DISPCAMPOS);

 if (posicao)
    pesquisa->flagplanilha |= VIDEO_PESQUISA_INICIALIZA;

 return(TRUE);
}

INT2 VIDEO_PESQUISA_seleciona(telapesq,param)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
{
 VIDEO_PESQUISA_PLANILHA *pesquisa;
 VIDEO_IMAGEMTELA        *imagem;
 INT2                     servrec,
                         cont,ret;
 servrec = FALSE;

 VIDEO_PESQUISA_mouse_posiciona(telapesq,param);

 if ((*param)->VIDEO_repdisp)
    return(TRUE);

 pesquisa = *telapesq;

 imagem = PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,pesquisa->tela->tela)->imagens;

 if (VIDEO_MOUSE_linha_atual < (imagem->lini+3))
    servrec = VD_MTTECLA(VD_NULO,SOBE);

 if (VIDEO_MOUSE_linha_atual > (imagem->linf-2))
    servrec = VD_MTTECLA(VD_NULO,DESCE);

 if (VIDEO_MOUSE_linha_atual == (imagem->linf-1))
    {
     if (((imagem->colf-6) == VIDEO_MOUSE_coluna_atual) ||
         ((imagem->colf-5) == VIDEO_MOUSE_coluna_atual))
         servrec = VD_MTTECLA(VD_NULO,ALT_MENOS);

     if (((imagem->colf-3) == VIDEO_MOUSE_coluna_atual) ||
         ((imagem->colf-2) == VIDEO_MOUSE_coluna_atual))
         servrec = VD_MTTECLA(VD_NULO,ALT_MAIS);
    }

 if (!servrec)
    if (VIDEO_MOUSE_linha_atual == pesquisa->linatual)
       {
        if (W((*param)->VIDEO_servrec) == VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTCLICK))
           servrec = VD_MTTECLA(ENTER ,ENTERSCAN);
       }
     else
       {
        VIDEO_TELA_ENTRADA_DADOS *telacampos;
        VIDEO_IMAGEMTELA         *imagem;
        VIDEO_CAMPO_TELA         *linhacampos,
                                 *campos;
        INT2                      contcampo,linha;

        telacampos = PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,pesquisa->tela->tela);
        imagem   = telacampos->imagens;

        pesquisa->flagplanilha |= VIDEO_PESQUISA_DISPCURSOR;

        linha = pesquisa->linatual;

        if (VIDEO_MOUSE_linha_atual > pesquisa->linatual)
           {
            for (cont = VIDEO_MOUSE_linha_atual - pesquisa->linatual;
                       cont;cont--,pesquisa->linatual++)
                 if ((ret = CTREE_find(pesquisa->indice,pesquisa->segchave,
                                   FIND_PROXIMO,CT_LE_EXTRA_REPASSA)) != 0)
                    {
                     char   buffer[200];
                     sprintf(buffer,CTREE_MENS_mens_padrao_err,
                                    VIDEO_PESQ_mens_fim_arquivo,
                                    (VIDEO_bufparamarq->bufdodas+CTREE_keyfil(pesquisa->indice))->reduzido,
                                    ret,isam_err);
                     VIDEO_mostra_mens_erro(buffer,
                                            ret != 101 && ret != 100   ?
                                            VIDEO_ERRO_fim_arq_planilha:
                                            TRUE                       );
                     servrec = VD_MTTECLA(VD_NULO,CTRL_PGUP);
                     break;
                    }

            linhacampos = PTR_CAST(VIDEO_CAMPO_TELA,
                                   imagem->campos->VIDEO_campos);
            for (campos = linhacampos,contcampo = 0;
                 contcampo < imagem->campos->VIDEO_numcampos;
                                             contcampo++,campos++)
                 campos->lin = pesquisa->linatual;
           }
         else
           {
            for (cont = pesquisa->linatual - VIDEO_MOUSE_linha_atual;
                       cont;cont--,pesquisa->linatual--)
                 if ((ret = CTREE_find(pesquisa->indice,pesquisa->segchave,
                                   FIND_ANTERIOR,CT_LE_EXTRA_REPASSA)) != 0)
                    {
                     char buffer[200];
                     sprintf(buffer,CTREE_MENS_mens_padrao_err,
                                    VIDEO_PESQ_mens_ini_arquivo,
                                    (VIDEO_bufparamarq->bufdodas+CTREE_keyfil(pesquisa->indice))->reduzido,
                                    ret,isam_err);
                     VIDEO_mostra_mens_erro(buffer,
                                            ret != 101 && ret != 100   ?
                                            VIDEO_ERRO_fim_arq_planilha:
                                            TRUE                       );
                     servrec = VD_MTTECLA(VD_NULO,CTRL_PGDN);
                     break;
                    }
            linhacampos = PTR_CAST(VIDEO_CAMPO_TELA,
                                   imagem->campos->VIDEO_campos);
            for (campos = linhacampos,contcampo = 0;
                 contcampo < imagem->campos->VIDEO_numcampos;
                                             contcampo++,campos++)
                 campos->lin = pesquisa->linatual;
           }

        VD_setatrib(imagem->coli+1,imagem->colf-1,
                    linha,linha,
                    PTR_CAST(VIDEO_CAMPO_TELA,
                    imagem->campos->VIDEO_campos)->saida);
       }

 if (servrec)
    {
     (*param)->VIDEO_servrec = servrec;
     (*param)->VIDEO_repdisp = TRUE;
    }

 return(TRUE);
}

