#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_opcao(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 (*campos)->opselec = (*campos)->opsel + 1;
 return(FALSE);
}
