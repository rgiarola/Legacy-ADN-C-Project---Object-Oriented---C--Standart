/*-----------------------------------------------------------------------------
                        COMUNICACAO ENTRE PROCESSOS
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
					ESTRUTURAS DE CONTROLE TE TRAFEGO DE MENSAGEM
-----------------------------------------------------------------------------*/
struct MessageCommunicationBlock {
  short status;
  char  reserved;
  char  spc;
  VD_VOID (*routineAddress)();
  short memoryAddress,
        memorySize;
  long  messageQueue;
  short timeOut;
  char  processor,
        circuit,
        id,
        channel;
  char  reservedSystem [42];
  char  *buffer;
};

/*-----------------------------------------------------------------------------
					 ESTRUTURAS DE IDENTIFICACAO DE PROCESSO
-----------------------------------------------------------------------------*/
struct IdProcessor {
  char  processor,
        circuit,
        id,
        channel;
};

/*-----------------------------------------------------------------------------
					 ESTRUTURA DE CONTROLE DE BLOCO DE MENSAGEM
-----------------------------------------------------------------------------*/
struct MessageBlock {
  char  reservedSystem [6];
  short messageLenght;
  char  processor,
        circuit,
        id,
        channel;
  long  source;
  char  data [4096];
};

/*-----------------------------------------------------------------------------
					 ESTRUTURA DE CONTROLE DE CEP ALTO NIVEL
-----------------------------------------------------------------------------*/
typedef struct
 {
  struct MessageCommunicationBlock *MCB;
  int                              desc;
 }HANDLE_CEP;

typedef struct
 {
  DWORD requisicao,
        desc;
  int   processo,servico,
        indice ,find,
        numseg ,tipo,
        tamanho,leitura;
  VIDEO_SEG_CHAVE seg[1];
 }CEP_CTRL_FIND;

typedef struct
 {
  int   loja,caixa,
        processo;
  DWORD desc,
		posicao[100];
 }CEP_CTRL_LOGIN;

typedef struct
 {
  DWORD  codigo;
  int    venda;
  double preco1;
  double preco2;
  int    filler;
 }PVENDA_CTRL_PROMOC;

typedef struct
 {
  BYTE   tipo;
  int    filler;
 }PVENDA_CTRL_MENS;

typedef struct
 {
  int    plano;
  int    flag;
  DWORD  cartao;
  char   buffer[20];
  int    filler;
 }PVENDA_CTRL_PLANO;


typedef struct
 {
  DWORD tamanho;
  int   indice;
  int   operacao;
  char  buffer[1];
 }PVENDA_LOG;

typedef struct
 {
  DATET  data;
  WORD   caixa;
  double documento;
  char   filler[2];
 }PVENDA_VERIFICA_CUPOM;

/*-----------------------------------------------------------------------------
							PROTOTIPOS DE FUNCOES
-----------------------------------------------------------------------------*/
int VIDEO_CEP_enviar(struct MessageCommunicationBlock *MCB,
                     char                             *buffer,
                     int                              tamanho,
                     struct IdProcessor               *bc_IdProc);

int VIDEO_CEP_callprocess(struct MessageCommunicationBlock *MCB,
                          struct IdProcessor               *bc_IdProc);

int VIDEO_CEP_catalog(struct MessageCommunicationBlock *MCB);

int VIDEO_CEP_read(struct MessageCommunicationBlock *MCB,
                   int    bc_TimOut,int bc_TipRecve,
                   char   **buffer,int *tamanho);

int VIDEO_CEP_close(struct MessageCommunicationBlock *MCB);

int VIDEO_CEP_open(struct MessageCommunicationBlock *MCB);

int VIDEO_CEP_freemcb(struct MessageCommunicationBlock **MCB);

struct MessageCommunicationBlock *VIDEO_CEP_creatmcb(int     bc_CodProc,
                                                     VD_VOID (*tratamensagem)(VD_VOID));

