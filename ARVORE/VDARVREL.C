#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO		  :  VIDEO_ARVORE_reendereca_linha()
 *----------------------------------------------------------------------------
 * Descricao	  :  prepara linha para reenderecamento de coluna
 *					 para navegacao vertical
 * Parametros	  :  arvore estrutura que contem o inicio da arvore
 * Retorno		  :  Nao Ha
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
VD_VOID VIDEO_ARVORE_reendereca_linha(arvore)
VIDEO_ARVORE_ESTRUTURA *arvore;
{
 struct VIDEO_ARVORE_LINHA    *linha;
 struct VIDEO_ARVORE_ELEMENTO *coluna;

 linha = arvore->linha_atual;
 while(linha)
  {
   coluna = linha->elemento;
   while(coluna)
    {
/*==========================================================================
SE ELEMENTO NAO POSSUIR O ENDERECO DO INFERIOR REENDERECA COLUNA DO ELEMENTO
==========================================================================*/
     if (!coluna->poslin)
         VIDEO_ARVORE_reendereca_coluna(linha,coluna);
     coluna = coluna->posterior;
    }
   linha = linha->posterior;
  }
}
