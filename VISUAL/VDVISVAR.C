#include <INCVIDEO.H>

VIDEO_ESTMANUT VIDEO_HELP_imagem_padrao = {
 VIDEO_padrao_sistema,    TELA_PADROES_TELAHELP,VD_NULO,VD_NULO},

               VIDEO_VISUAL_imagem_padrao = {
 VIDEO_padrao_sistema,    TELA_PADROES_TELAVIS,VD_NULO,VD_NULO},

               VIDEO_VISUAL_imagem_impressao = {
 VIDEO_padrao_sistema,    TELA_PADROES_TELAIMP,VD_NULO,VD_NULO},

               VIDEO_VISUAL_imagem_spool= {
 VIDEO_padrao_sistema,    TELA_PADROES_TELASPOO,VD_NULO,VD_NULO},

               VIDEO_VISUAL_imagem_arquivos= {
 VIDEO_padrao_sistema,    TELA_PADROES_TELARQVS,VD_NULO,VD_NULO},

               VIDEO_HELP_menu_padrao = {
 VIDEO_padrao_projeto, "MENUHELP",VD_NULO,VD_NULO},

               VIDEO_VISUAL_menu_config= {
 VIDEO_padrao_projeto, "CONFIG",VD_NULO,VD_NULO},

               VIDEO_VISUAL_menu_seleciona= {
 VIDEO_padrao_projeto, "VISUAL",VD_NULO,VD_NULO};

INT2 (*VIDEO_VISUAL_funcao_disparo)() = VIDEO_VISUAL_dispara_visual;

INT2 VIDEO_VISUAL_tabserv_LINPOS[] = {VD_MTTECLA(VD_NULO,DESCE),
                                    VD_MTTECLA(ENTER ,ENTERSCAN),
                                    VD_MTTECLA(10    ,ENTERSCAN),
                                    VD_NULO},

     VIDEO_VISUAL_tabserv_TABPOS[] = {VD_MTTECLA(VD_TAB ,TABSCAN),
                                      VD_MTTECLA(VD_NULO,CTRL_DIR),
                                      VD_NULO},

     VIDEO_VISUAL_tabserv_TABANT[] = {VD_MTTECLA(VD_NULO,CTRL_ESQ),
                                      VD_MTTECLA(VD_NULO,TABSCAN),VD_NULO},

     VIDEO_VISUAL_tabserv_COLPOS[] = {VD_MTTECLA(VD_NULO,DIREITA),VD_NULO},

     VIDEO_VISUAL_tabserv_COLANT[] = {VD_MTTECLA(VD_NULO,ESQUERDA),VD_NULO},


     VIDEO_VISUAL_tabserv_LINANT[] = {VD_MTTECLA(VD_NULO,SOBE),VD_NULO},

     VIDEO_VISUAL_tabserv_deleta[] = {VD_MTTECLA(VD_NULO,F9),VD_NULO},

     VIDEO_VISUAL_tabserv_spool[] = {VD_MTTECLA(ASCII_SPOOL,SCAN_SPOOL),
                                     VIDEO_MTTECLA(CTRLBAKSP,BAKSPSCAN),
                                     VD_NULO},

     VIDEO_VISUAL_tabserv_impress[] = {VD_MTTECLA(VD_NULO,F2),VD_NULO},

     VIDEO_VISUAL_tabserv_procura[] = {VD_MTTECLA(VD_NULO,F3),VD_NULO},

     VIDEO_VISUAL_tabserv_PAGPOS[] = {VD_MTTECLA(VD_NULO,PGDN),
                                    VD_MTTECLA(VD_NULO,ALT_D),VD_NULO},

     VIDEO_VISUAL_tabserv_PAGANT[] = {VD_MTTECLA(VD_NULO,PGUP),
                                    VD_MTTECLA(VD_NULO,ALT_U),VD_NULO},

     VIDEO_VISUAL_tabserv_INI[]    = {VD_MTTECLA(VD_NULO,HOME),
                                    VD_MTTECLA(VD_NULO,CTRL_HOME),
                                    VD_NULO},

     VIDEO_VISUAL_tabserv_FIM[]    = {VD_MTTECLA(VD_NULO,END),
                                    VD_MTTECLA(VD_NULO,CTRL_END),
                                    VD_NULO},

     VIDEO_VISUAL_tabserv_ULT[]    = {VD_MTTECLA(VD_NULO,CTRL_PGDN),
                                    VD_MTTECLA(VD_NULO,ALT_L),VD_NULO},

     VIDEO_VISUAL_tabserv_PRI[]    = {VD_MTTECLA(VD_NULO,CTRL_PGUP),
                                    VD_MTTECLA(VD_NULO,ALT_P),VD_NULO},

     VIDEO_VISUAL_tabserv_TER[]    = {VD_MTTECLA(VD_NULO,ESCAPESCAN),
                                    VD_MTTECLA(ESCAPE ,ESCAPESCAN),VD_NULO},

