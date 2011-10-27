#include <INCVIDEO.H>

/*============================================================================
# FUNCAO    :  Dcomp()
#=============================================================================
# Descricao :  Funcao de comparacao de chaves ou valores do tipo double
# Nota      :  NAO HA TESTE DE PARAMETROS, UTILIZADA EM PESQUISA BINARIA,
#              TRABALHA COM VALORES COM NO MAXIMO 14 CASAS DECIMAIS;       
# tipo      :  PADRAO aplicavel a qualquer programa.
#
# Parametros:  chave   => pointer do tipo double, indica a localizacao 
#                         da chave na memoria.
#              par1    => pointer do tipo double, indica a localizacao 
#                         da chave de teste na memoria.
#              tchave  => variavel do tipo int, indica o tamanho da chave.
#
# Retorno   :  0  se iguais
#              1  se chave maior que chave de teste
#              -1 se chave menor que chave de teste
#
# Autor     :  CELSO DE OLIVEIRA
#
# Ultima Revisao :       26/01/90  CELSO DE OLIVEIRA
#===========================================================================*/

INT2 VIDEO_Dcomp(chave,par1,tchave)
double *chave,
       *par1;
INT2    tchave;
{
 double ret;
 return(((ret = D(D(*(chave)) - D(*(par1)))) > D(0.01)) ? 1:
        ((ret > D(-0.01)) ? 0:-1));
}
