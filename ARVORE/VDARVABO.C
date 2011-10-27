#include <INCVIDEO.H>

INT2 VIDEO_ARVORE_aborta_arvore(VIDEO_ARVORE_ESTRUTURA **arvore,
                               VIDEO_NUCLEO_SERV      **param)
{
 VIDEO_ARVORE_ESTRUTURA *arvoreloc;

 arvoreloc = *arvore;

 if ((VIDEO_MOUSE_linclick == arvoreloc->lini)     &&
     (VIDEO_MOUSE_colclick >= (arvoreloc->colf-5)) &&
     (VIDEO_MOUSE_colclick <= (arvoreloc->colf-1)))
    {
     (*param)->VIDEO_repdisp = TRUE;
     (*param)->VIDEO_servrec = VIDEO_MTTECLA(ESCAPE,ESCAPESCAN);
     return(TRUE);
    }
 return(FALSE);
}

