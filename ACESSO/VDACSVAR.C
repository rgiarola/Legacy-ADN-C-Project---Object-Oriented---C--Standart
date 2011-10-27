#include <INCVIDEO.H>

BYTE  VIDEO_ACESSO_flag       = FALSE;
BYTE  VIDEO_ACESSO_retorno    = FALSE;
DWORD VIDEO_ACESSO_processo   = FALSE;
char  *VIDEO_acesso_posicao   = VD_NULO;

VIDEO_ACESSO_indice_acesso[]  = "ACESSO_KEY01",
VIDEO_ACESSO_indice_grupo[]   = "NIVEL_KEY01",
VIDEO_ACESSO_indice_usuario[] = "USUARIO_KEY01";

INT2 (*VIDEO_ACESSO_relatorio)() = RTREE_exec;
VIDEO_TABSERV *VIDEO_ACESSO_tela_navegacao	   = VD_NULO;
VIDEO_TABSERV *VIDEO_ACESSO_edicao_tela 	   = VD_NULO;
VIDEO_TABSERV *VIDEO_ACESSO_pesquisa_navegacao = VD_NULO;


