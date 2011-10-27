/* ============================================================================
  initial:      Inicializa o sistema e abre os arquivos
                especificados pelo arquivo de parametro.
                Este ja devem ter sido criados.
   ============================================================================ */
#include <INCVIDEO.H>

INT2 pinitial(arquivo_parametros)
unsigned char *arquivo_parametros;
{

    if ( DATABASE_OpenISAM(arquivo_parametros)) /*Abre o arquivo de parametros.*/
        terminate("\nERRO DE ABERTURA DE ARQUIVO DE PARAMETROS!!!");

	return;
}
