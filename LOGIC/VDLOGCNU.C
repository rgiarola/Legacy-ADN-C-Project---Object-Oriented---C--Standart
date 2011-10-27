#include <INCVIDEO.H>
#include <SIGNAL.H>
#include <LOGIC.H>

/*----------------------------------------------------------------------------
                              COMPARA NUMERO
----------------------------------------------------------------------------*/

int VIDEO_LOGIC_compara_numero(n1,n2)
char *n1,*n2;
{
 double valor;

 valor = CDOUBLE(n1)-CDOUBLE(n2);

 if (valor > 0.)
     return(1);
 if (valor < 0.0)
     return(-1);

 return(FALSE);
}

