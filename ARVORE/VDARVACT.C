#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_accept_arvore()
 *----------------------------------------------------------------------------
 * Descricao      :  funcao chamada pelo nucleo para startup da arvore e
 *                   geracao dos servicos de controle
 * Parametros     :  arvore  estrutura controladora da arvore
 * Retorno        :  servico gerado a partir do teclado
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_accept_arvore(arvore,param)
VIDEO_ARVORE_ESTRUTURA *arvore;
VIDEO_NUCLEO_SERV      *param;
{
 BYTE ascii,scan;

 VIDEO_tcursor(0X20,0X20);

 if (arvore->flagremontarvore)
    {
     VIDEO_ARVORE_desmonta_arvore(arvore);
     arvore->flagremontarvore = FALSE;
     arvore->flagdispprompt   =
     arvore->flagdisparvore   =
     arvore->flagmontarvore   = TRUE;
    }

 param->VIDEO_servrec = FALSE;

 if (arvore->flagmontarvore)
    {
#ifdef VIDEO_UNIX
     VIDEO_UNIX_flag_video = VD_NULO;
     VIDEO_UNIX_inicializa_tela();
#endif
     if (!VIDEO_ARVORE_monta_arvore(arvore))
        {
         VIDEO_ARVORE_desmonta_arvore(arvore);
         VIDEO_mostra_mens_erro(VIDEO_ARVORE_erro_montagem,
                                VIDEO_ERRO_monta_arvore);
         return(FALSE);
        }
     arvore->flagmontarvore = FALSE;
    }

 VIDEO_mensagem_default.lin = (arvore->linf-1 == (arvore->lini+arvore->lini_offset)) ?
                              arvore->linf : arvore->linf-1;
 VIDEO_mensagem_default.col = arvore->coli+arvore->coli_offset;

 if (arvore->flagdispmoldura)
    {
     if (arvore->flagsalva&VIDEO_ARVORE_FLAGPUSHWIN)
        {
         VD_PUSHWIN(arvore->coli,arvore->colf,arvore->lini,arvore->linf);
         arvore->flagsalva &= ~VIDEO_ARVORE_FLAGPUSHWIN;
        }

     VD_quadro(arvore->coli,arvore->colf,arvore->lini,arvore->linf,
			   arvore->cararv,arvore->cor_fundo);

     VD_vertical(arvore->lini+1,arvore->linf-3,arvore->colf,
                 arvore->carbar,arvore->cor_barras);
     VD_horizontal(arvore->coli,arvore->colf,arvore->linf-2,
                   arvore->carbar,arvore->cor_barras);

     VD_plotcarac(arvore->colf,arvore->lini+1,
                  VIDEO_SCROLL_SETACIMA,arvore->cor_setas);
     VD_plotcarac(arvore->colf,arvore->linf-2,
                  VIDEO_SCROLL_SETABAIXO,arvore->cor_setas);
     VD_plotcarac(arvore->colf-1,arvore->linf-2,
                  VIDEO_SCROLL_SETADIR,arvore->cor_setas);
	 VD_plotcarac(arvore->coli,arvore->linf-2,
                  VIDEO_SCROLL_SETAESQ,arvore->cor_setas);

     // T¡tulo da Arvore
     if (!(arvore->flagarvore&VIDEO_ARVDES_TITULO) &&
         arvore->titulo)
        {
         INT2 tamanho,
              posicao;

         VD_horizontal(arvore->coli,arvore->colf,arvore->lini,
                      VIDEO_ARVORE_espaco_branco,arvore->cor_titulo);
         /*
         VD_tprt_l(arvore->coli,arvore->lini,arvore->titulo,
                   arvore->cor_titulo);
          */
         tamanho = strlen (arvore->titulo);
         posicao = arvore->coli+((arvore->colf-arvore->coli)/2)-(tamanho/2);
         VD_tprt_l(posicao,arvore->lini,arvore->titulo,
                   arvore->cor_titulo);

        }


     // Rodap‚ da Arvore
     /*
     if (!(arvore->flagarvore&VIDEO_ARVDES_RODAPE))
        {
         VD_horizontal(arvore->coli,arvore->colf,arvore->linf,
                      VIDEO_ARVORE_espaco_branco,arvore->cor_rodape);
         VD_tprt_l(arvore->coli,arvore->linf,arvore->rodape,
                   arvore->cor_rodape);
        }
      */

     arvore->flagdispmoldura = FALSE;

     arvore->linha_initela = arvore->linha_atual = arvore->linha_inicial;
     arvore->elemento      = arvore->linha_atual->elemento;

     arvore->flagsalva |= VIDEO_ARVORE_FLAGSTATUS;
    }

 if (arvore->flagsalva&VIDEO_ARVORE_FLAGSTATUS)
    {
     VD_tprt_l(arvore->colf-5,arvore->lini,VIDEO_ARVORE_botton_termina,
                                           arvore->cor_titulo);
     VD_plotcarac(arvore->colf-3,arvore->lini,
                  VIDEO_ARVORE_caracter_termina,
              VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_MARROM,VD_BRIL));
     arvore->flagsalva &= ~VIDEO_ARVORE_FLAGSTATUS;
    }

 if (arvore->flagdisparvore)
    {
     VD_quadro(arvore->coli,arvore->colf-1,arvore->lini+1,arvore->linf-3,
			   arvore->cararv,arvore->cor_fundo);
     VIDEO_ARVORE_display_arvore(arvore);
     arvore->flagdisparvore = FALSE;
    }

 if (arvore->flagdisplinha)
    {
     VIDEO_ARVORE_display_linha(arvore);
     arvore->flagdisplinha = FALSE;
    }

 if (arvore->flagdispprompt)
    {
     INT2 lindisp,
         coldisp;
     coldisp = arvore->elemento->coluna - arvore->coli_arvore + arvore->coli+arvore->coli_offset;
     lindisp = arvore->linha_atual->linha - arvore->lini_arvore +
               arvore->lini+arvore->lini_offset;
     VD_setatrib(coldisp,coldisp+arvore->elemento->tamanho-1,lindisp,lindisp,
                         arvore->cor_selelem);
     arvore->flagdispprompt = FALSE;
     VIDEO_ARVORE_display_scrowbar(arvore);
    }

 if (arvore->flagfuncao&VIDEO_ARVORE_FUNCANT && arvore->userfunc)
    {
     if ( !(*(arvore)->userfunc)(&arvore,VIDEO_ARVORE_FUNCANT,&param))
        {
         param->VIDEO_repdisp = TRUE;
         param->VIDEO_servrec = VIDEO_MTTECLA(ESCAPE,ESCAPESCAN);
         return(TRUE);
        }
    }

