#include <INCVIDEO.H>
/* ============================================================================
                   Visualizacao de HELP e Arquivo Texto
                                Lib Visual
                               Tech C 1994
   ============================================================================
                     APAGA ARQUIVO QUE ESTA SENDO VISUALIZADO
   ============================================================================ */

INT2 VIDEO_VISUAL_deleta_arquivo(visual,param)
VIDEO_VISUAL_CONTROLE **visual;
VIDEO_NUCLEO_SERV     **param;
{
 VIDEO_VISUAL_CONTROLE *ctrlvisual = *visual;
 int                   ret;

 if (ctrlvisual->linhaaux)
    {
     char buffer[100];
     sprintf(buffer,VIDEO_TELA_confirma_delecao,ctrlvisual->nomevisual);
     if (VD_telaconf((80-strlen(buffer))/2,10,
                     buffer,VIDEO_PADRAO_COR) == 1)
        {
         VIDEO_VISUAL_flag_erro = FALSE;
         VIDEO_VISUAL_flag_int  = FALSE;
		 if (ctrlvisual->desc > 0)
            {
             ret = VIDEO_unlockfile(ctrlvisual->desc,0L,VIDEO_filelength(ctrlvisual->desc));
             VIDEO_close(ctrlvisual->desc);
             VIDEO_unlink(ctrlvisual->nomevisual);
             if (ret || VIDEO_VISUAL_flag_erro)
                {
                 char buffer[150];
                 sprintf(buffer,VIDEO_VISUAL_erro_delecao,ctrlvisual->nomevisual);
                 VIDEO_mostra_mens_erro(buffer,TRUE);
                }
			 ctrlvisual->desc = -1;
            }

		 VIDEO_VISUAL_flag_int	= TRUE;
         VIDEO_VISUAL_flag_erro = FALSE;
		 strcpy(VD_GETEND(BDISP_texto3,char),VIDEO_VISUAL_modo_pesquisa);
		 VIDEO_CRG_display_imagem(ctrlvisual->telavisual,1,1);
         (*param)->VIDEO_repdisp = TRUE;
         (*param)->VIDEO_servrec = VD_MTTECLA(VD_NULO,F3);;
		}
	}
 return(TRUE);
}


                                  
