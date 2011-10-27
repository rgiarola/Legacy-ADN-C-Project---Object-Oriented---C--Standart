#include<INCVIDEO.H>

/*===========================================================================
                             ANALIZA LINHA
===========================================================================*/
int VIDEO_MCLIN_analiza_linha_0(expande)
VIDEO_MCLIN_STR_EXPAND *expande;
{
 char *linha,*aux,*aux2[2];
 int  situacao  = 0,
      definicao = 0,
	  coment,cont,tamanho;

 coment = expande->coment;

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

/*===========================================================================
                           RETIRA BLOCO DE COMENTARIO
===========================================================================*/
 linha = expande->linha;
 situacao = FALSE;
 cont	  = 0;

 do
  {
   if ((aux2[cont] = strchr(linha,'/')) != VD_NULO)
      {
	   if (*(aux2[cont]+1) == '*')
		  {
		   if (++cont > 1)
			  return(VIDEO_MCLIN_ERRO_COMENTARIO)
		   situacao = VIDEO_MCLIN_INICIO_COMENTARIO;
		  }
		else
		  {
		   if (aux2[cont] != linha)
			   if (*(aux2[cont]-1) == '*')
				  {
				   if (cont)
					  {
					   tamanho = W(W(VIDEO_FP_OFF(aux2[1])) -
								   W(VIDEO_FP_OFF(aux2[0])) + 1;
					   VIDEO_setmem(
					  }


 if ((linha = strstr(expande->linha,"*/")) != VD_NULO)
    {
     int tam;

     tam = I(VIDEO_FP_OFF(linha))-I(VIDEO_FP_OFF(expande->buffer_leitura));

     if (tam > 1023 || tam < 0)
         VIDEO_mostra_mens_erro(VIDEO_texto_linguagem,VIDEO_ERRO_LING_analise_2);
     *linha = '\0';
     situacao = VIDEO_MCLIN_FIM_COMENTARIO;
     expande->linha = linha + 2;
	}

 if ((linha = strstr(expande->linha,"/*")) != VD_NULO)
    {
     int tam;

     tam = I(VIDEO_FP_OFF(linha))-I(VIDEO_FP_OFF(expande->buffer_leitura));

     if (tam > 1023 || tam < 0)
         VIDEO_mostra_mens_erro(VIDEO_texto_linguagem,VIDEO_ERRO_analise_4);

     *linha = '\0';
     situacao = VIDEO_MCLIN_INICIO_COMENTARIO;


    }

 if (situacao == VIDEO_MCLIN_FIM_COMENTARIO)
     --expande->coment;


 if (situacao == VIDEO_MCLIN_INICIO_COMENTARIO)
    ++expande->coment;

 if (expande->coment < 0)
    return(VIDEO_MCLIN_ERRO_COMENTARIO);

/*===========================================================================
                             TESTA DEFINICAO
===========================================================================*/
 if (expande->definicao[expande->niveldef])
	{
	 if (strstr(expande->linha+expande->poslinha,"##ENDIF") && !coment)
         return(VIDEO_MCLIN_FIM_DEFINICAO);

     if (!expande->flagdef[expande->niveldef] && !coment)
         return(VIDEO_MCLIN_COMENTARIO_LINHA);
	}

 if (strstr(expande->linha+expande->poslinha,"##INCLUDE") && !coment)
     return(VIDEO_MCLIN_INCLUDE_ARQUIVO);

 if (strstr(expande->linha+expande->poslinha,"##IFDEF") && !coment)
     return(VIDEO_MCLIN_INICIO_DEFINICAO);

 if (strstr(expande->linha+expande->poslinha,"##IFNDEF") && !coment)
     return(VIDEO_MCLIN_INICIO_NAODEFINICAO);

  if (expande->coment > 0)
    return(VIDEO_MCLIN_COMENTARIO);
 
 linha = expande->linha+expande->poslinha;

 while(*linha)
 {
  if (*linha != ' ')
     break;
  ++linha;
 }

 if (!strlen(linha))
    return(VIDEO_MCLIN_COMENTARIO_LINHA);

 return(VIDEO_MCLIN_GRAVA_LINHA);
}




