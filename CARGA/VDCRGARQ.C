#include <INCVIDEO.H>

VD_VOID VIDEO_scheduler_doda(/*IDE_DODA *dodaori,IDE_DODA *dodadest*/);

INT2 VIDEO_testa_nome_doda(/*IDE_DODA *dodadest,IDE_DODA *dodaori,WORD tamanho*/);

VIDEO_CTRL_CARGA         *VIDEO_ctrl_carga   = VD_NULO;
VIDEO_IMAGEMTELA         *VIDEO_imagem_atual = VD_NULO;
VIDEO_TELA_ENTRADA_DADOS *VIDEO_tela_atual   = VD_NULO;
VIDEO_CAMPO_CONSISTENCIA *VIDEO_cons_atual   = VD_NULO;
VIDEO_CAMPO_TELA         *VIDEO_campo_atual  = VD_NULO;
char                     *VIDEO_doda_campo   = VD_NULO;

INT2 VIDEO_cargaarq(tabreferbuffer,arqcarga,arqpath)
IDE_TABREFERBUFFER *tabreferbuffer;
char               *arqcarga,
                   *arqpath;
{
 INT2             descscript,cont, ret,
                  numarq,tampath,contarq,conttab;
 long int         tamarq,filelength();
 char             path[102],*buffer;
 IDE_ARQUIVOS     *arquivos;
 IDE_TABREFERDODA *work;

 if ((descscript = VIDEO_open_ler(arqpath)) <= 0)
     return(VIDEO_ERRO_carga_open_arq_path);

 if (((tamarq = filelength(descscript)) <= 0) || (tamarq > 100L))
    {
     VIDEO_close(descscript);
     return(VIDEO_ERRO_carga_tam_arq_path);
    }

 if (VIDEO_read(descscript,path,I(tamarq)) != I(tamarq))
    {
     VIDEO_close(descscript);
     return(VIDEO_ERRO_carga_read_arq_path);
    }

 VIDEO_close(descscript);

 path[I(tamarq)] = 0;
 for (cont = 0;path[cont];cont++)
     if (path[cont] == C(0X0D) || path[cont] == C(0X0A))
        {
         path[cont] = 0;
         tamarq = cont;
         break;
        }

 if (path[tamarq-1] != '\\')
    {
     path[tamarq] = '\\',
     path[tamarq+1]   = 0;
    }
 tampath = strlen(path)+1;

 if ((descscript = VIDEO_open_ler(arqcarga)) < 0)
     return(VIDEO_ERRO_carga_oper_arq_crg);
 
 if ((tamarq = filelength(descscript)) <= 0)
	{
     VIDEO_close(descscript);
     return(VIDEO_ERRO_carga_ler_arq_crg);
	}

 if (VIDEO_read(descscript,&numarq,sizeof(INT2)) != sizeof(INT2))
    {                                                  VIDEO_close(descscript);
     return(VIDEO_ERRO_carga_tam_arq_crg);
	}

 /*
 L¢gica: Utiliza‡„o Antiga ...
 */
 if ((VIDEO_bufparamarq = VIDEO_alloc_parametros(
                                W(tamarq)+(tampath*numarq+numarq*8))) == FALSE)
	{
     VIDEO_mostra_mens_erro_alloc(ALOCACAO_1_CARGAARQ);
     VIDEO_close(descscript);
     return(VIDEO_ERRO_carga_alloc_arq_crg);
	}


 /*
   L¢gica ADNMEM
 if ((ret=AdnMemAlocPool (DW (W(tamarq)+(tampath*numarq+numarq*8)),
                          (void **) &VIDEO_bufparamarq))!=FALSE)
    {
     if ((VIDEO_bufparamarq = VIDEO_alloc_parametros(
                                    W(tamarq)+(tampath*numarq+numarq*8))) == FALSE)
        {
         VIDEO_mostra_mens_erro_alloc(ALOCACAO_1_CARGAARQ);
         VIDEO_close(descscript);
         return(VIDEO_ERRO_carga_alloc_arq_crg);
        }
    }

 // printf ("\n (%p) ",VIDEO_bufparamarq); getch();
 */

 VIDEO_setmem(VIDEO_bufparamarq,W(tamarq)+(tampath*numarq+numarq*8),0);


 VIDEO_lseek(descscript,VIDEO_INI_ARQ,0L);
 if (VIDEO_read(descscript,VIDEO_bufparamarq,W(tamarq)) != W(tamarq))
	{
     VIDEO_close(descscript);
     VIDEO_free_alloc_parametros(VIDEO_bufparamarq);
     return(VIDEO_ERRO_carga_arq_crg);
	}

 VIDEO_close(descscript);

 VIDEO_bufparamarq->arquivos = VIDEO_TAB_ARQ;
 VIDEO_bufparamarq->indices  = VIDEO_TAB_IND;
 VIDEO_bufparamarq->chaves   = VIDEO_TAB_CHV;
 VIDEO_bufparamarq->dodas    = VIDEO_TAB_DODA;
 VIDEO_bufparamarq->bufdodas = VIDEO_TAB_TAB;
 // printf ("\n 1 "); getch();
 VIDEO_inicarqnome();
 // printf ("\n 2 "); getch();
 VIDEO_inicdodanome();
 // printf ("\n 3 "); getch();
 VIDEO_inictabref();

 // printf ("\n 4 "); getch();
 buffer = PTR_CAST(char,VIDEO_bufparamarq) + tamarq;
 arquivos = VIDEO_bufparamarq->arquivos;
 for (contarq = 0;contarq < VIDEO_bufparamarq->numarq &&
                  arquivos->pfilnam;contarq++,arquivos++)
     {
	  work = VIDEO_bufparamarq->bufdodas;
      if (memcmp(arquivos->pfilnam,CT_TEMPOR,CT_TEMPOR_TAM))
          for (conttab = 0;conttab < VIDEO_bufparamarq->numtab;conttab++,work++)
              {
               if (work->tipo == 1 &&
                   !strcmp(arquivos->pfilnam,work->reduzido))
                  {
                   if (*(arquivos->pfilnam-1) == 'D')
                      {
                       strcpy(buffer,path);
                       strcat(buffer,arquivos->pfilnam);
                       arquivos->pfilnam = work->nome = buffer;
                       buffer += (strlen(buffer)+1);
                      }
                   break;
                  }
              }
	 }


 // printf ("\n 5 "); getch();
 VIDEO_prepara_tabela_pesq_doda();

 // printf ("\n 6 "); getch();
 for (ret = 0;ret < 10;ret++)
     {
	  if (VIDEO_bufparamarq->numdoda > 1)
		  VIDEO_quick_sort(0,VIDEO_bufparamarq->numdoda-1,sizeof(IDE_DODA *),
					   sizeof(IDE_DODA *),0,
					   VIDEO_testa_nome_doda,
					   VIDEO_scheduler_doda,
					   (BYTE *) VIDEO_tabela_doda);
		else
          break;

	  for (cont = 0;cont < VIDEO_bufparamarq->numdoda;cont++)
		   if ((cont + 1) < VIDEO_bufparamarq->numdoda)
               if (strcmp((*(VIDEO_tabela_doda+cont))->fsymb,(*(VIDEO_tabela_doda+cont+1))->fsymb) > 0)
				  if (ret == 9)
					 {
					  VIDEO_freecarga();
                      return(VIDEO_ERRO_carga_sort_doda);
					 }
				   else
					 break;

      if (cont == VIDEO_bufparamarq->numdoda)
		 break;
     }

 // printf ("\n 7 "); getch();
 if ((ret = VIDEO_inicdodabuf()) != FALSE)
    {
     VIDEO_free_alloc_parametros(VIDEO_bufparamarq);
     return(ret);
	}

 // printf ("\n 8 "); getch();
 if (tabreferbuffer)
     while(tabreferbuffer->referencia)
      {
       IDE_TABREFERDODA *work;
       BOOLEAN          flag;

       work = VIDEO_bufparamarq->bufdodas;

       flag = FALSE;
       while(work->nome)
        {
         if (!strcmp(work->reduzido,tabreferbuffer->referencia))
            {
             *(tabreferbuffer->buffer) = work->buffer;
             flag = TRUE;
             break;
            }
         ++work;
        }

       if (!flag)
          {
           char   buffer[200];
           sprintf(buffer,VIDEO_CARGA_mens_elem_struct,
                   tabreferbuffer->referencia);
           VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_carga_end_estru_elem);
           VIDEO_freecarga();
           return(VIDEO_ERRO_carga_end_estru_elem);
          }
       ++tabreferbuffer;
      }

 // printf ("\n 9 "); getch();
 if (!VIDEO_organiza_tabela_de_funcoes())
    {
     VIDEO_mostra_mens_erro(VIDEO_erro_sort_func,
                            VIDEO_ERRO_tab_func_nao_ordenada);
     VIDEO_freecarga();
     return(VIDEO_ERRO_tab_func_nao_ordenada);
    }

 if (!VIDEO_organiza_tabela_de_elemetos())
    {
     VIDEO_mostra_mens_erro(VIDEO_erro_sort_elem,
                            VIDEO_ERRO_tab_elem_nao_ordenada);
     VIDEO_freecarga();
     return(VIDEO_ERRO_tab_elem_nao_ordenada);
    }

 randomize();

 VIDEO_save_screen = VIDEO_save_screen_default;
 // printf ("\n 10 FIM"); getch();

 return(FALSE);
}

