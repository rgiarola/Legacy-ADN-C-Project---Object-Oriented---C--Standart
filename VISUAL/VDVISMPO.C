#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_mouse_posiciona(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV   **param;
{
 VIDEO_VISUAL_CONTROLE *ctrlvisual;
 INT2                 repdisp,
                     servrec,
                     offlin;
 ctrlvisual = *visual;

 repdisp = servrec = FALSE;

 if (VIDEO_MOUSE_linha_atual == (ctrlvisual->linf+1))
     if (VIDEO_MOUSE_coluna_atual == ctrlvisual->colf)
         servrec = VD_MTTECLA(VD_TAB ,TABSCAN);
      else
        if (VIDEO_MOUSE_coluna_atual == ctrlvisual->coli)
            servrec = VD_MTTECLA(VD_NULO,TABSCAN);

 if (VIDEO_MOUSE_coluna_atual == (ctrlvisual->colf+1))
    if (VIDEO_MOUSE_linha_atual == ctrlvisual->lini)
        servrec = VD_MTTECLA(VD_NULO,PGUP);
      else
        if (VIDEO_MOUSE_linha_atual == ctrlvisual->linf)
            servrec = VD_MTTECLA(VD_NULO,PGDN);

 if (servrec)
    {
     (*param)->VIDEO_repdisp = TRUE;
     (*param)->VIDEO_servrec = servrec;
     return(TRUE);
    }


 if (VIDEO_MOUSE_linha_atual == (ctrlvisual->linf+2))
    {
     if ((VIDEO_MOUSE_coluna_atual >= ctrlvisual->coli)   &&
         (VIDEO_MOUSE_coluna_atual <= (ctrlvisual->coli+3)))
         {
          repdisp = TRUE;
          servrec = VD_MTTECLA(VD_NULO,PGUP);
         }

     if ((VIDEO_MOUSE_coluna_atual >= (ctrlvisual->coli+5)) &&
         (VIDEO_MOUSE_coluna_atual <= (ctrlvisual->coli+8)))
         {
          repdisp = TRUE;
          servrec = VD_MTTECLA(VD_NULO,PGDN);
         }

     if ((VIDEO_MOUSE_coluna_atual >= (ctrlvisual->coli+10)) &&
         (VIDEO_MOUSE_coluna_atual <= (ctrlvisual->coli+17)))
         {
          repdisp = TRUE;
          servrec = VD_MTTECLA(VD_NULO,CTRL_PGUP);
         }

     if ((VIDEO_MOUSE_coluna_atual >= (ctrlvisual->coli+19)) &&
         (VIDEO_MOUSE_coluna_atual <= (ctrlvisual->coli+24)))
         {
          repdisp = TRUE;
          servrec = VD_MTTECLA(VD_NULO,CTRL_PGDN);
         }

     if ((VIDEO_MOUSE_coluna_atual >= (ctrlvisual->colf-8))     &&
         (VIDEO_MOUSE_coluna_atual <= (ctrlvisual->colf-1)))
         {
          repdisp = TRUE;
		  servrec = VD_MTTECLA(VD_NULO,ALT_O);
         }

     if (!repdisp)
        {
         repdisp = TRUE;
         servrec = VD_MTTECLA(VD_NULO,CTRL_DIR);
        }
    }

 if (VIDEO_MOUSE_linha_atual == (ctrlvisual->lini-1))
     if ((VIDEO_MOUSE_coluna_atual >= (ctrlvisual->colf-5))     &&
         (VIDEO_MOUSE_coluna_atual <= (ctrlvisual->colf-1)))
          {
           servrec = VIDEO_MTTECLA(ESCAPE,ESCAPESCAN);
           repdisp = TRUE;
          }
        else
          {
           repdisp = TRUE;
           servrec = VD_MTTECLA(VD_NULO,SOBE);
          }

 if (!repdisp && VIDEO_MOUSE_linha_atual < ctrlvisual->lini)
    {
     repdisp = TRUE;
     servrec = VD_MTTECLA(VD_NULO,SOBE);
    }

 if (!repdisp && VIDEO_MOUSE_linha_atual > ctrlvisual->linf)
    {
     repdisp = TRUE;
     servrec = VD_MTTECLA(VD_NULO,DESCE);
    }

 if ((VIDEO_MOUSE_linha_atual  >= ctrlvisual->lini) &&
     (VIDEO_MOUSE_linha_atual  <= ctrlvisual->linf) &&
     (VIDEO_MOUSE_coluna_atual <= ctrlvisual->colf) &&
     (VIDEO_MOUSE_coluna_atual >= ctrlvisual->coli))
     if (ctrlvisual->lintela != VIDEO_MOUSE_linha_atual)
        {
         if (((offlin = VIDEO_MOUSE_linha_atual - ctrlvisual->lintela) > 0) &&
             ((ctrlvisual->linvisual+offlin) >= ctrlvisual->numlin))
             return(TRUE);

         ctrlvisual->linvisual += offlin;
         ctrlvisual->lintela = VIDEO_MOUSE_linha_atual;
         ctrlvisual->flags  |= VIDEO_VISUAL_RESSET_PROMPT;
        }

 if (!repdisp && VIDEO_MOUSE_coluna_atual < ctrlvisual->coli)
    {
     repdisp = TRUE;
     servrec = VD_MTTECLA(VD_NULO,CTRL_ESQ);
    }

 if (!repdisp && VIDEO_MOUSE_coluna_atual > ctrlvisual->colf)
    {
     repdisp = TRUE;
     servrec = VD_MTTECLA(VD_NULO,CTRL_DIR);
    }

 (*param)->VIDEO_repdisp = repdisp;
 (*param)->VIDEO_servrec = servrec;

 return(TRUE);
}


INT2 VIDEO_VISUAL_opcoes(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV     **param;
{
 if ((*visual)->visual_opcoes)
     return((*visual)->visual_opcoes(visual,param));
 return(TRUE);
}


INT2 VIDEO_VISUAL_menu(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV     **param;
{
 static BYTE    contvisual = 0;
 char           nomevisual[31],
                numvisual[2];
 INT2           ret,flag1,flag2,flag3;

 flag1 = flag2 = flag3 = TRUE;
 if (!contvisual)
    {
     ++contvisual;
     numvisual[1] = '\0';
	 if (VIDEO_CRG_carrega_objeto(&VIDEO_HELP_menu_padrao,2))
        {
		 VIDEO_CRG_prepara_menu(&VIDEO_HELP_menu_padrao);
         do
          {
		   if ((ret = VIDEO_CRG_dispara_menu(&VIDEO_HELP_menu_padrao,
                                        flag1,flag2,flag3)) > 0)
              {
               int tam;

               numvisual[0] = '0' + ret;
               strcpy(nomevisual,VIDEO_padrao_projeto);
               tam = strlen(nomevisual);
               nomevisual[tam] = '\\';
               nomevisual[tam+1] = '\0';

               strcat(nomevisual,VIDEO_padrao_sistema);
               tam = strlen(nomevisual);
               nomevisual[tam] = '\\';
               nomevisual[tam+1] = '\0';

               strcat(nomevisual,numvisual);
               VIDEO_VISUAL_dispara_visual(nomevisual,VD_NULO,TRUE,
                                           &VIDEO_HELP_imagem_padrao,
                                           VIDEO_VISUAL_menu,FALSE);
              }
            else
              break;

           flag1 = flag3 = FALSE;
           flag2 = TRUE;

          }while(TRUE);
         VD_POPWIN();
        }
	 VIDEO_CRG_libera_tela(&VIDEO_HELP_menu_padrao);
     --contvisual;
    }
 return(TRUE);
}
