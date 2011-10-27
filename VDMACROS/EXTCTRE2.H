/* ============================================================================
   EXTCTRE2.H   -   Arquivo de definicoes e variaveis de controle para uso
                    da biblioteca extendida de funcoes c-tree.

   M O D U L O        M U L T I      U S U A R I O

   ============================================================================ */
#define ctLP
#define CTREE_MULTI_USER    // Ctre Multi-usuario
#define CTREE_RTREE_ATIVO

                           /*Numero Maximo de Ifil para EXTCTREE*/
#define CTREE_MAXFIL      (53)

/* <<<<<<     Header Files Ctree - Inclusao Obrigatoria.    >>>>>*/
/*
  Nova Vers„o
#include "ctreep.h"
 */

#include "ctstdr.h"     // Turbo C - Header's: <dos.h>   / <alloc.h> / <stdio.h>
                        //                     <fcntl.h>

#include "ctoptnr.h"    // Arquivo de configuracao c-tree R E D E

#include "ctaerr.h"     // Variaveis globais, e codigos de manipulacao de erro.
#include "ctdecl.h"     // Prototipos das funcoes c-tree.
#include "cterrc.h"     // Meneomonicos dos codigos de erro.

#ifdef  ctNOGLOBALS             // Dados estaticos do CTREE e RTREE
#define  CTPERM
#include "ctstrc.h"
#include "ctgvar.h"             // Ctree
#undef  CTPERM

extern   CTGVAR  *ctWNGV;       // Header do Ctree
#endif


#ifdef  ctNOGLOBALS             // Dados estaticos do CTREE e RTREE
#define  CTPERM
#include "rtpars.h"
#include "rtstrc.h"      // Rtree
#include "rtgvar.h"

extern   RTGVAR  *rtWNGV;       // Header do Rtree
#undef  CTPERM
#endif

#ifdef   CTREE_RTREE_ATIVO
#include "rtdoda.h"     /* Arquivo de variaveis e estruturas RTREE.*/
#include "rtdecl.h"     /* Simples tipos para operacao.*/
#endif


/* <<<<<<   Definicoes de controle para funcao InitCtree    >>>>>>*/

#ifdef  CTREE_MULTI_USER    /* Determina o bufferiamento local para cada indice.*/
#define CTREE_buffers   I(17)
#else
#define CTREE_buffers   I(17)
#endif

#define CTREE_sects I( 8)    /* Determina o espaco a ser ocupado por no'B-tree.*/
#define CTREE_fils  I(100)   /* Determina o numero maximo de arquivos abertos ao*/
                            /* mesmo tempo.*/


/* =======================================================
    <<<<<<   Rememoracao de expressoes C-tree.   >>>>>>
   ======================================================= */
#define IDE_DODA       DATOBJ       /* Redeclaracao para o DODA.*/
#define IDE_ARQUIVOS   IFIL         /* Redeclaracao para o IFIL.*/
#define IDE_CHAVES     ISEG         /* Redeclaracao para segmentos.*/
#define IDE_INDEX      IIDX         /* Redeclaracao para os indices.*/

/* <<<< Transformacao e/ou manipulacao do segmento de Chave do Index. >>>>*/
#define NORMAL_SEG           REGSEG         /* Normal/Nenhuma Transformacao.*/

#define UCHAR_SEG            DECSEG         /* Segmento Unsigned char.*/
#define CHAR_SEG             BCDSEG         /* Segmento signed char.*/
#define UNSIGNED_CHAVE_SEG   INTSEG         /* Segmento unsigned Inteiro.*/
#define INTEIRO_CHAVE_SEG    SGNSEG         /* Segmento Inteiro c/Sinal.*/
#define AUTO_LONG_SEG        SRLSEG         /* Segmento de Incremento Automatico.*/
#define REAL_CHAVE_SEG       FLTSEG         /* Segmento float ou double.*/
#define STR_UPPER_SEG        UREGSEG        /* Upper alfa caracteres.*/

