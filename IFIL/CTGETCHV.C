/* ============================================================================
    CTREE_getchv()  - Consegue chave de busca em index, apartir do buffer de
                      dados.
                      Para   funcionamento  desta   funcao, so e'   necessario
                      determinar o numero do indice (soma-se 1 para o primeiro
                      indice,  2 para proximo,  e assim por diante,  no numero
                      do arquivo), e  inicializar os campos chaves que compoem
                      a chave deste.
    READREC()       - Nome abreviado.
    PARAMETROS      - numero do Indice,
                      target para acesso.
    RETORNA         - Zero se operacao OK, outro valor em erro.
   ============================================================================ */
#include <INCVIDEO.H>

INT2  CTREE_getchave( numero_indice, target, atual_buffer)
INT2 numero_indice;
char *target;
INT2 atual_buffer;
{
 IDE_ARQUIVOS *work_ifil;            /* Para localizacao do IDE_CHAVES.*/
 IDE_INDEX    *work_index;
 IDE_CHAVES   *work_chaves;
 char          work_target[128],     /* Para manipulacao do segmento chave.*/
              *buffer_dados;         /* Pont. buffer para os atuais dados.*/
 INT2           numero_segmentos,     /* Contador de segmentos.*/
               numero_arquivo,       /* Numero do Arquivo.*/
               posicao_target=0;     /* Posicao na chave.*/


 if( numero_indice < I(1) )
   return( I(-1) );


 if( target == VD_NILL(char) )
   return( I(-2) );


 /* Cosegue o ctree numero arquivo.*/
 if( (numero_arquivo=CTREE_keyfil( numero_indice )) < I(0) )
   return( I(-3) );

 ATUAL_NO_BUFFER = atual_buffer;
 if( (buffer_dados = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
   return( I(-4) );

 if( (work_ifil = CTREE_ifilend(numero_arquivo)) == VD_NILL(IDE_ARQUIVOS) )
   return( I(-5) );

 work_index = (work_ifil->ix + (numero_indice-numero_arquivo-1));

 if( work_ifil->dnumidx > 0 ) /* Se Existem indices declarados.*/
  {
   work_chaves      = (work_index->seg);
   numero_segmentos = (work_index->inumseg);
  }
 else
  return( I(-6) );    /* Esta funcao nao podera ascessar o arquivo.*/


 /* MONTA A CHAVE APARTIR DE SEUS SEGMENTOS.*/
 VIDEO_setmem( work_target, sizeof(work_target), 0);
 while( numero_segmentos > 0)
  {
   VIDEO_movbloco( &work_target[posicao_target],
           (buffer_dados+work_chaves->soffset),
           (work_chaves->slength) );
   posicao_target += work_chaves->slength;
   ++work_chaves;                       /* Prepara proximo segmento.*/
   --numero_segmentos;
  }

 VIDEO_movbloco( target, work_target, work_index->ikeylen );

return( I(0) );

}

