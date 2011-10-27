#include<INCVIDEO.H>

INT2 VIDEO_EDITA_monta_mascara(entrada,mascara,saida,caracter,col,flagset,flagmostra)
char    *entrada,
        *mascara,
        *saida,
        *caracter;
INT2     *col;
WORD    flagset,
        flagmostra;
{
 char    carmont;
 INT2     tammascara,
         tambuffer;
 BOOLEAN flagtest,
         retteste,
         flagcar;

 if (!mascara || !strlen(mascara))
    return(FALSE);

 do
  {
   flagtest = caracter == entrada;
   flagcar = VIDEO_EDITA_testa_caracter_na_mascara(entrada,*mascara,
                                                     &carmont,col);
   if (flagcar == TRUE)
      {
       if (flagtest)
          return(TRUE);
       if (*entrada)
          {
           *saida++ = flagmostra ? '*' : *entrada;
           ++entrada;
          }
         else
           *saida++ = carmont;
      }
    else
      if (flagcar == 2)
         {
          if (flagtest)
              return(TRUE);
          *saida++ = *mascara;
         }
       else
         {
          if (flagtest)
              return(FALSE);
          *saida++ = carmont;
          if (*entrada)
             {
              if (flagset)
                 *entrada = carmont;
              ++entrada;
             }
         }
  }while(*(++mascara));
  *saida = '\0';
 return(TRUE);
}

