/*----------------------------------------------------------------------------
                        EXTRUTURA DE CONTROLE DE ANALISE
----------------------------------------------------------------------------*/
typedef struct
 {
  char  **tabela;
  int   tipoobjeto;
 }VIDEO_MCLIN_CTRL_ANALISE;

/*----------------------------------------------------------------------------
                       EXTRUTURA DE CONTROLE DE LEITURA
----------------------------------------------------------------------------*/
struct VIDEO_MCLIN_CTRL_FONT
 {
  char	*buffer_leitura,
        *origem,*linha;
  DWORD posicao;
  int	descritor,
        lido,posbuffer,
        poslinha ,coment;
  WORD  flags;
  VIDEO_MCLIN_CTRL_FONT *proximo,
                           *anterior;
 };

/*----------------------------------------------------------------------------
                       EXTRUTURA DE CONTROLE DE COMPILACAO
----------------------------------------------------------------------------*/
typedef struct
 {
  INT2   (*gerador_compilacao)();
  struct VIDEO_MCLIN_CTRL_FONT fonte;
  BYTE   flagdef[10],
         definicao[10];
  VIDEO_MCLIN_CTRL_ANALISE *analise;
  WORD   requisitante;
 }VIDEO_MCLIN_CTRL_COMP;

/*----------------------------------------------------------------------------
                      OBJETOS POSSIVEIS DA LINHA DE COMANDO
----------------------------------------------------------------------------*/

#define    VIDEO_LINGUAGEM_DELIMITADOR 1
#define    VIDEO_LINGUAGEM_SEPARADOR   2
#define    VIDEO_LINGUAGEM_OPERLOGICO  3
#define    VIDEO_LINGUAGEM_OPERARIT    4
#define    VIDEO_LINGUAGEM_TIPOSCAMPOS 5
#define    VIDEO_LINGUAGEM_COMANDOS    6
#define    VIDEO_LINGUAGEM_REFERENCIA  7
#define    VIDEO_LINGUAGEM_VARIAVEL    8
#define    VIDEO_LINGUAGEM_OPERANDO    9

/*----------------------------------------------------------------------------
                            FLAGS DO ANALIZADOR LEXICO
----------------------------------------------------------------------------*/
#define    VIDEO_MCLIN_OPEN            VD_B0
#define    VIDEO_MCLIN_POSICIONA       VD_B1
#define    VIDEO_MCLIN_ALLOC_MEM       VD_B2
#define    VIDEO_MCLIN_FIM_ARQ         VD_B3
#define    VIDEO_MCLIN_LEU_LINHA       VD_B4
#define    VIDEO_MCLIN_TERMINA         VD_B5
#define    VIDEO_MCLIN_LER_BUFFER      VD_B6

/*----------------------------------------------------------------------------
                         SERVICOS DO NUCLEO ANALIZADOR
----------------------------------------------------------------------------*/
#define    VIDEO_MCLIN_INICIO_COMPILACAO   1
#define    VIDEO_MCLIN_PEGA_LINHA          2
#define    VIDEO_MCLIN_FILTRA_FASE_1       3
#define    VIDEO_MCLIN_TRATA_ERROS         4

#define    VIDEO_MCLIN_ANALIZA_LINHA       1
#define    VIDEO_MCLIN_FIM_COMPILACAO      3
#define    VIDEO_MCLIN_GRAVA_LINHA         4
#define    VIDEO_MCLIN_INCLUDE_ARQUIVO     5
#define    VIDEO_MCLIN_INICIO_COMENTARIO   6
#define    VIDEO_MCLIN_COMENTARIO_LINHA    7
#define    VIDEO_MCLIN_COMENTARIO          8
#define    VIDEO_MCLIN_ERRO_COMENTARIO     9
#define    VIDEO_MCLIN_FIM_COMENTARIO      10
#define    VIDEO_MCLIN_FIM_COMPILACAO_ERRO 11
#define    VIDEO_MCLIN_INICIO_DEFINICAO    12
#define    VIDEO_MCLIN_FIM_DEFINICAO       13
#define    VIDEO_MCLIN_ERRO_DEFINICAO      14
#define    VIDEO_MCLIN_INICIO_NAODEFINICAO 15

#define    VIDEO_ERRO_LING_tamanho_1  -1000
#define    VIDEO_ERRO_LING_analise_1  -1001
#define    ALOCACAO_PREP_VIDEO_MCLIN_1 -1002


extern int  VIDEO_MCLIN_desc_arq;
extern char VIDEO_MCLIN_nome_arq[];
extern char VIDEO_texto_linguagem[];

extren char *VIDEO_LINGUAGEM_tabela_comandos[],
            *VIDEO_LINGUAGEM_tabela_operlogic[],
            *VIDEO_LINGUAGEM_tabela_operarit[],
            *VIDEO_LINGUAGEM_tabela_separadores[],
            *VIDEO_LINGUAGEM_tabela_delimitadores[],
            *VIDEO_LINGUAGEM_tabela_tipodados[],
            *VIDEO_LINGUAGEM_tabela_referencia[];

char *VIDEO_MCLIN_pega_linha(VIDEO_MCLIN_STR_EXPAND *expande);
char *VIDEO_MCLIN_filtra_linha(VIDEO_MCLIN_STR_EXPAND *expande);