int CEP_inic_postfunc(int desc, VD_VOID (*funcao)());

int CEP_cataloga(int desc);

int CEP_interrog_mens(int desc);

int CEP_read(int desc,char **buffer,int tamanho,int tempo);

int CEP_write(int desc,char *buffer,int tamanho,int tempo,int delay);

int CEP_close(int desc);

int CEP_open(int numprocesso,VD_VOID (*post_processing)(VD_VOID));

int VIDEO_pop_pilha_desc_cep(int desc);

int VIDEO_push_pilha_desc_cep(int desc,VD_VOID (*post_processing)(VD_VOID));

int VIDEO_inicializa_cep(VD_VOID);

int CEP_login_sistema(int processo,VD_VOID (*post_processing)(VD_VOID));

int CEP_get_processo(int desc);

int CEP_find(int indice,VIDEO_SEG_CHAVE *seg,int find,int leitura);

int CEP_servidor(int servidor);

int CEP_processa_find(CEP_CTRL_FIND *ctrl_find);

int CEP_dispacha_mensagem(CEP_CTRL_FIND *ctrl_find);

int CEP_recebe_mensagem(int processo,DWORD requisicao,CEP_CTRL_FIND **ctrl_find);

int CEP_login_servcep(int loja,int caixa);

int CEP_logout_servcep(int loja,int caixa);

VD_VOID PVENDA_ajusta_log(int operacao,int indice);

int PVENDA_conecta_servidor(VD_VOID);

int CEP_shutdown(int loja,int caixa);

VD_VOID CEP_slice(BYTE tempo);

VD_VOID CEP_post_processing(VD_VOID);

int CEP_login_servidor(int processo);


VD_VOID CEP_trata_post_processing(VD_VOID);

int CEP_pop_buffer_processing(char *buffer,int  tamcopy);

int CEP_push_buffer_processing(char *origem,int  tamcopy);


/*-----------------------------------------------------------------------------
						  VARIAVEIS PARA CEP EM ALTO NIVEL
-----------------------------------------------------------------------------*/
extern  HANDLE_CEP *VIDEO_tabela_handle_cep;
extern  int        VIDEO_controle_pilha_cep;
extern  int        *VIDEO_pilha_cep        ;
extern  int        VIDEO_erro_cep          ;
extern  int        CEP_espera_read         ;
extern  int        CEP_espera_write        ;
extern  int        CEP_delay_write         ;
extern  DWORD      CEP_requisicao          ;
extern  int        CEP_login               ;
extern  int        CEP_numservidor         ;
extern  DWORD      CEP_descserv            ;
extern  DWORD      CEP_numens_rec          ;
extern  DWORD      CEP_numens_env          ;
extern  DWORD      CEP_numens_err          ;
extern  BYTE       CEP_slice_maximo        ;
extern  BYTE       CEP_slice_minimo        ;

/*-----------------------------------------------------------------------------
							 MACROS DE CONTROLE CEP
-----------------------------------------------------------------------------*/
#define ERRO_CEP						outregs.h.al
#define CEP_ERRO_DOS                    outregs.x.cflag
#define CEP_INT_21                      intdosx( &inregs, &outregs, &segregs )
#define CFLAG                           x.cflag
#define AX                              x.ax
#define BX                              x.bx
#define CX                              x.cx
#define DX                              x.dx
#define AH                              h.ah
#define AL                              h.al
#define BH                              h.bh
#define BL                              h.bl
#define CH                              h.ch
#define CL                              h.cl
#define DH                              h.dh
#define DL                              h.dl

