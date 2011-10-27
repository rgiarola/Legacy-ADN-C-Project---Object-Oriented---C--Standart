/* ============================================================================
   CTREE_open() - Protocolo de abertura de arquivos.
                  Esta funcao tenta abrir todos os arquivos de uma estrutura
                  apontadada por ATIVO_IFIL, se algum erro tenta criar os
                  arquivos, se erro de criacao (qq. erro interno do ctree),
                  executa REBUILD.
   OPEN()       - Nome abreviado.
   PARAMETRO    - Nenhum.
   RETORNA      - Zero se tudo OK, se nao, um valor negativo.

   CTREE_erroreb() : Mensagem de Erro Rebuild (Modo Multi Usuario).

   ============================================================================ */
#include <INCVIDEO.H>

INT2 CTREE_open(VOID)
{
 register INT2 control_datno;
 IDE_ARQUIVOS **auxifil;
 char         txterror[80];
 INT2          err,
              retorna_error;


 if( *ATIVO_IFIL == VD_NILL(IDE_ARQUIVOS) )
     return( I(-1) );    /* Sistema nao inicializado.*/

 auxifil = ATIVO_IFIL;

 /* Executa busca sobre todos arquivos ifil's.*/
 while( *auxifil )
  {
   /* Verifica se Arquivo Temporario.*/
   if ( !memcmp((*auxifil)->pfilnam, CT_TEMPOR, CT_TEMPOR_TAM) )
     {
/*    (*auxifil)->dfilno = control_datno;       // Inicializa o Identificador*/
/*    control_datno += ((*auxifil)->dnumidx+1); // Proximo Identificador.*/
      ++auxifil;
      continue;
     }

   control_datno = (*auxifil)->dfilno;
   (*auxifil)->dfilno = -1;

   if( (err=DATABASE_OpenIFile( *auxifil))!=0 ) /* Abre arquivo.*/
     {
      printf("\nERRO ABERTURA ARQUIVO No.%d-%s\nST %d",
              isam_fil, (*auxifil)->pfilnam, isam_err);
      printf("\nRotina Seguran‡a ...");

      retorna_error = TRUE;

      /* Arquivo nao pode ser aberto.*/
      if( err == FNOP_ERR )
       {   /* Tenta criar.*/

         printf("\nVerificando existˆncia ...");
		 if( (err=DATABASE_CreateIFile(*auxifil))!=0 )
           {
            printf("\nJ  existente ...  %d ST %d",
                   isam_fil,isam_err);
           }
          else
           {
			 CloseIFile( *auxifil );

             /* Reabre Arquivo.*/
             if( (err=OpenIFile( *auxifil))!=0 )
               {
                printf("\nCriando Arquivo %d ST %d",
                        isam_fil,isam_err);
                (*auxifil)->dfilno = control_datno;
                return( I(-1) );
               }
             else
               {
                retorna_error = FALSE;
                printf("\nArquivo Criado...");
               }
           }   /* Fim de Logica OPEN/CLOSE.*/
       }   /* Fim de Logica de Criacao de Arquivos.*/


      /* Se criacao falha && open falha tenta rebuild, se erro Ctree.*/
      if( err == KOPN_ERR || err == DOPN_ERR ||
          err == FCRP_ERR || err == FCMP_ERR || err == INIX_ERR )
        {
#ifndef CTREE_MULTI_USER
         printf("\n\nAgora em Rebuild...\n");

		 DATABASE_CloseIFile( *auxifil );

		 if( (err = DATABASE_RebuildIFile( *auxifil )) !=0 )
           {
            printf("\nFalha Rebuild... St %d %d", isam_fil,isam_err );
            (*auxifil)->dfilno = control_datno;
            return( I(-1) );
           }
         else
		   if( (err=DATABASE_OpenIFile( *auxifil))!=0 )
             {
              printf("Falha Rebuild RE-OPEN...  St %d %d",
                      isam_fil,isam_err);
              (*auxifil)->dfilno = control_datno;
              return( I(-1) );
             }   /* Fim de Logica OPEN/CLOSE.*/
           else
             retorna_error = FALSE;
#else
         CTREE_erroreb_rede(control_datno);
         return(-1);
#endif
        }   /* Fim de Logica REBUILD.*/

      if ( retorna_error )   /* Logica de Abertura Falha.*/
         {
          (*auxifil)->dfilno = control_datno;
          return( I(-2) );
         }

     }   /* Fim de Abertura com erro.*/

/*  (*auxifil)->dfilno = control_datno;       // Inicializa o Identificador.*/
/*  control_datno += ((*auxifil)->dnumidx+1); // Proximo Identificador.*/

    (*auxifil)->dfilno = control_datno;
    ++auxifil;                                /* Proxima Estrutura.*/

  }   /* Fim de Loop para Inicializacao de Arquivos.*/


 return ( FALSE ); /* OK...*/
}

INT2 CTREE_erroreb_rede(arquivo)
INT2 arquivo;
{
 printf("\n** Arquivo No.%d danificado ST[%d] **",arquivo,isam_err);
 printf("\nExecute VT-SALVA,como segue:");
 printf("\n\nVT-SALVA -?");
 printf("\n\nou LIGUE P/A NOVA VISŽO\n");

 return(FALSE);
}