/* Apenas para campos variaveis de Tamanho -> Nao em uso.*/
#define STR_COMPLETA_SEG     VARSEG        /* Somente Completa para Tamanho.*/
#define STR_COMPLETA_UPPER   UVARSEG       /* Completa e upper alfa caracteres.*/

/* Inverte a tipo de armazenamento em index de ascendente (default),*/
/* para a ordem descendente (atraves da operacao OR).*/
#define DSC_ORDEM            DSCSEG



/* <<<< Definicao de Tipos de armazenamento de Chaves em Index >>>>*/
#define TIPO_NORMAL_CHAVE     I(0)
#define TIPO_ESQUERDA_CHAVE   I(4)
#define TIPO_DIREITA_CHAVE    I(8)
#define TIPO_ESQDIR_CHAVE     I(12)


/* <<<< Definicao de Tipos para controle de arquivos >>>>*/
#define DEFAULT_MODO          (VIRTUAL|FIXED|SHARED)
#define DEFAULT_PERM_MODO     (VIRTUAL|FIXED|EXCLUSIVE)
#define DEFAULT_PERM_IDX_MODO (VIRTUAL|EXCLUSIVE)
#define DEFAULT_EXTENSAO      4096

#define DEFAULT_PATH_BARRA    '\\'



/* =======================================================
    <<<<<<   Estrutura de controle para operacao   >>>>>
    <<<<<<   da estrutura IFIL.                    >>>>>
   ======================================================= */
typedef struct
    {
        INT2           numero;
        WORD           tamanho;
        char           *primeiro_campo;
        IDE_ARQUIVOS   *controle_ctree;
    }   CONTROLE_ARQUIVOS;

/* =======================================================
    <<<<<<   Estrutura para operacao de chaves     >>>>>
    <<<<<<   para o protocolo de leitura.          >>>>>
   ======================================================= */
typedef struct {

    char *pointer;  /* Ponteiro para dado de composicao do segmento.*/
    INT2   tamanho;  /* Tamanho do Segmento.*/
    char  tipo;     /* Tipo do Segmento ( constante, campo constante, campo valor).*/

} VIDEO_SEG_CHAVE;

/* =======================================================
    <<<<<<   Estrutura para transferencia de dados >>>>>
    <<<<<<   via doda origem para doda destino.    >>>>>
   ======================================================= */

 typedef struct
  {
   char *destino,
        *origem;
  }VIDEO_TRANSP_DADOS;


/* ===========================================================================
   Definicao para Arquivos Temporarios.
   =========================================================================== */
#define VD_MAX_TMP            55
#define VD_MAX_TMP_NOME       70
#define CT_TEMPOR             "~"     /* Nome Inicial p/Identificacao Arq's TMP*/
#define CT_TEMPOR_TAM          1      /* Tamanho Base para Identificacao.*/
#define GetTempFileName       TMPNAME

typedef struct   {
   INT2  numero_arquivo;
   char temp_nome[VD_MAX_TMP_NOME];

  } CT_TMP_NOMES;





/* <<< Definicao para os tipos segmentos estrutura VIDEO_SEG_CHAVE. >>>*/
#define CT_SEG_CONST                1
#define CT_SEG_CAMPO_CONST          2
#define CT_SEG_CAMPO                3



/* =======================================================
    <<<<<<   Definicoes para operacao da funcao    >>>>>
    <<<<<<   CTREE_find().                         >>>>>
   ======================================================= */
/* <<< Definicao para o parametro modo_find. >>>*/
#define FIND_PROXIMO                0
#define FIND_ANTERIOR               1
#define FIND_PRIMEIRO               2
#define FIND_ULTIMO                 3
#define FIND_IGUAL                  4
#define FIND_MAIOR                  5
#define FIND_MAIOR_IGUAL            6
#define FIND_MENOR                  7
#define FIND_MENOR_IGUAL            8


