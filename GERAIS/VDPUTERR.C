#include <INCVIDEO.H>

INT2 VIDEO_grava_erro(mensagem)
char *mensagem;
{
 FILE *fp,*ctrt_fopen();
 int  try = 0;
 char    buffer[200],
         ArqDia[50];
 VD_time hora;
 VD_date data;
 DWORD   memdisp;
 int     dia,mes,ano;
 VD_gettime(&hora);
 VD_getdate(&data);

 do
  {
   fp = ctrt_fopen((pTEXT) VIDEO_arqstatus,(pTEXT) "a+b");
   if (fp == (FILE *) NULL)
      {
       if (try++ > 200)
          return(FALSE);
      }
    else
      break;
   vtclose();
  }while(TRUE);

 fprintf(fp,"%c%c%02d/%02d/%04d %02d:%02d:%02d %s",0X0D,0X0A,
                VD_dateDia(data),
                VD_dateMes(data),
                VD_dateAno(data),
                VD_timeHor(hora),
                VD_timeMin(hora),
                VD_timeSeg(hora),mensagem);

 ctrt_fclose(fp);


 // Criado um Novo LOG de Erros (POR DIA)
 // =-=========================================================================
 dia = VD_dateDia(data);
 mes = VD_dateMes(data);
 ano = VD_dateAno(data);
 if (ano>=2000)
    ano -= 2000;
  else
    ano -= 1900;
 sprintf (ArqDia,"ST%02d%02d%02d.ERR",ano,mes,dia);
 do
  {
   fp = ctrt_fopen((pTEXT) ArqDia,(pTEXT) "a+b");
   if (fp == (FILE *) NULL)
      {
       if (try++ > 200)
          return(FALSE);
      }
    else
      break;
   vtclose();
  }while(TRUE);

 fprintf(fp,"%c%c%02d/%02d/%04d %02d:%02d:%02d %s",0X0D,0X0A,
                VD_dateDia(data),
                VD_dateMes(data),
                VD_dateAno(data),
                VD_timeHor(hora),
                VD_timeMin(hora),
                VD_timeSeg(hora),mensagem);
 ctrt_fclose(fp);

 return(TRUE);
}

/************************************************************************

PLACA PREMIUN
SANSUNG SYNCMASTER 3
TRIDENTE
VESA LOCAL BUS TRIDENTE 1 MEGA
540 W
8 MEGA
GABINETE LONG TAL 3 DIGITOS
2 DRIVE
1 MOUSE LOGITECH
1 ESTABILIZADOR

TELEFONE 225-6365

************************************************************************/

