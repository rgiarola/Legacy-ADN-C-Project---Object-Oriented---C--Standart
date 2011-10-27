#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_monta_elemento()
 *----------------------------------------------------------------------------
 * Descricao      :  monta elemento de amostragem e sua coordenadas em x
 * Parametros     :  coluna       coluna real de amostragem
 *                   tamanho      tamanho de amostragem do elemento
 *                   flagfimlinha identificador de fim de linha
 *                   flagfimbloco identificador de fim de bloco
 *                   servico      codigo do servico a executar
 *                   elemento     endereco do elemento
 *                   anterior     endereco do elemento anterior
 *                   buffer       item a ser displado
 *                   linha        pointer para linha possuidora do elemento
 * Retorno		  :  Nao Ha
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
VD_VOID VIDEO_ARVORE_monta_elemento(coluna,tamanho,flagfimlinha,
             flagfimbloco,servico,elemento,anterior,buffer,linha)
INT2                          coluna,
                             tamanho,
                             flagfimlinha,
							 flagfimbloco,
							 servico;
struct VIDEO_ARVORE_ELEMENTO *elemento,
                             *anterior;
char                         *buffer,
                             *linha;
{
 elemento->coluna   = coluna,       /*coluna real de display*/
 elemento->tamanho  = tamanho,      /*tamanho do elemento*/
 elemento->fimlinha = flagfimlinha, /*flag de final de linha*/
 elemento->fimbloco = flagfimbloco, /*flag de final de bloco*/
 elemento->anterior = anterior,     /*elemento anterior*/
 elemento->elemento = buffer,       /*armazena elemento de display*/
 elemento->linha    = linha,        /*pointer para linha atual*/
 elemento->servico  = servico,      /*programa servico da opcao*/
 elemento->poslin	= elemento->antlin = elemento->posterior =
                      VD_NILL(struct VIDEO_ARVORE_ELEMENTO);
 elemento->pesquisado = FALSE;
}
