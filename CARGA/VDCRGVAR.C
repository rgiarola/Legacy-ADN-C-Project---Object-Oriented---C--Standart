#include <INCVIDEO.H>
/* ============================================================================
                              ADN VERSAO 2
                              Tech C 1993
  Vari veis da carga de arquivos
  Ultima altera‡„o 25/08/94

 =========================================================================== */


/* =========================================================================
               Pointer para extrutura de carga de arquivos
 ========================================================================= */
VIDEO_PARAMCRGARQ *VIDEO_bufparamarq = VD_NULO;

/* =========================================================================
               Pointer para extrutura de pesquisa bin ria em doda
 ========================================================================= */
IDE_DODA **VIDEO_tabela_doda = VD_NULO;

/* =========================================================================
  Pointer para extrutura de controle e pesquisa bin ria em indice e arquivo
 ========================================================================= */
IDE_TABREFERDODA **VIDEO_tabela_carga;
IDE_TABREFERDODA **VIDEO_tabela_carga_reduzido;

/* =========================================================================
        Controle de tipo de elemento pesquisados nas tabelas internas
 ========================================================================= */
INT2 VIDEO_tipo_elemento_pesquisado;

