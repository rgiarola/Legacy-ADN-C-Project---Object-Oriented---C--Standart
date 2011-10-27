#include<INCVIDEO.H>

/*===========================================================================
                             ANALIZA LINHA
===========================================================================*/
int VIDEO_MCLIN_analiza_linha_00(expande)
VIDEO_MCLIN_STR_EXPAND *expande;
{
 char *linha;
 linha = expande->expande->linha;

/*===========================================================================
                           RETIRA LINHA DE COMENTARIO
===========================================================================*/
 if ((aux = strstr(expande->linha,"//")) != VD_NULO)
    {
     int tam;
     tam = I(VIDEO_FP_OFF(aux))-I(VIDEO_FP_OFF(expande->buffer_leitura));

     if (tam > 1023 || tam < 0)
         VIDEO_mostra_mens_erro(VIDEO_texto_linguagem,VIDEO_ERRO_analise_3);

     *aux = '\0';
     if (aux == expande->linha)
        return(VIDEO_MCLIN_COMENTARIO_LINHA);
	}

 return(VIDEO_MCLIN_GRAVA_LINHA);
}




