#include <INCVIDEO.H>

INT2 VIDEO_MENU_seleciona_aborta(campos,param)
VIDEO_INFO_MENU   **campos;
VIDEO_NUCLEO_SERV **param;
{
 (*campos)->opselec = 0;
 return(FALSE);
}
