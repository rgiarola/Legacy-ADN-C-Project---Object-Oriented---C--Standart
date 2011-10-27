#include<INCVIDEO.H>

#define VDM_LENTO_VERTICAL(x,y)    ((x>=17)&&(x<=19)&&(y==7))
#define VDM_LENTO_HORIZONTAL(x,y)  ((x>=17)&&(x<=19)&&(y==11))
#define VDM_RAPIDO_VERTICAL(x,y)   ((x>=48)&&(x<=50)&&(y==7))
#define VDM_RAPIDO_HORIZONTAL(x,y) ((x>=48)&&(x<=50)&&(y==11))
#define VDM_SETADO(x,y)            ((x>=30)&&(x<=37)&&(y>=13)&&(y<=15))
#define VDM_REGUA_VERTICAL(x,y)    ((x>19)&&(x<48)&&(y==7))
#define VDM_REGUA_HORIZONTAL(x,y)  ((x>19)&&(x<48)&&(y==11))

VD_VOID VIDEO_MOUSE_config(VD_VOID)
{
 VIDEO_ESTMANUT VIDEO_MOUSE_tela =
  {VIDEO_padrao_sistema,    TELA_PADROES_MOUSE,VD_NULO,VD_NULO};
 BYTE ascii,scan;
 int  col,lin;

 if (VIDEO_MOUSE_ativo)
    {
	 VD_PUSHWIN(1,80,1,25);

     if (VIDEO_CRG_display_imagem(&VIDEO_MOUSE_tela,1,0))
        {
         VD_tcursor(0X32,0X32);
         VIDEO_MOUSE_flagtravado = TRUE;
         VIDEO_MOUSE_timetrav = 10;

         if (VIDEO_MOUSE_vel_horizontal > 100)
             VIDEO_MOUSE_vel_horizontal = 100;
         if (VIDEO_MOUSE_vel_vertical > 100)
             VIDEO_MOUSE_vel_vertical = 100;

         if (VIDEO_MOUSE_vel_horizontal < 0)
             VIDEO_MOUSE_vel_horizontal = 0;
         if (VIDEO_MOUSE_vel_vertical < 0)
             VIDEO_MOUSE_vel_vertical = 0;

         do
          {
		   col = (47.-20.)*((100-VIDEO_MOUSE_vel_vertical)/100.)+20;
           lin = 7;
           VIDEO_CLEAR_PIC(20,47,7,7,PD_COR_01);
		   VIDEO_plotcarac(col,lin,178,PD_COR_01);

           col = (47.-20.)*((100-VIDEO_MOUSE_vel_horizontal)/100.)+20;
		   lin = 11;
           VIDEO_CLEAR_PIC(20,47,11,11,PD_COR_01);
		   VIDEO_plotcarac(col,lin,178,PD_COR_01);

		   VIDEO_MOUSE_habcursor();
		   do
			{
			 VD_getkbd(&ascii,&scan);
			}while(I(VD_MTTECLA(1,VIDEO_MOUSE_BOTCLICK)) != I(VD_MTTECLA(ascii,scan)) &&
				   I(VD_MTTECLA(2,VIDEO_MOUSE_BOTCLICK)) != I(VD_MTTECLA(ascii,scan)) &&
				   I(VD_MTTECLA(1,VIDEO_MOUSE_BOTTRV))	 != I(VD_MTTECLA(ascii,scan)) &&
				   I(VD_MTTECLA(ENTER,ENTERSCAN))		 != I(VD_MTTECLA(ascii,scan)) &&
                   I(VD_MTTECLA(ESCAPE,ESCAPESCAN))      != I(VD_MTTECLA(ascii,scan)));

           VIDEO_MOUSE_deshabcursor();

		   switch(I(VD_MTTECLA(ascii,scan)))
            {
             case I(VD_MTTECLA(1,VIDEO_MOUSE_BOTCLICK)):
             case I(VD_MTTECLA(2,VIDEO_MOUSE_BOTCLICK)):
             case I(VD_MTTECLA(1,VIDEO_MOUSE_BOTTRV))  :
                  if (VDM_LENTO_VERTICAL(VIDEO_MOUSE_coluna_atual,
                                         VIDEO_MOUSE_linha_atual))
                     {
                      if ((VIDEO_MOUSE_vel_vertical + 1) <= 100)
                          VIDEO_MOUSE_vel_vertical += 1;
					  break;
					 }

				  if (VDM_RAPIDO_VERTICAL(VIDEO_MOUSE_coluna_atual,
										  VIDEO_MOUSE_linha_atual))
                     {
                      if ((VIDEO_MOUSE_vel_vertical - 1) >= 0)
                          VIDEO_MOUSE_vel_vertical -= 1;
					  break;
					 }

				  if (VDM_LENTO_HORIZONTAL(VIDEO_MOUSE_coluna_atual,
										   VIDEO_MOUSE_linha_atual))
                     {
                      if ((VIDEO_MOUSE_vel_horizontal + 1) <= 100)
                          VIDEO_MOUSE_vel_horizontal += 1;
					  break;
					 }

                  if (VDM_RAPIDO_HORIZONTAL(VIDEO_MOUSE_coluna_atual,
                                            VIDEO_MOUSE_linha_atual))
                     {
                      if ((VIDEO_MOUSE_vel_horizontal - 1) >= 0)
                          VIDEO_MOUSE_vel_horizontal -= 1;
					  break;
					 }

                  if (VDM_SETADO(VIDEO_MOUSE_coluna_atual,
                                 VIDEO_MOUSE_linha_atual))
                     {
                      VD_POPWIN();
                      return;
                     }

				  if (VDM_REGUA_VERTICAL(VIDEO_MOUSE_coluna_atual,
                                         VIDEO_MOUSE_linha_atual))
					 {
                      VIDEO_MOUSE_vel_vertical = 100 - 100./(47.-20.+1.)*(VIDEO_MOUSE_coluna_atual-19);
					  break;
					 }

				  if (VDM_REGUA_HORIZONTAL(VIDEO_MOUSE_coluna_atual,
										   VIDEO_MOUSE_linha_atual))
					 {
                      VIDEO_MOUSE_vel_horizontal = 100. - 100./(47.-20.+1.)*(VIDEO_MOUSE_coluna_atual-19);
					  break;
					 }

                  break;

             case I(VD_MTTECLA(ENTER,ENTERSCAN))  :
			 case I(VD_MTTECLA(ESCAPE,ESCAPESCAN)):VD_POPWIN();
												   return;
			}

           VIDEO_MOUSE_velocidade(W(0XF777));
           VIDEO_MOUSE_velocidade(W(0));
           VIDEO_MOUSE_dpi(VIDEO_MOUSE_vel_horizontal,VIDEO_MOUSE_vel_vertical);
           VIDEO_MOUSE_velocidade(W(0));

		  }while(TRUE);
		}
	 VD_POPWIN();
	}
}
