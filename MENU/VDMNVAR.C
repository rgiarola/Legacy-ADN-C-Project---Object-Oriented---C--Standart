#include <INCVIDEO.H>

/**************************************************************************
       FLAG DE HABILITACAO PARA MOVER E ATRIBUTO DO MENU para o editor
**************************************************************************/
//#define MOVER_ATRIBUTO



#ifdef VIDEO_DOS
INT2 VIDEO_MENU_seleciona_mouse(VIDEO_INFO_MENU   **campos,
                               VIDEO_NUCLEO_SERV **param);
#endif

INT2 VIDEO_MENU_opcao_anterior[]  = {VD_MTTECLA(VD_NULO,SOBE),VIDEO_NULO},

    VIDEO_MENU_opcao_posterior[] = {VD_MTTECLA(VD_NULO,DESCE),VIDEO_NULO},

    VIDEO_MENU_opcao_calculad[] = {VD_MTTECLA(VD_NULO,F4),VIDEO_NULO},

    VIDEO_MENU_opcao_direita[]   = {VD_MTTECLA(VD_NULO,CTRL_DIR),
                                    VD_MTTECLA(VD_NULO,TABSCAN),
                                    VD_MTTECLA(VD_TAB ,TABSCAN),
                                    VD_MTTECLA(VD_NULO,DIREITA),VIDEO_NULO},

    VIDEO_MENU_opcao_esquerda[]  = {VD_MTTECLA(VD_NULO,CTRL_ESQ),
                                    VD_MTTECLA(VD_NULO,ESQUERDA),VIDEO_NULO},

    VIDEO_MENU_opcao_primeira[]  = {VD_MTTECLA(VD_NULO,HOME), VIDEO_NULO},

    VIDEO_MENU_opcao_ultima[]    = {VD_MTTECLA(VD_NULO,END) , VIDEO_NULO},

    VIDEO_MENU_opcao_inicio[]    = {VD_MTTECLA(VD_NULO,CTRL_HOME),
                                    VD_MTTECLA(VD_NULO,CTRL_PGUP),VIDEO_NULO},

    VIDEO_MENU_opcao_fim[]       = {VD_MTTECLA(VD_NULO,CTRL_END),
                                    VD_MTTECLA(VD_NULO,CTRL_PGDN),VIDEO_NULO},

    VIDEO_MENU_opcao_seleciona[] = {VD_MTTECLA(ENTER,ENTERSCAN),
                                    VD_MTTECLA(CTRL_ENT,ENTERSCAN),
                                    VD_MTTECLA(ENTER,ALT_M),VIDEO_NULO},

    VIDEO_MENU_opcao_aborta[]    = {VD_MTTECLA(ESCAPE,ESCAPESCAN),
                                    VD_MTTECLA(VD_NULO,ESCAPESCAN),
                                    VIDEO_NULO},

/**************************************************************************
                 HABILITA MOVER E ATRIBUTO para o editor
**************************************************************************/
#ifdef MOVER_ATRIBUTO
    VIDEO_MENU_opcao_mover[]     = {VD_MTTECLA(VD_NULO,ALT_L),
                                    VD_MTTECLA(12,ALT_L),VIDEO_NULO},

    VIDEO_MENU_opcao_atributos[] = {VD_MTTECLA(VD_NULO,ALT_A)   ,
                                    VD_MTTECLA(1,ALT_A),VIDEO_NULO},
#endif

    VIDEO_MENU_opcao_pagpos[]    = {VD_MTTECLA(VD_NULO,PGDN),VIDEO_NULO},

    VIDEO_MENU_opcao_selec_letra[] = {VD_MTTECLA(LETRA_MENU,LETRA_MENU),VIDEO_NULO},

    VIDEO_MENU_opcao_pagant[]    = {VD_MTTECLA(VD_NULO,PGUP),VIDEO_NULO},

    VIDEO_MENU_tabserv_help[] =      {VD_MTTECLA(VD_NULO,F1),
#ifdef VIDEO_DOS
                                      VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTTRV),
#endif
                                      VD_NULO}

