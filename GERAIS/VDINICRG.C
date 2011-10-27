#include <INCVIDEO.H>
 
INT2    VIDEO_testa_nome_elemento();
INT2    VIDEO_testa_nome_reduzido();
VD_VOID VIDEO_scheduler_elemento();

extern IDE_TABREFERDODA **VIDEO_tabela_carga;

INT2 VIDEO_organiza_tabela_de_elemetos()
{
 IDE_TABREFERDODA **tabreferdoda, *tab,**tabrefer[2];
 INT2             cont,contele,conttipo,contitem[3] = {0,0,0};
 int              (*funcao[2])() = {VIDEO_testa_nome_elemento,
                                    VIDEO_testa_nome_reduzido};


 tab = VIDEO_bufparamarq->bufdodas;

 for (contele = 0;contele < VIDEO_bufparamarq->numtab;
                               contele++,tab++)
      tab->postab = contitem[tab->tipo-1]++;

 if (!VIDEO_prepara_tabela_pesq_carga())
    return(FALSE);

 tabrefer[0] = VIDEO_tabela_carga;
 tabrefer[1] = VIDEO_tabela_carga_reduzido;

 for (conttipo = 0;conttipo < 2;conttipo++)
      for (cont = 0;cont < 10;cont++)
          {
           VIDEO_quick_sort(0,
                            VIDEO_bufparamarq->numtab-1,
                            sizeof(IDE_TABREFERDODA *),
                            sizeof(IDE_TABREFERDODA *),
                            0,
                            funcao[conttipo],
                            VIDEO_scheduler_elemento,
                            (BYTE *) tabrefer[conttipo]);

           tabreferdoda = tabrefer[conttipo];

           for (contele = 0;contele < VIDEO_bufparamarq->numtab;
                                         contele++,tabreferdoda++)
               {
                if ((contele + 1) < VIDEO_bufparamarq->numtab)
                   {
                    if (((*tabreferdoda)->tipo - (*(tabreferdoda+1))->tipo) > 0 ||
                       (((*tabreferdoda)->tipo == (*(tabreferdoda+1))->tipo) &&
                       (!conttipo ? strcmp((*tabreferdoda)->nome,
                                    (*(tabreferdoda+1))->nome) > 0 :
                                    strcmp((*tabreferdoda)->reduzido,
                                    (*(tabreferdoda+1))->reduzido) > 0)))
                       if (cont == 9)
                           return(FALSE);
                         else
                           break;
                   }
               }

           if (contele == VIDEO_bufparamarq->numtab)
              break;
          }

 return(TRUE);
}

INT2 VIDEO_testa_nome_elemento(destino,origem,tamanho)
IDE_TABREFERDODA **destino,
                 **origem;
INT2              tamanho;
{
 INT2 ret;

 if ((ret = (*destino)->tipo - (*origem)->tipo) != FALSE)
    return(ret);
 return(strcmp((*destino)->nome,(*origem)->nome));
}

INT2 VIDEO_testa_nome_reduzido(destino,origem,tamanho)
IDE_TABREFERDODA **destino,
                 **origem;
INT2              tamanho;
{
 INT2 ret;

 if ((ret = (*destino)->tipo - (*origem)->tipo) != FALSE)
    return(ret);
 return(strcmp((*destino)->reduzido,(*origem)->reduzido));
}

VD_VOID VIDEO_scheduler_elemento(destino,origem)
IDE_TABREFERDODA **destino,
                 **origem;
{
 IDE_TABREFERDODA *elemento;
 elemento = *origem;
 *origem = *destino;
 *destino = elemento;
}

VIDEO_prepara_tabela_pesq_carga()
{
 IDE_TABREFERDODA **tab_elemento,
                  **tab_reduzido,
                  *elemento;
 INT2              cont;

 if ((VIDEO_tabela_carga = (IDE_TABREFERDODA **)
      VIDEO_alloc_parametros(
           VIDEO_bufparamarq->numtab*sizeof(IDE_TABREFERDODA *))) == VD_NULO)
     return(FALSE);

 if ((VIDEO_tabela_carga_reduzido = (IDE_TABREFERDODA **)
      VIDEO_alloc_parametros(
           VIDEO_bufparamarq->numtab*sizeof(IDE_TABREFERDODA *))) == VD_NULO)
    {
     VIDEO_FREE_ALLOC_MEM(VIDEO_tabela_carga);
     VIDEO_tabela_carga = VD_NULO;
     return(FALSE);
    }

 cont = 0;
 tab_elemento = VIDEO_tabela_carga;
 tab_reduzido = VIDEO_tabela_carga_reduzido;
 elemento     = VIDEO_bufparamarq->bufdodas;
 do
  {
   *tab_elemento = *tab_reduzido = elemento;
   ++elemento;
   ++tab_elemento;
   ++tab_reduzido;
  }while(++cont < VIDEO_bufparamarq->numtab);

 return(TRUE);
}