/* <<< Definicao para o parametro modo_leitura. >>>*/
#define CT_LE_DADOS                 0
#define CT_LE_EXTRA                 1
#define CT_LE_EXTRA_REPASSA         2


/*  ================================================================
    Numero indexador de controle para o buffer de dados.
    --->    Esta variavel controle qual dos dois buffer's de dados
            estara ativo para a leitura e/ou operacao em arquivo de
            dados.
    ================================================================ */
extern  INT2 ATUAL_NO_BUFFER;
/* Constantes para manipulacao ATUAL_NO_BUFFER*/
#ifdef  CTREE_MULTI_USER           /* Minimo numero de buffer's por arquivo.*/

 #ifdef      BUFFER_EXTRA_DISABLE
 #define     MIN_BUFFERS     2
 #else
 #define     MIN_BUFFERS     3
 #endif

#else

 #ifdef      BUFFER_EXTRA_DISABLE
 #define     MIN_BUFFERS     1
 #else
 #define     MIN_BUFFERS     2
 #endif

#endif  /* Ctree Multi-usuario.*/




#define     BUFFER_DADOS      0    /* Buffer para manipulacao de dados.*/
#define     BUFFER_EXTRA      1    /* Buffer para generico uso da manutencao.*/
#define     BUFFER_ISAM       2    /* Buffer para o current isam record.*/

#define     ATIVA_BUF_DADOS ATUAL_NO_BUFFER=BUFFER_DADOS
#define     ATIVA_BUF_EXTRA ATUAL_NO_BUFFER=BUFFER_EXTRA
#define     ATIVA_BUF_ISAM  ATUAL_NO_BUFFER=BUFFER_ISAM


/* =======================================================
    <<<<<<   Variaveis de Controle e macros para   >>>>>
    <<<<<<   operacao das funcoes extendidas C-tree>>>>>
   ======================================================= */
extern IDE_ARQUIVOS    *ATIVO_IFIL[]; /* Variavel de armazenamento da estrura IFIL.*/
extern IDE_DODA        *ATIVO_DODA; /* Variavel de armazenamento da estrura DODA.*/
extern CONTROLE_ARQUIVOS
        controle_arquivos[];  /* Estrutura auxiliar controle de arquivos.*/

       /* Controle de Nomes de Arquivos Temporarios.*/
extern CT_TMP_NOMES     *CT_arquivos_temporarios;


#define CTREE_NUMMAXSETS       7

extern INT2 CTREE_tabela_set_disp[CTREE_NUMMAXSETS],
           CTREE_num_set_disp;

#define CTREE_ERRO_SET 32768

/* =======================================================
    <<<<<<   Macros de controle para operacao      >>>>>
    <<<<<<   de C-tree                             >>>>>
   ======================================================= */
#define CTREE_logsis()      InitISAM( CTREE_buffers, CTREE_fils, CTREE_sects)


#include <ctree.vdo>    /* Redefine para as funcoes CTREE.*/
#ifndef _VIDEO_TRANSAC
#include <extproto.h>   /* Funcoes Prototype para extendida biblioteca ctree.*/
#endif

#define CTREE_cpydados(numero_arquivo)  CTREE_cpybuf(numero_arquivo, TRUE )
#define CTREE_cpyextra(numero_arquivo)  CTREE_cpybuf(numero_arquivo, FALSE)
#define CTREE_pusharq(x)				CTREE_posicao_arq(x,TRUE,VD_NULO)
#define CTREE_poparq(x,buffer)			CTREE_posicao_arq(x,FALSE,buffer)

#define CTREE_pusharqtest(buffer)       (buffer&&(CDWORD(buffer)!=VD_NULO))

extern BYTE  _log_disable;
extern BYTE  _log_tipo;
extern BYTE  _log_lock;
extern char  _log_obs1[41];
extern char  _log_obs2[41];
extern char  _log_user[21];
extern char  _log_oper[21];
extern char  _log_origem[11];
extern INT2  (*_log_funcao)(int Arquivo);

