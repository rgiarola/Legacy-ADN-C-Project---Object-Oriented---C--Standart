/* ============================================================================
    CTREE_dlvlen()   - Exclui Bloco Variavel de Tamanho do Arquivo.
    PARAMETRO:  numero_arquivo: Numero Ctree do arquivo de dados.
                buffer:         Pointer para Buffer.
                buf_len:        Tamanho do Buffer.
    RETORNA:    Zero se protocolo de exclusao bem sucedido,
                caso contrario, um nao valor zero.
   ============================================================================ */
#include <INCVIDEO.H>

INT2 CTREE_dlvrec( arquivo, extra_buffer, tamanho_buffer_extra )
INT2       arquivo;
char      *extra_buffer;
VRLEN     tamanho_buffer_extra;
{
 INT2           ret,
               real_arquivo;

 if ((real_arquivo=CTREE_tmpfil(arquivo)) <0 )
    return(-5);

 if ((ret=DeleteVRecord( real_arquivo ))!=0)
    return(ret);

 return(FALSE);
}

