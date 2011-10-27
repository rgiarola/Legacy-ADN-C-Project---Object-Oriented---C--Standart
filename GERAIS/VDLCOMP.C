#include <INCVIDEO.H>

/*============================================================================
# FUNCAO    :  Lcomp()
#=============================================================================
# Descricao :  Funcao de comparacao de chaves ou valores do tipo long INT2
# Nota      :  NAO HA TESTE DE PARAMETROS, UTILIZADA EM PESQUISA BINARIA.
# tipo      :  PADRAO aplicavel a qualquer programa.
#
# Parametros:  chave   => pointer do tipo long int, indica a localizacao 
#                         da chave na memoria.
#              par1    => pointer do tipo long int, indica a localizacao 
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

INT2 VIDEO_Lcomp(chave,par1,tchave)
long int *chave,
         *par1;
INT2      tchave;
{
 long int ret;
 return((((ret = L(L(*(chave)))) - L(*(par1))) > L(0L) ? I(1) :
          ((ret < L(0L))? I(-1) : I(0))));
}
