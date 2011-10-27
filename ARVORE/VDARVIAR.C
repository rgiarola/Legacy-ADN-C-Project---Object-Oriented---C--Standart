#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_inicio_arvore()
 *----------------------------------------------------------------------------
 * Descricao      :  funcao servidora seleciona inicio da arvore
 * Parametros     :  arvore  estrutura controladora da arvore
 *                   param   estrutura do nucleo do MSPAS
 * Retorno        :  TRUE
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_inicio_arvore(arvore,param)
VIDEO_ARVORE_ESTRUTURA **arvore;
VIDEO_NUCLEO_SERV      **param;
{
 struct VIDEO_ARVORE_LINHA *linha;
 VIDEO_ARVORE_ESTRUTURA       *arvoreloc;
 INT2                       cont,
                           numlin;
 arvoreloc = *arvore;
 arvoreloc->linha_initela = linha =
 arvoreloc->linha_atual = arvoreloc->linha_inicial;
 arvoreloc->elemento    = arvoreloc->linha_inicial->elemento;
 arvoreloc->coli_arvore = arvoreloc->coli+arvoreloc->coli_offset;
 arvoreloc->lini_arvore = arvoreloc->lini+arvoreloc->lini_offset;
 arvoreloc->colf_arvore = arvoreloc->colf-2;
 arvoreloc->linf_arvore = arvoreloc->linf-3;

 for (cont = (arvoreloc->linf_arvore - arvoreloc->lini_arvore);cont &&
           linha->posterior;cont--)
      linha = linha->posterior;

 arvoreloc->linha_fintela = linha;
 arvoreloc->flagdispprompt =
 arvoreloc->flagdisparvore = TRUE;
 return(TRUE);
}
