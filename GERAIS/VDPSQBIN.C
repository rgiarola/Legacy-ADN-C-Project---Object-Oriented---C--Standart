#include <INCVIDEO.H>

/*============================================================================
# FUNCAO    :  pesquisa()
#=============================================================================
# Descricao :  Funcao de pesquisa binaria para qualquer tipo de tabela.
# Nota      :  NAO HA TESTE DE LIMITE DE MEMORIA OU PARAMETROS.
# tipo      :  PADRAO aplicavel a qualquer programa.
#
# Parametros:  celula  => pointer do tipo char, indica a localizcao da tabela
#              medio   => pointer do tipo inteiro, armazenara a localizacao do
#                         item procurado ou a posicao do primeiro item maior.
#              compara_chaves => pointer do tipo int, indica o endereco da
#                                funcao de comparacao.
#              maior   => variavel tipo int, maior indice da tabela.
#              chave   => pointer do tipo char, indica o endereco da chave.
#              tchave  => variavel do tipo int, indica o tamanho da chave.
#              testru  => variavel do tipo int, tamanho da estrutura onde
#                         se localiza a chave.
#
# Retorno   :  TRUE  se encontrar a chave
#              FALSE se nao encontrar
#
# Autor     :  CELSO DE OLIVEIRA
#
# Ultima Revisao :       26/01/90  CELSO DE OLIVEIRA
#===========================================================================*/

INT2 VIDEO_pesquisa_binaria(celula,medio,compara_chaves,maior,chave,tchave,testru)
char      *celula;
INT2       *medio,
          (*compara_chaves)(VD_VOID *origem, VD_VOID *destino, WORD tam),
          maior;
char      *chave;
INT2       tchave,
          testru;
{
 INT2      menor, retorno;
 *(medio) = menor = 0;

 if (maior == 0)
     return(FALSE);

 do
   {
    *(medio)  = (maior + menor) / 2;
    if ((retorno =
		 (*compara_chaves) (chave,(celula + (*(medio) * testru)),tchave)) > 0)
       {
        menor = *(medio);
        if (maior == (*(medio)+1))
           {
            if (!(*compara_chaves)(chave,(celula+(maior*testru)),tchave))
               {
                *(medio) = maior;
                return(TRUE);
               }
            break;
           }
       }
     else
       {
        if (retorno < 0)
           maior = *(medio);
         else
            return(TRUE);
       }
   }while (maior > menor);

 *(medio) += (retorno > 0);
 return (FALSE);
}

