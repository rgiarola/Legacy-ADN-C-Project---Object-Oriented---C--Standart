#include <INCVIDEO.H>

VOID VIDEO_ACESSO_nao_disponivel(origem)
char *origem;
{
 char mensagem[100];
 strcpy(mensagem," [");
 strcat(mensagem,origem);
 strcat(mensagem,"]");
 strcat(mensagem," N„o Dispon¡vel");

 VD_telaerr((80-strlen(mensagem))/2,5,mensagem,VIDEO_COR_EXC_REGISTRO);
}

INT2 VIDEO_ACESSO_inclusao(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("INCLUSŽO");
 return(TRUE);
}

INT2 VIDEO_ACESSO_exclusao(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("EXCLUSŽO");
 return(TRUE);
}

INT2 VIDEO_ACESSO_alteracao(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("ALTERA€ŽO");
 return(TRUE);
}

INT2 VIDEO_ACESSO_pesquisa(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("PESQUISA");
 return(TRUE);
}

INT2 VIDEO_ACESSO_manutencao(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("MANUTEN€ŽO");
 return(TRUE);
}

INT2 VIDEO_ACESSO_pag_PGDN(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("PGDN");
 return(TRUE);
}

INT2 VIDEO_ACESSO_pag_PGUP(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("PGUP");
 return(TRUE);
}

INT2 VIDEO_ACESSO_pag_SHIFT_PGDN(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("SHIFT_PGDN");
 return(TRUE);
}

INT2 VIDEO_ACESSO_pag_SHIFT_PGUP(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("SHIFT_PGUP");
 return(TRUE);
}

INT2 VIDEO_ACESSO_pag_CTRL_PGUP(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("CTRL_PGUP");
 return(TRUE);
}

INT2 VIDEO_ACESSO_pag_CTRL_PGDN(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("CTRL_PGDN");
 return(TRUE);
}

INT2 VIDEO_ACESSO_spool_impressao(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("GERENCIADOR DE IMPRESSŽO");
 return(TRUE);
}

INT2 VIDEO_ACESSO_gerador_relatorios(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("GERADOR DE RELATORIOS");
 return(TRUE);
}

INT2 VIDEO_ACESSO_acesso_geral(VD_VOID)
{
 VIDEO_ACESSO_nao_disponivel("ACESSO");
 return(TRUE);
}

