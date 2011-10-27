#include <INCVIDEO.H>

VD_VOID VIDEO_CALC_calcula_percentual(campo)
VIDEO_CAMPO_TELA *campo;
{
 double aux1,aux2,aux3;

 aux1 = VIDEO_CALC_memoria_operacao;

 aux3 = 1.;
 if (campo->decimais)
    aux3 = pow(D(10.0),D(campo->decimais));

 if (campo->decimais)
    aux1 /= aux3;

 aux2 = D(aux1*(VIDEO_CALC_memoria_display/aux3/100.0));

 switch(VIDEO_CALC_operacao_atual)
  {
   case VIDEO_CALC_SOMA:
        VIDEO_CALC_memoria_operacao = aux1 + aux2;
        break;

   case VIDEO_CALC_SUBTRACAO:
        VIDEO_CALC_memoria_operacao = aux1 - aux2;
        break;

   case VIDEO_CALC_DIVISAO:
		if ((aux2 > -0.000000000000001) && (aux2 < 0.000000000000001))
		   {
            VIDEO_CALC_status |= VIDEO_CALC_ERRO;
            VD_GETBUF(BCALC_status,char) = 'E';
            return;
		   }
          else
            VIDEO_CALC_memoria_operacao = aux1 / aux2;
        break;

   case VIDEO_CALC_MULTIPLICACAO:
        VIDEO_CALC_memoria_operacao = aux2;
        break;
  }

 if (campo->decimais)
    VIDEO_CALC_memoria_operacao *= aux3;

 CDOUBLE(campo->buffer_binario) = VIDEO_CALC_memoria_operacao;
 VIDEO_CALC_status |= VIDEO_CALC_OPEREFET;
 VD_GETBUF(BCALC_status,char) = ' ';
}

