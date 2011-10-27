#include<INCVIDEO.H>

INT2 VIDEO_ARVORE_mouseumtrav(VIDEO_ARVORE_ESTRUTURA **arvore,
                              VIDEO_NUCLEO_SERV      **param)
{
 VIDEO_MOUSE_colclick = VIDEO_MOUSE_coluna_atual;
 VIDEO_MOUSE_linclick = VIDEO_MOUSE_linha_atual;

 if (VIDEO_ARVORE_aborta_arvore(arvore,param))
    return(TRUE);

 if (VIDEO_ARVORE_setas_mouse(arvore,param))
    return(TRUE);

 VIDEO_ARVORE_seleciona_mouse(arvore,param);
 return(TRUE);
}
