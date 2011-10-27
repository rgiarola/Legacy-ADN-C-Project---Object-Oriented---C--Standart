/* ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
   ³   EXCLUI ARQUIVOS TEMPORARIOS.                                           ³
   ³   Esta executa o protocolo de delecao de arquivos temporarios.           ³
   ³   O protocolo, indica que o arquivo devera ser fechado e posteriormente  ³
   ³   excluido.                                                              ³
   ³                                                                          ³
   ³   PARAMETROS:                                                            ³
   ³   Numero_arquivo -> numero do arquivo temporario que devera ser excluido ³
   ³           *  Com o parametro negativo, indica a exclusao de todos os     ³
   ³              arquivos.                                                   ³
   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ */
#include <INCVIDEO.H>

INT2 CTREE_deltmp( numero_arquivo )
INT2 numero_arquivo;
{
 register INT2  posicao=0;
 CT_TMP_NOMES *aux_tempor;      /* Controle Arquivos Temporarios.*/
 IDE_ARQUIVOS *ptrifil;
 INT2          loop_all=FALSE,cont;

 aux_tempor = CT_arquivos_temporarios;
 if (numero_arquivo<0)
    loop_all=TRUE;

do
  {
   while (posicao < VD_MAX_TMP)
     {
      if ((aux_tempor->numero_arquivo == numero_arquivo) ||
          (loop_all && aux_tempor->temp_nome[0])          )
         break;

      ++aux_tempor;
      ++posicao;
     }

   if (posicao >= VD_MAX_TMP )
      {
       return(-1);
      }

   if (loop_all)
      numero_arquivo = aux_tempor->numero_arquivo;

   if ((ptrifil=CTREE_ifilend(numero_arquivo))==VD_NULO )
       return( -2 );

   if (DATABASE_CloseIFile(ptrifil) )
      {
       char buffer[200];
       sprintf(buffer,CTREE_MENS_mens_padrao_err,
                      CTREE_mens_deltmp,
                      (VIDEO_bufparamarq->bufdodas+numero_arquivo)->reduzido,
                      TRUE,isam_err);
       VIDEO_mostra_mens_erro(buffer,VIDEO_ERRO_close_arq_tmp);
       return(-3);
      }

   DATABASE_unlink( aux_tempor->temp_nome );
   aux_tempor->numero_arquivo = -1;
   aux_tempor->temp_nome[0]   = VD_NULO;

   if ( ptrifil->dnumidx>0 ) /* Apaga o Indice*/
      {
       ++aux_tempor;
       DATABASE_unlink( aux_tempor->temp_nome);
       aux_tempor->numero_arquivo = -1;
       aux_tempor->temp_nome[0]   = VD_NULO;
      }

   ++aux_tempor;

  } while (loop_all);

 return(FALSE);
}

