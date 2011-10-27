#include <INCVIDEO.H>

INT2 VIDEO_CRG_executa_menu(menu)
VIDEO_ESTMANUT *menu;
{
 if (VIDEO_CRG_executa_menu_carrega(menu))
    {
     INT2 ret,f1 = TRUE,f2 = TRUE,f3 = TRUE;
     do
      {
       ret = VIDEO_CRG_dispara_menu(menu,f1,f2,f3);
       if ((VIDEO_TECLA_ESCAPE_MENU(menu) == VD_MTTECLA(ESCAPE,ESCAPESCAN)) ||
           (VIDEO_TECLA_ESCAPE_MENU(menu) == VD_MTTECLA(ENTER,ENTERSCAN)))
           break;
       f1 = f2 = f3 = FALSE;
      }while(TRUE);

     VD_POPWIN();
     VIDEO_CRG_libera_tela(menu);
     return(ret);
    }

 return(FALSE);
}

INT2 VIDEO_CRG_executa_menu_carrega(menu)
VIDEO_ESTMANUT *menu;
{
 if (VIDEO_CRG_carrega_objeto(menu,2))
    {
     VIDEO_CRG_prepara_menu(menu);
     return(TRUE);
    }
/*
  else
    if (isam_err)
       {
        char buffer[200];
        sprintf(buffer,VIDEO_CARGA_mens_exec_menu,
                        menu->sistcrg,menu->telacrg,isam_err);
        VIDEO_mostra_mens_erro(buffer,TRUE);
       }
*/
 return(FALSE);
}

