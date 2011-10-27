#include <INCVIDEO.H>

int matherr(struct exception *a)
{
 VIDEO_CALC_status |= VIDEO_CALC_ERRO;
 VD_GETBUF(BCALC_status,char) = 'E';
 a->retval = a->arg1 = a->arg2 = 0.0;
 return (TRUE);
}

