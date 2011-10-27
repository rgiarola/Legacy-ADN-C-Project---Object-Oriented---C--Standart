/* ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป
   บ Executa a compilacao de um rtree SCRIPT.                                 บ
   บ COMANDOS DE LINHA:                                                       บ
   บ      RCOMP <Nome do Script> <Nome do OUTPUT Compilado Script>            บ
   บ RETORNA: Zero em Compilacao OK.                                          บ
   บ          Maior que zero em erro.                                         บ
   บ                                                                          บ
   ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ
*/
#include <INCVIDEO.H>   /* Genericas inclusoes para do Sistema ADN.*/
#include "rtdoda.h"

#include "\estoque\include\padroes.h"
#include "\estoque\include\defestoq.h"       /* Definicoes de Estruturas de Estoque.*/
#include "\estoque\include\estproto.h"       /* Prototypes e estruturas externas.*/
#include "\estoque\include\ctbuffer.h"       /* Buffers dos arquivos.*/
#include "\estoque\include\ctarquiv.h"       /* Definicao das estrutura CTREE de arquivos*/

#include "\estoque\include\arvbasic.h"       /* Arvore de Cadastros Basicos.*/
#include "\estoque\include\arvconta.h"       /* Arvore do Contas Pagar e Receber.*/



EXTERN COUNT   isam_err,isam_fil;


main (argc,argv)
INT2        argc;
char      *argv[];
{
	COUNT	c;
    TEXT    rt_script[128],*rt_compilado,*pfn;

	COUNT rtcompiler();

    if (argc < 2)
     {
       printf("\nEntre com o RTREE SCRIPT >> ");
       gets(rt_script);
     }
    else
       ctrt_strcpy(rt_script,*++argv);


    if (argc > 2)
       rt_compilado = *++argv;
	else
       rt_compilado = "RTREE.CMP";


    CTREE_inicializa(&definicao_doda[0], &definicao_arquivos[0] );


    if ( CTREE_open() )
     {
       printf("\nERRO EM ABERTURA DE ARQUIVOS. - SISTEMA TERMINADO");
       printf("\nSTATUS: %d   ARQ:%d",isam_err, isam_fil );
       exit(1);
     }

    /* Funcao de Compilacao.*/
    c = rtcompiler(rt_script, ATIVO_DODA, rt_compilado);


    printf("\nCOMPILACAO TERMINADA... STATUS %d\n",c);
	CLISAM();
    ctrt_exit(c);

}
/* ---- Fim de funcao Compiladora... ------------------------------------------*/

