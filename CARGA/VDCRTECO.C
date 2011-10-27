#include <INCVIDEO.H>

VD_VOID VIDEO_CRG_end_cons_obrigatorio(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 char           *buffercrg;
 VIDEO_MENSAGEM *mensagem;

 buffercrg = PTR_CAST(char,strtelacrg);

 mensagem = consiste->objetocons.mens = W(consiste->objetocons.mens) +
            strtelacrg->menssai;
 mensagem->mensagem = W(mensagem->mensagem) + buffercrg;
}

VD_VOID VIDEO_CRG_end_cons_faixa(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 char             *buffercrg;
 VIDEO_CONS_FAIXA *faixa;

 buffercrg = PTR_CAST(char,strtelacrg);

 faixa = consiste->objetocons.faixa = W(consiste->objetocons.faixa) +
            strtelacrg->faixasai;
 faixa->mensagem = W(faixa->mensagem) + buffercrg;
 faixa->faixa    = W(faixa->faixa)    + buffercrg;
}

VD_VOID VIDEO_CRG_end_cons_manutencao(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 VIDEO_ESTMANUT *manutencao;
 char           *buffercrg;

 buffercrg = PTR_CAST(char,strtelacrg);

 manutencao = consiste->objetocons.manutencao =
              W(consiste->objetocons.manutencao) + strtelacrg->manutsai;

 manutencao->sistcrg = W(manutencao->sistcrg) + buffercrg;

 manutencao->telacrg = W(manutencao->telacrg) + buffercrg;
}

VD_VOID VIDEO_CRG_end_cons_menu(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 char            *buffercrg,
                 **opcoes;
 VIDEO_INFO_MENU *menu;
 INT2             cont;

 buffercrg = PTR_CAST(char,strtelacrg);

 menu = consiste->objetocons.menu =
              W(consiste->objetocons.menu) + strtelacrg->menusai;
 menu->MENU_pega_opcao = VIDEO_MENU_pega_selecao;
 menu->funcserv        = VIDEO_getkbd;
 opcoes = menu->opcoes = PTR_CAST(char *,(W(menu->opcoes)+buffercrg));

 menu->nomehelp    = (W(menu->nomehelp) !=  W(0XFFFE)) ?
         PTR_CAST(char,(W(menu->nomehelp)+buffercrg)) :
         VIDEO_NILL(char);

 menu->titulo    = (W(menu->titulo) !=  W(0XFFFE)) ?
         PTR_CAST(char,(W(menu->titulo)+buffercrg)) :
         VIDEO_NILL(char);

 menu->userserv    = (W(menu->userserv) !=  W(0XFFFE)) ?
         PTR_CAST(char,(W(menu->userserv)+buffercrg)) :
         VIDEO_NILL(char);

 menu->usermenu    = (W(menu->usermenu) !=  W(0XFFFE)) ?
         PTR_CAST(char,(W(menu->usermenu)+buffercrg)) :
         VIDEO_NILL(char);

 menu->userele     = (W(menu->userele) !=  W(0XFFFE)) ?
         PTR_CAST(char,(W(menu->userele)+buffercrg)) :
         VIDEO_NILL(char);

 cont = 0;
 do
  {
   *opcoes = W(*opcoes) + buffercrg;
   ++opcoes;
  }while(++cont < menu->numop);
}

VD_VOID VIDEO_CRG_end_cons_consdb(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 VIDEO_TRANSP_DADOS *transpdados;
 char               *buffercrg;
 VIDEO_SEG_CHAVE    *segchave;
 VIDEO_MENSAGEM     *mensagem;
 VIDEO_CONSDB       *consdb;

 buffercrg = PTR_CAST(char,strtelacrg);

 consdb = consiste->objetocons.consdb =
          W(consiste->objetocons.consdb) + strtelacrg->consdbsai;

 consdb->nomeindice = (W(consdb->nomeindice) != W(0XFFFE)) ?
                       W(consdb->nomeindice)+buffercrg  :
                       VIDEO_NILL(char);

 if (W(consdb->segchave) != W(0XFFFE))
    {
     segchave = consdb->segchave =
                       W(consdb->segchave) + strtelacrg->segchavesai;
     while(segchave->pointer)
      {
       segchave->pointer = W(segchave->pointer) + buffercrg;
       ++segchave;
      }
    }
  else
    consdb->segchave = VIDEO_NILL(VIDEO_SEG_CHAVE);

 if (W(consdb->transpdados) != W(0XFFFE))
    {
     transpdados = consdb->transpdados =
                  W(consdb->transpdados) + strtelacrg->transpdadossai;
     while(transpdados->destino)
      {
       transpdados->destino = W(transpdados->destino) + buffercrg;
       transpdados->origem = W(transpdados->origem) + buffercrg;
       ++transpdados;
      }
    }
  else
    consdb->transpdados = VIDEO_NILL(VIDEO_TRANSP_DADOS);

 if (W(consdb->mensagem) != W(0XFFFE))
    {
     mensagem = consdb->mensagem = W(consdb->mensagem) +
                                   strtelacrg->menssai;
     mensagem->mensagem = W(mensagem->mensagem) + buffercrg;
    }
  else
    mensagem->mensagem = VIDEO_NILL(VIDEO_MENSAGEM);

 consdb->situacao = &strtelacrg->telasai->imagem_ativa->flagimagem;

 consdb->posicao = 0;
}

