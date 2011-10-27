#include <INCVIDEO.H>

/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------
 * Descricao      :  conjunto de tabelas identificadoras das teclas de selecao
 *                   de servicos e os servicos correspondentes tratadores
 *                   das teclas
 * Autor          :  20/11/92  Celso de Oliveira
 * Ultima Revisao :  20/11/92  Celso de Oliveira
 *---------------------------------------------------------------------------*/
INT2 VIDEO_ARVORE_tabserv_COLPOST[] ={VIDEO_MTTECLA(VD_NULO,DIREITA),
                                     VIDEO_MTTECLA(VD_NULO,TABSCAN),
                                     VIDEO_MTTECLA(VD_TAB ,TABSCAN),
                                     VIDEO_MTTECLA('6',DIREITA),VD_NULO},

    VIDEO_ARVORE_tabserv_COLANT[]   ={VIDEO_MTTECLA(VD_NULO,ESQUERDA),
                                      VIDEO_MTTECLA('4',ESQUERDA),VD_NULO},

    VIDEO_ARVORE_tabserv_ESPECIAIS[]={VIDEO_MTTECLA(VD_NULO,CTRL_F1),
                                      VIDEO_MTTECLA(VD_NULO,CTRL_F2),
                                      VIDEO_MTTECLA(VD_NULO,CTRL_F3),
                                      VIDEO_MTTECLA(VD_NULO,CTRL_F4),
                                      VIDEO_MTTECLA(VD_NULO,CTRL_F5),
                                      VIDEO_MTTECLA(VD_NULO,CTRL_F6),
                                      VIDEO_MTTECLA(VD_NULO,CTRL_F7),
                                      VIDEO_MTTECLA(VD_NULO,CTRL_F8),
                                      VIDEO_MTTECLA(VD_NULO,CTRL_F9),
                                      VIDEO_MTTECLA(VD_NULO,CTRL_F10),
                                      VD_NULO},

    VIDEO_ARVORE_tabserv_LININF[]   ={VIDEO_MTTECLA(VD_NULO,DESCE),
                                      VIDEO_MTTECLA('2',DESCE),VD_NULO},

    VIDEO_ARVORE_tabserv_LINSUP[]   ={VIDEO_MTTECLA(VD_NULO,SOBE),
                                      VIDEO_MTTECLA('8',SOBE),VD_NULO},

	VIDEO_ARVORE_tabserv_TERMINA[]	={VIDEO_MTTECLA(VD_NULO,ESCAPESCAN),
									  VIDEO_MTTECLA(ESCAPE,ESCAPESCAN),VD_NULO},

	VIDEO_ARVORE_tabserv_SELEC[]	= {VD_MTTECLA(ENTER ,ENTERSCAN),
									   VD_MTTECLA(ENTER ,ALT_M	  ),
                                       VD_MTTECLA(10    ,ENTERSCAN),VD_NULO},

    VIDEO_ARVORE_tabserv_PGUP[]     ={VIDEO_MTTECLA(VD_NULO,PGUP),
                                      VIDEO_MTTECLA('9',PGUP),VD_NULO},

    VIDEO_ARVORE_tabserv_PGDN[]     ={VIDEO_MTTECLA(VD_NULO,PGDN),
                                      VIDEO_MTTECLA('3',PGDN),VD_NULO},

    VIDEO_ARVORE_tabserv_CTRL_PGUP[] ={VIDEO_MTTECLA(VD_NULO,CTRL_PGUP),
                                       VD_NULO},

    VIDEO_ARVORE_tabserv_CTRL_PGDN[] ={VIDEO_MTTECLA(VD_NULO,CTRL_PGDN),
                                       VD_NULO},

    VIDEO_ARVORE_tabserv_HOME[]      ={VIDEO_MTTECLA(VD_NULO,HOME),
                                       VIDEO_MTTECLA('7',HOME),VD_NULO},

    VIDEO_ARVORE_tabserv_END[]       ={VIDEO_MTTECLA(VD_NULO,END),
                                      VIDEO_MTTECLA('1',END),VD_NULO},

    VIDEO_ARVORE_tabserv_CTRL_HOME[] ={VIDEO_MTTECLA(VD_NULO,CTRL_HOME),
                                       VD_NULO},

    VIDEO_ARVORE_tabserv_CTRL_END[]  ={VIDEO_MTTECLA(VD_NULO,CTRL_END),
                                       VD_NULO},

    VIDEO_ARVORE_tabserv_CTRL_DIR[]  ={VIDEO_MTTECLA(VD_NULO,CTRL_DIR),
                                       VD_NULO},

    VIDEO_ARVORE_tabserv_calculadora[]  ={VIDEO_MTTECLA(VD_NULO,F4),
                                          VIDEO_MTTECLA(VD_NULO,ALT_F4),
					  VD_NULO},

    VIDEO_ARVORE_tabserv_CTRL_ESQ[]  ={VIDEO_MTTECLA(VD_NULO,CTRL_ESQ),
                                      VD_NULO}
