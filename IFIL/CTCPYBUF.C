/* ============================================================================
    CTREE_cpybuf()  - Executa alternacao de buffer's de um arquivo especificado.
    CTCPYBUF()      - Nome abreviado.
    PARAMETROS      - numero do arquivo
                      modo de operacao: >0    - Extra para Dados
                                        TRUE  - Extra para Dados (Recria Isam)
                                        FALSE - Dados para Extra
                      OBS: O modo de operacao e'usado para especificar em que
                           buffer estarao os dados. Em sistemas multi-usuarios,
                           no minimo tres buffer's, em mono-usuario, no minimo
                           dois buffer's.
    RETORNA         - Zero se operacao OK, outro caso, um valor diferente.
   ============================================================================ */
#include <INCVIDEO.H>

INT2   CTREE_cpybuf( numero_arquivo, modo_operacao)
INT2   numero_arquivo,
       modo_operacao;
{
 IDE_ARQUIVOS *work_ifil;
 INT2           err;
 char         *buffer_isam,
              *buffer_aux_01,
              *buffer_aux_02,
              *buffer_origem,
              *buffer_destino;

 ATIVA_BUF_DADOS;
 if( (buffer_aux_01=CTREE_filbuf(numero_arquivo))==VD_NILL(char) )
     return( I(-2) );

 ATIVA_BUF_EXTRA;
 if( (buffer_aux_02=CTREE_filbuf(numero_arquivo))==VD_NILL(char) )
     return( I(-3) );

 
 if( modo_operacao)
   {        /* BUFFER Origem esta no buffer de extra.*/
    buffer_origem  = buffer_aux_02;
    buffer_destino = buffer_aux_01;
   }
 else
   {        
            /* BUFFER Origem esta no buffer de dados.*/
    buffer_origem  = buffer_aux_01;
    buffer_destino = buffer_aux_02;
   }


 /* Obtem estrutura de controle IDE_ARQUIVOS.*/
 if( (work_ifil = CTREE_ifilend(numero_arquivo)) == VD_NILL(IDE_ARQUIVOS) )
     return( I(-4) );

 VIDEO_movbloco( buffer_destino, buffer_origem, work_ifil->dreclen );

#ifdef CTREE_MULTI_USER     /* Protocolo Multi-Usuario para Gravacao.*/
 // Aten‡„o -> N„o mude op‡„o MODO==TRUE, algumas fun‡„o passam valores
 //            diferentes para n„o executar esta c¢pia ...
 if (modo_operacao == TRUE )
    {
     ATIVA_BUF_ISAM;
     if ((buffer_isam=CTREE_filbuf(numero_arquivo))==VD_NILL(char) )
        return( I(-5) );
     VIDEO_movbloco( buffer_isam, buffer_origem, work_ifil->dreclen );
    }
#endif
 return( I(0) );

}

