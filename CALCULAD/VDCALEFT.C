#include <INCVIDEO.H>

VD_VOID VIDEO_CALC_efetua_operacao(campo)
VIDEO_CAMPO_TELA *campo;
{
 double varaux, valor;

 varaux = 1.0;
 valor  = VIDEO_CALC_memoria_display;

 if (campo->decimais)
     varaux = pow(10.0,D(campo->decimais));

 valor = VIDEO_CALC_memoria_display;
 switch(VIDEO_CALC_operacao_secundaria)
  {
   case VIDEO_CALC_SOMA:
        VIDEO_CALC_memoria_operacao += VIDEO_CALC_memoria_display;
        VD_GETBUF(BCALC_operacao,char) = ' ';
        break;

   case VIDEO_CALC_SUBTRACAO:
        VIDEO_CALC_memoria_operacao -= VIDEO_CALC_memoria_display;
        VD_GETBUF(BCALC_operacao,char) = ' ';
        break;

   case VIDEO_CALC_DIVISAO:
        valor  /= varaux;
        if ((valor > -0.000000000000001) && (valor <  0.000000000000001))
           {
            VIDEO_CALC_status |= VIDEO_CALC_ERRO;
            VD_GETBUF(BCALC_status,char) = 'E';
            return;
		   }
		VIDEO_CALC_memoria_operacao /= valor;
        VD_GETBUF(BCALC_operacao,char) = ' ';
        break;

   case VIDEO_CALC_MULTIPLICACAO:
        VIDEO_CALC_memoria_operacao *= D(VIDEO_CALC_memoria_display/varaux);
        VD_GETBUF(BCALC_operacao,char) = ' ';
        break;

   case VIDEO_CALC_PERCENTUAL:VIDEO_CALC_calcula_percentual(campo);
        VD_GETBUF(BCALC_operacao,char) = ' ';
        VIDEO_CALC_operacao_secundaria = 0;
        return;

   case VIDEO_CALC_EXPONECIAL:
        VIDEO_CALC_operacao_secundaria = 0;
        VD_GETBUF(BCALC_operacao,char) = ' ';
        if (VIDEO_CALC_memoria_operacao < 0)
           {
            VIDEO_CALC_status |= VIDEO_CALC_ERRO;
            VIDEO_CALC_status |= VIDEO_CALC_REDISPLAY;
            VIDEO_CALC_memoria_operacao=
            VIDEO_CALC_memoria_display =
            CDOUBLE(campo->buffer_binario);
            VD_GETBUF(BCALC_status,char) = 'E';
            return;
           }

        VIDEO_CALC_memoria_operacao = pow(VIDEO_CALC_memoria_operacao/varaux,
                                          VIDEO_CALC_memoria_display/varaux)*varaux;
  }

 CDOUBLE(campo->buffer_binario) = VIDEO_CALC_memoria_operacao;

 VIDEO_CALC_status |= VIDEO_CALC_OPEREFET;

 VD_GETBUF(BCALC_status,char) = ' ';
}

