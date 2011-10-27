#include <INCVIDEO.H>

INT2 VIDEO_mostra_erro_critico(flagerro)
int flagerro;
{
 static BYTE    flag  = FALSE;
 int            ret,old_isam_err;
 VIDEO_ESTMANUT tela  = {VIDEO_padrao_sistema,TELA_PADROES_ERROCRIT};
 char           mens1[] = "Erro Cr¡tico",
                mens2[] = "Execute Rotina de Seguran‡a",
                buffer[200];
 ++flag;

 VD_PUSHWIN(1,80,1,25);
#ifdef DATABASE_CTREE
 old_isam_err = isam_err;

 if (flag == 2 || !VIDEO_CRG_display_imagem(&tela,1,0))
    {
#endif
     sprintf(buffer,CTREE_MENS_mens_padrao_err,
                    mens1,mens2,
                    flagerro,old_isam_err);
     ret = VD_telamensagem((80-strlen(buffer))/2-2,VIDEO_LIN_MENSAGEM,
                           buffer,VIDEO_mensagem_default.cor,3);
#ifdef DATABASE_CTREE
    }
  else
    {
     sprintf(buffer,"ST[%d/%d]",flagerro,old_isam_err);
     VD_tprt_l(59,9,buffer,0);
     ret = VD_MTTECLA(ESCAPE,ESCAPESCAN);
     VIDEO_freq();
    }
#endif

 VIDEO_espera(100);
 VD_POPWIN();

 --flag;
 return(ret);
}




