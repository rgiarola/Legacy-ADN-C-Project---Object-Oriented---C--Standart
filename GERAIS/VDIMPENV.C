#include <INCVIDEO.H>
#ifdef VIDEO_write
#undef VIDEO_write
#endif

#define VIDEO_write(desc,buffer,tam)    write(desc,buffer,tam)

WORD VIDEO_IMPRESS_envia(carac,impressora)
char carac;
int  impressora;
{
 BOOLEAN flagint = FALSE, flagstatus,flagerro;
 int ret         = VIDEO_IMPRESSORA_OK;
 /*
 char teste[50];
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
 */

#ifdef MS_C
 union REGS regs;
 IstoEUmAvisoDeCompatibilidadedeCompilacao_NaoSeraApresentadoEmBC

 if (!impressora)
    {
     BOOLEAN flagint = FALSE, flagstatus,flagerro;
     int ret         = VIDEO_IMPRESSORA_OK;

     if (getvect(0X24) != VIDEO_VISUAL_nova_int24)
        {
         glagint = TRUE;
         VIDEO_VISUAL_velha_int24 = getvect(0X24);
         setvect(0X24,VIDEO_VISUAL_nova_int24);
        }

     flagerro   = VIDEO_VISUAL_flag_erro;
     flagstatus = VIDEO_VISUAL_flag_int;
	 VIDEO_VISUAL_flag_erro = FALSE;
     VIDEO_VISUAL_flag_int  = FALSE;
     if (VIDEO_write(VIDEO_IMPRESSORA_PADRAO,&carac,1) != 1 ||
         VIDEO_VISUAL_flag_erro)
        ret = VIDEO_ERRO_IMPRESSORA;

     if (flagint)
         setvect(0X24,VIDEO_VISUAL_velha_int24);

     VIDEO_VISUAL_flag_erro = flagerro  ;
     VIDEO_VISUAL_flag_int  = flagstatus;

     return(ret);
    }
 regs.h.ah = VIDEO_IMPRESSORA_ENVIA;
 regs.h.al = carac;
 regs.x.dx = --impressora;
 int86(VIDEO_IMPRESSORA_INT,&regs,&regs);
 return(I(regs.h.ah));
#else
/*
  Utilizando o BIOS, n„o ‚ necess rio INT24 para Manipular...
 if (getvect(0X24) != VIDEO_VISUAL_nova_int24)
    {
     // Obriga Instalacao
     flagint = TRUE;
     VIDEO_VISUAL_velha_int24 = getvect(0X24);
     setvect(0X24,VIDEO_VISUAL_nova_int24);
    }
 flagerro   = VIDEO_VISUAL_flag_erro;
 flagstatus = VIDEO_VISUAL_flag_int;
 VIDEO_VISUAL_flag_erro = FALSE;
 VIDEO_VISUAL_flag_int  = FALSE;
*/

/*
  Removido -> A INT21 n„o est  mapeando corretamente os c¢digos de erros ...
 if (!impressora)
    {
     // Tecnica 1
     if (VIDEO_write(VIDEO_IMPRESSORA_PADRAO,&carac,1) != 1 ||
         VIDEO_VISUAL_flag_erro)
        {
         ret = VIDEO_ERRO_IMPRESSORA;
         if (flagint)
             setvect(0X24,VIDEO_VISUAL_velha_int24);

         VIDEO_VISUAL_flag_erro = flagerro  ;
         VIDEO_VISUAL_flag_int  = flagstatus;
        }

     // Tecnica 2
     //
     // if ( ((fwrite (&carac,1,1,stdprn))!=1) || VIDEO_VISUAL_flag_erro)
     //     {
     //      ret = VIDEO_ERRO_IMPRESSORA;
     //      if (flagint)
     //          setvect(0X24,VIDEO_VISUAL_velha_int24);
     //
     //      VIDEO_VISUAL_flag_erro = flagerro  ;
     //      VIDEO_VISUAL_flag_int  = flagstatus;
     //     }
     //

     return(ret);
    }
 */


 _DX = impressora-1;
 _AH = VIDEO_IMPRESSORA_ENVIA;           // Servico 0X00
 _AL = carac;                            // Caracter a Enviar
 geninterrupt(0x17);                     // 0X17 (Servi‡o de Impressora)
 ret = _AX;
 /*
 retorno15 = ret&B15 ? 1 : 0;
 retorno14 = ret&B14 ? 1 : 0;
 retorno13 = ret&B13 ? 1 : 0;
 retorno12 = ret&B12 ? 1 : 0;
 retorno11 = ret&B11 ? 1 : 0;
 retorno10 = ret&B10 ? 1 : 0;
 retorno09 = ret&B09 ? 1 : 0;
 retorno08 = ret&B08 ? 1 : 0;
 retorno07 = ret&B07 ? 1 : 0;
 retorno06 = ret&B06 ? 1 : 0;
 retorno05 = ret&B05 ? 1 : 0;
 retorno04 = ret&B04 ? 1 : 0;
 retorno03 = ret&B03 ? 1 : 0;
 retorno02 = ret&B02 ? 1 : 0;
 retorno01 = ret&B01 ? 1 : 0;
 retorno00 = ret&B00 ? 1 : 0;
                                         // 7 6 5 4 3 2 1 0
 sprintf (teste,"IMPRESSORA %d (%c) Ret %d %d%d%d%d%d%d%d%d %d%d%d%d%d%d%d%d ",
          impressora,carac,ret,
          retorno15,retorno14,retorno13,retorno12,retorno11,retorno10,
          retorno09,retorno08,retorno07,retorno06,retorno05,retorno04,
          retorno03,retorno02,retorno01,retorno00);
 VIDEO_grava_erro (teste);
 */

 /*
 Foi Desatviado por que n„o trazia beneficios...
 if (flagint)
     setvect(0X24,VIDEO_VISUAL_velha_int24);

 VIDEO_VISUAL_flag_erro = flagerro  ;
 VIDEO_VISUAL_flag_int  = flagstatus;
  */

 return(W(ret));
#endif
}
/*
imparquivo(carac)
char carac;
{
 int desc;
 vtclose();
 vtclose();
 if ((desc = VIDEO_open("SPOOL.SPL",
                       O_BINARY|O_APPEND|O_CREAT|O_RDWR,S_IREAD|S_IWRITE))> 0)
	{
     VIDEO_write(desc,&carac,1);
     VIDEO_close(desc);
	}
 return(VIDEO_IMPRESSORA_OK);
}

 return(imparquivo(carac));
*/
