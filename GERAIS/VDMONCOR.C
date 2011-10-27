#include <INCVIDEO.H>

BYTE VIDEO_monta_cor(cor)
BYTE cor;
{
#ifdef VIDEO_DOS
 BYTE fundo,frente,cortab,
 	   *tabfundo,*tabfrente;
 int  cont;

 fundo  = B(cor&B(0XF0));
 frente = B(cor&B(0X0F));

 if (VIDEO_tabela_cor_de_fundo)
	{
	 tabfundo  = VIDEO_tabela_cor_de_fundo;
	 tabfrente = VIDEO_tabela_cor_de_frente;

     for (cortab = cont = 0;cont < 16 && (cortab&(VD_B0|VD_B1)) != (VD_B0|VD_B1);
										  cont++,tabfundo+=2,tabfrente+=2)
		 {
          if (!(cortab&VD_B0) && fundo == *tabfundo)
			 {
			  fundo = *(tabfundo+1);
              cortab |= VD_B0;
			 }

          if (!(cortab&VD_B1) && frente == *tabfrente)
			 {
              frente = *(tabfrente+1);
              cortab |= VD_B1;
			 }
		 }
	}

 return(B(fundo)|B(frente));
#endif

#ifdef VIDEO_UNIX
 return(B(cor&B(VIDEO_INTER|VIDEO_BRIL)));
#endif
}