#ifdef VIDEO_DOS
                                      ,

    VIDEO_MENU_tabserv_mouse[] = {VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTCLICK),
                                  VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTCLICK),
                                  VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTTRV),
                                                  VD_NULO}
#endif
                                                  ;

/*****************************************************************************/

VIDEO_TABSERV VIDEO_MENU_tabela_de_servicos[] = {
{VIDEO_MENU_opcao_anterior ,VIDEO_MENU_seleciona_anterior },
{VIDEO_MENU_opcao_posterior,VIDEO_MENU_seleciona_posterior},
{VIDEO_MENU_opcao_direita  ,VIDEO_MENU_seleciona_direita  },
{VIDEO_MENU_opcao_esquerda ,VIDEO_MENU_seleciona_esquerda },
{VIDEO_MENU_opcao_primeira ,VIDEO_MENU_seleciona_primeira },
{VIDEO_MENU_opcao_inicio   ,VIDEO_MENU_seleciona_inicio   },
{VIDEO_MENU_opcao_fim      ,VIDEO_MENU_seleciona_fim      },
{VIDEO_MENU_opcao_ultima   ,VIDEO_MENU_seleciona_ultima   },
{VIDEO_MENU_opcao_pagpos   ,VIDEO_MENU_seleciona_pagpos   },
{VIDEO_MENU_opcao_pagant   ,VIDEO_MENU_seleciona_pagant   },
{VIDEO_MENU_opcao_aborta   ,VIDEO_MENU_seleciona_aborta   },
{VIDEO_MENU_opcao_seleciona,VIDEO_MENU_seleciona_opcao    },

/**************************************************************************
                 HABILITA MOVER E ATRIBUTO para o editor
**************************************************************************/
#ifdef MOVER_ATRIBUTO
{VIDEO_MENU_opcao_mover    ,VIDEO_MENU_seleciona_mover    },
{VIDEO_MENU_opcao_atributos,VIDEO_MENU_seleciona_atributos},
#endif

{VIDEO_MENU_tabserv_help   ,VIDEO_MENU_seleciona_help     },
#ifdef VIDEO_DOS
{VIDEO_MENU_tabserv_mouse  ,VIDEO_MENU_seleciona_mouse    },
#endif
{VIDEO_MENU_opcao_calculad ,VIDEO_CALC_dispara            },
{VIDEO_MENU_opcao_selec_letra,VIDEO_MENU_seleciona_letra  },
{VIDEO_VISUAL_tabserv_spool, VIDEO_VISUAL_dispara_spool   },
{VIDEO_NULO                ,VIDEO_NULO                    }};


