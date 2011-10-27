#include <INCVIDEO.H>

INT2 VIDEO_gerwindow_mem(coli,colf,lini,linf,operacao,imagem)
INT2          coli, colf,
             lini, linf,
             operacao;
VIDEO_ESTWIN **imagem;
{     
 char         *buffer_aux;
 WORD         tam, contaux;
 VIDEO_ESTWIN *IMAGE_aux;
 long int     totmem;

 if (operacao && (operacao < 2) && !VIDEO_teste_4(coli,colf,lini,linf))
    return(VIDEO_ERRGERW01);

#if defined(__VIDEO_ADM_WINDOW_CARGA_PARAMETROS)
 switch(operacao)
  {
   case  VIDEO_WPUSH :
                 if (VIDEO_adm_window_parametros->VIDEO_num_desc_win
                     == VIDEO_MAXWINDOW)
                     return(VIDEO_ERRGERW02);
                 contaux = VIDEO_push_descwin();
                 IMAGE_aux =
                 &VIDEO_adm_window_parametros->VIDEO_pilha_win[contaux];
                 if (VIDEO_ALLOC_MEM(IMAGE_aux->buffer,
                    (colf-coli+1)*(linf-lini+1)*2) == VIDEO_NULO)
                    {
                     VIDEO_pop_descwin();
                     return (VIDEO_ERRGERW03);
                    }
                 VIDEO_lertela(coli,colf,lini,linf,IMAGE_aux->buffer);
                 VIDEO_movbloco(IMAGE_aux,&coli,4*sizeof(coli));
                 ++VIDEO_adm_window_parametros->VIDEO_num_desc_win;
                 return(contaux);

   case  VIDEO_WPOP:
                 if (!VIDEO_adm_window_parametros->VIDEO_num_desc_win)
                     return(VIDEO_ERRGERW04);
                 contaux = VIDEO_pop_descwin();
                 IMAGE_aux =
                 &VIDEO_adm_window_parametros->VIDEO_pilha_win[contaux];
                 VIDEO_grvtela(IMAGE_aux->coli,IMAGE_aux->colf,
                               IMAGE_aux->lini,IMAGE_aux->linf,
                               IMAGE_aux->buffer);
                 VIDEO_FREE_ALLOC_MEM(IMAGE_aux->buffer);
                 --VIDEO_adm_window_parametros->VIDEO_num_desc_win;
                 return(contaux);

   case  VIDEO_WFREE : if (!VIDEO_adm_window_parametros->VIDEO_num_desc_win)
                     return(VIDEO_ERRGERW05);
                 contaux = VIDEO_pop_descwin();
                 IMAGE_aux = &VIDEO_adm_window_parametros->VIDEO_pilha_win[contaux];
                 VIDEO_FREE_ALLOC_MEM(IMAGE_aux->buffer);
                 --VIDEO_adm_window_parametros->VIDEO_num_desc_win;
                 return(contaux);

   case  VIDEO_WFREE_ALL:
           if (!VIDEO_adm_window_parametros->VIDEO_num_desc_win)
              return(VIDEO_ERRGERW06);
do
 {
  VIDEO_FREE_ALLOC_MEM(
VIDEO_adm_window_parametros->VIDEO_pilha_win[VIDEO_pop_descwin()].buffer);
}while(--VIDEO_adm_window_parametros->VIDEO_num_desc_win);
return(TRUE);

   case  VIDEO_WGET  :

 if (!VIDEO_adm_window_parametros->VIDEO_num_desc_win)
    return(VIDEO_ERRGERW07);
 if ((buffer_aux =
     memchr(PTR_CAST(char,
     VIDEO_adm_window_parametros->VIDEO_pilha_descritor_usado_buffer),
     C(coli), VIDEO_adm_window_parametros->VIDEO_num_desc_win))
     == VIDEO_NILL(char))
     return(VIDEO_ERRGERW08);
 *imagem = &VIDEO_adm_window_parametros->VIDEO_pilha_win[coli];
 return(coli);

   case VIDEO_WMEM   :
     if (!VIDEO_adm_window_parametros->VIDEO_num_desc_win)
         return(VIDEO_ERRGERW09);
     buffer_aux = PTR_CAST(char,
     VIDEO_adm_window_parametros->VIDEO_pilha_descritor_usado_buffer);

     for (totmem = contaux = 0;
          contaux < VIDEO_adm_window_parametros->VIDEO_num_desc_win;
          ++contaux,++buffer_aux)
         {
          IMAGE_aux =
          &VIDEO_adm_window_parametros->VIDEO_pilha_win[I(*buffer_aux)];
          totmem += L((IMAGE_aux->colf - IMAGE_aux->colf + 1) *
                      (IMAGE_aux->linf - IMAGE_aux->lini + 1) * 2);
         }

     if (imagem)
         CLONG(imagem) = totmem;
     return(UI(totmem / 16L + 1));

   case  VIDEO_WDEL  :
  if (!VIDEO_adm_window_parametros->VIDEO_num_desc_win)
      return(VIDEO_ERRGERW10);

  if ((buffer_aux = memchr(PTR_CAST(char,
       VIDEO_adm_window_parametros->VIDEO_pilha_descritor_usado_buffer),
       C(coli), VIDEO_adm_window_parametros->VIDEO_num_desc_win))
       == VIDEO_NILL(char))
      return(VIDEO_ERRGERW11);

   VIDEO_FREE_ALLOC_MEM(VIDEO_adm_window_parametros->VIDEO_pilha_win[coli].buffer);

   if (buffer_aux != (VIDEO_adm_window_parametros->VIDEO_pilha_descritor_usado_buffer-1))
       VIDEO_copbloco(buffer_aux,buffer_aux+1,
       W(VIDEO_adm_window_parametros->VIDEO_pilha_descritor_usado_buffer-1)-W(buffer_aux));
   return(coli);
  }
#else
 switch(operacao)
  {
   case  VIDEO_WPUSH :
                 if (VIDEO_num_desc_win == VIDEO_MAXWINDOW)
                    return(VIDEO_ERRGERW02);
                 contaux = VIDEO_push_descwin();
                 IMAGE_aux = &VIDEO_pilha_win[contaux];
                 if (VIDEO_ALLOC_MEM(IMAGE_aux->buffer,
                    (colf-coli+1)*(linf-lini+1)*2) == VIDEO_NULO)
                     VIDEO_mostra_mens_erro_alloc(ALOCACAO_1_PUSHWIN);
                   else
                     {
                      VIDEO_lertela(coli,colf,lini,linf,IMAGE_aux->buffer);
                      VIDEO_movbloco(IMAGE_aux,&coli,4*sizeof(coli));
                     }
                 ++VIDEO_num_desc_win;
                 return(contaux);

   case  VIDEO_WPOP  :
                 if (!VIDEO_num_desc_win)
                     return(VIDEO_ERRGERW04);
                 contaux = VIDEO_pop_descwin();
                 IMAGE_aux = &VIDEO_pilha_win[contaux];
                 if (IMAGE_aux->buffer)
                     VIDEO_grvtela(IMAGE_aux->coli,IMAGE_aux->colf,
                                   IMAGE_aux->lini,IMAGE_aux->linf,
                                   IMAGE_aux->buffer);
                     VIDEO_FREE_ALLOC_MEM(IMAGE_aux->buffer);

                 VIDEO_setmem(IMAGE_aux,sizeof(VIDEO_ESTWIN),0);
                 --VIDEO_num_desc_win;
                 return(contaux);

   case  VIDEO_WPUSHATR :
                 if (VIDEO_num_desc_win == VIDEO_MAXWINDOW)
                    return(VIDEO_ERRGERW02);
                 contaux = VIDEO_push_descwin();
                 IMAGE_aux = &VIDEO_pilha_win[contaux];
                 if (VIDEO_ALLOC_MEM(IMAGE_aux->buffer,
                    (colf-coli+1)*(linf-lini+1)) == VIDEO_NULO)
                    VIDEO_mostra_mens_erro_alloc(ALOCACAO_2_PUSHWIN);
                  else
                    {
                     VIDEO_leratrib(coli,colf,lini,linf,IMAGE_aux->buffer);
                     VIDEO_movbloco(IMAGE_aux,&coli,4*sizeof(coli));
                    }
                 ++VIDEO_num_desc_win;
                 return(contaux);

   case  VIDEO_WPOPATR  :
                 if (!VIDEO_num_desc_win)
                     return(VIDEO_ERRGERW04);
                 contaux = VIDEO_pop_descwin();
                 IMAGE_aux = &VIDEO_pilha_win[contaux];
                 if (IMAGE_aux->buffer)
                    {
                     VIDEO_grvatrib(IMAGE_aux->coli,IMAGE_aux->colf,
                                   IMAGE_aux->lini,IMAGE_aux->linf,
                                   IMAGE_aux->buffer);
                     VIDEO_FREE_ALLOC_MEM(IMAGE_aux->buffer);
                    }
                 --VIDEO_num_desc_win;
                 return(contaux);

   case  VIDEO_WFREE :
                 if (!VIDEO_num_desc_win)
                     return(VIDEO_ERRGERW05);
                 contaux = VIDEO_pop_descwin();
                 IMAGE_aux = &VIDEO_pilha_win[contaux];
                 if (IMAGE_aux->buffer)
                     VIDEO_FREE_ALLOC_MEM(IMAGE_aux->buffer);
                 --VIDEO_num_desc_win;
                 return(contaux);

   case  VIDEO_WFREE_ALL:
         if (!VIDEO_num_desc_win)
             return(VIDEO_ERRGERW06);
         do
          {
           if ((IMAGE_aux = &VIDEO_pilha_win[VIDEO_pop_descwin()])->buffer)
               VIDEO_FREE_ALLOC_MEM(IMAGE_aux->buffer);
          }while(--VIDEO_num_desc_win);
         return(TRUE);

   case  VIDEO_WGET  :
            if (!VIDEO_num_desc_win)
               return(VIDEO_ERRGERW07);
            if ((buffer_aux =
               memchr(PTR_CAST(char,VIDEO_pilha_descritor_usado_buffer),
               C(coli), VIDEO_num_desc_win)) == VIDEO_NILL(char))
               return(VIDEO_ERRGERW08);
            *imagem = &VIDEO_pilha_win[coli];
            return(coli);

   case VIDEO_WMEM   :
         if (!VIDEO_num_desc_win)
            return(VIDEO_ERRGERW09);
         buffer_aux = PTR_CAST(char,VIDEO_pilha_descritor_usado_buffer);

         for (totmem = contaux = 0;contaux < VIDEO_num_desc_win;
              ++contaux,++buffer_aux)
             {
              IMAGE_aux = &VIDEO_pilha_win[I(*buffer_aux)];
              totmem += L((IMAGE_aux->colf - IMAGE_aux->colf + 1) *
                        (IMAGE_aux->linf - IMAGE_aux->lini + 1) * 2);
             }

         if (imagem)
            CLONG(imagem) = totmem;
         return(W(totmem / 16L + 1));

   case  VIDEO_WDEL  :

         if (!VIDEO_num_desc_win)
             return(VIDEO_ERRGERW10);

         if ((buffer_aux = memchr(PTR_CAST(char,
                           VIDEO_pilha_descritor_usado_buffer),
                          C(coli), VIDEO_num_desc_win)) == VIDEO_NILL(char))
             return(VIDEO_ERRGERW11);

         if (VIDEO_pilha_win[coli].buffer)
             VIDEO_FREE_ALLOC_MEM(VIDEO_pilha_win[coli].buffer);

         if (buffer_aux != (VIDEO_pilha_descritor_usado_buffer-1))
             VIDEO_copbloco(buffer_aux,buffer_aux+1,
             W(VIDEO_pilha_descritor_usado_buffer-1)-W(buffer_aux));

         return(coli);
  }
#endif
 return(VIDEO_ERRGERW12);
}  
