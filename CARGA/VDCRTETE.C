#include <INCVIDEO.H>

INT2 VIDEO_CRG_endereca_tela(strtelacrg)
VIDEO_TABCRGTELA *strtelacrg;
{
 char               *buffercrg;
 VIDEO_SEG_CHAVE    *segchave;
 VIDEO_IMAGEMTELA   *imagem;
 VIDEO_CAMPO_TELA   *campos;
 VIDEO_TRANSP_DADOS *transpdados;
 INT2                cont;

 buffercrg = PTR_CAST(char,strtelacrg);
 strtelacrg->nutelasai      =
   PTR_CAST(VIDEO_NUCLEO_SERV       ,(buffercrg+W(strtelacrg->nutelasai     )));
 strtelacrg->telasai        =
   PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,(buffercrg+W(strtelacrg->telasai       )));
 strtelacrg->imagemsai      =
   PTR_CAST(VIDEO_IMAGEMTELA        ,(buffercrg+W(strtelacrg->imagemsai     )));
 strtelacrg->nucampossai    =
   PTR_CAST(VIDEO_NUCLEO_SERV       ,(buffercrg+W(strtelacrg->nucampossai   )));
 strtelacrg->campossai      =
   PTR_CAST(VIDEO_CAMPO_TELA        ,(buffercrg+W(strtelacrg->campossai     )));
 strtelacrg->conssai        =
   PTR_CAST(VIDEO_CAMPO_CONSISTENCIA,(buffercrg+W(strtelacrg->conssai       )));
 strtelacrg->menssai        =
   PTR_CAST(VIDEO_MENSAGEM          ,(buffercrg+W(strtelacrg->menssai       )));
 strtelacrg->segchavesai    =
   PTR_CAST(VIDEO_SEG_CHAVE         ,(buffercrg+W(strtelacrg->segchavesai   )));
 strtelacrg->consdbsai      =
   PTR_CAST(VIDEO_CONSDB            ,(buffercrg+W(strtelacrg->consdbsai     )));
 strtelacrg->menusai        =
   PTR_CAST(VIDEO_INFO_MENU         ,(buffercrg+W(strtelacrg->menusai       )));
 strtelacrg->planilhasai    =
   PTR_CAST(VIDEO_PESQUISA_PLANILHA ,(buffercrg+W(strtelacrg->planilhasai   )));
 strtelacrg->transpdadossai =
   PTR_CAST(VIDEO_TRANSP_DADOS      ,(buffercrg+W(strtelacrg->transpdadossai)));
 strtelacrg->manutsai       =
   PTR_CAST(VIDEO_ESTMANUT          ,(buffercrg+W(strtelacrg->manutsai      )));
 strtelacrg->faixasai       =
   PTR_CAST(VIDEO_CONS_FAIXA        ,(buffercrg+W(strtelacrg->faixasai      )));
 strtelacrg->buffersai		=
   PTR_CAST(char                    ,(buffercrg+W(strtelacrg->buffersai     )));

 strtelacrg->nutelasai->VIDEO_campos   =
                           PTR_CAST(VIDEO_TAB_FUNC,strtelacrg->telasai);
 strtelacrg->nutelasai->VIDEO_tabserv  = VIDEO_TELA_tabserv_edicao_tela;
 imagem = strtelacrg->telasai->imagem_ativa =
          strtelacrg->telasai->imagens = strtelacrg->imagemsai;
 strtelacrg->telasai->accept_tela      = VIDEO_TELA_accept_tela;
 strtelacrg->telasai->imagem_accept    = 0;

 cont = 0;
 do
  {
   strtelacrg->telasai->imagem_ativa = strtelacrg->telasai->imagens + cont;

   imagem->ident = (W(imagem->ident) !=  W(0XFFFE))       ?
           PTR_CAST(char,(W(imagem->ident)+buffercrg)) :
           VIDEO_NILL(char);

   imagem->nmindarq = (W(imagem->nmindarq) !=  W(0XFFFE))    ?
           PTR_CAST(char,(W(imagem->nmindarq)+buffercrg)) :
           VIDEO_NILL(char);

   imagem->nmindsub = (W(imagem->nmindsub) !=  W(0XFFFE))    ?
           PTR_CAST(char,(W(imagem->nmindsub)+buffercrg)) :
           VIDEO_NILL(char);

   imagem->nmindpai = (W(imagem->nmindpai) !=  W(0XFFFE))    ?
           PTR_CAST(char,(W(imagem->nmindpai)+buffercrg)) :
           VIDEO_NILL(char);

   imagem->userfunc    = (W(imagem->userfunc) !=  W(0XFFFE)) ?
           PTR_CAST(char,(W(imagem->userfunc)+buffercrg)) :
           VIDEO_NILL(char);

   imagem->userserv    = (W(imagem->userserv) !=  W(0XFFFE)) ?
           PTR_CAST(char,(W(imagem->userserv)+buffercrg)) :
           VIDEO_NILL(char);

   imagem->mensagem    = (W(imagem->mensagem) !=  W(0XFFFE)) ?
           PTR_CAST(char,(W(imagem->mensagem)+buffercrg)) :
           VIDEO_NILL(char);

   imagem->nomehelp    = (W(imagem->nomehelp) !=  W(0XFFFE)) ?
           PTR_CAST(char,(W(imagem->nomehelp)+buffercrg)) :
           VIDEO_NILL(char);

   if (W(imagem->segchave) != W(0XFFFE))
      {
       segchave = imagem->segchave =
                  W(imagem->segchave)+strtelacrg->segchavesai;
       while(segchave->pointer)
        {
         segchave->pointer = W(segchave->pointer) + buffercrg;
         ++segchave;
        }
      }
    else
      imagem->segchave = VIDEO_NILL(VIDEO_SEG_CHAVE);

   if (W(imagem->transpdados) != W(0XFFFE))
      {
       transpdados = imagem->transpdados =
                    W(imagem->transpdados) + strtelacrg->transpdadossai;
       while(transpdados->destino)
        {
         transpdados->destino = W(transpdados->destino) + buffercrg;
         transpdados->origem  = W(transpdados->origem)  + buffercrg;
         ++transpdados;
        }
      }
    else
      imagem->transpdados = VIDEO_NILL(VIDEO_TRANSP_DADOS);

   if (W(imagem->campos) != W(0XFFFE))
      {
       imagem->campos   = W(imagem->campos)+strtelacrg->nucampossai;
       campos = W(imagem->campos->VIDEO_campos)+strtelacrg->campossai;
       imagem->campos->VIDEO_campos = PTR_CAST(VIDEO_TAB_FUNC,campos);
       imagem->campos->VIDEO_tabserv = VIDEO_TELA_tabserv_navegacao;
       if (!VIDEO_CRG_endereca_campos(campos,imagem->campos->VIDEO_numcampos,strtelacrg))
          return(FALSE);
      }
    else
      imagem->campos = VIDEO_NILL(VIDEO_NUCLEO_SERV);

   ++imagem;

  }while(++cont < strtelacrg->contimagemsai);

 return(TRUE);
}
