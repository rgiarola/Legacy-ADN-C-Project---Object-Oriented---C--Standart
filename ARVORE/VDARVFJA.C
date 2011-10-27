#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_fim_janela()
 *----------------------------------------------------------------------------
 * Descricao      :  funcao servidora seleciona fin da janela da arvore
 * Parametros     :  arvore  estrutura controladora da arvore
 *                   param   estrutura do nucleo do MSPAS
 * Retorno        :  TRUE
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_fim_janela(arvore,param)
VIDEO_ARVORE_ESTRUTURA **arvore;
VIDEO_NUCLEO_SERV      **param;
{
 struct VIDEO_ARVORE_ELEMENTO *elemento;
 struct VIDEO_ARVORE_LINHA    *linha;
 VIDEO_ARVORE_ESTRUTURA       *arvoreloc;
 BOOLEAN                      encontrou;

 arvoreloc = *arvore;
 linha = arvoreloc->linha_fintela;
 encontrou = FALSE;

 do
  {
   elemento = linha->elemento;
   while(elemento->posterior)
        elemento = elemento->posterior;
   do
    {
     if ((elemento->coluna + elemento->tamanho - 1) > arvoreloc->colf_arvore)
        if (elemento->anterior)
           elemento = elemento->anterior;
         else
           break;
      else
        {
         encontrou = (elemento->coluna >= arvoreloc->coli_arvore);
         break;
        }
    }while(TRUE);

   if (encontrou)
      break;
   linha = linha->anterior;
  }while(TRUE);

 VIDEO_ARVORE_desativa_prompt(arvoreloc,arvoreloc->elemento);
 arvoreloc->linha_atual = linha;
 arvoreloc->elemento = elemento;
 arvoreloc->flagdispprompt = TRUE;
 return(TRUE);
}
