#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_desativa_prompt()
 *----------------------------------------------------------------------------
 * Descricao      :  desativa o prompt da opcao na arvore
 * Parametros     :  arvore pointer para a arvore montada
 *                   elemnto elemento a ser retirado o prompt
 * Retorno		  :  Nao Ha
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
VD_VOID VIDEO_ARVORE_desativa_prompt(arvore,elemento)
VIDEO_ARVORE_ESTRUTURA       *arvore;
struct VIDEO_ARVORE_ELEMENTO *elemento;
{
 INT2 lindisp,
     coldisp;
 coldisp = elemento->coluna - arvore->coli_arvore +
           arvore->coli+arvore->coli_offset;
 lindisp = arvore->linha_atual->linha - arvore->lini_arvore +
           arvore->lini+arvore->lini_offset;
 VD_setatrib(coldisp,coldisp+arvore->elemento->tamanho-1,
             lindisp,lindisp,elemento->servico    ?
                             arvore->cor_elemento :
                             arvore->cor_opcoes   );
}
