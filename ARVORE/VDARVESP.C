/* ----------------------------------------------------------------------------
   VDARVESP.C
   Servi‡o de Tratamento de Fun‡”es Especiais
   Teclas CTRL+Fx


   ---------------------------------------------------------------------------- */
#include <INCVIDEO.H>


INT2 VIDEO_ARVORE_funcoes_especiais(arvore,param)
VIDEO_ARVORE_ESTRUTURA **arvore;
VIDEO_NUCLEO_SERV      **param;
{
 if (VIDEO_trata_funcoes_especiais)
    {
     (*VIDEO_trata_funcoes_especiais)
               (VIDEO_FUNCAO_ESPECIAL_ARVORE,
                VD_MTTECLA ((*arvore)->ascii,(*arvore)->scan) );
    }

 return(TRUE);
}