#ifdef VIDEO_DOS
INT2 VIDEO_MENU_seleciona_mouse(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 VIDEO_INFO_MENU *work;
 INT2             servrec,lin,col,
                 numop,numpag,aux;

 work = *campos;

 servrec = FALSE;

 if (VIDEO_MOUSE_coluna_atual < (work->coli-1))
    servrec = VD_MTTECLA(VD_NULO,ESQUERDA);

 if (!servrec && VIDEO_MOUSE_coluna_atual > (work->coli+(work->numpag+1)*work->tamcol-1))
    servrec = VD_MTTECLA(VD_NULO,DIREITA);

 if (!servrec && VIDEO_MOUSE_linha_atual == (work->lini - 1))
    {
     col = work->coli+(work->numpag+1)*work->tamcol - 1;

     if ((aux = col-work->coli+1) > 4)
        {
         col -= (4+(aux>5));
         if ((VIDEO_MOUSE_coluna_atual >= col) &&
             (VIDEO_MOUSE_coluna_atual <= (col + 4)))
             servrec = VD_MTTECLA(ESCAPE,ESCAPESCAN);
        }
      else
        {
         col -= (2+(aux>3));
         if ((VIDEO_MOUSE_coluna_atual >= col) &&
             (VIDEO_MOUSE_coluna_atual <= (col+2)))
             servrec = VD_MTTECLA(ESCAPE,ESCAPESCAN);
        }
    }

 if (!servrec && VIDEO_MOUSE_linha_atual < work->lini)
    servrec = VD_MTTECLA(VD_NULO,SOBE);

 if (!servrec && VIDEO_MOUSE_linha_atual > work->linf)
    servrec = VD_MTTECLA(VD_NULO,DESCE);


 if (servrec)
    {
     (*param)->VIDEO_repdisp = TRUE;
     (*param)->VIDEO_servrec = servrec;
     return(TRUE);
    }

/*
 VD_gtxy(1,10);
 printf("work->numpag %6d\nwork->colpag %6d\n"
        "work->colatu %6d\nwork->numlin %6d\n"
        "work->opsel  %6d\nwork->lin    %6d\n"
        "work->col    %6d\nwork->opini  %6d\n"
        "                                    ",work->numpag,work->colpag,
                                               work->colatu,work->numlin,
                                               work->opsel ,work->lin,
                                               work->col   ,work->opini);
 getch();
*/

 if ((VIDEO_MOUSE_linha_atual == work->lin) &&
     (VIDEO_MOUSE_coluna_atual >= work->col) &&
     (VIDEO_MOUSE_coluna_atual <= (work->col+work->tamcol-1)))
     {
      if (W((*param)->VIDEO_servrec) == VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTCLICK) ||
          W((*param)->VIDEO_servrec) == VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTCLICK))
         {
          (*param)->VIDEO_repdisp = TRUE;
          (*param)->VIDEO_servrec = VD_MTTECLA(ENTER ,ENTERSCAN);
         }
      return(TRUE);
     }

 for (numpag = 0,col = work->coli;numpag <= work->numpag;numpag++)
      if ((VIDEO_MOUSE_coluna_atual >= (col+(numpag*work->tamcol))) &&
          (VIDEO_MOUSE_coluna_atual <= (col+((numpag+1)*work->tamcol)-1)))
         {
          numop = numpag*work->numlin + (VIDEO_MOUSE_linha_atual-work->lini);
/*
          VD_gtxy(1,1);
          printf("work->numpag %6d\nwork->colpag %6d\n"
                 "work->colatu %6d\nwork->numlin %6d\n"
                 "work->opsel  %6d\nwork->lin    %6d\n"
                 "work->col    %6d\nwork->opini  %6d\n"
                 "numpag       %6d\numop         %6d\n"
                 "work->numop  %6d"                    ,work->numpag,work->colpag,
                                                        work->colatu,work->numlin,
                                                        work->opsel ,work->lin   ,
                                                        work->col   ,work->opini ,
                                                        numpag      ,numop,
                                                        work->numop);
          getch();
*/

          if ((work->opini + numop) >= work->numop)
             {
              (*param)->VIDEO_repdisp = TRUE;
              (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,CTRL_PGDN);
              break;
             }

          VIDEO_setatrib(work->col,work->col+work->tamdispop-1,
                         work->lin,work->lin,work->cor_opcao);

          work->opsel = work->opini + numop;

          work->colpag  = numpag;
          work->colatu += (numpag-work->numpag);

          work->lin = VIDEO_MOUSE_linha_atual;
          work->col = col+(numpag*work->tamcol);

/*
          VD_gtxy(1,10);
          printf("work->numpag %6d\nwork->colpag %6d\n"
                 "work->colatu %6d\nwork->numlin %6d\n"
                 "work->opsel  %6d\nwork->lin    %6d\n"
                 "work->col    %6d\nwork->opini  %6d\n"
                 "numop        %6d\nwork->numop  %6d"  ,work->numpag,work->colpag,
                                                        work->colatu,work->numlin,
                                                        work->opsel ,work->lin,
                                                        work->col   ,work->opini,
                                                        numop,work->numop);
          getch();
*/

          if (W((*param)->VIDEO_servrec) == VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTCLICK) ||
			  W((*param)->VIDEO_servrec) == VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTCLICK))
             {
              (*param)->VIDEO_repdisp = TRUE;
              (*param)->VIDEO_servrec = VD_MTTECLA(ENTER ,ENTERSCAN);
              break;
             }

          work->flagdispop = TRUE;
          break;
         }

 return(TRUE);
}
#endif
