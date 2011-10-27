#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_selec_tela_anterior(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_TELA_ENTRADA_DADOS *telaaux;
 INT2                      accept;

 telaaux = *tela;
 accept  = telaaux->imagem_accept;

 if (telaaux->imagem_accept)
    {
     VIDEO_IMAGEMTELA *imagem,*imagwork;

     imagem = telaaux->imagem_ativa;
     --telaaux->imagem_accept;
     (telaaux->imagens+telaaux->imagem_accept)->flagimagem |=
                                         (VIDEO_TELA_DISPIMAGEM|
										  VIDEO_TELA_DISPCAMPOS|
										  VIDEO_TELA_FLAGRESETDISPLAY);

     if ((telaaux->imagens+telaaux->imagem_accept)->arquivo ==
          telaaux->imagem_ativa->arquivo)
          if (telaaux->imagem_ativa->flagimagem&VIDEO_TELA_INICIMAGEM)
             (telaaux->imagens+telaaux->imagem_accept)->flagimagem |=
             VIDEO_TELA_INICIMAGEM;
            else
             (telaaux->imagens+telaaux->imagem_accept)->flagimagem &=
             ~VIDEO_TELA_INICIMAGEM;

     if (accept != telaaux->imagem_accept)
        VIDEO_TELA_desativa_status(telaaux->imagens+accept);

     imagwork = telaaux->imagens+telaaux->imagem_accept;

     if ((imagem->flagimagem&VIDEO_TELA_FLAGREGALT) &&
         imagem->nmindsub && (!imagwork->nmindsub || strcmp(imagwork->nmindsub,imagem->nmindsub)))
        {
         char buffer[100];
         strcpy(buffer,VIDEO_TELA_mens_tela_proc_info);
         sprintf(&buffer[strlen(buffer)]," [%s]",(imagem->ident) ?
                                                  imagem->ident :
                                                  VIDEO_TELA_mens_tela_proc_def);
         strcat(buffer,VIDEO_TELA_mens_tela_proc_salv);
         VIDEO_mostra_mens_erro(buffer,TRUE);
        }
   }
 return(TRUE);
}


