#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_desmonta_arvore()
 *----------------------------------------------------------------------------
 * Descricao      :  desmonta a arvore desalocando a memoria
 *                   alocada na montagem
 * Parametros     :  arvore pointer para a arvore montada
 * Retorno		  :  Nao Ha
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
VD_VOID VIDEO_ARVORE_desmonta_arvore(arvore)
VIDEO_ARVORE_ESTRUTURA *arvore;
{
 struct VIDEO_ARVORE_LINHA    *linha,
                              *linha_ant;
 struct VIDEO_ARVORE_ELEMENTO *elemento,
                              *elemento_ant;

 linha = arvore->linha_inicial;
 while(linha->posterior)
     linha = linha->posterior;
 do
  {
   elemento = linha->elemento;
   while(elemento->posterior)
       elemento = elemento->posterior;
   do
    {
     elemento_ant = elemento->anterior;
     VIDEO_free_alloc_parametros(elemento);
     elemento = elemento_ant;
    }while(elemento);
   linha_ant = linha->anterior;
   VIDEO_free_alloc_parametros(linha);
   linha = linha_ant;
  }while(linha);
}
