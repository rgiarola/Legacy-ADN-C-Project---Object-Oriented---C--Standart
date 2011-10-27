/* ======================================================
    CTREE_adrec()   - Adiciona Registro em arquivo.
    PARAMETRO:  Numero Ctree do arquivo de dados.
    RETORNA:    Zero se protocolo de gravacao bem sucedido,
                caso contrario, um nao valor zero.
   ====================================================== */
#include <INCVIDEO.H>

INT2 CTREE_adrec(numero_arquivo)
INT2 numero_arquivo;
{
 INT2   ret, real_arquivo;
 char *buffer;

 ATIVA_BUF_DADOS;
 if( (buffer = CTREE_filbuf(numero_arquivo)) == VD_NILL(char) )
   return( I(-1) );

 /* Consegue um Lock, grava registro, livra look*/

 if( (real_arquivo=CTREE_tmpfil(numero_arquivo))<0 )
   return(I(-2));

 if (_log_lock)
    if(DATABASE_LockISAM(DATABASE_ENABLE))
      return( I(isam_err) );

 if( (ret=DATABASE_AddRecord(real_arquivo,buffer))!=0)
   {
    if (_log_lock)
       DATABASE_LockISAM(DATABASE_FREE);
    return( ret);
   }

 if (_log_lock)
    if ((ret=DATABASE_LockISAM(DATABASE_FREE))!=FALSE)
       return (ret);

 if (!_log_disable)
    {
     strcpy (_log_oper,"INCLUI");
     CTREE_adlog(numero_arquivo);
    }


 return(FALSE);
}

