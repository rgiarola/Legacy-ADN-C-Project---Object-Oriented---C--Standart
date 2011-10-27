#include <INCVIDEO.H>

long int VIDEO_systime(VOID)
{
 VD_time hora_sistema;

 VD_gettime( &hora_sistema );

 return( L(VIDEO_timein( VD_timeHor(hora_sistema),VD_timeMin(hora_sistema),
                       VD_timeSeg(hora_sistema))) );
}

/* ----------------------------------------------------------------------------
   VIDEO_timein()
   CONVERTE  TIME do tipo FORMAL para computacional
   retorna computacional
   ---------------------------------------------------------------------------- */
long int VIDEO_timein(hora, minuto, segundo)
int hora,
    minuto,
    segundo;
{
 return( L(L(segundo)+L(minuto*100L)+L(hora*10000L)) );
}


/* ----------------------------------------------------------------------------
   VIDEO_timein()
   CONVERTE  TIME do tipo computacional para FORMAL
   retorna FALSE se convertido
   ---------------------------------------------------------------------------- */
int VIDEO_timeout(long compute, int *hora, int *minuto, int *segundo)
{
 long auxtime;

 if (!compute)
    {
     *hora = *minuto = *segundo = 0;
     return(TRUE);
    }

 auxtime = (compute/100L)*100L;
 *segundo= compute - auxtime;

 compute = auxtime/100L;

 auxtime = (compute/100L)*100L;
 *minuto = compute - auxtime;

 compute = auxtime/100L;

 auxtime = (compute/100L)*100L;
 *hora   = compute - auxtime;

 if ( *hora<0 || *minuto<0 || *segundo<0)
    return(TRUE);

 return(FALSE);
}