#define CEP_HEADER_MENS                 ((sizeof(int)*8)+(sizeof(DWORD)*2))
#define CEP_TRASACAO_FIND				I(1)
#define CEP_TRASACAO_LOGIN				I(2)
#define CEP_TRASACAO_LOGOUT 			I(3)
#define CEP_TRASACAO_GETPROCESSO		I(4)
#define CEP_TRASACAO_ROTEARPROCESSO 	I(5)
#define CEP_TRASACAO_ADDREC 			I(6)
#define CEP_TRASACAO_REWREC 			I(7)
#define CEP_TRASACAO_DELREC             I(15)
#define CEP_TRASACAO_PROMOCAO           I(8)
#define CEP_TRASACAO_PLANO              I(9)
#define CEP_TRASACAO_VERIFICAR          I(10)
#define CEP_TRASACAO_DESATIVAR          I(11)
#define CEP_TRASACAO_ADDLOG             I(12)
#define CEP_TRASACAO_REWLOG             I(13)
#define CEP_TRASACAO_DELLOG             I(14)
#define CEP_TRASACAO_MENS               I(16)
#define CEP_TRASACAO_INIC_VENDA         I(17)
#define CEP_BUFFER_MENSAGEM             (15*1024)

#define CEP_rewrec(indice) CEP_processa_registro(indice,CEP_TRASACAO_REWREC)
#define CEP_addrec(indice) CEP_processa_registro(indice,CEP_TRASACAO_ADDREC)
#define CEP_delrec(indice) CEP_processa_registro(indice,CEP_TRASACAO_DELREC)
#define CEP_rewlog(indice) CEP_processa_registro(indice,CEP_TRASACAO_REWLOG)
#define CEP_addlog(indice) CEP_processa_registro(indice,CEP_TRASACAO_ADDLOG)
#define CEP_dellog(indice) CEP_processa_registro(indice,CEP_TRASACAO_DELLOG)

#define CEPERR_OVERFLOW_PILHA_DESCRITOR  -1001
#define CEPERR_UNDERFLOW_PILHA_DESCRITOR -1002
#define CEPERR_CRIACAO_MCB               -1003                         
#define CEPERR_DESCRITOR_NAO_ABERTO      -1004
#define CEPERR_PROCESSO_NAO_ENCONTRADO   -1005
#define CEPERR_BUFFER_NAO_ENVIADO        -1006
#define CEPERR_MENSAGEM_NAO_ENCONTRADA   -1007
#define CEPERR_READ_IRRECUPERAVEL        -1008
#define CEPERR_READ_RRECUPERAVEL         -1009
#define CEPERR_READ_TIMEOUT              -1010
#define CEPERR_IMPOSSIVEL_CATALOGAR      -1011
#define CEPERR_IMPOSSIVEL_LOGIN          -1012
#define CEPERR_IMPOSSIVEL_LOGOUT         -1013
#define CEPERR_SERVICO_NAO_CATALOGADO    -1014
#define CEPERR_DESCRITOR_NAO_FECHADO     -1015
#define CEPERR_CONTROLE_COMUNICACAO      -1016
#define CEPERR_ALOCACAO_DE_MEMORIA       -1099

#define CEPERR_OPERACAO_SEM_ERROS            0
#define CEPERR_MODULO_COMUNICACAO            1
#define CEPERR_CANAL_NAO_ESTA_ABERTO         2
#define CEPERR_ESTOURO_BUFFER_DESTINO        3
#define CEPERR_IRRECUPERAVEL_TRANSMISAO      4
#define CEPERR_DESTINO_NAO_ABERTO_RECEPCAO   5
#define CEPERR_ERRO_NA_RECEPCAO              6
#define CEPERR_MENSAGEM_NAO_DISPONIVEL       7
#define CEPERR_CODIGO_NAO_LOCALIZADO         8
#define CEPERR_CODIGO_JA_CATALOGADO          9
#define CEPERR_CANAL_JA_ESTA_ABERTO         10
#define CEPERR_CANAL_JA_CATALOGADO          11
#define CEPERR_MUITOS_CANAIS_ABERTOS        12
#define PVENDA_REG_HEADER_VENDA   '0'
#define PVENDA_REG_ITEM_VENDA     '1'
#define PVENDA_REG_FEC_VENDA      '2'

