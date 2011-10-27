#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO		  :  VIDEO_ARVORE_monta_arvore()
 *----------------------------------------------------------------------------
 * Descricao	  :  monta a arvore a partir dos itens dos blocos
 * Parametros	  :  arvore  pointer para a raiz da arvore
 *					 blocos  blocos de itens e subitens da arvore
 * Retorno		  :  Nao Ha
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_monta_arvore(arvore)
VIDEO_ARVORE_ESTRUTURA		*arvore;
{
 struct VIDEO_ARVORE_ELEMENTO *inicio;
 struct VIDEO_ARVORE_LINHA    *linha;
 INT2                          lini,
                              coli,
                              ret;

 lini = arvore->lini+arvore->lini_offset;
 coli = arvore->coli+arvore->coli_offset;

 arvore->coli_arvore = coli;
 arvore->lini_arvore = lini;
 arvore->colf_arvore = arvore->colf-2;
 arvore->linf_arvore = arvore->linf-3;

 arvore->maxcol      = 0;

 if ((arvore->linha_inicial = arvore->linha_atual =
	  (struct VIDEO_ARVORE_LINHA *)
      VIDEO_alloc_parametros(sizeof(struct VIDEO_ARVORE_LINHA))) == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_1_MONTA_ARVORE);
     return(FALSE);
    }

 arvore->linha_atual->anterior = VD_NILL(struct VIDEO_ARVORE_LINHA);

 if ((inicio = arvore->linha_atual->elemento =
	  (struct VIDEO_ARVORE_ELEMENTO *)
      VIDEO_alloc_parametros(sizeof(struct VIDEO_ARVORE_ELEMENTO)))
      == VD_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_2_MONTA_ARVORE);
     VIDEO_free_alloc_parametros(arvore->linha_atual);
     return(FALSE);
    }

 ret = VIDEO_ARVORE_monta_bloco(arvore->blocos,&arvore->linha_atual,
                    VD_NILL(struct VIDEO_ARVORE_ELEMENTO),coli,&lini,0,
                    arvore->tamespaco,&arvore->maxcol);

 arvore->linha_final = arvore->linha_atual;
 arvore->linha_atual = arvore->linha_inicial;
 arvore->elemento    = arvore->linha_atual->elemento = inicio;

 VIDEO_ARVORE_reendereca_linha(arvore);
 if (ret)
    {
     linha = arvore->linha_initela = arvore->linha_inicial;
     for (coli = (arvore->linf_arvore - arvore->lini_arvore);coli &&
               linha->posterior;coli--)
          linha = linha->posterior;
     arvore->linha_fintela = linha;
    }
 arvore->maxlin = arvore->linha_final->linha -
                  arvore->linha_inicial->linha + 1;
 arvore->maxcol = arvore->maxcol - arvore->elemento->coluna + 1;

 return(ret);
}
