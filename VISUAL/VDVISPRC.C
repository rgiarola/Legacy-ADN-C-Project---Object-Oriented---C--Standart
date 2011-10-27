#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_procura_arquivo(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV     **param;
{
 VIDEO_VISUAL_CONTROLE *ctrlvisual;
 char                  nomevisual[61],
                       titulo[80];
 int                   desc,descaux,col;
 BOOLEAN               flagerro;
 DWORD                 tamanho;

 ctrlvisual = *visual;

 if (!ctrlvisual->linhaaux)
    return(TRUE);

/************************************************************************
                            LIBERA DESCRITOR DO CTREE
 ************************************************************************/
 vtclose();
 vtclose();
 vtclose();

/************************************************************************
                         SETA BARRA DE STATUS DA TELA
 ************************************************************************/
 VD_PUSHWIN(ctrlvisual->coli,ctrlvisual->colf,ctrlvisual->linf+4,ctrlvisual->linf+4);
 VIDEO_CLEAR_PIC(ctrlvisual->coli,ctrlvisual->colf-15,ctrlvisual->linf+4,ctrlvisual->linf+4,
                 VD_FORMATO(VD_VERMELHO,VD_INTER,VD_BLANK,VD_BRIL));
 VD_tprt_l(ctrlvisual->coli+2,ctrlvisual->linf+4,VIDEO_VISUAL_modo_pesquisa,0);

/************************************************************************
                              LOOP DE SELECAO
 ************************************************************************/
 flagerro = FALSE;
 do
  {
   VIDEO_VISUAL_flag_erro = FALSE;
   VIDEO_VISUAL_flag_int  = TRUE;

   if (!VISUAL_menu_arquivos(nomevisual)) //SELECIONA ARQUIVO PARA VISUALIZACAO
      {
       if (!flagerro)
           VD_POPWIN();

       if (flagerro || ctrlvisual->desc < 0)
          {
           (*param)->VIDEO_servrec = VD_MTTECLA(ESCAPE,ESCAPESCAN);
           (*param)->VIDEO_repdisp = TRUE;
           VIDEO_VISUAL_flag_erro = FALSE;
           VIDEO_VISUAL_flag_int  = TRUE;
          }

       return(TRUE);
      }

   VIDEO_VISUAL_flag_erro = FALSE;
   VIDEO_VISUAL_flag_int  = FALSE;
   if ((desc = VIDEO_open_io(nomevisual)) <= 0 || // ABRE ARQUIVO SELECINADO
        VIDEO_VISUAL_flag_erro)
      {
       char bufaux[100];
       sprintf(bufaux,VIDEO_VISUAL_mens_arquivo_visual,nomevisual);
       VIDEO_mostra_mens_erro(bufaux,TRUE);
       VIDEO_VISUAL_flag_erro = FALSE;
       VIDEO_VISUAL_flag_int  = TRUE;
       continue;
      }

   if (VIDEO_lockfile(desc,0L,VIDEO_filelength(desc)) < 0 || // lock em arquivo
      VIDEO_VISUAL_flag_erro)
      {
       char bufaux[100];
       sprintf(bufaux,VIDEO_VISUAL_mens_arquivo_visual,nomevisual);
       VIDEO_mostra_mens_erro(bufaux,TRUE);
       VIDEO_VISUAL_flag_erro = FALSE;
       VIDEO_VISUAL_flag_int  = TRUE;
       close(desc);
       continue;
      }


/************************************************************************
                            LIBERA ARQUIVO ANTERIOR
 ************************************************************************/
   if (!flagerro)
       VD_POPWIN();


   strcpy(titulo,ctrlvisual->titulo);
   strcat(titulo,nomevisual);
   strcat(titulo," ");
   strcpy(VD_GETEND(BDISP_texto3,char),VIDEO_VISUAL_modo_visual);
   VIDEO_CRG_display_imagem(ctrlvisual->telavisual,1,1);
   VIDEO_setatrib(ctrlvisual->coli-1,ctrlvisual->colf,
                  ctrlvisual->linf+4,ctrlvisual->linf+4,
                  VD_FORMATO(VD_VERMELHO,VD_NORMAL,VD_BLANK,VD_BRIL));
   VIDEO_setatrib(ctrlvisual->coli-1,ctrlvisual->colf-15,
                  ctrlvisual->linf+4,ctrlvisual->linf+4,
                  VD_FORMATO(VD_VERMELHO,VD_INTER,VD_BLANK,VD_BRIL));

   if (!flagerro && ctrlvisual->desc > 0)
      {
       if (VIDEO_unlockfile(ctrlvisual->desc,0L,VIDEO_filelength(ctrlvisual->desc)) < 0)
          {
           char buffer[150];
           sprintf(buffer,VIDEO_VISUAL_mens_erro_visual,ctrlvisual->nomevisual);
           VIDEO_mostra_mens_erro(buffer,TRUE);
          }

       VIDEO_close(ctrlvisual->desc);
      }

   flagerro = TRUE;

/************************************************************************
                            PREPARA NOVO ARQUIVO
 ************************************************************************/
   ctrlvisual->desc = desc;

   col = ((ctrlvisual->colf-ctrlvisual->coli+1) - strlen(titulo))/2;
   if (col < 0)
      {
       titulo[(ctrlvisual->colf-ctrlvisual->coli)] = 0;
       col = 0;
      }
   col += ctrlvisual->coli;

   VD_tprt_l(col,ctrlvisual->linf+2,titulo,0);

   ctrlvisual->pos_ini = 0;

   ctrlvisual->lintela = ctrlvisual->lini;
   ctrlvisual->refcol  = ctrlvisual->linvisual = 0;
   ctrlvisual->pos_ini  = ctrlvisual->lido = 0;

   VIDEO_VISUAL_flag_erro = FALSE;
   VIDEO_VISUAL_flag_int  = TRUE;
/************************************************************************
                                 INDEXA TEXTO
 ************************************************************************/
   if (!VIDEO_VISAO_indexa_texto(ctrlvisual))
      {
       char buffer[150];
       sprintf(buffer,VIDEO_VISUAL_mens_erro_visual,nomevisual);
       VIDEO_mostra_mens_erro(buffer,TRUE);
       close(desc);
	   ctrlvisual->desc = -1;
       continue;
      }

   ctrlvisual->pos_ini = 0;
   VIDEO_VISUAL_flag_erro = FALSE;
   VIDEO_VISUAL_flag_int  = TRUE;
/************************************************************************
                           CARREGA PRIMEIRA PAGINA
 ************************************************************************/
   if (VIDEO_VISUAL_carrega_pagina(ctrlvisual,-1))
      {
       char buffer[150];
       sprintf(buffer,VIDEO_VISUAL_mens_erro_visual,nomevisual);
       VIDEO_mostra_mens_erro(buffer,TRUE);
       close(desc);
	   ctrlvisual->desc = -1;
       continue;
      }

   strcpy(ctrlvisual->nomevisual,nomevisual);
   break;

  }while(TRUE);
 VD_POPATR();
 VD_POPATR();

 ctrlvisual->flags |= (VIDEO_VISUAL_DISPLAY_PROMPT|
                       VIDEO_VISUAL_DISPLAY_PAGINA);

 VIDEO_VISUAL_flag_erro = FALSE;
 VIDEO_VISUAL_flag_int  = TRUE;
 return(TRUE);
}


