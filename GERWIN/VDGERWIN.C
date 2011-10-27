//#define VIDEO_GERWIN_ARQUIVO
#include <INCVIDEO.H>

#ifdef VIDEO_GERWIN_ARQUIVO
INT2 VIDEO_gerwindow_swap_in(INT2 coli, INT2 colf,
                             INT2 lini, INT2 linf,INT2 num_imagem);

INT2 VIDEO_gerwindow_swap_out(INT2 coli, INT2 colf,
                              INT2 lini, INT2 linf,INT2 num_imagem);
#endif

INT2 VIDEO_gerwindow(coli,colf,lini,linf,operacao,imagem)
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
     return(VIDEO_ERRO_GERWIN_param_invalidos);


#if defined(__VIDEO_ADM_WINDOW_CARGA_PARAMETROS)
 switch(operacao)
  {
   case  VIDEO_WPUSH :
                 if (VIDEO_adm_window_parametros->VIDEO_num_desc_win
                     == VIDEO_MAXWINDOW)
                     return(VIDEO_ERRO_GERWIN_estouro_descr);
                 contaux = VIDEO_push_descwin();
                 IMAGE_aux =
                 &VIDEO_adm_window_parametros->VIDEO_pilha_win[contaux];
                 if (VIDEO_ALLOC_MEM(IMAGE_aux->buffer,
                    (colf-coli+1)*(linf-lini+1)*2) == VIDEO_NULO)
                    {
                     VIDEO_mostra_mens_erro_alloc(
                     VIDEO_pop_descwin();
                     return();
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
                    return(VIDEO_ERRO_GERWIN_estouro_descr);
                 contaux = VIDEO_push_descwin();
                 IMAGE_aux = &VIDEO_pilha_win[contaux];
#ifdef VIDEO_GERWIN_ARQUIVO
                 if (VIDEO_modo_swap_window)
                    {
                     if (VIDEO_gerwindow_swap_out(coli,colf,lini,linf,contaux+1))
                        {
                         VIDEO_movbloco(&IMAGE_aux->coli,&coli,4*sizeof(coli));
                         IMAGE_aux->buffer = CAST_CHAR((contaux+1));
                        }
                      else
						{
						 VIDEO_setmem(IMAGE_aux,sizeof(VIDEO_ESTWIN),0);
                         contaux = 0 - contaux;
                        }
                    }
                  else
#endif
                    {
                     if (VIDEO_ALLOC_MEM(IMAGE_aux->buffer,
                        (colf-coli+1)*(linf-lini+1)*2) == VIDEO_NULO)
                         VIDEO_mostra_mens_erro_alloc(ALOCACAO_1_PUSHWIN);
                       else
                         {
                          VIDEO_lertela(coli,colf,lini,linf,IMAGE_aux->buffer);
                          VIDEO_movbloco(IMAGE_aux,&coli,4*sizeof(coli));
                         }
                    }
                 ++VIDEO_num_desc_win;
                 return(contaux);

   case  VIDEO_WPOP  :
                 if (!VIDEO_num_desc_win)
                     return(VIDEO_ERRO_GERWIN_num_desc_win);
                 contaux = VIDEO_pop_descwin();
                 IMAGE_aux = &VIDEO_pilha_win[contaux];
                 if (IMAGE_aux->buffer)
#ifdef VIDEO_GERWIN_ARQUIVO
                     if (VIDEO_modo_swap_window)
                        {
                         if (!VIDEO_gerwindow_swap_in(IMAGE_aux->coli,IMAGE_aux->colf,
                                                 IMAGE_aux->lini,IMAGE_aux->linf,
                                                 contaux+1))
                            contaux = 0 -contaux;
                        }
                      else
#endif
						{
                         VIDEO_grvtela(IMAGE_aux->coli,IMAGE_aux->colf,
                                       IMAGE_aux->lini,IMAGE_aux->linf,
                                       IMAGE_aux->buffer);
                         VIDEO_FREE_ALLOC_MEM(IMAGE_aux->buffer);
                        }
                 VIDEO_setmem(IMAGE_aux,sizeof(VIDEO_ESTWIN),0);
                 --VIDEO_num_desc_win;
                 return(contaux);

   case  VIDEO_WPUSHATR :
                 if (VIDEO_num_desc_win == VIDEO_MAXWINDOW)
                    return(VIDEO_ERRO_GERWIN_estouro_descr);
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
                     return(VIDEO_ERRO_GERWIN_num_desc_win);
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
                     return(VIDEO_ERRO_GERWIN_num_desc_win);
                 contaux = VIDEO_pop_descwin();
                 IMAGE_aux = &VIDEO_pilha_win[contaux];
                 if (!VIDEO_modo_swap_window && IMAGE_aux->buffer)
                     VIDEO_FREE_ALLOC_MEM(IMAGE_aux->buffer);
                 --VIDEO_num_desc_win;
                 return(contaux);

   case  VIDEO_WFREE_ALL:
         if (!VIDEO_num_desc_win)
             return(VIDEO_ERRO_GERWIN_num_desc_win);
         do
          {
           if (!VIDEO_modo_swap_window)
               if ((IMAGE_aux = &VIDEO_pilha_win[VIDEO_pop_descwin()])->buffer)
                   VIDEO_FREE_ALLOC_MEM(IMAGE_aux->buffer);
          }while(--VIDEO_num_desc_win);
         return(TRUE);

   case  VIDEO_WGET  :
            if (!VIDEO_num_desc_win)
               return(VIDEO_ERRO_GERWIN_num_window);
            if ((buffer_aux =
               memchr(PTR_CAST(char,VIDEO_pilha_descritor_usado_buffer),
               C(coli), VIDEO_num_desc_win)) == VIDEO_NILL(char))
               return(VIDEO_ERRO_GERWIN_num_window);
            *imagem = &VIDEO_pilha_win[coli];
            return(coli);

   case VIDEO_WMEM   :
         if (!VIDEO_num_desc_win)
            return(VIDEO_ERRO_GERWIN_num_desc_win);
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
             return(VIDEO_ERRO_GERWIN_num_desc_win);

         if ((buffer_aux = memchr(PTR_CAST(char,
                           VIDEO_pilha_descritor_usado_buffer),
                          C(coli), VIDEO_num_desc_win)) == VIDEO_NILL(char))
             return(VIDEO_ERRO_GERWIN_num_window_del);

         if (!VIDEO_modo_swap_window && VIDEO_pilha_win[coli].buffer)
             VIDEO_FREE_ALLOC_MEM(VIDEO_pilha_win[coli].buffer);

         if (buffer_aux != (VIDEO_pilha_descritor_usado_buffer-1))
             VIDEO_copbloco(buffer_aux,buffer_aux+1,
             W(VIDEO_pilha_descritor_usado_buffer-1)-W(buffer_aux));

         return(coli);
  }

#endif

 return(VIDEO_ERRO_GERWIN_param_invalidos);
}

#ifdef VIDEO_GERWIN_ARQUIVO
INT2 VIDEO_gerwindow_swap_out(coli,colf,lini,linf,num_imagem)
INT2         coli, colf,
             lini, linf,
             num_imagem;
{
 char         *buffer;
 INT2         arquivo,indice,
              real_arquivo,tamreg;
 IDE_ARQUIVOS *workifil;

 indice       = CTREE_keynm(VIDEO_GERAIS_indice_gerwin);
 arquivo      = CTREE_keyfil(indice);
 real_arquivo = CTREE_tmpfil(arquivo);
 workifil     = CTREE_ifilend(arquivo);

 ATIVA_BUF_DADOS;
 CTREE_inbuf(arquivo);
 VD_GETBUF(VIDEO_CARGA_CRG_tipoobj,WORD) = num_imagem;

 if (CTREE_find(indice,VD_NULO,
                FIND_IGUAL,CT_LE_EXTRA_REPASSA) == FALSE)
    {
     if (DATABASE_LockISAM(DATABASE_ENABLE))
         return(FALSE);
    
     if (DeleteVRecord( real_arquivo ) != FALSE)
        {
         DATABASE_LockISAM(DATABASE_FREE);
         return(FALSE);
        }

     if (DATABASE_LockISAM(DATABASE_FREE))
         return(FALSE);
    }

 tamreg = workifil->dreclen+(colf-coli+1)*(linf-lini+1)*2;

 if (VIDEO_ALLOC_MEM(buffer,tamreg) == VIDEO_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_3_PUSHWIN);
     return(FALSE);
    }

 CTREE_inbuf(arquivo);
 VD_GETBUF(VIDEO_CARGA_CRG_tipoobj,WORD) = num_imagem;

 VD_GETBUF(VIDEO_CARGA_CRG_tamext,WORD) = tamreg;

 ATIVA_BUF_DADOS;
 VIDEO_movbloco(buffer,CTREE_filbuf(arquivo),workifil->dreclen);
 VIDEO_lertela(coli,colf,lini,linf,buffer+workifil->dreclen);

 if (DATABASE_LockISAM(DATABASE_ENABLE))
     return(FALSE);

 if (DATABASE_AddVRecord(real_arquivo,buffer,tamreg) != FALSE)
    {
     DATABASE_LockISAM(DATABASE_FREE);
     return(FALSE);
    }

 DATABASE_LockISAM(DATABASE_FREE);

 VIDEO_FREE_ALLOC_MEM(buffer);

 return(TRUE);
}


