#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_pagina_posterior()
 *----------------------------------------------------------------------------
 * Descricao      :  funcao servidora seleciona a pagina posterior (inferior)
 *                   da arvore
 * Parametros     :  arvore  estrutura controladora da arvore
 *                   param   estrutura do nucleo do MSPAS
 * Retorno        :  TRUE
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_pagina_posterior(arvore,param)
VIDEO_ARVORE_ESTRUTURA **arvore;
VIDEO_NUCLEO_SERV      **param;
{
 struct VIDEO_ARVORE_ELEMENTO *elemento;
 struct VIDEO_ARVORE_LINHA    *inicio,*fim;
 VIDEO_ARVORE_ESTRUTURA       *arvoreloc;
 INT2                          cont;
 BOOLEAN                      encontrou;

 arvoreloc = *arvore;
 inicio = arvoreloc->linha_fintela;
 encontrou = FALSE;
 if (inicio->posterior)
    {
     fim = inicio = inicio->posterior;
     cont = 0;
     while(fim->posterior &&
          (cont < (arvoreloc->linf_arvore - arvoreloc->lini_arvore)))
        {
         fim = fim->posterior;
         ++cont;
        }

     if (cont < (arvoreloc->linf_arvore - arvoreloc->lini_arvore))
        {
         inicio = fim;
         cont = 0;
         while(inicio->anterior &&
              (cont < (arvoreloc->linf_arvore - arvoreloc->lini_arvore)))
            {
             inicio = inicio->anterior;
             ++cont;
            }
        }
     arvoreloc->linha_initela = inicio;
     arvoreloc->linha_fintela = fim;
     do
      {
       elemento = inicio->elemento;
       while(elemento->posterior)
          elemento = elemento->posterior;
       do
        {
         if ((elemento->coluna + elemento->tamanho - 1+2) >
              arvoreloc->colf_arvore)
            if (elemento->anterior)
               elemento = elemento->anterior;
             else
               break;
          else
            {
             encontrou = (elemento->coluna >= arvoreloc->coli_arvore) &&
                           ((elemento->coluna + elemento->tamanho-1 + 2) <=
                           arvoreloc->colf_arvore);
             break;
            }
        }while(TRUE);
       if (encontrou || inicio == fim)
           break;
       inicio = inicio->posterior;
      }while(TRUE);

     if (!encontrou)
        {
         inicio = arvoreloc->linha_initela;
         elemento = inicio->elemento;
         while(elemento->posterior)
            elemento = elemento->posterior;
         if ((elemento->coluna + elemento->tamanho-1 + 2) > arvoreloc->colf)
            {
             arvoreloc->colf_arvore = (elemento->coluna + elemento->tamanho-1+3);
             arvoreloc->coli_arvore = arvoreloc->colf_arvore -
                            ((arvoreloc->colf-2) - (arvoreloc->coli+arvoreloc->coli_offset));
            }
          else
            {
             arvoreloc->colf_arvore = arvoreloc->colf -2;
             arvoreloc->coli_arvore = arvoreloc->coli +arvoreloc->coli_offset;
            }
        }
     arvoreloc->lini_arvore = arvoreloc->linha_initela->linha;
     arvoreloc->linf_arvore = arvoreloc->lini_arvore +
                      ((arvoreloc->linf-3) - (arvoreloc->lini+arvoreloc->lini_offset));
     arvoreloc->linha_atual = inicio;
     arvoreloc->elemento    = elemento;
     arvoreloc->flagdispprompt =
     arvoreloc->flagdisparvore = TRUE;
    }
 return(TRUE);
}



