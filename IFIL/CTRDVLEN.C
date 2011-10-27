/* ============================================================================
    CTREE_rdvlen()   - Le Parte Variavel de Tamanho do Arquivo.
    PARAMETRO:  numero_arquivo: Numero Ctree do arquivo de dados.
                buffer:         Pointer para Buffer.
                buf_len:        Tamanho do Buffer.
    RETORNA:    Zero se protocolo de leitura bem sucedido,
                caso contrario, um nao valor zero.
   ============================================================================ */
#include <INCVIDEO.H>

CTREE_rdvlen( arquivo, extra_buffer, tamanho_buffer_extra )
INT2       arquivo;
char      *extra_buffer;
VRLEN     tamanho_buffer_extra;
{
 IDE_ARQUIVOS *aux_arquivo;
 char         *ent_buffer;
 INT2           buf_tam_ent,
               ret,
               real_arquivo;

 if( extra_buffer && tamanho_buffer_extra<=0)
   return(-1);

 if( (aux_arquivo=CTREE_ifilend(arquivo)) == VD_NILL(IDE_ARQUIVOS) )
   return(-2);

 buf_tam_ent = tamanho_buffer_extra+aux_arquivo->dreclen;

 if( VIDEO_ALLOC_MEM( ent_buffer, buf_tam_ent) == VD_NULO)
   {
    VIDEO_mostra_mens_erro_alloc(ALOCACAO_READVLEN);
    return(-4);
   }


 if( (real_arquivo=CTREE_tmpfil(arquivo))<0)
   {
    VIDEO_FREE_ALLOC_MEM(ent_buffer);
    return(-5);
   }

 /* Consegue a estrutura TOTAL do Arquivo.*/
 if( (ret=DATABASE_ReReadVRecord(real_arquivo, ent_buffer, buf_tam_ent))!=0)
    {
     VIDEO_FREE_ALLOC_MEM(ent_buffer);
     return(ret);
    }

 /* Separa Parte Variavel de Tamnho ===========================================*/
 VIDEO_movbloco( extra_buffer, ent_buffer+aux_arquivo->dreclen,
         tamanho_buffer_extra );

 VIDEO_FREE_ALLOC_MEM(ent_buffer);

 return(FALSE);
}

