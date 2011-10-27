#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_primeiro_item()
 *----------------------------------------------------------------------------
 * Descricao      :  funcao servidora seleciona o primeiro item da linha e
 *                   janela atual da arvore
 * Parametros     :  arvore  estrutura controladora da arvore
 *                   param   estrutura do nucleo do MSPAS
 * Retorno        :  TRUE
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_primeiro_item(arvore,param)
VIDEO_ARVORE_ESTRUTURA **arvore;
VIDEO_NUCLEO_SERV      **param;
{
 struct VIDEO_ARVORE_ELEMENTO *elemento;
 VIDEO_ARVORE_ESTRUTURA       *arvoreloc;

 arvoreloc = *arvore;
 elemento = arvoreloc->linha_atual->elemento;
 do
  {
   if (elemento->coluna < arvoreloc->coli_arvore)
      if (elemento->posterior)
          elemento = elemento->posterior;
        else
          break;
      else
        break;
  }while(TRUE);

 VIDEO_ARVORE_desativa_prompt(arvoreloc,arvoreloc->elemento);
 arvoreloc->elemento = elemento;
 arvoreloc->flagdispprompt = TRUE;
 return(TRUE);
}
