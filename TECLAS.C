#include <INCVIDEO.H>

main()
{
 BYTE     ascii,scan,
          teclas,
          far *teclado,
          far *tec2;
 char     buffer[200];
 BYTE *buffer_teclado = MK_FP(0X0040,0X001E);
 WORD *inicio_teclado = MK_FP(0X0040,0X001A),
      *fim_teclado    = MK_FP(0X0040,0X001C);

 teclado = MK_FP(0X0040,0X0017);
 tec2    = MK_FP(0X0040,0X0018);

 clrscr();
 ascii = scan = 0;
 do
  {
// if(kbhit())
//   VD_getkbd(&ascii,&scan);
     VD_getkey(&ascii,&scan);

   teclas = *teclado;
   sprintf(buffer,"IN %d CL %d NL %d SL %d AL %d CT %d SE %d SD %d ASCII %d SCAN %d CAR %c   ",
   ((teclas & VD_B7) ? 1 : 0),
   ((teclas & VD_B6) ? 1 : 0),
   ((teclas & VD_B5) ? 1 : 0),
   ((teclas & VD_B4) ? 1 : 0),
   ((teclas & VD_B3) ? 1 : 0),
   ((teclas & VD_B2) ? 1 : 0),
   ((teclas & VD_B1) ? 1 : 0),
   ((teclas & VD_B0) ? 1 : 0),
   ascii,scan,ascii);
   VD_tprt_l(2,3,buffer,7);
   VD_gtxy(1,10);
   printf("%04X %04X",*inicio_teclado,*fim_teclado);

   teclas = *tec2;
   sprintf(buffer,"IN %d CL %d NL %d SL %d PA %d SY %d AE %d CE %d ",
   ((teclas & VD_B7) ? 1 : 0),
   ((teclas & VD_B6) ? 1 : 0),
   ((teclas & VD_B5) ? 1 : 0),
   ((teclas & VD_B4) ? 1 : 0),
   ((teclas & VD_B3) ? 1 : 0),
   ((teclas & VD_B2) ? 1 : 0),
   ((teclas & VD_B1) ? 1 : 0),
   ((teclas & VD_B0) ? 1 : 0));
   VD_tprt_l(2,4,buffer,7);
  }while(ascii != 27);
}

