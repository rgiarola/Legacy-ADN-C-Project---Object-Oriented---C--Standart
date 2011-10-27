#include <INCVIDEO.H>

main()
{
 INT2 col,lin,botpres,numclick,colpress,linpress,cont,velocidade;
 char buffer[200];
 BYTE ascii,scan;

 cont = col = lin = botpres = numclick = colpress = linpress = 0;

 if ((VIDEO_MOUSE_ativo = VIDEO_MOUSE_inicializa()) > 0)
    {
     VIDEO_MOUSE_setpos(1,1);
     VIDEO_MOUSE_habcursor();
     VIDEO_MOUSE_deshabcursor();
    }

 VD_CLS;

 do
  {
   botpres = numclick = colpress = linpress = 0;
   VIDEO_MOUSE_habcursor();
   VIDEO_MOUSE_getpos(&col,&lin);

   if (VIDEO_MOUSE_intbotpres())
      {
       VIDEO_MOUSE_intbot(&botpres,&numclick,&colpress,&linpress);
       VIDEO_MOUSE_deshabcursor();
       sprintf(buffer,"COL %2d LIN %2d BOT %d NUMCLICK %d COLC %2d LINC %2d %d",
                      col,lin,botpres,numclick,colpress,linpress,++cont);
       VD_tprt_l(1,1,buffer,7);
       VIDEO_MOUSE_habcursor();
      }

   if (VD_getkey(&ascii,&scan))
      {
       if (ascii == 'A')
          break;

       VD_CLS;
       VD_gtxy(1,1);
       col = atoi(gets(buffer));
       lin = atoi(gets(buffer));
       VIDEO_MOUSE_dpi(col,lin);
       lin = atoi(gets(buffer));
       VIDEO_MOUSE_velocidade(lin);
      }

  }while(TRUE);

 VIDEO_MOUSE_deshabcursor();
}



