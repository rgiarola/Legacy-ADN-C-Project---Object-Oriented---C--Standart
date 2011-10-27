#include <INCVIDEO.H>

INT2 VIDEO_PESQUISA_dispara_userserv(telapesq,param)
VIDEO_PESQUISA_PLANILHA **telapesq;
VIDEO_NUCLEO_SERV       **param;
{
 VIDEO_IMAGEMTELA *imagem;
 VIDEO_TABFUNCAO  *tabfuncuser;

 imagem = PTR_CAST(VIDEO_TELA_ENTRADA_DADOS,(*telapesq)->tela->tela)->imagens;

 if (imagem->userserv)
    {
	 tabfuncuser = VIDEO_funcao_tabfuncuser(imagem->userserv);

	 if (tabfuncuser && tabfuncuser->userfunc)
		 return((*tabfuncuser->userfunc)(telapesq,param));
      else
        {
         char buffer[200];
         sprintf(buffer,VIDEO_funcao_nao_enc,imagem->userserv);
         VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_funcao_serv_nao_encontrada);
        }
    }

 return(TRUE);
}


