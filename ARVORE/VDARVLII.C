#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_linha_inferior()
 *----------------------------------------------------------------------------
 * Descricao      :  funcao servidora seleciona a linha inferior da arvore
 * Parametros     :  arvore  estrutura controladora da arvore
 *                   param   estrutura do nucleo do MSPAS
 * Retorno        :  TRUE
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_linha_inferior(arvore,param)
VIDEO_ARVORE_ESTRUTURA **arvore;
VIDEO_NUCLEO_SERV      **param;
{
 struct VIDEO_ARVORE_ELEMENTO *elemento,*anterior;
 struct VIDEO_ARVORE_LINHA    *linha,*linant;
 VIDEO_ARVORE_ESTRUTURA       *arvoreloc;
 INT2                          cont,lindisp,
                              coldisp;

 arvoreloc = *arvore;
 anterior = elemento = arvoreloc->elemento;
 linant = linha = arvoreloc->linha_atual;

 if (elemento->poslin)
    {
     elemento = elemento->poslin;
     linha = PTR_CAST(struct VIDEO_ARVORE_LINHA,elemento->linha);
     if (((elemento->coluna + elemento->tamanho - 1 + 2) <=
         arvoreloc->colf_arvore) &&
         (elemento->coluna >= arvoreloc->coli_arvore))
        {
         VIDEO_ARVORE_desativa_prompt(arvoreloc,anterior);
         if (linha->linha <= arvoreloc->linf_arvore)
            {
             arvoreloc->elemento       = elemento;
             arvoreloc->linha_atual    = linha;
             arvoreloc->flagdispprompt = TRUE;
            }
          else
            {
             arvoreloc->lini_arvore = linha->linha -
                                      (arvoreloc->linf_arvore - arvoreloc->lini_arvore);
             arvoreloc->linf_arvore = linha->linha;
             arvoreloc->flagdispprompt = TRUE;
             arvoreloc->linha_fintela  = linha;
             if (linant->linha == (linha->linha - 1))
                 {
                  arvoreloc->flagdisplinha  = TRUE;
                  VD_sobe_win(arvoreloc->coli,arvoreloc->colf-1,
                         arvoreloc->lini+arvoreloc->lini_offset,arvoreloc->linf-3,1);
                 }
               else
                 arvoreloc->flagdisparvore = TRUE;
             arvoreloc->elemento       = elemento;
             arvoreloc->linha_atual    = linha;
             for (cont = 0;cont < (arvoreloc->linf_arvore - arvoreloc->lini_arvore);cont++)
                 if (linha->anterior)
                    linha = linha->anterior;
                  else
                    break;
             arvoreloc->linha_initela  = linha;
            }
        }
      else
        {
         if (linha->linha > arvoreloc->linf_arvore)
            {
             arvoreloc->lini_arvore = linha->linha -
                                      (arvoreloc->linf_arvore - arvoreloc->lini_arvore);
             arvoreloc->linf_arvore = linha->linha;
             arvoreloc->linha_fintela  = linha;
             arvoreloc->linha_atual    = linha;
             for (cont = 0;cont < (arvoreloc->linf_arvore - arvoreloc->lini_arvore);cont++)
                 if (linha->anterior)
                    linha = linha->anterior;
                  else
                    break;
             arvoreloc->linha_initela  = linha;
            }

         if (anterior->coluna <= elemento->coluna)
            {
             arvoreloc->colf_arvore = elemento->coluna+elemento->tamanho-1+3;
             arvoreloc->coli_arvore = arvoreloc->colf_arvore -
                         ((arvoreloc->colf-2) - (arvoreloc->coli+arvoreloc->coli_offset));
            }
          else
            {
             arvoreloc->coli_arvore = elemento->coluna;
             arvoreloc->colf_arvore = arvoreloc->coli_arvore +
             ((arvoreloc->colf-2) - (arvoreloc->coli+arvoreloc->coli_offset));
            }
         arvoreloc->elemento       = elemento;
         arvoreloc->flagdispprompt = TRUE;
         arvoreloc->flagdisparvore = TRUE;
        }
    }
  else
    if (linha->posterior)
	   {
		linha = linha->posterior;
        elemento = linha->elemento;
        do
         {
          if (elemento->coluna >= arvoreloc->coli_arvore)
              break;
          else
            if (elemento->posterior)
                elemento = elemento->posterior;
              else
                break;
         }while(TRUE);

        if ((elemento->coluna >= arvoreloc->coli_arvore) &&
            (elemento->coluna+elemento->tamanho-1+2) <= arvoreloc->colf_arvore)
            {
             VIDEO_ARVORE_desativa_prompt(arvoreloc,anterior);
             if (linha->linha <= arvoreloc->linf_arvore)
                {
				 arvoreloc->elemento	   = elemento;
				 arvoreloc->linha_atual    = linha;
				 arvoreloc->flagdispprompt = TRUE;
				}
              else
                {
                 arvoreloc->lini_arvore = linha->linha -
                                          (arvoreloc->linf_arvore - arvoreloc->lini_arvore);
                 arvoreloc->linf_arvore = linha->linha;
                 arvoreloc->flagdispprompt = TRUE;
                 arvoreloc->linha_fintela  = linha;
                 arvoreloc->flagdisparvore = TRUE;
                 arvoreloc->elemento       = elemento;
                 arvoreloc->linha_atual    = linha;
                 for (cont = 0;cont < (arvoreloc->linf_arvore - arvoreloc->lini_arvore);cont++)
                     if (linha->anterior)
                        linha = linha->anterior;
                      else
                        break;
                 arvoreloc->linha_initela  = linha;
                }
            }
          else
            {
             arvoreloc->linha_atual    = linha;
             if (linha->linha > arvoreloc->linf_arvore)
                {
                 arvoreloc->lini_arvore = linha->linha -
                       (arvoreloc->linf_arvore - arvoreloc->lini_arvore);
                 arvoreloc->linf_arvore = linha->linha;
                 arvoreloc->linha_fintela  = linha;
                 for (cont = 0;cont < (arvoreloc->linf_arvore - arvoreloc->lini_arvore);cont++)
                     if (linha->anterior)
                        linha = linha->anterior;
                      else
                        break;
                 arvoreloc->linha_initela  = linha;
                }

             if (anterior->coluna <= elemento->coluna)
                {
                 arvoreloc->colf_arvore = elemento->coluna+elemento->tamanho-1+3;
                 arvoreloc->coli_arvore = arvoreloc->colf_arvore -
                             ((arvoreloc->colf-2) - (arvoreloc->coli+arvoreloc->coli_offset));
                }
              else
                {
                 arvoreloc->coli_arvore = elemento->coluna;
                 arvoreloc->colf_arvore = arvoreloc->coli_arvore +
                      ((arvoreloc->colf-2) - (arvoreloc->coli+arvoreloc->coli_offset));
                }
             arvoreloc->elemento       = elemento;
             arvoreloc->flagdispprompt = TRUE;
             arvoreloc->flagdisparvore = TRUE;
            }
       }
 return(TRUE);
}
