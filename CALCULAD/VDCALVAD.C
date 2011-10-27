#include <INCVIDEO.H>

WORD VIDEO_tabskip_calculadora[] = {
                  VIDEO_MTTECLA(ENTER   ,ENTERSCAN),
                  VIDEO_MTTECLA(CTRL_ENT,ENTERSCAN),
                  VIDEO_MTTECLA(VD_NULO ,ESCAPESCAN),
                  VIDEO_MTTECLA(ESCAPE  ,ESCAPESCAN),

                  VIDEO_MTTECLA(VD_NULO ,ALT_S),
                  VIDEO_MTTECLA('S'     ,ALT_S),
                  VIDEO_MTTECLA('s'     ,ALT_S),
                  VIDEO_MTTECLA(19      ,ALT_S),

                  VIDEO_MTTECLA(VD_NULO ,ALT_F),
                  VIDEO_MTTECLA('F'     ,ALT_F),
                  VIDEO_MTTECLA('f'     ,ALT_F),
                  VIDEO_MTTECLA(6       ,ALT_F),

                  VIDEO_MTTECLA('M'     ,ALT_M),
                  VIDEO_MTTECLA('m'     ,ALT_M),

                  VIDEO_MTTECLA('A'     ,ALT_A),
                  VIDEO_MTTECLA('a'     ,ALT_A),
                  VIDEO_MTTECLA(VD_NULO ,ALT_A),
                  VIDEO_MTTECLA(1       ,ALT_A),

                  VIDEO_MTTECLA('C'     ,ALT_C),
                  VIDEO_MTTECLA('c'     ,ALT_C),
                  VIDEO_MTTECLA(VD_NULO ,ALT_C),
                  VIDEO_MTTECLA(3       ,ALT_C),

                  VIDEO_MTTECLA('T'     ,ALT_T),
                  VIDEO_MTTECLA('t'     ,ALT_T),
                  VIDEO_MTTECLA(VD_NULO ,ALT_T),
                  VIDEO_MTTECLA(20      ,ALT_T),

                  VIDEO_MTTECLA(42      ,9    ),
                  VIDEO_MTTECLA(42      ,55   ),

                  VIDEO_MTTECLA(61      ,13   ),

                  VIDEO_MTTECLA(37      ,6    ),

                  VIDEO_MTTECLA(47      ,53   ),
                  VIDEO_MTTECLA(43      ,13   ),
                  VIDEO_MTTECLA(43      ,78   ),
                  VIDEO_MTTECLA(45      ,74   ),
                  VIDEO_MTTECLA(45      ,12   ),
                  VIDEO_MTTECLA(VD_NULO ,F3   ),
                  VIDEO_MTTECLA(VD_NULO ,F4   ),
                  VIDEO_MTTECLA(VD_NULO ,F5   ),
                  VIDEO_MTTECLA(VD_NULO ,F6   ),
                  VIDEO_MTTECLA(VD_NULO ,F7   ),
                  VIDEO_MTTECLA(VD_NULO ,F8   ),
                  VIDEO_MTTECLA(VD_NULO ,F1   ),
                  VIDEO_MTTECLA(VD_NULO ,VD_NULO)};

INT2 (*VIDEO_CALC_funcao_teclado)() = VD_NULO;

VIDEO_ESTMANUT VIDEO_CALC_telacalc =
               { VIDEO_padrao_sistema,  TELA_PADROES_TELACALC};

VIDEO_SWAP_TRATADOR_SERVICO VIDEO_CALC_tratador[] = {
    {VD_MTTECLA(VD_NULO,F10),VIDEO_TELA_troca_serv_teclas,VIDEO_GRI_RET_TRUE},
    {VD_NULO,VD_NULO,VD_NULO}};



