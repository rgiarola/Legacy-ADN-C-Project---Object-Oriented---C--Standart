#include <INCVIDEO.H>

INT2 VIDEO_testa_nome_elemento_tabreferdoda();
INT2 VIDEO_testa_nome_reduzido_tabreferdoda();

extern INT2 VIDEO_tipo_elemento_pesquisado;

IDE_TABREFERDODA *VIDEO_elemento_tabrefer(elemento,tipo)
char *elemento;
INT2  tipo;
{
 INT2             numelem,cont, *tab,tipopesq = FALSE;
 static INT2      tabelem[5] = {-1,-1,-1,-1,-1};
 IDE_TABREFERDODA **tabreferdoda,**tabrefer[2];
 int              (*funcao[2])() = {VIDEO_testa_nome_elemento_tabreferdoda,
                                    VIDEO_testa_nome_reduzido_tabreferdoda};

 tabrefer[0] = VIDEO_tabela_carga;
 tabrefer[1] = VIDEO_tabela_carga_reduzido;

 VIDEO_tipo_elemento_pesquisado = tipo;

 if (tipo == 5)
    {
     tipo = 1;
     tipopesq = TRUE;
    }

 for (cont = 0,tab = tabelem,tabreferdoda = tabrefer[tipopesq];
              (cont < 5) && (*tab > -1);tab++,cont++)
      if (((*(tabreferdoda+*tab))->tipo == tipo) &&
            !strcmp(elemento,tipopesq ? (*(tabreferdoda+*tab))->reduzido :
                                        (*(tabreferdoda+*tab))->nome))
           {
            if (cont)
               {
                cont = *tab;
                *tab = *tabelem;
                *tabelem = cont;
               }
            return(*(tabrefer[tipopesq]+*tabelem));
           }

 if (VIDEO_pesquisa_binaria((char *) tabrefer[tipopesq],&numelem,
     funcao[tipopesq],VIDEO_bufparamarq->numtab-1,
     elemento,sizeof(IDE_TABREFERDODA *),sizeof(IDE_TABREFERDODA *)))
    {
     VIDEO_copbloco(&tabelem[1],&tabelem[0],4*sizeof(INT2));
     tabelem[0] = numelem;
     return(*(tabrefer[tipopesq]+numelem));
    }

 return(VD_NILL(IDE_TABREFERDODA));
}


INT2 VIDEO_testa_nome_elemento_tabreferdoda(elemento,origem,tamanho)
char             *elemento;
IDE_TABREFERDODA **origem;
INT2              tamanho;
{
 INT2 ret,tipo;

 tipo = VIDEO_tipo_elemento_pesquisado;

 if ((ret = tipo - (*origem)->tipo) != 0)
    return(ret);

 return(strcmp(elemento,(*origem)->nome));
}

INT2 VIDEO_testa_nome_reduzido_tabreferdoda(elemento,origem,tamanho)
char             *elemento;
IDE_TABREFERDODA **origem;
INT2              tamanho;
{
 INT2 ret,tipo;

 tipo = 1;

 if ((ret = tipo - (*origem)->tipo) != 0)
    return(ret);

 return(strcmp(elemento,(*origem)->reduzido));
}

