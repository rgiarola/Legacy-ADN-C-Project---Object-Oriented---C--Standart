#include <INCVIDEO.H>

INT2 VIDEO_CALC_dispara()
{
 BOOLEAN flagerro = TRUE;

 if (VIDEO_CALC_status&VIDEO_CALC_ATIVA)
    return(TRUE);

 if (VIDEO_CRG_carrega_objeto(&VIDEO_CALC_telacalc,1))
    {
     if (VIDEO_CRG_prepara_tela(&VIDEO_CALC_telacalc))
        {
         VIDEO_CALC_inicializa();
         VIDEO_CRG_dispara_tela(&VIDEO_CALC_telacalc);
         VIDEO_TECLADO_funcao_auxiliar = VIDEO_CALC_funcao_teclado;
         VIDEO_swap_tratadores(VIDEO_CALC_tratador,VIDEO_TELA_tabserv_navegacao,
                               TRUE,VD_NULO);
         VIDEO_CALC_status = VD_NULO;
         flagerro = FALSE;
        }
     VIDEO_CRG_libera_tela(&VIDEO_CALC_telacalc);
    }

 if (flagerro)
    {
     char buffer[200],bufaux[10];
     if (isam_err || uerr_cod)
         sprintf(buffer,VIDEO_CARGA_mens_exec_tela,
                        VIDEO_CALC_telacalc.sistcrg,
                        itoa(CINT(&VIDEO_CALC_telacalc.telacrg),bufaux,10),
                        isam_err);
         else
           strcpy(buffer,VIDEO_calculadora_nao_disp);
     VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_objeto_nao_carregado);
    }

 return(TRUE);
}