#ifdef VIDEO_DOS
,
    VIDEO_ARVORE_tabserv_mouseumclick[] = {VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTCLICK),
                                           VD_NULO},

    VIDEO_ARVORE_tabserv_mousedoisclick[] =
                                       {VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTCLICK),
                                        VD_NULO},

    VIDEO_ARVORE_tabserv_mouseumtrav[] = {VIDEO_MTTECLA(1,VIDEO_MOUSE_BOTTRV),
                                          VD_NULO},

    VIDEO_ARVORE_tabserv_mousedoistrav[] =
                                       {VIDEO_MTTECLA(VD_NULO,F1),
                                        VIDEO_MTTECLA(2,VIDEO_MOUSE_BOTTRV),
                                        VD_NULO}
#endif
                                        ;

VIDEO_TABSERV VIDEO_ARVORE_tabela_navegacao[] = {
{VIDEO_ARVORE_tabserv_COLPOST  ,VIDEO_ARVORE_coluna_posterior   },
{VIDEO_ARVORE_tabserv_COLANT   ,VIDEO_ARVORE_coluna_anterior    },
{VIDEO_ARVORE_tabserv_ESPECIAIS,VIDEO_ARVORE_funcoes_especiais  },
{VIDEO_ARVORE_tabserv_LININF   ,VIDEO_ARVORE_linha_inferior     },
{VIDEO_ARVORE_tabserv_LINSUP   ,VIDEO_ARVORE_linha_superior     },
{VIDEO_ARVORE_tabserv_SELEC    ,VIDEO_ARVORE_seleciona          },
{VIDEO_ARVORE_tabserv_TERMINA  ,VIDEO_ARVORE_termina            },
{VIDEO_ARVORE_tabserv_PGUP     ,VIDEO_ARVORE_pagina_anterior    },
{VIDEO_ARVORE_tabserv_PGDN     ,VIDEO_ARVORE_pagina_posterior   },
{VIDEO_ARVORE_tabserv_CTRL_PGUP,VIDEO_ARVORE_inicio_arvore      },
{VIDEO_ARVORE_tabserv_CTRL_PGDN,VIDEO_ARVORE_fim_arvore         },
{VIDEO_ARVORE_tabserv_HOME     ,VIDEO_ARVORE_primeiro_item      },
{VIDEO_ARVORE_tabserv_END      ,VIDEO_ARVORE_ultimo_item        },
{VIDEO_ARVORE_tabserv_CTRL_DIR ,VIDEO_ARVORE_fim_linha          },
{VIDEO_ARVORE_tabserv_CTRL_ESQ ,VIDEO_ARVORE_inicio_linha       },
{VIDEO_ARVORE_tabserv_CTRL_HOME,VIDEO_ARVORE_inicio_janela      },
{VIDEO_ARVORE_tabserv_CTRL_END ,VIDEO_ARVORE_fim_janela         },

#ifdef VIDEO_DOS
{VIDEO_ARVORE_tabserv_mouseumclick  ,VIDEO_ARVORE_mouseumclick  },
{VIDEO_ARVORE_tabserv_mousedoisclick,VIDEO_ARVORE_mousedoisclick},
{VIDEO_ARVORE_tabserv_mouseumtrav   ,VIDEO_ARVORE_mouseumtrav   },
{VIDEO_ARVORE_tabserv_mousedoistrav ,VIDEO_ARVORE_mousedoistrav },
#endif
{VIDEO_ARVORE_tabserv_calculadora   ,VIDEO_CALC_dispara         },
{VIDEO_VISUAL_tabserv_spool         ,VIDEO_VISUAL_dispara_spool },
{VD_NULO                            ,VD_NULO                    }};






