#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_monta_bloco()
 *----------------------------------------------------------------------------
 * Descricao      :  monta o bloco de membros na arvore, membros podem ser
 *                   ramo ou ponta
 * Parametros     :  membros     bloco de membros a ser montado na arvore
 *                   linha       linha onde se localiza cada elemento do
 *                               membro
 *                   anterior    pointer para o elemento anterior
 *                   coluna_disp coluna real do elemento
 *                   linha_disp  linha real do elemento
 *                   chamada     numero recursivo da chamada
 *                   espaco      tamanho do espaco entre colunas
 *                   maxcol      tamanho da maior coluna
 * Retorno		  :  Nao Ha
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_monta_bloco(membros,linha,anterior,coluna_disp,linha_disp,
                             chamada,espaco,maxcol)
struct VIDEO_ARVORE_UNIDADE  *membros;
struct VIDEO_ARVORE_LINHA    **linha;
struct VIDEO_ARVORE_ELEMENTO *anterior;
INT2                          coluna_disp,
                             *linha_disp,
                             chamada,
                             espaco,
                             *maxcol;
{
 struct VIDEO_ARVORE_LINHA    *linaux;
 struct VIDEO_ARVORE_ELEMENTO *aux;
 INT2                          cont,
                              tamanho,
							  tamaux,
                              retmonta,
                              contponta;

 tamanho = cont = 0;

 retmonta = TRUE;

 if (!membros->item)   /*se nao ha itens retorna*/
     return(TRUE);

 while((membros+cont)->item)   /*pega o maior item da tabela*/
  {
   char *auxbuf;
   tamaux = strlen((membros+cont)->item);

   if (!tamaux)
      return(FALSE);

   if (tamaux > tamanho)
      tamanho = tamaux;
   ++cont;
  }
                             /*tamanho possui o tamanho do maior item*/
 if (!cont)
    return(FALSE);

 (*linha)->linha = *linha_disp;     /*seta linha real de displagem*/

 if (*maxcol < coluna_disp)
    *maxcol = coluna_disp;

 contponta = 1;
 do
  {
   if (membros->subitens)
      {
                                     /* monta o elemento o item*/
       VIDEO_ARVORE_monta_elemento(coluna_disp,tamanho,contponta,
                      !(membros+1)->item,
					  membros->servico,(*linha)->elemento,anterior,
					  membros->item,PTR_CAST(char,(*linha)));
                                    /* se problemas de alocacao retorna falso*/
       ++contponta;
       if ((aux = (struct VIDEO_ARVORE_ELEMENTO *)
           VIDEO_alloc_parametros(sizeof(struct VIDEO_ARVORE_ELEMENTO)))
           == VD_NULO)
		  {
		   (*linha)->elemento->posterior =
								VD_NILL(struct VIDEO_ARVORE_ELEMENTO);
		   (*linha)->posterior = VD_NILL(struct VIDEO_ARVORE_LINHA);
           while((*linha)->elemento->anterior)
             (*linha)->elemento = (*linha)->elemento->anterior;
           VIDEO_mostra_mens_erro_alloc(ALOCACAO_1_MONTA_BLOCO);
		   return(FALSE);
		  }
									 /* posiciona no proximo elemento da linha*/
       (*linha)->elemento->posterior = aux;
       anterior                      = (*linha)->elemento;
       (*linha)->elemento            = aux;
                             /* chama monta bloco recursivo com os subitens*/
	   if (!VIDEO_ARVORE_monta_bloco(membros->subitens,linha,
            anterior,coluna_disp+tamanho+espaco,linha_disp,chamada+1,espaco,
            maxcol))
		  {
           while((*linha)->elemento->anterior)
             (*linha)->elemento = (*linha)->elemento->anterior;
		   return(FALSE);
		  }
                             /* termina chamada do subitens*/
	   anterior = VD_NILL(struct VIDEO_ARVORE_ELEMENTO);
                             /* pega proximo membro*/
       ++membros;
      }
    else
      {                                /* monta o elemento o item*/
       VIDEO_ARVORE_monta_elemento(coluna_disp,tamanho,contponta,
                      !(membros+1)->item,
                      membros->servico,(*linha)->elemento,anterior,
                      membros->item,PTR_CAST(char,(*linha)));
       ++contponta;
	   if (membros->servico)
          {             /* se membro e servico e ponta*/
		   (*linha)->elemento->posterior = VD_NILL(struct VIDEO_ARVORE_ELEMENTO);
                        /* alloca memoria para proxima linha*/
                        /* se problemas de alocacao retorna falso*/
						/* reposiciona no primeiro elemento dalinha terminada*/
           while((*linha)->elemento->anterior)
             (*linha)->elemento = (*linha)->elemento->anterior;

		   if ((linaux = (struct VIDEO_ARVORE_LINHA *)
               VIDEO_alloc_parametros(sizeof(struct VIDEO_ARVORE_LINHA)))
               ==VD_NULO)
			  {
           VIDEO_mostra_mens_erro_alloc(ALOCACAO_1_MONTA_BLOCO);
			   (*linha)->posterior = VD_NILL(struct VIDEO_ARVORE_LINHA);
			   return(FALSE);
			  }

                        /* reendereca para proxima linha*/
           (*linha)->posterior = linaux;
           linaux->anterior    = *linha;
           *linha              = linaux;
		   linaux->elemento  = VD_NILL(struct VIDEO_ARVORE_ELEMENTO);
		   linaux->posterior = VD_NILL(struct VIDEO_ARVORE_LINHA);

                        /* alloca memoria para o proximo elemento*/
                        /* se problemas de alocacao retorna falso*/

           if ((linaux->elemento = (struct VIDEO_ARVORE_ELEMENTO *)
                VIDEO_alloc_parametros(sizeof(struct VIDEO_ARVORE_ELEMENTO)))
                == VD_NULO)
               return(FALSE);

                        /* aponta para proxima linha*/
           *linha_disp += (membros->salto + 1);
           (*linha)->linha = *linha_disp;

           anterior = VD_NILL(struct VIDEO_ARVORE_ELEMENTO);
          }
        else
          {
		   (*linha)->posterior = VD_NILL(struct VIDEO_ARVORE_LINHA);
                        /* alloca memoria para o proximo elemento*/
                        /* se problemas de alocacao retorna falso*/
           if ((aux = (struct VIDEO_ARVORE_ELEMENTO *)
               VIDEO_alloc_parametros(sizeof(struct VIDEO_ARVORE_ELEMENTO)))
               == VD_NULO)
			  {
			   (*linha)->elemento->posterior =
									VD_NILL(struct VIDEO_ARVORE_ELEMENTO);
			   while((*linha)->elemento->anterior)
				 (*linha)->elemento = (*linha)->elemento->anterior;
			   return(FALSE);
			  }
           (*linha)->elemento->posterior = aux;
           anterior                      = (*linha)->elemento;
           (*linha)->elemento            = aux;
          }
       ++membros;
      }
  }while(membros->subitens || membros->item);

 if (!chamada && retmonta)		/*desaloca memoria allocada para o ultimo item*/
    {
	 VIDEO_free_alloc_parametros((*linha)->elemento);
	 (*linha) = (*linha)->anterior;
	 VIDEO_free_alloc_parametros((*linha)->posterior);
	 (*linha)->posterior = VD_NILL(struct VIDEO_ARVORE_LINHA);
     (*linha)->elemento->posterior = VD_NILL(struct VIDEO_ARVORE_ELEMENTO);
    }
 return(TRUE);
}

