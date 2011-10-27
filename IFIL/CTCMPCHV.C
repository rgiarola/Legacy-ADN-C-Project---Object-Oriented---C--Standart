/* ============================================================================
    CTREE_cmpchave()- Compara seguementos de uma chave, apartir do protocolo
                      VIDEO_SEG_CHAVE, na comparacao da(s) parte(s) constantes
                      com suas respectivas posicoes no buffer de leitura.
    CTCMPCHAVE()    - Nome abreviado.
    PARAMETROS      - numero do Indice,
                      chave,
                      modo_leitura.
                      OBS: O modo de leitura e'usado para especificar em que
                           buffer estarao os dados. Em sistemas multi-usuarios,
                           no minimo tres buffer's, em mono-usuario, no minimo
                           dois buffer's, sao avaliaveis.
    RETORNA         - Zero se criterio de comparacao OK, maior que zero se
                      maior, menor que zero se chave menor.
   ============================================================================ */
#include <INCVIDEO.H>

INT2 CTREE_cmpchave( numero_indice, video_chave, buffer_dados )
INT2              numero_indice;          /* Numero do Indice.*/
VIDEO_SEG_CHAVE *video_chave;           /* Segmento(s) de chave.*/
INT2              buffer_dados;          /* Indicador para o buffer de dados.*/
{
  IDE_DODA        *work_doda;
  IDE_ARQUIVOS    *work_ifil;           /* Para localizacao do IDE_CHAVES.*/
  IDE_INDEX       *work_index;
  IDE_CHAVES      *work_index_seg;
  VIDEO_SEG_CHAVE *work_video_chave;    /* Para manuseio de segmentos.*/

  char            *buffer_comparacao,   /* Buffer de dados para comparacao.*/
                  *buffer_base;         /* Buffer base.*/
  INT2              posicao_segmento=0,  /* Posicao no buffer de comparacao.*/
                   numero_segmentos,    /* Numero de Segmentos da chave.*/
                   numero_arquivo;      /* Numero Ctree do arquivo.*/


  if( video_chave == VD_NILL(VIDEO_SEG_CHAVE) )
    return( I(-1) );

  if( (numero_arquivo=CTREE_keyfil(numero_indice)) < 0)
    return( I(-1) );

  /* Obtem estrutura de controle IDE_ARQUIVOS.*/
  if( (work_ifil = CTREE_ifilend(numero_arquivo)) == VD_NILL(IDE_ARQUIVOS) )
    return( I(-2) );

  /*VD_gtxy(1,23); printf("FUNCAO CMPCHV: work_ifil->didx %d",*/
  /*work_ifil->dnumidx); getch();*/

  if( work_ifil->dnumidx == 0 ) /* Se nao Existem indices declarados...*/
    return( I(-3) );


  /* CONSEGUE A POSICAO DO ( BUFFER ) DE DADOS*/
  /* =====================================================================*/
  if( buffer_dados == CT_LE_DADOS )
    ATIVA_BUF_DADOS;
  else
    ATIVA_BUF_EXTRA;

  if( (buffer_comparacao = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
    return( I(-4) );
  /* =====================================================================*/


  work_index       = (work_ifil->ix + (numero_indice-numero_arquivo-1));
  work_index_seg   = (work_index->seg);
  numero_segmentos = (work_index->inumseg);

  work_video_chave = video_chave;
  

  /* COMPARA SEGMENTOS DA CHAVE (PROTOCOLO VIDEO_SEG_CHAVE).*/
  while( posicao_segmento < numero_segmentos     &&
         work_video_chave->tipo    !=  VD_NULO   &&
         work_video_chave->tamanho !=  VD_NULO )
   {
    if( work_video_chave->tipo == CT_SEG_CONST       ||
        work_video_chave->tipo == CT_SEG_CAMPO_CONST )
     {
      INT2 retorno;
      if( work_video_chave->tipo == CT_SEG_CAMPO_CONST )
       {
        if( (work_doda=CTREE_dodaend(work_video_chave->pointer)) ==
            VD_NILL(IDE_DODA) )
         return( I(-7) );
        else
            buffer_base = work_doda->fadr;
       }
      else
       buffer_base =  work_video_chave->pointer;

      retorno=memcmp( buffer_base,
                      (buffer_comparacao+work_index_seg->soffset),
                      work_video_chave->tamanho );

      /* DIFERENCA EM COMPARACAO DETECTADA.*/
      if( retorno != 0 )
       return( I(retorno) );

     }
    ++work_video_chave;           /* Prepara proximos segmentos.*/
    ++work_index_seg;
    ++posicao_segmento;
   }

 return( I(0) );

}
/* ============================================================================*/


