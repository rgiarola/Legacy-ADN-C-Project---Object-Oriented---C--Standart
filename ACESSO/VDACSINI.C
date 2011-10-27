#include <INCVIDEO.H>

int VIDEO_ACESSO_inicializa(VD_VOID)
{
 if (!VIDEO_ACESSO_inicializa_tabela(VIDEO_TELA_tabserv_navegacao,
									&VIDEO_ACESSO_tela_navegacao))
	return(FALSE);

 if (!VIDEO_ACESSO_inicializa_tabela(VIDEO_TELA_tabserv_edicao_tela,
									&VIDEO_ACESSO_edicao_tela))
	{
	 VIDEO_FREE_ALLOC_MEM(VIDEO_ACESSO_tela_navegacao);
	 return(FALSE);
	}

 if (!VIDEO_ACESSO_inicializa_tabela(VIDEO_PESQUISA_tabserv_navegacao,
									&VIDEO_ACESSO_pesquisa_navegacao))
	{
	 VIDEO_FREE_ALLOC_MEM(VIDEO_ACESSO_tela_navegacao);
	 VIDEO_FREE_ALLOC_MEM(VIDEO_ACESSO_edicao_tela);
	 return(FALSE);
	}

 VIDEO_ACESSO_flag = TRUE;

 return(TRUE);
}

int VIDEO_ACESSO_conta_tabela_servico(VIDEO_TABSERV *tabela)
{
 int cont = 0;
 while(tabela->VIDEO_servico)
  {
   ++cont;
   ++tabela;
  }
 return(cont);
}

int VIDEO_ACESSO_inicializa_tabela(VIDEO_TABSERV *origem,
                                   VIDEO_TABSERV **destino)
{
 int cont;

 if ((cont = VIDEO_ACESSO_conta_tabela_servico(origem)) <= 0)
     return(FALSE);

 if (VIDEO_ALLOC_MEM(*destino,cont*sizeof(VIDEO_TABSERV)) == VD_NULO)
     return(FALSE);

 VIDEO_movbloco(*destino,origem,cont*sizeof(VIDEO_TABSERV));

 return(TRUE);
}

int VIDEO_ACESSO_restaura(VD_VOID)
{
 if (!VIDEO_ACESSO_restaura_tabela(VIDEO_TELA_tabserv_navegacao,
                                   VIDEO_ACESSO_tela_navegacao))
	return(FALSE);

 if (!VIDEO_ACESSO_restaura_tabela(VIDEO_TELA_tabserv_edicao_tela,
                                   VIDEO_ACESSO_edicao_tela))
	 return(FALSE);

 if (!VIDEO_ACESSO_restaura_tabela(VIDEO_PESQUISA_tabserv_navegacao,
                                   VIDEO_ACESSO_pesquisa_navegacao))
	 return(FALSE);

 return(TRUE);
}

int VIDEO_ACESSO_restaura_tabela(VIDEO_TABSERV *origem,
                                 VIDEO_TABSERV *destino)
{
 int cont;

 if ((cont = VIDEO_ACESSO_conta_tabela_servico(origem)) <= 0)
     return(FALSE);

 VIDEO_movbloco(origem,destino,cont*sizeof(VIDEO_TABSERV));

 return(TRUE);
}

