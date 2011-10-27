#include<INCVIDEO.H>

INT2 VIDEO_display_mascara(col,lin,entrada,mascara,cor,flagset,flagmostra)
INT2     col,
        lin;
char    *entrada,
        *mascara;
BYTE    cor;
WORD    flagset,
        flagmostra;
{
 char *buffer,
      *bfdisp;

 if ((buffer = VIDEO_EDITA_expande_mascara(mascara)) == VIDEO_NILL(char))
     return(FALSE);

 if ((bfdisp = VIDEO_alloc_parametros(strlen(buffer)+2)) == VIDEO_NILL(char))
    {
	 VIDEO_mostra_mens_erro_alloc(ALOCACAO_DISP_MASCARA);
     VIDEO_free_alloc_parametros(buffer);
     return(FALSE);
    }

 if (!VIDEO_EDITA_monta_mascara(entrada,buffer,bfdisp,
              VIDEO_NILL(char),VIDEO_NILL(INT2),flagset,flagmostra))
    {
     VIDEO_free_alloc_parametros(buffer);
     VIDEO_free_alloc_parametros(bfdisp);
     return(FALSE);
    }

 VIDEO_tprt_l(col,lin,bfdisp,cor);
 VIDEO_free_alloc_parametros(buffer);
 VIDEO_free_alloc_parametros(bfdisp);
 return(TRUE);
}

