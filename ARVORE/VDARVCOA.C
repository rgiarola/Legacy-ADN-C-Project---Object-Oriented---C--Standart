#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_coluna_anterior()
 *----------------------------------------------------------------------------
 * Descricao      :  funcao servidora seleciona coluna anterior da arvore
 * Parametros     :  arvore  estrutura controladora da arvore
 *                   param   estrutura do nucleo do MSPAS
 * Retorno        :  TRUE
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_coluna_anterior(arvore,param)
VIDEO_ARVORE_ESTRUTURA **arvore;
VIDEO_NUCLEO_SERV      **param;
{
 struct VIDEO_ARVORE_ELEMENTO *elemento,*anterior;
 struct VIDEO_ARVORE_LINHA    *linha,*linant;
 VIDEO_ARVORE_ESTRUTURA       *arvoreloc;
 INT2                          cont;

 arvoreloc = *arvore;
 anterior  = elemento = arvoreloc->elemento;
 linant = linha = arvoreloc->linha_atual;

 if (elemento->anterior)
    {
	 elemento = elemento->anterior;
	 if (elemento->coluna >= arvoreloc->coli_arvore)
         VIDEO_ARVORE_desativa_prompt(arvoreloc,anterior);
      else
        {
         arvoreloc->coli_arvore = elemento->coluna;
         arvoreloc->colf_arvore = arvoreloc->coli_arvore +
                     ((arvoreloc->colf-2) - (arvoreloc->coli+arvoreloc->coli_offset));
         arvoreloc->flagdisparvore = TRUE;
        }
     arvoreloc->flagdispprompt = TRUE;
     arvoreloc->elemento       = elemento;
    }
  else
    if (linha->anterior)
       {
        linha = linha->anterior;
        elemento = linha->elemento;
        do
         {
          if (elemento->coluna < anterior->coluna)
             {
              if (elemento->posterior)
                  elemento = elemento->posterior;
                else
                  break;
             }
           else
            if (elemento->anterior)
               {
                elemento = elemento->anterior;
                break;
               }
             else
               if (linha->anterior)
                  {
                   linha = linha->anterior;
                   elemento = linha->elemento;
                  }
                else
                 break;
         }while(TRUE);

        if ((elemento->coluna >= arvoreloc->coli_arvore) &&
            ((elemento->coluna+elemento->tamanho-1+2) <=
                                 arvoreloc->colf_arvore))
           {
            VIDEO_ARVORE_desativa_prompt(arvoreloc,anterior);
            if ((linha->linha >= arvoreloc->lini_arvore)    &&
               (linha->linha <= arvoreloc->linf_arvore))
               {
                arvoreloc->elemento       = elemento;
                arvoreloc->linha_atual    = linha;
                arvoreloc->flagdispprompt = TRUE;
               }
             else
               {
                arvoreloc->linf_arvore = linha->linha +
                            (arvoreloc->linf_arvore - arvoreloc->lini_arvore);
                arvoreloc->lini_arvore = linha->linha;
                arvoreloc->flagdispprompt = TRUE;
                arvoreloc->linha_initela  = linha;
                if (linant->linha == (linha->linha + 1))
                    {
                     arvoreloc->flagdisplinha  = TRUE;
                     VD_desce_win(arvoreloc->coli,arvoreloc->colf-1,
                            arvoreloc->lini+arvoreloc->lini_offset,arvoreloc->linf-4,1);
                    }
                  else
                    arvoreloc->flagdisparvore = TRUE;
                arvoreloc->elemento       = elemento;
                arvoreloc->linha_atual    = linha;
                for (cont = 0;cont <
                    (arvoreloc->linf_arvore - arvoreloc->lini_arvore);cont++)
                    if (linha->posterior)
                       linha = linha->posterior;
                     else
                       break;
                arvoreloc->linha_fintela  = linha;
               }
           }
         else
           {
            arvoreloc->linha_atual    = linha;
            if (linha->linha < arvoreloc->lini_arvore)
               {
                arvoreloc->linf_arvore = linha->linha +
                            (arvoreloc->linf_arvore - arvoreloc->lini_arvore);
                arvoreloc->lini_arvore = linha->linha;
                arvoreloc->linha_initela  = linha;
                for (cont = 0;cont <
                    (arvoreloc->linf_arvore - arvoreloc->lini_arvore);cont++)
                    if (linha->anterior)
                       linha = linha->posterior;
                     else
                       break;
                arvoreloc->linha_fintela  = linha;
               }
            arvoreloc->coli_arvore = elemento->coluna;
            arvoreloc->colf_arvore = arvoreloc->coli_arvore +
            ((arvoreloc->colf-2) - (arvoreloc->coli+arvoreloc->coli_offset));
            arvoreloc->flagdispprompt = TRUE;
            arvoreloc->flagdisparvore = TRUE;
            arvoreloc->elemento       = elemento;
           }
       }
 return(TRUE);
}