INT2 VIDEO_gerwindow_swap_in(coli,colf,lini,linf,num_imagem)
INT2         coli, colf,
             lini, linf,
             num_imagem;
{
 char         *buffer;
 INT2         arquivo,indice,
              real_arquivo,tamreg;
 IDE_ARQUIVOS *workifil;

#ifndef _VIDEO_TRANSAC
 indice       = CTREE_keynm(VIDEO_GERAIS_indice_gerwin);
 arquivo      = CTREE_keyfil(indice);
 real_arquivo = CTREE_tmpfil(arquivo);
 workifil     = CTREE_ifilend(arquivo);

 ATIVA_BUF_DADOS;
 CTREE_inbuf(arquivo);
 VD_GETBUF(VIDEO_CARGA_CRG_tipoobj,WORD) = num_imagem;

 if (CTREE_find(indice,VD_NULO,
                FIND_IGUAL,CT_LE_EXTRA_REPASSA) != FALSE)
    return(FALSE);
    
 tamreg = VD_GETBUF(VIDEO_CARGA_CRG_tamext,WORD);

 if (VIDEO_ALLOC_MEM(buffer,tamreg) == VIDEO_NULO)
    {
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_4_PUSHWIN);
     return(FALSE);
    }

 if (DATABASE_ReReadVRecord(real_arquivo, buffer ,tamreg))
    {
     VIDEO_FREE_ALLOC_MEM(buffer);
     return(FALSE);
    }

 VIDEO_grvtela(coli,colf,lini,linf,buffer+workifil->dreclen);

 VIDEO_FREE_ALLOC_MEM(buffer);
#endif
 return(TRUE);
}
#endif

