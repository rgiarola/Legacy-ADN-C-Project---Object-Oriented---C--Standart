#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO         :  VIDEO_ARVORE_display_conect_linha()
 *----------------------------------------------------------------------------
 * Descricao      :  displa as linhas verticais de coneccao da arvore
 * Parametros	  :  arvore pointer para a estrutura de arvore
 * Retorno		  :  Nao Ha
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
VD_VOID VIDEO_ARVORE_display_conect_linha(arvore)
VIDEO_ARVORE_ESTRUTURA *arvore;
{
 struct VIDEO_ARVORE_ELEMENTO *elemento,
                              *posterior,
                              *anterior;
 struct VIDEO_ARVORE_LINHA    *linha,
                              *linant,
                              *linpost;
 INT2                          lindisp,
                              linconect,
                              coldisp,
                              lini, linf;
 BOOLEAN                      conect;
 BYTE                         ascii,scan;

 linha    = arvore->linha_inicial;
 conect   = ~arvore->linha_inicial->elemento->pesquisado;
 do
  {
   elemento = linha->elemento;
   do
    {
     linant = linha;
     anterior = elemento;
     if (anterior->coluna >= arvore->coli_arvore &&
        conect != anterior->pesquisado)
        {
         if ((anterior->coluna + anterior->tamanho-1+2) <= arvore->colf_arvore)
            {
             do
              {
/*               anterior->pesquisado = conect;*/
               coldisp = anterior->coluna - arvore->coli_arvore +
                         arvore->coli + arvore->coli_offset;
               if (anterior->poslin)
                  {
                   posterior = anterior->poslin;
                   linpost =
                       PTR_CAST(struct VIDEO_ARVORE_LINHA,posterior->linha);
                   if (!anterior->fimbloco)
                      {
                       lini = linant->linha;
                       linf = linpost->linha;
/*                       VD_gtxy(1,21);*/
/*                       printf("LINI %2d LINF %2d",lini,linf);*/
/*                       VD_getkbd(&ascii,&scan);*/
                       if (linf != lini+1)
                          {
                           if (lini > arvore->linf_arvore)
                              break;
                           if (linf < arvore->lini_arvore)
                              break;
                           if (lini < arvore->lini_arvore)
                              lini = arvore->lini_arvore;
                            else
                              ++lini;
                           if (linf > arvore->linf_arvore)
                              linf = arvore->linf_arvore;
                            else
                              --linf;
/*                           VD_gtxy(1,22);*/
/*                           printf("LINI %2d LINF %2d",lini,linf);*/
                           lini = (lini - arvore->lini_arvore) +
                                  arvore->lini+arvore->lini_offset;
                           linf = (linf - arvore->lini_arvore) +
                                  arvore->lini+arvore->lini_offset;
                           VD_vertical_simples(lini,linf,coldisp-1,
                                  arvore->cor_linhas);
/*                           VD_gtxy(1,23);*/
/*                           printf("LINI %2d LINF %2d",lini,linf);*/
/*                           VD_getkbd(&ascii,&scan);*/
/*                           if (ascii == 27)*/
/*                               exit(0);*/
                          }
                      }
                   anterior = anterior->poslin;
                   linant = linpost;
                  }
/*             anterior->pesquisado = conect;*/
              }while(anterior->poslin);
            }
        }
/*     elemento->pesquisado = conect;*/
     elemento = elemento->posterior;
    }while(elemento);
   linha = linha->posterior;
  }while(linha);
}

