/* ============================================================================
  create:       Cria os arquivos de dados e indices
                especificados pelo arquivo de parametro.
                <<<< Esta funcao tambem inicializa o sistema. >>>>
   ============================================================================ */
#include <INCVIDEO.H>

INT2 pcreate(arquivo_parametros)
char *arquivo_parametros;
{
	if ( DATABASE_CreateISAM(arquivo_parametros) )	 /* Nome do arquivo de parametros.*/
        terminate("IMPOSSIBILIDADE DE CRIAR ARQUIVOS E/OU INDICES");
    else
      printf("\nSUCESSO EM CRIACAO DE ARQUIVOS E INDICES");

    return 0;
}

