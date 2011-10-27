#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_accept_visual(visual,param)
VIDEO_VISUAL_CONTROLE *visual;
VIDEO_NUCLEO_SERV   *param;
{
 INT2  linivisual,
      linitela,
      offlin;
 BYTE ascii,scan;

 VD_tcursor(0X20,0X20);

 param->VIDEO_servrec = FALSE;

 if (visual->flags&VIDEO_VISUAL_PEGA_LINHA_ANT)
    {
     visual->flags &= ~VIDEO_VISUAL_PEGA_LINHA_ANT;
     if (VIDEO_VISUAL_carrega_pagina(visual,-1))
        {
         param->VIDEO_servrec = VD_MTTECLA(ESCAPE,ESCAPESCAN);
         param->VIDEO_repdisp = TRUE;
         VD_PUSHATR(1,1,1,1);
         VD_PUSHATR(1,1,1,1);
         return(TRUE);
        }
    }

 if (visual->flags&VIDEO_VISUAL_PEGA_LINHA_POS)
    {
     visual->flags &= ~VIDEO_VISUAL_PEGA_LINHA_POS;
     if (VIDEO_VISUAL_carrega_pagina(visual,-1))
        {
         param->VIDEO_servrec = VD_MTTECLA(ESCAPE,ESCAPESCAN);
         param->VIDEO_repdisp = TRUE;
         VD_PUSHATR(1,1,1,1);
         VD_PUSHATR(1,1,1,1);
         return(TRUE);
        }
    }

 if (visual->flags&VIDEO_VISUAL_PEGA_PAG_ANT)
    {
     visual->flags &= ~VIDEO_VISUAL_PEGA_PAG_ANT;
     if (VIDEO_VISUAL_carrega_pagina(visual,TRUE))
        {
         param->VIDEO_servrec = VD_MTTECLA(ESCAPE,ESCAPESCAN);
         param->VIDEO_repdisp = TRUE;
         VD_PUSHATR(1,1,1,1);
         VD_PUSHATR(1,1,1,1);
         return(TRUE);
        }
    }

 if (visual->flags&VIDEO_VISUAL_PEGA_PAG_POS)
    {
     int cont,chamada;
     visual->flags &= ~VIDEO_VISUAL_PEGA_PAG_POS;
     chamada = 0;

     do
      {
       if (VIDEO_VISUAL_carrega_pagina(visual,FALSE))
          {
           param->VIDEO_servrec = VD_MTTECLA(ESCAPE,ESCAPESCAN);
           param->VIDEO_repdisp = TRUE;
           VD_PUSHATR(1,1,1,1);
           VD_PUSHATR(1,1,1,1);
           return(TRUE);
          }

       for (cont = 0;cont < visual->numlin;cont++)
            if (!visual->linha[cont] && visual->lido > visual->numlin)
                break;

      }while((cont < visual->numlin) && ++chamada < 2);
    }

 if (visual->flags&VIDEO_VISUAL_SALVA_FUNDO)
    {
     visual->flags &= ~VIDEO_VISUAL_SALVA_FUNDO;
     VD_PUSHWIN(visual->coli,visual->colf,
                visual->lini,visual->linf);
    }

 if (visual->flags&VIDEO_VISUAL_DISPLAY_PAGINA)
    {
     visual->flags &= ~VIDEO_VISUAL_DISPLAY_PAGINA;
     VD_POPWIN();

     VD_PUSHWIN(visual->coli,visual->colf,
                visual->lini,visual->linf);

     VD_PUSHATR(visual->coli,visual->colf,
                visual->lini,visual->linf);

     offlin = visual->lintela - visual->lini;
     for (linivisual = visual->linvisual - offlin,
          linitela = visual->lintela - offlin;
                     (linitela <= visual->linf) &&
                     (linivisual <  visual->numlin);
                                  linitela++,linivisual++)
         {
          if (strlen(visual->linha[linivisual]) > visual->refcol)
             {
              char *linha;
              int  tamanho;
              tamanho = visual->colf-visual->coli+2;

              if (VIDEO_ALLOC_MEM(linha,tamanho) == VD_NULO)
                 {
                  VIDEO_mostra_mens_erro_alloc(ALOCACAO_VISUALACT_1);
                 }
               else
                 {
                  VD_movbloco(linha,visual->linha[linivisual]+visual->refcol,tamanho-1);
                  linha[tamanho-1] = 0;
                  VIDEO_setmem(&linha[strlen(linha)],tamanho-1-strlen(linha),' ');
                  VD_tprt_l(visual->coli,linitela,linha,0);
                  VIDEO_FREE_ALLOC_MEM(linha);
                 }
             }
         }
    }

 if (visual->flags&VIDEO_VISUAL_DISPLAY_LINHA)
    {
     visual->flags &= ~VIDEO_VISUAL_DISPLAY_LINHA;

     VD_PUSHATR(visual->coli,visual->colf,
                 visual->lintela,visual->lintela);

     VIDEO_CLEAR_PIC(visual->coli,visual->colf,
                 visual->lintela,visual->lintela,7);

     if (strlen(visual->linha[visual->linvisual]) > visual->refcol)
        {
         char *linha;
         int  tamanho;

         tamanho = visual->colf-visual->coli+2;

         if (VIDEO_ALLOC_MEM(linha,tamanho) == VD_NULO)
            {
             VIDEO_mostra_mens_erro_alloc(ALOCACAO_VISUALACT_2);
            }
          else
            {
             VD_movbloco(linha,visual->linha[visual->linvisual]+visual->refcol,tamanho-1);
             linha[tamanho-1] = 0;
             VIDEO_setmem(&linha[strlen(linha)],tamanho-1-strlen(linha),' ');
             VD_tprt_l(visual->coli,visual->lintela,linha,0);
             VIDEO_FREE_ALLOC_MEM(linha);
            }
        }

     VD_POPATR();
    }

 if (visual->flags&VIDEO_VISUAL_RESSET_PROMPT)
    {
     VD_POPATR();
     visual->flags &= ~VIDEO_VISUAL_RESSET_PROMPT;
     visual->flags |= VIDEO_VISUAL_DISPLAY_PROMPT;
    }

 offlin = visual->lintela - visual->lini;
 for (linivisual = visual->linvisual - offlin,
      linitela = visual->lintela - offlin;
                 (linitela <= visual->linf) &&
                 (linivisual <  visual->numlin);
                              linitela++,linivisual++)
     {
      char *lin;
      int quebra;
      long int linatual;

      linatual = visual->pos_ini + linivisual+1;

      if ((quebra = linatual%L(VD_GETBUF(BREL_selec6,BYTE))) == 0)
         quebra = VD_GETBUF(BREL_selec6,BYTE);

      lin = visual->linha[linivisual];
      do
       {
        if (*lin == '' || (quebra == 1 && linatual > 1))
           {
            VD_setatrib(visual->coli,visual->colf,
                             linitela,linitela,
                             VD_FORMATO(VD_BLANK,VD_NORMAL,VD_PRETO,VD_BRIL));
            if ((linitela == visual->lintela) &&
                !(visual->flags&VIDEO_VISUAL_DISPLAY_PROMPT))
                VD_setatrib(visual->coli,visual->colf,linitela,linitela,
                            VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));

            break;
           }
        if (!*lin)
            break;
        ++lin;
       }while(TRUE);
     }

 if (visual->flags&VIDEO_VISUAL_DISPLAY_PROMPT)
    {
     visual->flags &= ~VIDEO_VISUAL_DISPLAY_PROMPT;

     VD_PUSHATR(visual->coli,visual->colf,
                 visual->lintela,visual->lintela);

     VD_setatrib(visual->coli,visual->colf,
                 visual->lintela,visual->lintela,VD_FORMATO(VD_VERMELHO,VD_NORMAL,
                                                        VD_BLANK,VD_BRIL));
    }

 if (visual->linhaaux)
     VIDEO_VISUAL_mostra_linha_scrow(visual);

#ifdef VIDEO_DOS
 if (VIDEO_MOUSE_ativo)
    {
     VIDEO_MOUSE_habcursor();
     VIDEO_MOUSE_flagtravado = TRUE;
     VIDEO_MOUSE_timetrav = 10;
    }
#endif

#ifdef VIDEO_UNIX
 VIDEO_UNIX_refresh_tela();
#endif


 VD_getkbd(&ascii,&scan);

#ifdef VIDEO_DOS
 if (VIDEO_MOUSE_ativo)
     VIDEO_MOUSE_deshabcursor();
#endif

 param->VIDEO_servrec = VIDEO_MTTECLA(ascii,scan);

 return(TRUE);
}