#ifdef VIDEO_DOS
 VIDEO_MOUSE_flagtravado = TRUE;

 if (VIDEO_MOUSE_ativo)
    {
     VIDEO_MOUSE_habcursor();
     VIDEO_MOUSE_timetrav = 10;
    }
#endif

#ifdef VIDEO_UNIX
     VIDEO_UNIX_refresh_tela();
#endif

 VD_getkbd(&arvore->ascii,&arvore->scan);

#ifdef VIDEO_DOS
 if (VIDEO_MOUSE_ativo)
    if ((arvore->scan != VIDEO_MOUSE_BOTCLICK) && (arvore->scan != VIDEO_MOUSE_BOTTRV))
       VIDEO_MOUSE_deshabcursor();

 VIDEO_MOUSE_flagtravado = FALSE;
#endif

 param->VIDEO_servrec = VIDEO_MTTECLA(arvore->ascii,arvore->scan);

 if (arvore->flagfuncao&VIDEO_ARVORE_FUNCPOS && arvore->userfunc )
    {
     if ( !(*(arvore)->userfunc)(&arvore,VIDEO_ARVORE_FUNCPOS,&param) )
        {
         param->VIDEO_repdisp = TRUE;
         param->VIDEO_servrec = VIDEO_MTTECLA(ESCAPE,ESCAPESCAN);
         return(TRUE);
        }
    }

 param->VIDEO_servrec = VIDEO_MTTECLA(arvore->ascii,arvore->scan);

 return(TRUE);
}