VD_VOID VIDEO_CRG_end_cons_user_func(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 char *buffercrg;

 buffercrg = PTR_CAST(char,strtelacrg);
 consiste->objetocons.user_cons =
           (W(consiste->objetocons.user_cons) != W(0XFFFE)) ?
           W(consiste->objetocons.user_cons) + buffercrg :
           VIDEO_NILL(char);
}

VD_VOID VIDEO_CRG_end_cons_busca(consiste,strtelacrg)
VIDEO_CAMPO_CONSISTENCIA *consiste;
VIDEO_TABCRGTELA         *strtelacrg;
{
 VIDEO_TRANSP_DADOS      *transpdados;
 VIDEO_ESTMANUT          *manutencao;
 char                    *buffercrg;
 VIDEO_PESQUISA_PLANILHA *planilha;
 VIDEO_SEG_CHAVE         *segchave;

 buffercrg = PTR_CAST(char,strtelacrg);

 planilha = consiste->objetocons.planilha =
            W(consiste->objetocons.planilha) + strtelacrg->planilhasai;

 planilha->nomeindice = (W(planilha->nomeindice) != W(0XFFFE)) ?
                        W(planilha->nomeindice)+buffercrg   :
                        VIDEO_NILL(char);

 if (W(planilha->segchave) != W(0XFFFE))
    {
     segchave = planilha->segchave =
                       W(planilha->segchave) + strtelacrg->segchavesai;
     while(segchave->pointer)
      {
       segchave->pointer = W(segchave->pointer) + buffercrg;
       ++segchave;
      }
    }
  else
    planilha->segchave = VIDEO_NILL(VIDEO_SEG_CHAVE);

 if (W(planilha->transpdados) != W(0XFFFE))
    {
     transpdados = planilha->transpdados =
                   W(planilha->transpdados) + strtelacrg->transpdadossai;
     while(transpdados->destino)
      {
       transpdados->destino = W(transpdados->destino) + buffercrg;
       transpdados->origem = W(transpdados->origem) + buffercrg;
       ++transpdados;
      }
    }
  else
    planilha->transpdados = VIDEO_NILL(VIDEO_TRANSP_DADOS);

 manutencao = planilha->tela =
              W(planilha->tela) + strtelacrg->manutsai;
 manutencao->sistcrg = W(manutencao->sistcrg) + buffercrg;

 manutencao->telacrg = W(manutencao->telacrg) + buffercrg;

 manutencao->strtelacrg =
 manutencao->tela       = VD_NULO;

 planilha->pesquisa_tela = VIDEO_PESQUISA_accept_tela;

 planilha->flagplanilha  = VIDEO_PESQUISA_DISPCURSOR |
                           VIDEO_PESQUISA_DISPIMAGEM |
                           VIDEO_PESQUISA_DISPLINHA  |
                           VIDEO_PESQUISA_INICIALIZA |
                           VIDEO_PESQUISA_SALVATELA  ;

 planilha->nomehelp    = (W(planilha->nomehelp) !=  W(0XFFFE)) ?
         PTR_CAST(char,(W(planilha->nomehelp)+buffercrg)) :
         VIDEO_NILL(char);
}


/*
saibuf(buffer)
char *buffer;
{
 INT2 desc;
 vtclose();
 desc = open("buffer",O_BINARY|O_RDWR|O_CREAT|O_APPEND,S_IREAD|S_IWRITE);
 write(desc,buffer,strlen(buffer));
 close(desc);
}

*/
