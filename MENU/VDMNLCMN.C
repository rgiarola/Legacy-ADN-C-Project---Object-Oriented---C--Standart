#include <INCVIDEO.H>

INT2 VIDEO_MENU_localiza_menu(desc,menu_num)
INT2 desc,
    menu_num;
{
 INT2 cont,
     num;
 do
  {
   if (VIDEO_read(desc,&num,2) != 2)
      return(VIDEO_MENU_NAO_LOCALIZADO);
   if (num == menu_num)
      return(VIDEO_MENU_LOCALIZADO);
   if (VIDEO_read(desc,&num,2) != 2)
      return(VIDEO_MENU_ERRO_ARQUIVO);
   VIDEO_lseek(desc,L(num+sizeof(VIDEO_INFO_MENU)),VD_MEIO_ARQ);
  }while(TRUE);
}
