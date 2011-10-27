#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 * FUNCAO		  :  VIDEO_ARVORE_display_arvore()
 *----------------------------------------------------------------------------
 * Descricao	  :  displa a arvore conforme coordenadas especificadas
 * Parametros	  :  arvore pointer para a estrutura de arvore
 * Retorno		  :  Nao Ha
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
VD_VOID VIDEO_ARVORE_display_arvore(arvore)
VIDEO_ARVORE_ESTRUTURA *arvore;
{
 struct VIDEO_ARVORE_ELEMENTO *elemento,
                              *posterior,
                              *anterior;
 struct VIDEO_ARVORE_LINHA    *linha,
                              *linant,
                              *linpost;
 INT2                          conecesq,
                              lindisp,
                              coldisp,
                              coli, colf,
                              lini, linf;
 BOOLEAN                      flagant;

 linha    = arvore->linha_initela;
 elemento = linha->elemento;
 do
  {
   conecesq = TRUE;
   flagant = FALSE;
   if (linha->linha >= arvore->lini_arvore)
      if (linha->linha <= arvore->linf_arvore)
          do
           {
            if (elemento->coluna >= arvore->coli_arvore)
               {
                lindisp = linha->linha     - arvore->lini_arvore +
                          arvore->lini+arvore->lini_offset;
                if ((elemento->coluna + elemento->tamanho-1+2) <= arvore->colf_arvore)
                   {
                    flagant = TRUE;
                    coldisp = elemento->coluna - arvore->coli_arvore +
                              arvore->coli+arvore->coli_offset;

                    VIDEO_ARVORE_display_elemento(coldisp,lindisp,
                                arvore->cor_fundo,elemento->servico ?
                                      arvore->cor_elemento :
                                      arvore->cor_opcoes   ,elemento);
/*
                    VD_quadro(coldisp,coldisp+elemento->tamanho-1,lindisp,
                              lindisp,arvore->cararv,arvore->cor_fundo);
                    VD_tprt_l(coldisp,lindisp,elemento->elemento,
                              arvore->cor_elemento);
                    VD_setatrib(coldisp,coldisp+elemento->tamanho-1,lindisp,
                                lindisp,arvore->cor_elemento);
*/
                    if (elemento->anterior && conecesq)
                       {
                        VD_plotcarac(coldisp-2,lindisp,
                                     VIDEO_ARVORE_SETAESQ,arvore->cor_linhas);
                        VD_plotcarac(coldisp-1,lindisp,
                                     VIDEO_LINHAHORIZ,arvore->cor_linhas);
                       }

                    if (!conecesq)
                       {
                        anterior = elemento->anterior;
                        coli = (anterior->coluna+anterior->tamanho-1)
                                - arvore->coli_arvore+arvore->coli + arvore->coli_offset + 1;
                        colf = coldisp -1;
                        VD_horizontal_simples(coli,colf,lindisp,
                                              arvore->cor_linhas);
                       }

                    if (elemento->fimbloco)
                       {
                        if (elemento->fimlinha > 1)
                            VD_plotcarac(coldisp-1,lindisp,
                                  192,arvore->cor_linhas);
                       }
                     else
                       {
                        if (elemento->fimlinha > 1)
                            VD_plotcarac(coldisp-1,lindisp,
                                  195,arvore->cor_linhas);
                          else
                            VD_plotcarac(coldisp-1,lindisp,
                                  194,arvore->cor_linhas);
                       }
                    conecesq = FALSE;
                   }
                 else
                   {
                    if (elemento->anterior && flagant)
                       {
                        elemento = elemento->anterior;
                        coldisp = elemento->coluna - arvore->coli_arvore +
                                  arvore->coli+arvore->coli_offset + elemento->tamanho - 1;
                        VD_plotcarac(coldisp+2,lindisp,
                                     VIDEO_ARVORE_SETADIR,arvore->cor_linhas);
                        VD_plotcarac(coldisp+1,lindisp,
                                     VIDEO_LINHAHORIZ,arvore->cor_linhas);
                       }
                    break;
                   }
               }
            elemento = elemento->posterior;
           }while(elemento);
        else
          break;
   linha = linha->posterior;
   elemento = linha->elemento;
  }while(linha && (linha->linha <= arvore->linf_arvore));
 VIDEO_ARVORE_display_conect_linha(arvore);
}

VD_VOID VIDEO_ARVORE_display_elemento(col,lin,cor_fundo,cor_elemento,elemento)
INT2                         col,lin;
BYTE                         cor_fundo,
                             cor_elemento;
struct VIDEO_ARVORE_ELEMENTO *elemento;
{
 char buffer[200],*auxbuf;

 if (elemento->posterior)
     VIDEO_horizontal_simples(col,col+elemento->tamanho-1,lin,cor_elemento);

 strcpy(buffer,elemento->elemento);
 auxbuf = buffer+strlen(buffer)-1;
 while (auxbuf!=buffer)
  {
   if (*(auxbuf) != ' ')
      {
       *(auxbuf+1) = VD_NULO;
       break;
      }
   --auxbuf;
  }

 VD_tprt_l(col,lin,buffer,cor_elemento);
}

