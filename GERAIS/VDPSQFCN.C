#include <INCVIDEO.H>

INT2 VIDEO_testa_nome_funcao_pesquisa();

VIDEO_TABFUNCAO *VIDEO_funcao_tabfuncuser(nomefunc)
char *nomefunc;
{
 INT2             numfunc,cont, *tab;
 static INT2      tabfunc[5] = {-1,-1,-1,-1,-1};
 VIDEO_TABFUNCAO *tabfuncuser;

 if (VIDEO_numtabfuncuser <= 0)
    return(VD_NILL(VIDEO_TABFUNCAO));

 for (cont = 0,tab = tabfunc,tabfuncuser = VIDEO_tabfuncuser;
              (cont < 5) && (*tab > -1);tab++,cont++)
      if (!strcmp(nomefunc,(tabfuncuser+*tab)->nomefunc))
         {
          if (cont)
             {
              cont = *tab;
              *tab = *tabfunc;
              *tabfunc = cont;
             }
          return(tabfuncuser+*tabfunc);
         }

 if (VIDEO_pesquisa_binaria((char *) &VIDEO_tabfuncuser[1],&numfunc,
     VIDEO_testa_nome_funcao_pesquisa,VIDEO_numtabfuncuser-1,
     nomefunc,sizeof(VIDEO_TABFUNCAO),sizeof(VIDEO_TABFUNCAO)))
    {
     VIDEO_copbloco(&tabfunc[1],&tabfunc[0],4*sizeof(INT2));
     tabfunc[0] = numfunc+1;
     return(&VIDEO_tabfuncuser[numfunc+1]);
    }

 return(VD_NILL(VIDEO_TABFUNCAO));
}


INT2 VIDEO_testa_nome_funcao_pesquisa(nomefunc,origem,tamanho)
char            *nomefunc;
VIDEO_TABFUNCAO *origem;
INT2             tamanho;
{
 return(strcmp(nomefunc,origem->nomefunc));
}


