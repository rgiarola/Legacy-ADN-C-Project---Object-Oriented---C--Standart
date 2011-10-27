#include <INCVIDEO.H>

INT2 VIDEO_TELA_mouse_posiciona(VIDEO_TELA_ENTRADA_DADOS **telas,
                               VIDEO_NUCLEO_SERV        **param);

INT2 VIDEO_TELA_mouse_dispcons(VIDEO_TELA_ENTRADA_DADOS **telas,
                              VIDEO_NUCLEO_SERV        **param);

INT2 VIDEO_TELA_mouse_help(VIDEO_TELA_ENTRADA_DADOS **telas,
                          VIDEO_NUCLEO_SERV        **param);

INT2 VIDEO_TELA_dispara_userfunc(VIDEO_TELA_ENTRADA_DADOS **telas,
                                 VIDEO_NUCLEO_SERV        **param);

#if defined(__VIDEO_TELA_CARGA_PARAMETROS)
VIDEO_TABSERV *VIDEO_TELA_tabserv_navegacao;
#else

INT2 VIDEO_TELA_tabserv_POS[] = {VD_MTTECLA(VD_NULO,TABSCAN),
                                 VD_MTTECLA(VD_TAB ,TABSCAN),
                                 VD_MTTECLA(VD_NULO,CTRL_DIR),
                                 VD_MTTECLA(VD_NULO,DIREITA),
                                 VD_NULO},

    VIDEO_TELA_tabserv_ANT[] = {VD_MTTECLA(VD_NULO,CTRL_ESQ),
                                VD_MTTECLA(VD_NULO,ESQUERDA),
                                VD_NULO},

    VIDEO_TELA_tabserv_DBMAIOR[] = {VD_MTTECLA(VD_NULO,SHIFT_PGDN),
                                    VD_NULO},

    VIDEO_TELA_tabserv_DBMENOR[] = {VD_MTTECLA(VD_NULO,SHIFT_PGUP),
                                    VD_NULO},
    
    VIDEO_TELA_tabserv_SUP[] = {VD_MTTECLA(VD_NULO,SOBE),
                                VD_NULO},

    VIDEO_TELA_tabserv_INF[] = {VD_MTTECLA(VD_NULO,DESCE),
                                VD_NULO},

    VIDEO_TELA_tabserv_INI[] = {VD_MTTECLA(VD_NULO,CTRL_HOME),
                                VD_NULO},

    VIDEO_TELA_tabserv_FIM[] = {VD_MTTECLA(VD_NULO,CTRL_END),
                                VD_NULO},

    VIDEO_TELA_tabserv_TER[] = {VD_MTTECLA(VD_NULO,ESCAPESCAN),
                                VD_MTTECLA(VD_NULO,ALT_O),
                                VD_MTTECLA(ESCAPE ,ESCAPESCAN),
                                VD_NULO},

    VIDEO_TELA_tabserv_CON[] = {VD_MTTECLA(ENTER ,ENTERSCAN),
                                VD_MTTECLA(10    ,ENTERSCAN),
                                VD_NULO},

    VIDEO_TELA_tabserv_DBPOS[] = {VD_MTTECLA(VD_NULO,PGDN),
                                  VD_NULO},

    VIDEO_TELA_tabserv_DBANT[] = {VD_MTTECLA(VD_NULO,PGUP),
                                  VD_NULO},

    VIDEO_TELA_tabserv_DBULT[] = {VD_MTTECLA(VD_NULO,CTRL_PGDN),
                                  VD_NULO},

    VIDEO_TELA_tabserv_DBPRI[] = {VD_MTTECLA(VD_NULO,CTRL_PGUP),
                                  VD_NULO},

    VIDEO_TELA_tabserv_TELADM[] = {VD_MTTECLA(VD_NULO,ALT_S),
                                   VD_MTTECLA(VD_NULO,ALT_E),
                                   VD_MTTECLA(VD_NULO,ALT_MAIS),
                                   VD_MTTECLA(VD_NULO,ALT_MENOS),
                                   VD_MTTECLA(VD_NULO,ALT_P),
                                   VD_MTTECLA(VD_NULO,ALT_B),
                                   VD_MTTECLA(VD_NULO,ALT_M),
                                   VD_MTTECLA(VD_NULO,ALT_R),
                                   VD_MTTECLA(VD_NULO,ALT_A),
                                   VD_MTTECLA(VD_NULO,F1),
                                   VD_MTTECLA(1,VIDEO_MOUSE_BOTCLICK),
                                   VD_MTTECLA(2,VIDEO_MOUSE_BOTCLICK),
                                   VD_MTTECLA(1,VIDEO_MOUSE_BOTTRV),
                                   VD_MTTECLA(2,VIDEO_MOUSE_BOTTRV),
                                   VD_MTTECLA(VD_NULO,ALT_C),
                                   VD_NULO},

	VIDEO_TELA_tabserv_INC[] = {VD_MTTECLA(VD_NULO,ALT_I),
                                VD_NULO},

    VIDEO_TELA_tabserv_PASTA[] = {VD_MTTECLA(VD_NULO,ALT_P),VD_NULO},

    VIDEO_TELA_tabserv_COPIA[] = {VD_MTTECLA(VD_NULO,ALT_C),VD_NULO},

    VIDEO_TELA_tabserv_BUSCA[] = {VD_MTTECLA(VD_NULO,ALT_B),VD_NULO},

    VIDEO_TELA_tabserv_calculadora[] = {VD_MTTECLA(VD_NULO,F4),VD_NULO},

    VIDEO_TELA_tabserv_TROCASERVREC[] = {VD_MTTECLA(VD_NULO,F10),
                                         VD_MTTECLA(VD_NULO,F9 ),
                                         VD_MTTECLA(VD_NULO,F8 ),
                                         VD_MTTECLA(VD_NULO,F7 ),
                                         VD_MTTECLA(VD_NULO,F6 ),
                                         VD_MTTECLA(VD_NULO,F5 ),
                                         VD_NULO};

   extern INT2 VIDEO_TELA_tabserv_aborta[];

   extern INT2 VIDEO_ARVORE_tabserv_ESPECIAIS[];

