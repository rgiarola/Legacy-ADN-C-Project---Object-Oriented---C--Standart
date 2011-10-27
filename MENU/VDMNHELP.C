#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_help(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 if ((*campos)->nomehelp)
     VIDEO_VISUAL_dispara_visual((*campos)->nomehelp,VD_NULO,TRUE,
                                 &VIDEO_HELP_imagem_padrao,
                                 &VIDEO_VISUAL_menu,FALSE);
 return(TRUE);
}

