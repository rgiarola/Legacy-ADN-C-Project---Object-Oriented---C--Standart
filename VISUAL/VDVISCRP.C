#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_carrega_pagina(visual,sentido)
VIDEO_VISUAL_CONTROLE *visual;
int                   sentido;
{
 int      cont,tam,ret;
 char     *buffer,*linha;
 long int posicao,lido;

 posicao = visual->pos_ini;

 if (sentido > 0)
    {
     if ((visual->pos_ini = visual->pos_ini - visual->numlin) < 0)
        {
         visual->pos_ini = 0;
        }
    }
  else
    if (sentido == 0)
        if ((visual->pos_ini = visual->pos_ini + visual->numlin) > visual->lido)
           {
            if ((visual->pos_ini = visual->lido - visual->numlin) < 0)
                visual->pos_ini = 0;
           }
         else
           if (visual->pos_ini == visual->lido && visual->numlin == visual->lido)
               visual->pos_ini = 0;


 VIDEO_VISUAL_flag_erro = FALSE;
 VIDEO_VISUAL_flag_int  = FALSE;
 VIDEO_lseek(visual->descindex,visual->pos_ini*sizeof(DWORD),VIDEO_INI_ARQ);

 if (VIDEO_VISUAL_flag_erro)
    {
     char bufaux[100];
     visual->pos_ini = posicao;
     sprintf(bufaux,VIDEO_VISUAL_mens_erro_visual,visual->nomevisual);
     VIDEO_mostra_mens_erro(bufaux,TRUE);
     VIDEO_VISUAL_flag_erro = FALSE;
     VIDEO_VISUAL_flag_int  = TRUE;
     return(TRUE);
    }

 linha = visual->linhaaux;
 VIDEO_setmem(linha,4096,C(10));

 for (lido = cont = 0;cont <= visual->numlin;cont++)
     {
      if (VIDEO_read(visual->descindex,&posicao,sizeof(DWORD)) &&
          !VIDEO_VISUAL_flag_erro)
         {
          visual->linha[cont] = linha;
          VIDEO_lseek(visual->desc,posicao,VIDEO_INI_ARQ);
          if (VIDEO_VISUAL_flag_erro)
             {
              char bufaux[100];
              sprintf(bufaux,VIDEO_VISUAL_mens_erro_visual,visual->nomevisual);
              VIDEO_mostra_mens_erro(bufaux,TRUE);
              VIDEO_VISUAL_flag_erro = FALSE;
              VIDEO_VISUAL_flag_int  = TRUE;
              return(TRUE);
             }

          ret = VIDEO_read(visual->desc,linha,VIDEO_VISUAL_MAX_COL);

          if (VIDEO_VISUAL_flag_erro)
             {
              char bufaux[100];
              sprintf(bufaux,VIDEO_VISUAL_mens_erro_visual,visual->nomevisual);
              VIDEO_mostra_mens_erro(bufaux,TRUE);
              VIDEO_VISUAL_flag_erro = FALSE;
              VIDEO_VISUAL_flag_int  = TRUE;
              return(TRUE);
             }

          if (ret)
             {
              if ((buffer = strchr(linha,C(13))) == VD_NULO)
                 if ((buffer = strchr(linha,(10))) == VD_NULO)
                    {
                     visual->linha[cont] = VD_NULO;
                     continue;
                    }
              *(buffer) = 0;
              lido += (strlen(linha)+1);
              linha = visual->linhaaux + lido;
             }
         }
       else
         visual->linha[cont] = VD_NULO;
     }

 return(FALSE);
}




