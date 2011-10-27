#include <INCVIDEO.H>

INT2 VIDEO_PESQUISA_termina(telapesq,param)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
{
 VIDEO_PESQUISA_PLANILHA *pesquisa;
 VIDEO_NUCLEO_SERV       *nucleo;
 INT2                     cont;

 nucleo   = *param;
 pesquisa = PTR_CAST(VIDEO_PESQUISA_PLANILHA,nucleo->VIDEO_campos);

 for (cont = 0;cont < nucleo->VIDEO_numcampos;cont++,pesquisa++)
      if (pesquisa->flagplanilha&VIDEO_PESQUISA_ATIVADA)
		 {
          if (pesquisa->flagplanilha&VIDEO_PESQUISA_POPWIN)
			 VD_POPWIN();

		  if (pesquisa->buffer_pesq)
			 VIDEO_FREE_ALLOC_MEM(pesquisa->buffer_pesq);

          pesquisa->buffer_pesq = VD_NULO;

          if (pesquisa->tela)
              VIDEO_CRG_libera_tela(pesquisa->tela);

          pesquisa->flagplanilha &= ~VIDEO_PESQUISA_ATIVADA;
         }

 return(FALSE);
}