int VIDEO_prepara_tabela_pesq_doda(VD_VOID)
{
 IDE_DODA **tabela_doda,
           *doda;
 INT2       cont,ret;


// if ((ret=AdnMemAlocPool (VIDEO_bufparamarq->numdoda*sizeof(IDE_DODA *),
//                          &doda))!=FALSE)
//    {
     if ((VIDEO_tabela_doda = (IDE_DODA **)
          VIDEO_alloc_parametros(VIDEO_bufparamarq->numdoda*
                                 sizeof(IDE_DODA **))) == VD_NULO)
        {
         VIDEO_mostra_mens_erro_alloc(ALOCACAO_2_CARGAARQ);
         VIDEO_freecarga();
         return(-8);
        }
//    }
//  else
//    {
//     VIDEO_tabela_doda = (IDE_DODA **)doda;
//    }

 cont = 0;
 tabela_doda = VIDEO_tabela_doda;
 doda = VIDEO_bufparamarq->dodas;
 do
  {
   *tabela_doda = doda;
   ++doda;
   ++tabela_doda;
  }while(++cont < VIDEO_bufparamarq->numdoda);

 return(FALSE);
}

VD_VOID VIDEO_scheduler_doda(dodadest,dodaori)
IDE_DODA **dodadest,
         **dodaori;
{
 IDE_DODA *doda;
 doda = *dodadest;
 *dodadest = *dodaori;
 *dodaori = doda;
}

INT2 VIDEO_testa_nome_doda(dodadest,dodaori,tamanho)
IDE_DODA **dodadest,
         **dodaori;
WORD     tamanho;
{
 return(strcmp((*dodadest)->fsymb,(*dodaori)->fsymb));
}
