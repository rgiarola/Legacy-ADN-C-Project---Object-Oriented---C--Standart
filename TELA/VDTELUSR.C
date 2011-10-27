#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_dispara_userserv(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_TABFUNCAO *tabfuncuser;
 INT2             ret;

 if ((*tela)->imagem_ativa->userserv)
    {
     tabfuncuser = VIDEO_funcao_tabfuncuser((*tela)->imagem_ativa->userserv);

	 if (tabfuncuser && tabfuncuser->userfunc)
        {
         VIDEO_TELA_desativa_status((*tela)->imagem_ativa);
         (*tela)->imagem_ativa->flagimagem |=
                  (VIDEO_TELA_DISPIMAGEM|VIDEO_TELA_DISPCAMPOS|
                   VIDEO_TELA_FLAGRESETDISPLAY);
         return((*tabfuncuser->userfunc)(tela,param));
        }
      else
        {
         char buffer[200];
		 sprintf(buffer,VIDEO_funcao_nao_enc,(*tela)->imagem_ativa->userserv);
		 VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_funcao_tela_serv_nao_enc);
        }
    }

 return(TRUE);
}
