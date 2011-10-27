#include <INCVIDEO.H>

VD_VOID VIDEO_espera(tempo)
int tempo;
{
 VD_time inicio,fim;
 double  totini,totfim;

 VD_gettime(&inicio);
 do
  {
   VD_gettime(&fim);
   totfim = VIDEO_total_tempo(fim);
   totini = VIDEO_total_tempo(inicio);
   if (totfim < totini)
      break;
  }while((totfim - totini) < tempo);
}

double VIDEO_total_tempo(tempo)
VD_time tempo;
{
 return(VD_timeHor(tempo) * 360000. +
        VD_timeMin(tempo) * 6000.   +
        VD_timeSeg(tempo) * 100.    +
        VD_timeHsc(tempo));
}

VD_time VIDEO_conv_tempo_total(double TempoTotal)
{
 DWORD   hor,
         min,
         seg,
         decs;
 VD_time ConvTempo;

 hor = DW (TempoTotal / 360000UL);
 TempoTotal -= hor * 360000UL;

 min = DW (TempoTotal / 6000UL);
 TempoTotal -= min * 6000UL;

 seg = DW (TempoTotal / 100UL);
 TempoTotal -= seg * 100UL;

 decs = DW (TempoTotal);

 VD_timeHor(ConvTempo) = hor;
 VD_timeMin(ConvTempo) = min;
 VD_timeSeg(ConvTempo) = seg;
 VD_timeHsc(ConvTempo) = decs;

 return (ConvTempo);
}

