/* ----------------------------------------------------------------------------
   VDTELESP.C
   Servi‡o de Tratamento de Fun‡”es Especiais
   Teclas CTRL+Fx


   ---------------------------------------------------------------------------- */
#include <INCVIDEO.H>


INT2 VIDEO_TELA_funcoes_especiais(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 if (VIDEO_trata_funcoes_especiais)
    {
     (*VIDEO_trata_funcoes_especiais)
               (VIDEO_FUNCAO_ESPECIAL_TELA,
               (*param)->VIDEO_servrec);

     (*param)->VIDEO_servrec = VD_MTTECLA (VD_NULO, ALT_R);
     (*param)->VIDEO_repdisp = TRUE;
    }

 return(TRUE);
}