VIDEO_TABSERV VIDEO_TELA_tabserv_navegacao[] = {
{   VIDEO_TELA_tabserv_TROCASERVREC,VIDEO_TELA_troca_serv_teclas},
{   VIDEO_TELA_tabserv_POS    , VIDEO_TELA_campo_posterior     },
{   VIDEO_TELA_tabserv_ANT    , VIDEO_TELA_campo_anterior      },
{   VIDEO_TELA_tabserv_SUP    , VIDEO_TELA_linha_anterior      },
{   VIDEO_TELA_tabserv_INF    , VIDEO_TELA_linha_posterior     },
{   VIDEO_TELA_tabserv_INI    , VIDEO_TELA_primeiro_campo      },
{   VIDEO_TELA_tabserv_FIM    , VIDEO_TELA_ultimo_campo        },
{   VIDEO_TELA_tabserv_CON    , VIDEO_TELA_consiste_campo      },
{   VIDEO_TELA_tabserv_TELADM , VIDEO_TELA_chama_data_base_adm },
{   VIDEO_TELA_tabserv_TER    , VIDEO_TELA_aborta_tela         },
{   VIDEO_TELA_tabserv_DBPOS  , VIDEO_TELA_data_base_adm_pos   },
{   VIDEO_TELA_tabserv_DBMAIOR, VIDEO_TELA_data_base_adm_maior },
{   VIDEO_TELA_tabserv_DBANT  , VIDEO_TELA_data_base_adm_ant   },
{   VIDEO_TELA_tabserv_DBMENOR, VIDEO_TELA_data_base_adm_menor },
{   VIDEO_TELA_tabserv_DBPRI  , VIDEO_TELA_data_base_adm_pri   },
{   VIDEO_TELA_tabserv_DBULT  , VIDEO_TELA_data_base_adm_ult   },
{   VIDEO_TELA_tabserv_userserv,VIDEO_TELA_chama_data_base_adm },
{   VIDEO_TELA_tabserv_INC    , VD_NULO                        },
{   VIDEO_TELA_tabserv_calculadora, VIDEO_CALC_dispara         },
{   VIDEO_TELA_tabserv_aborta , VD_NULO                        },
{   VIDEO_VISUAL_tabserv_spool, VIDEO_VISUAL_dispara_spool     },
{   VIDEO_ARVORE_tabserv_ESPECIAIS,VIDEO_TELA_funcoes_especiais},
{   VD_NULO                   , VD_NULO                        }};



