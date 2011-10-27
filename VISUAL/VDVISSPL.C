#include <INCVIDEO.H>

INT2 VIDEO_VISUAL_dispara_spool(VD_VOID)
{
 int flagmouse = FALSE;

 if (VIDEO_MOUSE_ativo && VIDEO_MOUSE_cursor_ativo)
    {
     VIDEO_MOUSE_deshabcursor();
     flagmouse = TRUE;
    }

 (VIDEO_VISUAL_funcao_disparo)(VD_NULO,VIDEO_VISUAL_titulo_tela,FALSE,
                                &VIDEO_VISUAL_imagem_padrao,VD_NULO,FALSE);
 if (flagmouse)
    VIDEO_MOUSE_habcursor();


 return(TRUE);
}

