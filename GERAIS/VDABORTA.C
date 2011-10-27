#include <INCVIDEO.H>

int VIDEO_aborta(VD_VOID)
{
 return(TRUE);
/*
 static BOOLEAN flagaborta = FALSE;

 disable();
 if (flagaborta)
    {
     enable();
     return(TRUE);
    }
 ++flagaborta;
 enable();

 {
  BOOLEAN flag24 = FALSE, flag05 = FALSE, flagpop;

  flagpop = VIDEO_modo_swap_window;
  VIDEO_modo_swap_window = FALSE;

 if (getvect(0X24) == VIDEO_VISUAL_nova_int24)
    {
     flag24 = TRUE;
     setvect(0X24,VIDEO_VISUAL_velha_int24);
    }

 if (getvect(0X05) == VIDEO_VISUAL_nova_int05)
    {
     flag05 = TRUE;
     setvect(0X05,VIDEO_VISUAL_velha_int05);
    }

 switch(VIDEO_mostra_mens_erro("Encerra Sistema ",FALSE))
  {
   case VD_MTTECLA(1,VIDEO_MOUSE_BOTCLICK):
   case VD_MTTECLA(2,VIDEO_MOUSE_BOTCLICK):
   case VD_MTTECLA(1,VIDEO_MOUSE_BOTTRV)  :
   case VD_MTTECLA(2,VIDEO_MOUSE_BOTTRV)  :
        if (!(((VIDEO_LIN_MENSAGEM+3) == VIDEO_MOUSE_linha_atual) &&
              (VIDEO_MOUSE_coluna_atual >= 36) &&
              (VIDEO_MOUSE_coluna_atual <= 41)))
              break;
                                           
   case VD_MTTECLA('S',ALT_S)       :
   case VD_MTTECLA('s',ALT_S)       :
   case VD_MTTECLA('',ALT_S)       :
   case VD_MTTECLA(VD_NULO,ALT_O)   :
   case VD_MTTECLA(ENTER ,ENTERSCAN):
   case VD_MTTECLA(10    ,ENTERSCAN):
        return(FALSE);
  }
 if (flag05)
     setvect(0X05,VIDEO_VISUAL_nova_int05);

 if (flag24)
     setvect(0X24,VIDEO_VISUAL_nova_int24);

  VIDEO_modo_swap_window = flagpop;
 }
 disable();
 --flagaborta;
 enable();
 return(TRUE);

*/
}

