/* ============================================================================

                              PROTCOMP 1.00
                              Tech C 1993
                     NUCLEO DE COMPILACAO DA LINGUAGEM

   ============================================================================ */

#include<INCVIDEO.H>
#include "VDLINALF.H"

INT2 VIDEO_MCLIN_SERVREC_inicio_compilacao[] = {VIDEO_MCLIN_INICIO_COMPILACAO,VD_NULO};

INT2 VIDEO_MCLIN_SERVREC_pega_linha[]        = {VIDEO_MCLIN_PEGA_LINHA,VD_NULO};

INT2 VIDEO_MCLIN_SERVREC_filtra_fase_1[]     = {VIDEO_MCLIN_FILTRA_FASE_1,VD_NULO};

INT2 VIDEO_MCLIN_SERVREC_trata_erros[]       = {VIDEO_MCLIN_TRATA_ERROS,VD_NULO};

VIDEO_TABSERV VIDEO_MCLIN_tabserv_compilacao[] = {
{  VIDEO_MCLIN_SERVREC_inicio_compilacao, VIDEO_MCLIN_EXECSERV_inicio_compilacao},
{  VIDEO_MCLIN_SERVREC_pega_linha       , VIDEO_MCLIN_EXECSERV_pega_linha       },
{  VIDEO_MCLIN_SERVREC_filtra_fase_1    , VIDEO_MCLIN_EXECSERV_filtra_fase_1    },
{  VIDEO_MCLIN_SERVREC_trata_erros      , VIDEO_MCLIN_EXECSERV_trata_erros      },