#ifdef VIDEO_DOS
    VIDEO_VISUAL_tabserv_posiciona[] = {VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTCLICK),
                                      VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTTRV),
                                      VD_NULO},
#endif

    VIDEO_VISUAL_tabserv_calculadora[] = {VD_MTTECLA(VD_NULO,F4),VD_NULO},

    VIDEO_VISUAL_tabserv_menu[] = {VD_MTTECLA(VD_NULO,ALT_O),
                                 VD_MTTECLA(VD_NULO,F1),VD_NULO};

VIDEO_TABSERV VIDEO_VISUAL_tabserv_navegacao[] = {
{   VIDEO_VISUAL_tabserv_LINPOS   , VIDEO_VISUAL_linha_posterior     },
{   VIDEO_VISUAL_tabserv_COLPOS   , VIDEO_VISUAL_coluna_posterior    },
{   VIDEO_VISUAL_tabserv_TABPOS   , VIDEO_VISUAL_tab_posterior       },
{   VIDEO_VISUAL_tabserv_LINANT   , VIDEO_VISUAL_linha_anterior      },
{   VIDEO_VISUAL_tabserv_COLANT   , VIDEO_VISUAL_coluna_anterior     },
{   VIDEO_VISUAL_tabserv_TABANT   , VIDEO_VISUAL_tab_anterior        },
{   VIDEO_VISUAL_tabserv_PAGPOS   , VIDEO_VISUAL_pagina_posterior    },
{   VIDEO_VISUAL_tabserv_PAGANT   , VIDEO_VISUAL_pagina_anterior     },
{   VIDEO_VISUAL_tabserv_INI      , VIDEO_VISUAL_inicio_pagina       },
{   VIDEO_VISUAL_tabserv_FIM      , VIDEO_VISUAL_fim_pagina          },
{   VIDEO_VISUAL_tabserv_ULT      , VIDEO_VISUAL_ultima_linha        },
{   VIDEO_VISUAL_tabserv_PRI      , VIDEO_VISUAL_primeira_linha      },
{   VIDEO_VISUAL_tabserv_impress  , VIDEO_VISUAL_imprime_arquivo     },
{   VIDEO_VISUAL_tabserv_procura  , VIDEO_VISUAL_procura_arquivo     },

#ifdef VIDEO_DOS
{VIDEO_VISUAL_tabserv_posiciona   , VIDEO_VISUAL_mouse_posiciona     },
#endif

{   VIDEO_VISUAL_tabserv_TER      , VIDEO_VISUAL_termina             },
{   VIDEO_VISUAL_tabserv_menu     , VIDEO_VISUAL_opcoes              },
{   VIDEO_VISUAL_tabserv_deleta   , VIDEO_VISUAL_deleta_arquivo      },
{   VIDEO_VISUAL_tabserv_calculadora, VIDEO_CALC_dispara             },
{	VD_NULO 					  , VD_NULO 						 }};

