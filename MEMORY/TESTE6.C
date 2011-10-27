#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <bios.h>

#define B00                    (int)(    1)
#define B01                    (int)(    2)
#define B02                    (int)(    4)
#define B03                    (int)(    8)
#define B04                    (int)(   16)
#define B05                    (int)(   32)
#define B06                    (int)(   64)
#define B07                    (int)(  128)
#define B08                    (int)(  256)
#define B09                    (int)(  512)
#define B10                    (int)( 1024)
#define B11                    (int)( 2048)
#define B12                    (int)( 4096)
#define B13                    (int)( 8192)
#define B14                    (int)(16384)
#define B15                    (int)(32768)

void main(void)
{
 char teste[100];
 char retorno15,
      retorno14,
      retorno13,
      retorno12,
      retorno11,
      retorno10,
      retorno09,
      retorno08,
      retorno07,
      retorno06,
      retorno05,
      retorno04,
      retorno03,
      retorno02,
      retorno01,
      retorno00;
 union REGS regin, regout;
 unsigned int AX;
 unsigned int AH;
 /*
 regin.h.ah = 0x00;
 regin.h.al = 'a';
 regin.x.dx = 0;
 int86 (0x17,&regin,&regout);
 AX = regout.x.ax;
 AH = regout.x.flags;
 */

 printf ("\n Inciou...");
 _DX = 0;
 _AH = 0x00;
 _AL = 'A';
 geninterrupt(0x17);                     // 0X17 (Servi‡o de Impressora)
                                         // 7 6 5 4 3 2 1 0
 AX = _AX;
 regout.x.cflag = 0; // _CFLAG;
 regout.x.flags = _FLAGS;

 retorno15 = AX&B15 ? 1 : 0;
 retorno14 = AX&B14 ? 1 : 0;
 retorno13 = AX&B13 ? 1 : 0;
 retorno12 = AX&B12 ? 1 : 0;
 retorno11 = AX&B11 ? 1 : 0;
 retorno10 = AX&B10 ? 1 : 0;
 retorno09 = AX&B09 ? 1 : 0;
 retorno08 = AX&B08 ? 1 : 0;
 retorno07 = AX&B07 ? 1 : 0;
 retorno06 = AX&B06 ? 1 : 0;
 retorno05 = AX&B05 ? 1 : 0;
 retorno04 = AX&B04 ? 1 : 0;
 retorno03 = AX&B03 ? 1 : 0;
 retorno02 = AX&B02 ? 1 : 0;
 retorno01 = AX&B01 ? 1 : 0;
 retorno00 = AX&B00 ? 1 : 0;


 sprintf (teste,"Flag %d %d Ret %d %d %d %d %d %d %d %d %d %d%d%d%d%d%d%d%d ",
          regout.x.cflag,
          regout.x.flags,
          AX,
          retorno15,retorno14,retorno13,retorno12,retorno11,retorno10,
          retorno09,retorno08,retorno07,retorno06,retorno05,retorno04,
          retorno03,retorno02,retorno01,retorno00);

 printf ("\n %s",teste); getch();

 exit (0);
}

