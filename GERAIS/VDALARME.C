#include <INCVIDEO.H>

ALARME_TIPO VIDEO_tabela_alarme[] = {
       {700,    700,    0,      20, 200,    1,  1},
       {950,    950,    0,      20, 200,    1,  1},
       {950,    700,    250,    50, 200,    1,  1},
       {950,    700,    250,    37, 200,    2,  1},
       {1050,   700,    350,    20, 200,    3,  1},
       {1100,   700,    200,    15, 100,    3,  1},
       {1300,   700,    300,    20, 0,      1,  2}};

VD_VOID VIDEO_freq(VD_VOID)
{
 register int freq=700;
          int sobe=1,
          minimo = 2,
          tecla;
 BYTE     ascii,scan;

 while(VIDEO_getkey(&ascii,&scan));

 tecla = FALSE;

 while(TRUE)
  {
   sound(freq);
   VIDEO_espera(1);

   if (VIDEO_getkey(&ascii,&scan))
       tecla = TRUE;

   if (!minimo)
      break;

   if (sobe)
      { // Frenquencia ascendente.
       if (freq < 1500)
          freq += 85;
        else
          {
           sobe = 0;
           if (tecla && minimo)
               --minimo;
          }
      }
    else
      { // Frequencia descendente.
       if (freq > 700)
          freq -= 75;
        else
          sobe = TRUE;
      }
  }

 nosound();
}

VD_VOID VIDEO_alarme_sonoro(maximo,minimo,inc,tempo1,tempo2,vezes,loop)
int maximo,minimo,inc,tempo1,tempo2,vezes,loop;
{
 BYTE    ascii = 0,scan = 0;
 int     freq,inicio,sobe,
         cont,cont2, saida;
 VD_time tinicio,tfim;

 while(VIDEO_getkey(&ascii,&scan));

 VD_gettime(&tinicio);

 sobe = TRUE;
 do
  {
   ascii = scan = 0;
   while(!VIDEO_getkey(&ascii,&scan))
    {
     for (cont = 0;cont < vezes && !ascii && !scan;cont++)
         {
          freq  = minimo;
          cont2 = 0;
          sobe  = TRUE;
          do
           {
            sound(freq);

            VIDEO_espera(tempo1);

            if (VIDEO_getkey(&ascii,&scan))
               break;

            if (sobe)
               {
                if (freq < maximo)
                   freq += inc;
                 else
                   {
                    sobe = FALSE;
                    ++cont2;
                   }
               }
             else
               {
                if (freq > minimo)
                   freq -= inc;
                 else
                   {
                    sobe = TRUE;
                    ++cont2;
                   }
               }
           }while(cont2 < loop  && !ascii && !scan);
         }

     nosound();

     if (ascii || scan)
        break;

     VIDEO_espera(tempo2);
    }

   if (ascii || scan)
      {
       saida = TRUE;
       ascii = scan = 0;
      }

   if (saida)
      {
       VD_gettime(&tfim);

       if (VIDEO_total_tempo(tfim) < VIDEO_total_tempo(tinicio))
          tinicio = tfim;

       if ((VIDEO_total_tempo(tfim)-VIDEO_total_tempo(tinicio)) > 200)
           ascii = scan = TRUE;
      }

  }while(!ascii && !scan);
}


