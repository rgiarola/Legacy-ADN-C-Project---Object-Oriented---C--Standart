#include <INCVIDEO.H>

// Estruturas e variaveis de arquivo.
#include "buffers.h"
#include "arquivos.h"

/* ============================================================================
                            Inicio da Funcao main()
   ============================================================================ */
// Operacao de Cores.
#define ATR_PLANO FORMATO(AzulCel, Bril, AzulTurq, Normal)
#define ATR_OPER  FORMATO(AzulTurq, Bril, Branco, Normal)

main (argc,argv)
int argc;
TEXT *argv[];
{
    register int count;
    int salva_last_pos_x, salva_last_pos_y;
    int arquivo;
    char texto[80];

    if(CTREE_inicializa( &definicao_doda[0], &definicao_arquivos[0] )<I(0))
        {
            printf("\nINVALIDA INICIALIZACAO EXTENDIDO CTREE");
            exit( 1 );
        }

    // Inicializa o sistema para o uso do C-tree.
    if( CTREE_open() )
        {
            printf("INICIALIZACAO DE SISTEMA COM ERRO - SISTEMA FINALIZADO!!!");
            exit( 1 );
        }

    if ( (arquivo = CTREE_filnm("CLIENTES")) < 0 )
        {
            printf("NUMERO DO ARQUIVO NAO PODE SER CONSEGUIDO. SISTEMA FINALIZADO");
        }
    else
        {
            CTREE_inbuf(arquivo);     // Inicializa o Buffer de Dados.
            ARQ_A01[0].A01_tipo   = 'F';

            strcpy( &ARQ_A01[0].A01_endereco[0],"RUA MONTE SIMPLON 924/303");
            strcpy( &ARQ_A01[0].A01_bairro[0],  "NOVA SUISSA" );
            strcpy( &ARQ_A01[0].A01_cidade[0],  "BELO HORIZONTE" );
            strcpy( &ARQ_A01[0].A01_estado[0],  "MG" );
            ARQ_A01[0].A01_cep      = 3046070UL;
            ARQ_A01[0].A01_telefone = 3348475UL;
            ARQ_A01[0].A01_cep = 3046070UL;
            strcpy( &ARQ_A01[0].A01_historico[0], "SISTEMA TESTES CTREE" );

            ARQ_A01[0].A01_codigo = 1UL;
            while( ARQ_A01[0].A01_codigo < 500UL )
                {

                    // Prepara o campo para gravacao.
                    setmem( &ARQ_A01[0].A01_razao[0],
                            sizeof(ARQ_A01[0].A01_razao),  ' ' );
                    ultoa( ARQ_A01[0].A01_codigo, &ARQ_A01[0].A01_razao[0], 10);

                    count=0;
                    while( ARQ_A01[0].A01_razao[count++]!='\0' );
                    setmem( &ARQ_A01[0].A01_razao[count-1], 35-count-1, ' ');
                    ARQ_A01[0].A01_razao[35]='\0';


                    if( CTREE_adrec(arquivo) != 0 )
                        {
                            sprintf(texto,"ATENCAO!!! ERRO EM ARQUIVO %d %d",
                            isam_err, isam_fil);
                            printf("\n\n%s",texto);
                            break;
                        }

                    ++(ARQ_A01[0].A01_codigo);

                }

        }


    CLISAM();                  // Fecha os arquivos.

    return 0;
}

