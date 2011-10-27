
#define VIDEO_LOGIC_LINHA_NULA      1
#define VIDEO_LOGIC_PRIMEIRO_OPER   2
#define VIDEO_LOGIC_SEGUNDO_OPER    3
#define VIDEO_LOGIC_INCPER          4
#define VIDEO_LOGIC_INCSTRING       5
#define VIDEO_LOGIC_DIVZERO         6
#define VIDEO_LOGIC_DESCOPER        7
#define VIDEO_LOGIC_DODANDEF        8
#define VIDEO_LOGIC_ALLOCMEM        9
#define VIDEO_LOGIC_TIPODODA        10
#define VIDEO_LOGIC_TIPOBJETO       11
#define VIDEO_LOGIC_STRING          12
#define VIDEO_LOGIC_PARENTESES      13
#define VIDEO_LOGIC_OPERADOR_DIF    14
#define VIDEO_LOGIC_OPERADOR_IGUAL  15
#define VIDEO_LOGIC_OPERADOR_AND    16
#define VIDEO_LOGIC_OPERADOR_OU     17
#define VIDEO_LOGIC_FIM_INESPERADO  18
#define VIDEO_LOGIC_POTENCIAINV     19

/*----------------------------------------------------------------------------
                        EXTRUTURA DE CONTROLE DE ANALISE
----------------------------------------------------------------------------*/
typedef struct
 {
  int	tipoobjeto,
		grupo,
        nivel;
  char	objeto[21];
 }VIDEO_LOGIC_OBJETO;

/*----------------------------------------------------------------------------
                      OBJETOS POSSIVEIS DA LINHA DE COMANDO
----------------------------------------------------------------------------*/

#define VIDEO_LOGIC_OPERLOGICO_MAIOR   1 // >
#define VIDEO_LOGIC_OPERLOGICO_MAIORI  2 // >=
#define VIDEO_LOGIC_OPERLOGICO_MENOR   3 // <
#define VIDEO_LOGIC_OPERLOGICO_MENORI  4 // <=
#define VIDEO_LOGIC_OPERLOGICO_IGUAL   5 // ==
#define VIDEO_LOGIC_OPERLOGICO_DIFER   6 // !=
#define VIDEO_LOGIC_OPERLOGICO_AND	   7 // &&
#define VIDEO_LOGIC_OPERLOGICO_OR	   8 // ||
#define VIDEO_LOGIC_CONST_STRING	   9 // "
#define VIDEO_LOGIC_CONST_NUMERICA     10 // 9-0
#define VIDEO_LOGIC_OPERARIT_EXP       11 // ^
#define VIDEO_LOGIC_OPERARIT_RESTO     12 // %
#define VIDEO_LOGIC_OPERARIT_RAIZ	   13 // ##
#define VIDEO_LOGIC_OPERARIT_SQRT      14 // #
#define VIDEO_LOGIC_OPERARIT_INT       15 // %%
#define VIDEO_LOGIC_OPERARIT_DECIMAL   16 // ~
#define VIDEO_LOGIC_OPERARIT_SOMA      17 // +
#define VIDEO_LOGIC_OPERARIT_SUB       18 // -
#define VIDEO_LOGIC_OPERARIT_MULT      19 // *
#define VIDEO_LOGIC_OPERARIT_DIVISAO   20 // /
#define VIDEO_LOGIC_DODA               21 // var
#define VIDEO_LOGIC_RETORNO            22 // RETORNO DE OPERACAO
#define VIDEO_LOGIC_NUMERO_CONV        23 // 9-0

/*----------------------------------------------------------------------------
		      GRUPOS DE OBJETOS PARA ANALISE
----------------------------------------------------------------------------*/
#define VIDEO_LOGIC_OPERARIT_NIVEL1    1
#define VIDEO_LOGIC_OPERARIT_NIVEL2    2
#define VIDEO_LOGIC_OPERARIT_NIVEL3    3
#define VIDEO_LOGIC_OPERLOGIC          4
#define VIDEO_LOGIC_PORTALOGIC         5
#define VIDEO_LOGIC_CONST              6
#define VIDEO_LOGIC_VAR                7

#define RETLOGIC(retorno)              CDOUBLE(retorno->objeto)


int VIDEO_LOGIC_consiste_operacao(VIDEO_LOGIC_OBJETO *work,
				  VIDEO_LOGIC_OBJETO *inicio,
				  VIDEO_LOGIC_OBJETO *elemento,
				  char **var1,char **var2);

int VIDEO_LOGIC_analise_expresao(char *expresao,VIDEO_LOGIC_OBJETO *retorno,
                                 VIDEO_LOGIC_OBJETO **objetos,int nivel);

int VIDEO_LOGIC_analise_logica(VIDEO_LOGIC_OBJETO *inicio,
                               VIDEO_LOGIC_OBJETO **elemento,
							   VIDEO_LOGIC_OBJETO *retorno);

int VIDEO_LOGIC_testa_numero(char *n);

int VIDEO_LOGIC_compara_numero(char *n1,char *n2);

int VIDEO_LOGIC_converte_operando(VIDEO_LOGIC_OBJETO *objeto,
								  char				 **ptr);

int VIDEO_LOGIC_analise(char *linha,VIDEO_LOGIC_OBJETO *retorno);

VD_VOID VIDEO_LOGIC_retira_numero(VIDEO_LOGIC_OBJETO *objeto,char **expresao);

extern VIDEO_LOGIC_OBJETO *VIDEO_LOGIC_objetos;

extern int                VIDEO_LOGIC_erro_float_;

VD_VOID VIDEO_LOGIC_float_error(VD_VOID);

