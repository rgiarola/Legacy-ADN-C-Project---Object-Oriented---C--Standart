#include <INCVIDEO.H>

VD_VOID VIDEO_CALC_inicializa()
{
 VIDEO_CALC_memoria_auxiliar =
 VIDEO_CALC_memoria_operacao =
 VIDEO_CALC_memoria_display  =
 VIDEO_CALC_status           =
 VIDEO_CALC_operacao_atual   =
 VIDEO_CALC_operacao_secundaria = VD_NULO;
 VIDEO_CALC_funcao_teclado = VIDEO_TECLADO_funcao_auxiliar;
 VIDEO_TECLADO_funcao_auxiliar = VIDEO_CALC_intercepta_caracter;
 PTR_CAST(VIDEO_CAMPO_TELA,PTR_CAST(VIDEO_TABCRGTELA,
		  VIDEO_CALC_telacalc.strtelacrg)->imagemsai->campos->VIDEO_campos)->tabskip =
          VIDEO_tabskip_calculadora;
 VIDEO_swap_tratadores(VIDEO_CALC_tratador,VIDEO_TELA_tabserv_navegacao,FALSE,VD_NULO);
 VIDEO_CALC_status = VIDEO_CALC_ATIVA;
 VD_GETBUF(BCALC_status,char) = VD_GETBUF(BCALC_operacao,char) = ' ';
 VD_GETBUF(BCALC_decimais,BYTE) = 2;
 VD_GETBUF("CALC_valor",double)  = 0;
}


