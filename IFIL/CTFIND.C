/* ============================================================================
    CTREE_find()    - Localiza um registro pela analise de prefixos, sufixos e
                      parciais chaves, ou simples buscas.
                      Para   funcionamento  desta   funcao, so e'   necessario
                      determinar o numero do indice (soma-se 1 para o primeiro
                      indice,  2 para proximo,  e assim por diante,  no numero
                      do arquivo), e  inicializar os campos chaves que compoem
                      a chave deste.
    CTFIND()        - Nome abreviado.
    PARAMETROS      - numero do Indice,
                      chave,
                      modo find,
                      modo leitura.
                      OBS: O modo de leitura e'usado para especificar em que
                           buffer estarao os dados. Em sistemas multi-usuarios,
                           no minimo tres buffer's, em mono-usuario, no minimo
                           dois buffer's, sao avaliaveis.
    RETORNA         - Zero se operacao OK, se chave nao encontrada retorna valor
                      negativo, em outro caso, retorna ctree isam_err.
   ============================================================================ */
#include <INCVIDEO.H>


INT2   CTREE_find( numero_indice, chave, modo_find, modo_leitura)
INT2                numero_indice;
VIDEO_SEG_CHAVE   *chave;
INT2                modo_find,
                   modo_leitura;
{
    IDE_DODA         *work_doda;        /* Ponteiro para o manuseio do nome do campo.*/
    VIDEO_SEG_CHAVE  *work_seg_chave;   /* Ponteiro salva posicao do parametro.*/

    char          work_target[128],     /* Para manipulacao dos segmento chave.*/
                 *target,               /* Ponteiro para o target.*/
                 *buffer_doda;
    INT2           posicao_target,       /* Marca a posicao de concatenacao.*/
                  err,                  /* Manipulacao do codigo de erros.*/
                  numero_arquivo,       /* Numero ctree do arquivo de dados.*/
                  real_arquivo,
                  flag_seg_const=FALSE, /* Flag para apreciacao chaves constantes.*/
                  modo_interno,
                  old_isam_err,aux_erro;

    modo_interno = (modo_leitura == CT_LE_EXTRA_REPASSA) ? CT_LE_EXTRA
                                                         : modo_leitura;

    /* <<<<<< Check de Parametros >>>>>*/
    if( numero_indice  < I(1) )
        {   /* Ctree numero do Indice fora de linha.*/
            return( I(-1) );
        }

    /* <<<<<<< Operacao de Find>>>>>*/
    if( modo_find<0 || modo_find>8 )
        return( I(-2) );


    VIDEO_setmem( work_target, sizeof(work_target), 0);
    if ( chave != VD_NILL(VIDEO_SEG_CHAVE) )
     {
      /* ================================================
         A chave sera'montada apartir do parametro chave,
         pelo protocolo VIDEO_SEG_CHAVE.
         ================================================ */
      posicao_target = 0;
      work_seg_chave = chave;    /* Salva estado do parametro.*/

      while( work_seg_chave->tipo    != VD_NULO &&
             work_seg_chave->tamanho != VD_NULO )
       {
         if( work_seg_chave->tipo == CT_SEG_CONST      ||
             work_seg_chave->tipo == CT_SEG_CAMPO_CONST )
           {
            flag_seg_const = TRUE;  /* Comparacao por constantes.*/

            if( work_seg_chave->tipo == CT_SEG_CAMPO_CONST )
             {
               work_doda   = CTREE_dodaend( work_seg_chave->pointer );
               buffer_doda = work_doda->fadr;

               VIDEO_movbloco( &work_target[posicao_target], buffer_doda,
                       work_seg_chave->tamanho );
             }
            else
             VIDEO_movbloco( &work_target[posicao_target], work_seg_chave->pointer,
                     work_seg_chave->tamanho );

            posicao_target+= work_seg_chave->tamanho;

           }
         else
           { /* Campo de VALOR.*/

            work_doda   = CTREE_dodaend( work_seg_chave->pointer );
            buffer_doda = work_doda->fadr;

            switch( modo_find )
             {
              case FIND_IGUAL      :
              case FIND_MAIOR      :
              case FIND_MAIOR_IGUAL:
              case FIND_MENOR      :
              case FIND_MENOR_IGUAL:
                   VIDEO_movbloco( &work_target[posicao_target], buffer_doda,
                           work_seg_chave->tamanho );
                   break;
              case FIND_PROXIMO    :
              case FIND_ANTERIOR   :
                   break;
              case FIND_PRIMEIRO   :
                   VIDEO_setmem( &work_target[posicao_target],
                           work_seg_chave->tamanho, 0);
                   break;
              case FIND_ULTIMO     :
                   VIDEO_setmem( &work_target[posicao_target],
                           work_seg_chave->tamanho, 255 );
                   break;
              default:     /* Tipo de Parametro Invalido.*/
                   return( I(-10) );
             }
            posicao_target += work_seg_chave->tamanho;
           }
         ++work_seg_chave;
       }
      target = work_target; /* Seta o ponteiro de acesso.*/
     }
    else
     {
       /* ============================================
          Parametro chave e'NULO -> Idica que a chave
          sera'montada apartir do buffer de dados.
          Protocolo IDE_CHAVES.
          ============================================ */
       target = VD_NILL(char);
     }

    if( (numero_arquivo=CTREE_keyfil( numero_indice )) < I(0) )
       return( I(-15) );

    if( (real_arquivo  =CTREE_tmpfil(numero_arquivo)) <0 )
       return( I(-16) );

    /* Salva a Atual posicao no arquivo.*/
	if( (err=DATABASE_ResetRecord(real_arquivo,DATABASE_SAVCURI))!=0)
      return( I(err) );

    /* =======================================
       Tenta Localizar/Conseguir o proximo
       registro, apartir da montada chave.
       ======================================= */
    switch( modo_find )
     {
      case FIND_IGUAL      :
           err = CTREE_readrec (numero_indice, target, modo_interno );
           break;

      case FIND_MAIOR      :
           /*err = CTREE_grtrec(numero_indice, target, modo_interno );*/
           /*break;*/

      case FIND_PRIMEIRO   :
           if( !flag_seg_const ) /* Nao ha constantes para delimitar o arquivo.*/
             {
              err = CTREE_frsrec( numero_indice, modo_interno );
              break;
             }
      case FIND_MAIOR_IGUAL:
           err = CTREE_gterec( numero_indice, target, modo_interno );
           break;

      case FIND_MENOR      :
           /*err = CTREE_letrec(numero_indice, target, modo_interno );*/
           /*break;*/

      case FIND_ULTIMO     :
           if( !flag_seg_const ) /* Nao ha constantes para delimitar o arquivo.*/
             {
              err = CTREE_lstrec( numero_indice, modo_interno );
              break;
             }
      case FIND_MENOR_IGUAL:
           err = CTREE_lterec(numero_indice, target, modo_interno );
           break;

      case FIND_PROXIMO    :
           err = CTREE_nxtrec(numero_indice, modo_interno );
           break;

      case FIND_ANTERIOR   :
           err = CTREE_prvrec(numero_indice, modo_interno );
           break;

      default:     /* Tipo de Parametro Invalido.*/
           old_isam_err = isam_err;

           if( (err=DATABASE_FreeCuri(real_arquivo))!=0)
              return( I(err) );

           isam_err = old_isam_err;
           return( I(-11) );

     }  /* Fim de Switch....*/

    /* Registro nao localizado.*/
	if ( err )
	   {
        old_isam_err = isam_err;
        if( (aux_erro = DATABASE_FreeCuri(real_arquivo))!=0)
           return( I(aux_erro) );
        isam_err = old_isam_err;
		return( I(err) );
	   }


    /* VERIFICA SE CRITERIO CONSTANTES OK!!!*/
    if( (numero_arquivo != numero_indice)            &&
         chave          != VD_NILL(VIDEO_SEG_CHAVE) )
     if( (err=CTREE_cmpchave(numero_indice, chave, modo_interno)) != 0)
      {
       if(DATABASE_ResetRecord(real_arquivo, DATABASE_RSTCURI))  /* Reseta para a posicao anterior.*/
         return( I(isam_err) );
       return( I(101) );    /* <- OBS: Retorna o c-tree erro de criterio busca.*/
      }


      /* Repassa os dados do Buffer Dados para o Buffer de Extra.*/
    if( modo_leitura == CT_LE_EXTRA_REPASSA )
      CTREE_cpybuf( numero_arquivo, TRUE);

    return( DATABASE_FreeCuri(real_arquivo) );
}

