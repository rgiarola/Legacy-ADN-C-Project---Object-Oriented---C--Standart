#include<INCVIDEO.H>

INT2 VIDEO_ARVORE_mousedoistrav(VIDEO_ARVORE_ESTRUTURA **arvore,
                               VIDEO_NUCLEO_SERV      **param)
{
 VIDEO_ARVORE_ESTRUTURA *arvloc;

 arvloc = *arvore;

 if (arvloc->nomehelp)
    {
     if (VIDEO_MOUSE_ativo)
        if (!((arvloc->scan != VIDEO_MOUSE_BOTCLICK)&&(arvloc->scan != VIDEO_MOUSE_BOTTRV)))
           VIDEO_MOUSE_deshabcursor();

     VD_PUSHWIN(arvloc->colf-5,arvloc->colf-1,
                arvloc->lini,arvloc->lini);
     VIDEO_horizontal(arvloc->colf-5,arvloc->colf-1,
                      arvloc->lini,VIDEO_ARVORE_espaco_branco,arvloc->cor_titulo);
     VIDEO_VISUAL_dispara_visual(arvloc->nomehelp,VD_NULO,TRUE,
                                 &VIDEO_HELP_imagem_padrao,
                                 VIDEO_VISUAL_menu,FALSE);
     VD_POPWIN();
     if (VIDEO_MOUSE_ativo)
        if (!((arvloc->scan != VIDEO_MOUSE_BOTCLICK)&&(arvloc->scan != VIDEO_MOUSE_BOTTRV)))
         VIDEO_MOUSE_habcursor();
    }
 return(TRUE);
}
