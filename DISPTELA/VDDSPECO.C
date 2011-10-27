
int VIDEO_DISPLAY_cons_obrigatorio(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 VIDEO_MENSAGEM *mensagem;

 mensagem = consiste->objetocons.mens;
 printf("CONS MENSAGEM COL %2d LIN %2d TAMMENS %2d MENS [%s]\n",
 mensagem->col,mensagem->lin,strlen(mensagem->mensagem),mensagem->mensagem);

 return(TRUE);
}

int VIDEO_DISPLAY_cons_faixa(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 VIDEO_MENSAGEM *mensagem;

 mensagem = consiste->objetocons.mens;
 printf("CONS FAIXA COL %2d LIN %2d TAMFAIXA %2d FAIXA [%s]\n",
 mensagem->col,mensagem->lin,strlen(mensagem->mensagem),mensagem->mensagem);

 return(TRUE);
}

int VIDEO_DISPLAY_cons_manutencao(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 VIDEO_ESTMANUT *manutencao;

 manutencao = consiste->objetocons.manutencao;
 printf("CONS MANUT TAMSIS %2d SISTEMA [%20s] TAMTELA %2d TELA [%s]\n",
 strlen(manutencao->sistcrg),manutencao->sistcrg,
 strlen(manutencao->telacrg),manutencao->telacrg);

 return(TRUE);
}

int VIDEO_DISPLAY_cons_menu(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 char            **opcoes;
 VIDEO_INFO_MENU *menu;
 int             cont;

 menu = consiste->objetocons.menu;
 opcoes = menu->opcoes;

 printf("CONS MENU NUMOP %2d\n",menu->numop);

 cont = 0;
 do
  {
   printf("NUMOP %2d TAMOP %2d OPCAO %s \n",
                   cont,strlen(*opcoes),*opcoes);

   ++opcoes;
  }while(++cont < menu->numop);

 return(TRUE);
}

int VIDEO_DISPLAY_cons_consdb(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 VIDEO_TRANSP_DADOS *transpdados;
 VIDEO_SEG_CHAVE    *segchave;
 VIDEO_MENSAGEM     *mensagem;
 VIDEO_CONSDB       *consdb;

 consdb = consiste->objetocons.consdb;
 if (consdb->nomeindice)
     printf("CONSDB INDICE %2d %s \n",strlen(consdb->nomeindice),
                    consdb->nomeindice);
   else
     printf("CONSDB INDICE NULO \n");


 if (consdb->segchave)
    {
     segchave = consdb->segchave;
     while(segchave->pointer)
      {
       printf("CONSDB SEGCHAVE POINTER %2d %20s TIPO %2d TAMANHO %2d\n",
               strlen(segchave->pointer),segchave->pointer,segchave->tipo,
               segchave->tamanho);

       ++segchave;
      }
    }
  else
     printf("CONSDB SEGCHAVE NULO \n");

 if (consdb->transpdados)
    {
     transpdados = consdb->transpdados;
     while(transpdados->destino)
      {
       printf("CONSDB TRANSPDADOS ORIGEM %2d %20s DESTINO %2d %20s \n",
               strlen(transpdados->origem) ,transpdados->origem,
               strlen(transpdados->destino),transpdados->destino);
       ++transpdados;
      }
    }
  else
     printf("CONSDB TRANSPDADOS NULO \n");

 if (consdb->mensagem)
    {
     mensagem = consdb->mensagem;
     printf("CONSDB COL %2d LIN %2d TAMMENS %2d MENS [%s]\n",
     mensagem->col,mensagem->lin,strlen(mensagem->mensagem),mensagem->mensagem);

    }
  else
     printf("CONSDB MENSAGEM NULA \n");

 return(TRUE);
}

int VIDEO_DISPLAY_cons_valkey(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 return(VIDEO_DISPLAY_cons_consdb(consiste,strtelacrg));
}

int VIDEO_DISPLAY_cons_dupkey(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 return(VIDEO_DISPLAY_cons_consdb(consiste,strtelacrg));
}

int VIDEO_DISPLAY_cons_posiciona(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 return(VIDEO_DISPLAY_cons_consdb(consiste,strtelacrg));
}

int VIDEO_DISPLAY_cons_user_func(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 if (consiste->objetocons.user_cons)
    {
     printf("CONSDB USERCONS %d %s \n",
      strlen(consiste->objetocons.user_cons),consiste->objetocons.user_cons,
	  0x0d,0x0a);

    }
  else
     printf("CONSDB USERCONS  NULA \n");

 return(TRUE);
}

int VIDEO_DISPLAY_cons_busca(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 VIDEO_TRANSP_DADOS      *transpdados;
 VIDEO_ESTMANUT          *manutencao;
 VIDEO_PESQUISA_PLANILHA *planilha;
 VIDEO_SEG_CHAVE         *segchave;

 planilha = consiste->objetocons.planilha;

 if (planilha->nomeindice)
     printf("PLANILHA INDICE %2d %s \n",strlen(planilha->nomeindice),
                    planilha->nomeindice);
   else
     printf("PLANILHA INDICE NULO \n");

 if (planilha->segchave)
    {
     segchave = planilha->segchave;
     while(segchave->pointer)
      {
       printf("PLANILHA SEGCHAVE POINTER %2d %20s TIPO %2d TAMANHO %2d\n",
               strlen(segchave->pointer),segchave->pointer,segchave->tipo,
               segchave->tamanho);

       ++segchave;
      }
    }
  else
     printf("PLANILHA SEGCHAVE NULO \n");

 if (planilha->transpdados)
    {
     transpdados = planilha->transpdados;
     while(transpdados->destino)
      {
       printf("PLANILHA TRANSPDADOS ORIGEM %2d %20s DESTINO %2d %20s \n",
               strlen(transpdados->origem) ,transpdados->origem,
               strlen(transpdados->destino),transpdados->destino);

       ++transpdados;
      }
    }
  else
     printf("PLANILHA TRANSPDADOS NULO \n");

 if (planilha->nomehelp)
	{
     printf("PLANILHA HELP %2d %20s \n",strlen(planilha->nomehelp),
     planilha->nomehelp);
    }
  else
     printf("PLANILHA HELP NULO \n");

 return(TRUE);
}



