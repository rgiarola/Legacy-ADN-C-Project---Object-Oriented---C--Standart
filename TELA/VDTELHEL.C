#include <INCVIDEO.H>

INT2 VIDEO_TELA_mouse_help(tela,param)
VIDEO_TELA_ENTRADA_DADOS **tela;
VIDEO_NUCLEO_SERV        **param;
{
 VIDEO_IMAGEMTELA *imagem;

 imagem = (*tela)->imagem_ativa;
 if (imagem->nomehelp)
    {
     VD_PUSHWIN(imagem->colf-7,imagem->colf,imagem->lini,imagem->lini);
     VD_PUSHWIN(imagem->coli,imagem->colf,imagem->linf,imagem->linf);
     VIDEO_TELA_desativa_status(imagem);
     VIDEO_VISUAL_dispara_visual(imagem->nomehelp,VD_NULO,TRUE,
                                 &VIDEO_HELP_imagem_padrao,
                                 VIDEO_VISUAL_menu,FALSE);
     VD_POPWIN();
     VD_POPWIN();
    }
 return(TRUE);
}


