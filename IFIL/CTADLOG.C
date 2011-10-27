/*
   ADLOG
   Rotinas de Suporte a Log de Opera‡”es
   > Utilizado pelos fun‡”es: CTADREC,
                              CTREWREC,
                              CTDLREC
     Acrescenta Informa‡”es automaticamente ao arquivo LOG.DAT
     Vari veis externas devem ser inicializadas, para que a fun‡„o LOG
     tenha efeito.
     _log_tipo  -> Tipo de Log
     _log_obs1  -> Observa‡„o 1
     _log_obs2  -> Observa‡„o 2
     _log_origem-> Origem do Disparo
     _log_lock  -> Lock Disable (Grava‡„o)

     _log_disable-> TRUE - Log Desativado

 */
#include <INCVIDEO.H>
BYTE  _log_disable=FALSE,
      _log_tipo,            // Tipo de Log (Separa‡„o da Armazenagem)
      _log_lock=TRUE;       // LOCK Disable
char  _log_obs1[41],        // Valor Alterado DE:
      _log_obs2[41],        // Valor Alterado PARA:
      _log_user[21],        // Respons vel pela Altera‡„o
      _log_oper[21],        // Opera‡„o (INCLUSAO,ALTERA€ŽO,EXCLUSŽO,OUTROS);
      _log_origem[11];      // Fun‡„o de Origem

INT2  (*_log_funcao)(int Arquivo);

