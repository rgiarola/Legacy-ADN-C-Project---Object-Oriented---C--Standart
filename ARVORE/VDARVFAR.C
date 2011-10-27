#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_fim_arvore()
 *----------------------------------------------------------------------------
 * Descricao      :  funcao servidora seleciona final da arvore
 * Parametros     :  arvore  estrutura controladora da arvore
 *                   param   estrutura do nucleo do MSPAS
 * Retorno        :  TRUE
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_fim_arvore(arvore,param)
VIDEO_ARVORE_ESTRUTURA **arvore;
VIDEO_NUCLEO_SERV      **param;
{
 struct VIDEO_ARVORE_LINHA    *linha;
 struct VIDEO_ARVORE_ELEMENTO *elemento;
 VIDEO_ARVORE_ESTRUTURA       *arvoreloc;
 INT2                           cont;

 arvoreloc = *arvore;
 arvoreloc->linha_atual = arvoreloc->linha_fintela =
 linha = arvoreloc->linha_final;
 elemento               = linha->elemento;
  for (cont = (arvoreloc->linf_arvore - arvoreloc->lini_arvore);cont &&
           linha->anterior;cont--)
      linha = linha->anterior;

 arvoreloc->linha_initela = linha;
 while(elemento->posterior)
    elemento = elemento->posterior;
 arvoreloc->elemento    = elemento;
 arvoreloc->lini_arvore = arvoreloc->linha_initela->linha;
 arvoreloc->linf_arvore = arvoreloc->linha_fintela->linha;

 if ((elemento->coluna + elemento->tamanho + 3) > arvoreloc->colf)
    {
     arvoreloc->colf_arvore = (elemento->coluna + elemento->tamanho-1+2);
     arvoreloc->coli_arvore = arvoreloc->colf_arvore -
            ((arvoreloc->colf-2) - (arvoreloc->coli+arvoreloc->coli_offset));
    }
  else
    {
     arvoreloc->colf_arvore = arvoreloc->colf-2;
     arvoreloc->coli_arvore = arvoreloc->coli+arvoreloc->coli_offset;
    }

 arvoreloc->flagdispprompt =
 arvoreloc->flagdisparvore = TRUE;
 return(TRUE);
}
