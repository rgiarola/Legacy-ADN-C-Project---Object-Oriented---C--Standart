/* ============================================================================
    CTREE_advrec()   - Adiciona Registro em arquivo Variavel de Tamanho.
    PARAMETRO:  numero_arquivo: Numero Ctree do arquivo de dados.
                buffer:         Pointer para Buffer.
                buf_len:        Tamanho do Buffer.
    RETORNA:    Zero se protocolo de gravacao bem sucedido,
                caso contrario, um nao valor zero.
   ============================================================================ */
#include <INCVIDEO.H>


INT2 CTREE_advrec( arquivo, extra_buffer, tamanho_buffer_extra)
INT2       arquivo;
char      *extra_buffer;
VRLEN     tamanho_buffer_extra;
{
 IDE_ARQUIVOS *aux_arquivo;
 char         *sai_buffer,
              *aux_buffer;
 INT2          buf_tam_sai,
              ret,
              real_arquivo;

 if( (aux_arquivo=CTREE_ifilend(arquivo)) == VD_NILL(IDE_ARQUIVOS) )
   return(-1);

 buf_tam_sai=tamanho_buffer_extra+aux_arquivo->dreclen;

 /*printf("\nTAMANHO REGISTRO: %d",buf_tam_sai);*/

 ATIVA_BUF_DADOS;
 if( (aux_buffer=CTREE_filbuf(arquivo))==VD_NILL(char) )
   return(-2);

 if( VIDEO_ALLOC_MEM( sai_buffer, buf_tam_sai) == FALSE )
   {
    VIDEO_mostra_mens_erro_alloc(ALOCACAO_ADDVREC);
    return(-3);
   }

 VIDEO_movbloco( sai_buffer, aux_buffer, aux_arquivo->dreclen );

 if( extra_buffer && tamanho_buffer_extra )
  {
    VIDEO_movbloco( sai_buffer+aux_arquivo->dreclen,
           extra_buffer, tamanho_buffer_extra);
  }

 if( (real_arquivo=CTREE_tmpfil(arquivo))<0 )
   {
    VIDEO_FREE_ALLOC_MEM(sai_buffer);
    return(-4);
   }

 if(DATABASE_LockISAM(DATABASE_ENABLE))
   {
    VIDEO_FREE_ALLOC_MEM(sai_buffer);
    return( I(isam_err) );
   }

 if( (ret=DATABASE_AddVRecord(real_arquivo, sai_buffer, buf_tam_sai))!=0)
  {
   VIDEO_FREE_ALLOC_MEM(sai_buffer);
   DATABASE_LockISAM(DATABASE_FREE);
   return( ret);
  }

 VIDEO_FREE_ALLOC_MEM(sai_buffer);

 return(DATABASE_LockISAM(DATABASE_FREE));
}