INT2   VIDEO_TELA_tabserv_DBADM[] = {VD_MTTECLA(VD_NULO,ALT_S)    ,VD_NULO},
       VIDEO_TELA_tabserv_DBEXC[] = {VD_MTTECLA(VD_NULO,ALT_E)    ,VD_NULO},
       VIDEO_TELA_tabserv_TLPOS[] = {VD_MTTECLA(VD_NULO,ALT_MAIS) ,VD_NULO},
       VIDEO_TELA_tabserv_TLANT[] = {VD_MTTECLA(VD_NULO,ALT_MENOS),VD_NULO},
       VIDEO_TELA_tabserv_DBPRG[] = {VD_MTTECLA(VD_NULO,PGDN),
                                     VD_MTTECLA(VD_NULO,PGUP),
                                     VD_MTTECLA(VD_NULO,SHIFT_PGDN),
                                     VD_MTTECLA(VD_NULO,SHIFT_PGUP),
                                     VD_MTTECLA(VD_NULO,CTRL_PGDN),
                                     VD_MTTECLA(VD_NULO,CTRL_PGUP),
                                     VD_MTTECLA(B(0X0F),B(0X0F)),VD_NULO},

    VIDEO_TELA_tabserv_posiciona[] = {VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTCLICK),
                                      VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTTRV),
                                                    VD_NULO},

    VIDEO_TELA_tabserv_dispcons[]  = {VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTCLICK),
                                                    VD_NULO},

    VIDEO_TELA_tabserv_help[] =      {VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTTRV),
                                      VIDEO_MTTECLA(VD_NULO,F1),
                                                     VD_NULO},

    VIDEO_TELA_tabserv_manut[] =      {VIDEO_MTTECLA(VD_NULO,ALT_M),
                                                    VD_NULO},

    VIDEO_TELA_tabserv_refresh[] =    {VD_MTTECLA(VD_NULO,ALT_R),
                                                    VD_NULO},

    VIDEO_TELA_tabserv_restela[] =    {VD_MTTECLA(VD_NULO,ALT_A),
                                                    VD_NULO},

    VIDEO_TELA_tabserv_increg[]  =    {VIDEO_DATABASE_INCLUSAO,VD_NULO},

    VIDEO_TELA_tabserv_altreg[]  =    {VIDEO_DATABASE_ALTERACAO,VD_NULO},

    VIDEO_TELA_tabserv_aborta[]  =    {VIDEO_MTTECLA(ESCAPE,ESCAPE),VD_NULO};


VIDEO_TABSERV VIDEO_TELA_tabserv_edicao_tela[] = {
{VIDEO_TELA_tabserv_DBADM,     VIDEO_TELA_data_base_adm           },
{VIDEO_TELA_tabserv_DBPRG,     VIDEO_TELA_data_base_preg          },
{VIDEO_TELA_tabserv_DBEXC,     VIDEO_TELA_data_base_exc           },
{VIDEO_TELA_tabserv_TLPOS,     VIDEO_TELA_selec_tela_posterior    },
{VIDEO_TELA_tabserv_TLANT,     VIDEO_TELA_selec_tela_anterior     },
{VIDEO_TELA_tabserv_TER,       VIDEO_TELA_termina_edicao          },
{VIDEO_TELA_tabserv_PASTA,     VIDEO_TELA_seleciona_pasta         },
{VIDEO_TELA_tabserv_COPIA,     VIDEO_TELA_seleciona_copia         },
{VIDEO_TELA_tabserv_BUSCA,     VIDEO_TELA_busca_pesquisa          },
{VIDEO_TELA_tabserv_posiciona, VIDEO_TELA_mouse_posiciona         },
{VIDEO_TELA_tabserv_dispcons,  VIDEO_TELA_mouse_dispcons          },
{VIDEO_TELA_tabserv_help,      VIDEO_TELA_mouse_help              },
{VIDEO_TELA_tabserv_refresh,   VIDEO_TELA_refresh_imagens         },
{VIDEO_TELA_tabserv_restela,   VIDEO_TELA_reseta_imagem           },
{VIDEO_TELA_tabserv_manut,     VIDEO_TELA_dispara_manutencao      },
{VIDEO_TELA_tabserv_userserv,  VIDEO_TELA_dispara_userserv        },
{VIDEO_TELA_tabserv_INC,       VIDEO_TELA_seleciona_inclusao      },
{VIDEO_TELA_tabserv_CON,       VIDEO_TELA_dispara_display         },
{VIDEO_TELA_tabserv_increg,    VIDEO_TELA_data_base_adm_inclusao  },
{VIDEO_TELA_tabserv_altreg,    VIDEO_TELA_data_base_adm_alteracao },
{VIDEO_TELA_tabserv_aborta,    VIDEO_TELA_aborta_tudo             },
{VD_NULO, VD_NULO}};
#endif

int (*VIDEO_TELA_funcao_inclusao)(int flag,int arquivo,char *buffer) = VD_NULO;

int (*VIDEO_TELA_funcao_exclusao)(int flag,int arquivo,char *buffer) = VD_NULO;

int (*VIDEO_TELA_funcao_alteracao)(int flag,int arquivo,char *buffer) = VD_NULO;





