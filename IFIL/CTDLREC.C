/* ======================================================
    CTREE_adrec()   - Deleta Registro em arquivo.
    PARAMETRO:  Numero Ctree do arquivo de dados.
    RETORNA:    Zero se protocolo de exclusao bem sucedido,
                caso contrario, um nao valor zero.
   ====================================================== */
#include <INCVIDEO.H>

INT2 CTREE_dlrec(numero_arquivo)
INT2 numero_arquivo;
{
 INT2   ret,real_arquivo;

 if( (real_arquivo=CTREE_tmpfil( numero_arquivo ))< 0)
  return(-1);

 /* Consegue um Lock, deleta registro, livra look*/
 if (_log_lock)
    if(DATABASE_LockISAM(DATABASE_ENABLE))
      return( I(isam_err) );

 if((ret=DATABASE_DeleteRecord(real_arquivo))!=0)
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
     strcpy (_log_oper,"EXCLUI");
     CTREE_adlog(numero_arquivo);
    }

 return( FALSE );
}


