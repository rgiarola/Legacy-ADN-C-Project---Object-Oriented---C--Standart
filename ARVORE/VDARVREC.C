#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO		  :  VIDEO_ARVORE_reendereca_coluna()
 *----------------------------------------------------------------------------
 * Descricao	  :  reendereca coluna para navegacao vertical
 * Parametros	  :  linhainicial  linha inicial de reenderecamento
 *					 colunainicial coluna inicial e referencia de
 *								   reenderecamento
 * Retorno		  :  Nao Ha
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
VD_VOID VIDEO_ARVORE_reendereca_coluna(linhainicial,colunainicial)
struct VIDEO_ARVORE_LINHA    *linhainicial;
struct VIDEO_ARVORE_ELEMENTO *colunainicial;
{
 struct VIDEO_ARVORE_ELEMENTO *varre_coluna1,
                              *varre_coluna2;
 INT2                          coli_ant,
							  colf_ant,
							  coli_atu,
							  colf_atu;

 varre_coluna1 = colunainicial;
 linhainicial  = linhainicial->posterior;
/*==========================================================================
 VARRE DA LINHA INICIAL ATE A ULTIMA LINHA EM BUSCA DE ELEMENTOS QUE ESTEJAM
              DENTRO DAS COORDENADAS DA COLUNA INICIAL
==========================================================================*/
 while(linhainicial)
  {
   varre_coluna2 = linhainicial->elemento;
   linhainicial  = linhainicial->posterior;
   while(varre_coluna2)
    {
     coli_ant = colunainicial->coluna;
     colf_ant = colunainicial->coluna + colunainicial->tamanho - 1;
     coli_atu = varre_coluna2->coluna;
     colf_atu = varre_coluna2->coluna + colunainicial->tamanho - 1;
     if (coli_ant >= coli_atu)
        if (colf_ant <= colf_atu)
           {
            varre_coluna1->poslin = varre_coluna2;
            varre_coluna2->antlin = varre_coluna1;
            varre_coluna1         = varre_coluna2;
            break;
           }
     varre_coluna2 = varre_coluna2->posterior;
    }
  }
}
