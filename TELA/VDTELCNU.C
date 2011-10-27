#include <INCVIDEO.H>
/* ok*/
INT2 VIDEO_TELA_compara_numero(string1,string2,tamanho)
char *string1,
	 *string2;
WORD tamanho;
{
 double valor,
		decimais;
 char   *aux,
        carac;
 INT2    flagdec,
        tam;

 tam = strlen(string2);
 if (tamanho < tam)
    {
     carac = *(string2+tamanho);
     *(string2+tamanho) = '\0';
    }
  else
    carac = 0;

 flagdec  = FALSE;
 decimais = 1.;
 aux	  = string2;
 while(*aux)
  {
   if (flagdec)
	  decimais *= 10.;
   if (*aux++ == '.')
	  flagdec = TRUE;
  }

 valor = CDOUBLE(string1) - D(atof(string2) * decimais);

 if (carac)
    *(string2+tamanho) = carac;

 if (valor > 0.001)
     return(1);

 if (valor < -0.001)
     return(-1);

 return(FALSE);
}

