/* ============================================================================ 
   CTREE_filnm()  - Dado o nome do arquivo, esta funcao retorna o numero ctree
                    do arquivo.
   PARAMETROS:      Nome do arquivo
                    Path:    TRUE->Com path      FALSE-> Extrai a PATH do nome.
   RETORNA:         O ctree numero do arquivo, em erro retorna um numero
                    negativo.
   ============================================================================ */
#include <INCVIDEO.H>

INT2   CTREE_filnm(nome_arquivo,path)
char   *nome_arquivo;
INT2   path;
{
 IDE_TABREFERDODA *elemento;

 if (!nome_arquivo)
    return( I(-1) );

 if ((elemento = VIDEO_elemento_tabrefer(nome_arquivo,path ? 5 : 1)) ==
     VD_NILL(IDE_TABREFERDODA))
     return( I(-2) );

 return(elemento->numero);
}

/*
 IDE_ARQUIVOS **auxifil;
 char           aux_nome[128],
                arq_nome[128];
 INT2            posicao;

 if (!nome_arquivo)
    return( I(-1) );

 auxifil = ATIVO_IFIL;
 while (*auxifil)
   {
    if (!path)
       {
        strcpy( aux_nome,(*auxifil)->pfilnam );
        posicao = strlen (aux_nome)-1;
        while(posicao>=0)
          {
           if ( aux_nome[posicao] == DEFAULT_PATH_BARRA )
               break;
           --posicao;
          }
        if (posicao)
           ++posicao;
        strcpy( arq_nome, &aux_nome[posicao] );
       }
     else
       strcpy( arq_nome, (*auxifil)->pfilnam );

    if( !strcmp( arq_nome, nome_arquivo) )
         return( (*auxifil)->dfilno );

    ++auxifil;
   }

 return( I(-2) );
*/

