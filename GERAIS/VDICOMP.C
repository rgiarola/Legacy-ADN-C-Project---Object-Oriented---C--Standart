#include <INCVIDEO.H>

/*============================================================================
# FUNCAO    :  icomp()
#=============================================================================
# Descricao :  Funcao de comparacao de chaves ou valores do tipo long int
# Nota      :  NAO HA TESTE DE PARAMETROS, UTILIZADA EM PESQUISA BINARIA.
# tipo      :  PADRAO aplicavel a qualquer programa.
#
# Parametros:  chave   => pointer do tipo int, indica a localizacao 
#                         da chave na memoria.
#              par1    => pointer do tipo int, indica a localizacao 
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

INT2 VIDEO_Icomp(chave,par1,tchave)
INT2  *chave,
     *par1,
     tchave;
{
 return(I(I(*chave)-I(*par1)));
}
