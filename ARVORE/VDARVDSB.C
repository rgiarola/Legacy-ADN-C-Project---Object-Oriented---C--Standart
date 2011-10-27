#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_display_scrowbar()
 *----------------------------------------------------------------------------
 * Descricao      :  funcao chamada pelo nucleo para startup da arvore e
 *                   geracao dos servicos de controle
 * Parametros     :  arvore  estrutura controladora da arvore
 * Retorno        :  servico gerado a partir do teclado
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
VD_VOID VIDEO_ARVORE_display_scrowbar(arvore)
VIDEO_ARVORE_ESTRUTURA *arvore;
{
 INT2 col,lin;

 VD_vertical(arvore->lini+2,arvore->linf-3,arvore->colf,
            arvore->carbar,arvore->cor_barras);

 VD_horizontal(arvore->coli+1,arvore->colf-2,arvore->linf-2,
            arvore->carbar,arvore->cor_barras);

 lin = I(D(D(D(arvore->linha_atual->linha-arvore->lini)/
       D(D(arvore->maxlin)/D(arvore->linf_arvore - arvore->lini_arvore))) +
       D(arvore->lini + 2)));

 if (lin > arvore->linf-3)
    lin = arvore->linf-3;

 if (lin < arvore->lini+2)
    lin = arvore->lini+2;

 VD_plotcarac(arvore->colf,lin,arvore->carscrow,arvore->cor_scrowbar);

 col = I(D(D(D((arvore->elemento->coluna)-(arvore->coli+arvore->coli_offset))/
       D(D(arvore->maxcol)/D(arvore->colf_arvore - arvore->coli_arvore))) +
       D(arvore->coli + arvore->coli_offset)));

 if (col > arvore->colf-2)
    col = arvore->colf-2;

 if (col < arvore->coli+arvore->coli_offset)
    col = arvore->coli+arvore->coli_offset;

 if ((arvore->elemento->tamanho+arvore->elemento->coluna) >=
    (arvore->maxcol + arvore->coli + arvore->coli_offset))
    col = arvore->colf-2;

 VD_plotcarac(col,arvore->linf-2,arvore->carscrow,arvore->cor_scrowbar);
}


