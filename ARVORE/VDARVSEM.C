#include<INCVIDEO.H>

INT2 VIDEO_ARVORE_seleciona_mouse(arvore,param)
VIDEO_ARVORE_ESTRUTURA **arvore;
VIDEO_NUCLEO_SERV      **param;
{
 struct VIDEO_ARVORE_ELEMENTO *elemento;
 struct VIDEO_ARVORE_LINHA    *linha;
 VIDEO_ARVORE_ESTRUTURA       *arvore_loc;

 arvore_loc = *arvore;

 if ((VIDEO_MOUSE_colclick > (arvore_loc->colf-2)) ||
     (VIDEO_MOUSE_colclick < (arvore_loc->coli+arvore_loc->coli_offset)) ||
	 (VIDEO_MOUSE_linclick > (arvore_loc->linf-3)) ||
     (VIDEO_MOUSE_linclick < (arvore_loc->lini+arvore_loc->lini_offset)))
     return(FALSE);

 linha = arvore_loc->linha_initela;

 do
  {
   if ((linha->linha-arvore_loc->lini_arvore+arvore_loc->lini+arvore_loc->lini_offset) ==
       VIDEO_MOUSE_linclick)
      {
       elemento = linha->elemento;
       do
        {
        if (elemento->coluna >= arvore_loc->coli_arvore)
           {
            if ((elemento->coluna + elemento->tamanho-1) <= arvore_loc->colf_arvore)
               {
                if ((VIDEO_MOUSE_colclick <=
                     (elemento->coluna-arvore_loc->coli_arvore+
                      arvore_loc->coli+arvore_loc->coli_offset+elemento->tamanho - 1)) &&
                    (VIDEO_MOUSE_colclick >=
                     (elemento->coluna-arvore_loc->coli_arvore+
                      arvore_loc->coli+arvore_loc->coli_offset)))
                        {
						 if (elemento != arvore_loc->elemento)
							{
							 VIDEO_ARVORE_desativa_prompt(arvore_loc,arvore_loc->elemento);
							 arvore_loc->flagdispprompt = TRUE;
							 arvore_loc->elemento = elemento;
							 arvore_loc->linha_atual = linha;
                             VIDEO_MOUSE_deshabcursor();
                            }
						 return(TRUE);
                        }
               }
             else
               return(FALSE);
           }
         elemento = elemento->posterior;
        }while(elemento);
       return(FALSE);
      }
   if (linha == arvore_loc->linha_fintela)
	  break;
   linha = linha->posterior;
  }while(linha);
 return(FALSE);
}
