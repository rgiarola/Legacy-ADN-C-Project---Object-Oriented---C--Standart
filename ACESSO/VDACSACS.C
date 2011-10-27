#include <INCVIDEO.H>

/* ----------------------------------------------------------------------------
   VIDEO_acess()
   PARAMETRO:      modulo  -> Numero do Modulo de Check
                   *acesso -> Mensagem de Restricao ao modulo
                   flagrel -> Selecao para check de relatorios/modulo
   ---------------------------------------------------------------------------- */
INT2 VIDEO_ACESSO_(modulo,acesso,flagrel)
INT2  modulo;        // Modulo de Acesso (Basicos, Contas, Etc...)
char *acesso;        // Mensagem
INT2  flagrel;       // Check Relatorio
{
 INT2  servicos[6],
      contserv;
 char *permiss;

// permiss  = &controle_senha.permiss1[0]+(10*modulo); ** Instrucao Anterior **

 permiss  = (controle_senha->permiss1)+(10*modulo);


 if ( (flagrel && *(permiss+5)!='X') || (*permiss++ != 'X'))
    {
     VD_telaerr((80-strlen(acesso))/2,7,acesso,VIDEO_COR_EXC_REGISTRO);
     return(FALSE);
    }

 if (flagrel)
    return(TRUE);

 VIDEO_swap_tratadores(VIDEO_tabserv_tela_nivel_campo,
                       VIDEO_TELA_tabserv_navegacao,TRUE,VD_NULO);

 VIDEO_swap_tratadores(VIDEO_tabserv_tela_nivel_imagem,
                       VIDEO_TELA_tabserv_edicao_tela,TRUE,VD_NULO);

 contserv = 0;
 VIDEO_setmem(servicos,sizeof(INT2)*6,0);

 if (*permiss++ != 'X')
    servicos[contserv++] = VIDEO_DATABASE_INCLUSAO;

 if (*permiss++ != 'X')
    servicos[contserv++] = VIDEO_DATABASE_ALTERACAO;

 if (*permiss++ != 'X')
    servicos[contserv++] = VD_MTTECLA(VD_NULO,ALT_E);

 if (*permiss++ != 'X')
    {
     servicos[contserv++] = VD_MTTECLA(VD_NULO,ALT_B);
     VIDEO_swap_tratadores(VIDEO_tabserv_tela_nivel_campo,
                           VIDEO_TELA_tabserv_navegacao,FALSE,VD_NULO);
    }
 ++permiss;

 if (*permiss++ != 'X')
    servicos[contserv++] = VD_MTTECLA(VD_NULO,ALT_M);

 if (contserv)
     VIDEO_swap_tratadores(VIDEO_tabserv_tela_nivel_imagem,
                           VIDEO_TELA_tabserv_edicao_tela,FALSE,servicos);

 return(TRUE);
}

