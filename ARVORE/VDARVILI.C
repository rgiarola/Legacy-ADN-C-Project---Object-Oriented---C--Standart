#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_inicio_linha()
 *----------------------------------------------------------------------------
 * Descricao      :  funcao servidora seleciona o inicio da linha atual
 *                   da arvore
 * Parametros     :  arvore  estrutura controladora da arvore
 *                   param   estrutura do nucleo do MSPAS
 * Retorno        :  TRUE
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_inicio_linha(arvore,param)
VIDEO_ARVORE_ESTRUTURA **arvore;
VIDEO_NUCLEO_SERV      **param;
{
 struct VIDEO_ARVORE_ELEMENTO *elemento;
 VIDEO_ARVORE_ESTRUTURA       *arvoreloc;
 arvoreloc = *arvore;
 elemento = arvoreloc->linha_atual->elemento;

 if (arvoreloc->elemento != elemento)
    {
     if ((arvoreloc->coli_arvore > elemento->coluna) ||
         (arvoreloc->colf_arvore < (elemento->coluna + elemento->tamanho-1)))
         {
          arvoreloc->flagdisparvore = TRUE;
          arvoreloc->coli_arvore = elemento->coluna;
          arvoreloc->colf_arvore = arvoreloc->coli_arvore +
                      ((arvoreloc->colf-2) - (arvoreloc->coli+arvoreloc->coli_offset));
         }
      else
        VIDEO_ARVORE_desativa_prompt(arvoreloc,arvoreloc->elemento);
     arvoreloc->elemento = elemento;
     arvoreloc->flagdispprompt = TRUE;
    }
 return(TRUE);
}
