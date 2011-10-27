#include <INCVIDEO.H>

INT2 VIDEO_CRG_dispara_menu(menu,flagdispcol,flagdispop,flagmoldura)
VIDEO_ESTMANUT *menu;
INT2            flagdispcol,
			   flagdispop,
			   flagmoldura;
{
 VIDEO_NUCLEO_SERV *nucleo;
 VIDEO_INFO_MENU   *menudisp;
 char			   *buffercrg;
 INT2               cont;

 buffercrg = PTR_CAST(char,menu->strtelacrg);

 menudisp   = PTR_CAST(VIDEO_INFO_MENU,(buffercrg+sizeof(VIDEO_NUCLEO_SERV)));
 nucleo = PTR_CAST(VIDEO_NUCLEO_SERV,buffercrg);
 menudisp->flagdispcol = flagdispcol;
 menudisp->flagdispop  = flagdispop;
 menudisp->flagmoldura = flagmoldura;
 menudisp->opselec     = 0;
 nucleo->VIDEO_servrec =
 nucleo->VIDEO_repdisp = FALSE;

 VIDEO_NUCLEO_servidor_mspas(nucleo);

 return(menudisp->opselec);
}

