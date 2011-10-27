#include<INCVIDEO.H>

INT2 VIDEO_ARVORE_setas_mouse(arvore,param)
VIDEO_ARVORE_ESTRUTURA **arvore;
VIDEO_NUCLEO_SERV      **param;
{
 VIDEO_ARVORE_ESTRUTURA *arvore_loc;
 arvore_loc = *arvore;

 if ((VIDEO_MOUSE_colclick == arvore_loc->colf) &&
     (VIDEO_MOUSE_linclick == (arvore_loc->lini+arvore_loc->lini_offset)))
	 {
	  VIDEO_MOUSE_deshabcursor();
	  return(VIDEO_ARVORE_linha_superior(arvore,param));
	 }

 if ((VIDEO_MOUSE_colclick == arvore_loc->colf) &&
     (VIDEO_MOUSE_linclick == (arvore_loc->linf-2)))
	 {
	  VIDEO_MOUSE_deshabcursor();
	  return(VIDEO_ARVORE_linha_inferior(arvore,param));
	 }

 if ((VIDEO_MOUSE_colclick == (arvore_loc->colf-1)) &&
     (VIDEO_MOUSE_linclick == (arvore_loc->linf-2)))
	 {
	  VIDEO_MOUSE_deshabcursor();
	  return(VIDEO_ARVORE_coluna_posterior(arvore,param));
	 }

 if ((VIDEO_MOUSE_colclick == arvore_loc->coli) &&
     (VIDEO_MOUSE_linclick == (arvore_loc->linf-2)))
	 {
	  VIDEO_MOUSE_deshabcursor();
	  return(VIDEO_ARVORE_coluna_anterior(arvore,param));
	 }
 return(FALSE);
}
